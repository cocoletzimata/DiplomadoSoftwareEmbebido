/*
 * CAN_Drv.c
 *
 *  Created on: 09/03/2021
 *      Author: Marco
 */

/*-----------------------------------------------------------*/

#include <HW_Layer/CANDriver.h>
#include "FreeRTOS.h"
#include "task.h"
/* "interrupt_manager.h" is required for importing symbols
 * related to interrupt configurations. */
#include "interrupt_manager.h"
#include "sdk_project_config.h"
/* Need to add to the Include Path (-I):
 * ../SDK/platform/drivers/src/flexcan
 * for the compiler to find "flexcan_hw_access.h" and
 * "flexcan_irq.h" */
#include "flexcan_irq.h"
#include "flexcan_hw_access.h"
#include "BoardDefines.h"

/* ---------------------------- */
/*  Macros and private defines  */
/* ---------------------------- */

#define FLEXCAN_INSTANCE 	can_instance0.instIdx

/* ------------------ */
/*  Imported symbols  */
/* ------------------ */
/* Symbol required for FLEXCAN_SetMsgBuffIntCmd API */
CAN_Type * const flexcanBase[] = CAN_BASE_PTRS;

/* ------------------------------- */
/* Prototypes of private functions */
/* ------------------------------- */
static void isr_CAN_MB(void);
static void CAN_pal_event_callback(uint32_t instance, can_event_t eventType,
							uint32_t objIdx,
							void *driverState);

/* ------------------------------- */
/* Global private data definitions */
/* ------------------------------- */
/* Global variable to hold the received message data from CAN PAL */
can_message_t rx_message;
/* Global variable to hold the last generated event from CAN PAL */
can_event_t can_event_type;
/* Default information for TX messages */
flexcan_data_info_t default_tx_info = {
	.msg_id_type = FLEXCAN_MSG_ID_STD, 	/* Send standard ID messages by default */
	.data_length = 8, 					/* By default assume 8 data bytes.
										 * Needs to change per each transmission. */
#if FEATURE_CAN_HAS_FD
	.fd_enable = false,					/* Assume no FD frame by default */
	.fd_padding = 0,						/* Assume padding of 0x00 by default */
	.enable_brs = false,            /* Disable bit rate switch in CAN FD frame by default */
#endif
	.is_remote = false              /* Assume data frame by default (not remote frame) */
};


/* -------------------- */
/* Function Definitions */
/* -------------------- */


/* ============================================================================
 * Function Name:
 * Description:
 * Arguments:
 * Return:
 * ========================================================================= */
void app_init_CAN(void)
{
	volatile status_t local_status; /* Holds return status of APIs */
	can_buff_config_t can_pal_buff_config = { /* Generic buffer config */
			.enableFD = false,
			.enableBRS = false,
			.fdPadding = 0x00,
			.idType = CAN_MSG_ID_STD,
			.isRemote = false
		};

	/* Initialize CAN Pal  */
	local_status = CAN_Init(&can_instance0, &can_config0);

	/* Initialize CAN Pal Rx Buffer */
	/* Using a dummy ID in the acceptance filter. Later on the filter
	 * will be changed to accept all messages.
	 * Using message buffer (MB) 0 for reception. */
	local_status = CAN_ConfigRxBuff(&can_instance0, CAN_PAL_RX_BUFFER, &can_pal_buff_config, 0x10);

	/* Set Global Acceptance filter (will override individual MB filters) */
	/* Filter will accept any incoming message */
	FLEXCAN_DRV_SetRxMaskType(FLEXCAN_INSTANCE, FLEXCAN_RX_MASK_GLOBAL);
	/* Set acceptance filter for Standard IDs */
	FLEXCAN_DRV_SetRxMbGlobalMask(FLEXCAN_INSTANCE,FLEXCAN_MSG_ID_STD,0);

	/* Initialize CAN Pal Tx Buffer */
	/* Will use message buffer (MB) 1 for Transmission */
	local_status = CAN_ConfigTxBuff(&can_instance0,CAN_PAL_TX_BUFFER, &can_pal_buff_config);

	/* Associate CAN event callback */
	/* This callback will be called within ISR context */
	local_status = CAN_InstallEventCallback(&can_instance0,&CAN_pal_event_callback,NULL);

	/* Install CAN0 MB interrupt handler */
	/* Same interrupt is shared for events on message buffers 0 to 15 */
	/* Using own ISR function */
	INT_SYS_InstallHandler(CAN0_ORed_0_15_MB_IRQn, isr_CAN_MB, NULL);
	/* Enable CAN0 MB interrupt handler */
	INT_SYS_EnableIRQ(CAN0_ORed_0_15_MB_IRQn);

	/* To allow calls safe APIs from FreeRTOS, setting inteerrupt priority to
	be equal to or lower than configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY. */
	INT_SYS_SetPriority(CAN0_ORed_0_15_MB_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY );

	/* Enable RX/TX interrupts */
	local_status = FLEXCAN_SetMsgBuffIntCmd(flexcanBase[FLEXCAN_INSTANCE],CAN_PAL_RX_BUFFER,true);
	local_status = FLEXCAN_SetMsgBuffIntCmd(flexcanBase[FLEXCAN_INSTANCE],CAN_PAL_TX_BUFFER,true);

	/* Set-up reception of MB 0 (reception message buffer) */
	/* Received data will be put into the global variable rx_message */
	local_status = CAN_Receive(&can_instance0, CAN_PAL_RX_BUFFER, &rx_message);

	(void)local_status; /* Remove warning of unused variable */
}

/* ============================================================================
 * Function Name:
 * Description:
 * Arguments:
 * Return:
 * ========================================================================= */
static void CAN_pal_event_callback(uint32_t instance, can_event_t eventType,
							uint32_t objIdx,
							void *driverState)
{
	volatile uint32_t test = 0; /* Dummy variable for debugging */

	/* Set the received event to a global variable */
	can_event_type = eventType;
	if(eventType == CAN_EVENT_RX_COMPLETE)
	{
		/* Successful reception has been completed */
		/* Data shall be available at variable rx_message */
		test++;
	}
	else if(eventType == CAN_EVENT_TX_COMPLETE)
	{
		/* Successful transmission */
		test++;
	}
	else
	{
		/* Nothing to do */
	}
}

/* ============================================================================
 * Function Name:
 * Description:
 * Arguments:
 * Return:
 * ========================================================================= */
static void isr_CAN_MB(void)
{
	/* CAll generated ISR from CAN driver */
	CAN0_ORed_0_15_MB_IRQHandler();

	/* IRQ disables RX interrupt, re-enable it to have continuous reception. */
	if(can_event_type == CAN_EVENT_RX_COMPLETE){
		CAN_Receive(&can_instance0, CAN_PAL_RX_BUFFER, &rx_message);
	}
}


/* ============================================================================
 * Function Name:
 * Description:
 * Arguments:
 * Return:
 * ========================================================================= */
status_t send_CAN_message(uint32_t msg_id, uint8_t length, uint8_t * data)
{
	default_tx_info.data_length = length;
	volatile status_t local_status;

	/* Request msg transmission to CAN driver */
	/* Will use the defined message buffer (1 for TX) */
	local_status = FLEXCAN_DRV_Send(FLEXCAN_INSTANCE,
										CAN_PAL_TX_BUFFER,
										&default_tx_info,
										msg_id,
										data);
	return local_status;
}
