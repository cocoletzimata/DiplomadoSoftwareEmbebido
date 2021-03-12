/*
 * Proyect_Tasks.c
 *
 *  Created on: 10/03/2021
 *      Author: Marco
 */
/* SDK includes. */


#include <HW_Layer/CANDriver.h>
#include <HW_Layer/SensorManager.h>
#include "sdk_project_config.h"
#include "status.h"
#include "can_pal.h"


/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

/*Local includes.*/
#include "Project_Tasks.h"
#include "Personal_EVB_Drv.h"

/* SDK includes. */
#include "BoardDefines.h"



/*system tasks*/
static void Task_20ms( void *pvParameters ); //Private function, Only the xTaskCreate call it
static void Task_200ms( void *pvParameters ); //Private function, Only the xTaskCreate call it
static void Task_100ms( void *pvParameters ); //Private function, Only the xTaskCreate call it

/*FRTOs variable*/
volatile int exit_code = 0;


/*Global variables*/
int adc_threshold_exceeded;
int TogglePins = 1;
bool toggleLED;

void Tasks_INIT(void){

	/*Init Task 20ms*/
	xTaskCreate( Task_20ms, "Task_20ms", Task_20ms_Stack_Size, NULL, Task_20ms_priority, NULL );
	/*Init Task 100ms*/
	xTaskCreate( Task_100ms, "Task_100ms", Task_100ms_Stack_Size, NULL, Task_100ms_priority, NULL );
	/*Init Task 200ms*/
	xTaskCreate( Task_200ms, "Task_200ms", Task_200ms_Stack_Size, NULL, Task_200ms_priority, NULL );
}




static void Task_20ms( void *pvParameters )
{


	TickType_t xNextWakeTime; //tick modeling

	/* Casting pvParameters to void because it is unused */
	(void)pvParameters;

	/* Initialise xNextWakeTime - this only needs to be done once. */
	/* The xLastWakeTime variable needs to be initialized with the current tickcount.
	 * Note that this is the only time the variable is explicitly written to. After this
	 * xLastWakeTime is managed automatically by the vTaskDelayUntil()API function. */
	xNextWakeTime = xTaskGetTickCount();

	  /*LEDs initialization*/
	  LED(RED,OFF);
	  LED(GREEN,OFF);
	  LED(BLUE,OFF);

	for( ;; )
	{

		/* Place this task in the blocked state until it is time to run again.
		The block time is specified in ticks, the constant used converts ticks
		to ms.  While in the Blocked state this task will not consume any CPU
		time. */
		vTaskDelayUntil( &xNextWakeTime, Task_20ms_Period );

        /*ADC update*/

	   if (adcConvDone == true)
		{
			/* Clear conversion done interrupt flag */
			adcConvDone = false;
			/* Trigger PDB timer */
			PDB_DRV_SoftTriggerCmd(PDB_INSTANCE);
		}

		/*flag update*/

		if(adcRawValue >= 500)
		{
			adc_threshold_exceeded = true;
		}
		else
		{
			adc_threshold_exceeded = false;
		}



	}
}

static void Task_100ms( void *pvParameters )
{

	status_t local_satus;

	uint8_t test_tx_data[8];

	volatile uint8_t debug_Error_Status;

	bool button1State;
	bool button2State;


	TickType_t xNextWakeTime; //tick modeling

	/* Casting pvParameters to void because it is unused */
	(void)pvParameters;

	/* Initialise xNextWakeTime - this only needs to be done once. */
	/* The xLastWakeTime variable needs to be initialized with the current tickcount.
	 * Note that this is the only time the variable is explicitly written to. After this
	 * xLastWakeTime is managed automatically by the vTaskDelayUntil()API function. */
	xNextWakeTime = xTaskGetTickCount();


	for( ;; )
	{


		/* Place this task in the blocked state until it is time to run again.
		The block time is specified in ticks, the constant used converts ticks
		to ms.  While in the Blocked state this task will not consume any CPU
		time. */
		vTaskDelayUntil( &xNextWakeTime, Task_100ms_Period );


        button1State = Read_Pin(PTC,SW2);
        button2State = Read_Pin(PTC,SW3);


        if(button1State)
        {
        	test_tx_data[0] |= BIT0;
        }
        else
        {
        	test_tx_data[0] &= ~BIT0;
        }

        if(button2State)
		{
			test_tx_data[1] |= BIT0 ;
		}
		else
		{
			test_tx_data[1] &= ~BIT0 ;
		}

		test_tx_data[2]= 0x00;
		test_tx_data[3]= 0x00;
		test_tx_data[4]= 0x00;
		test_tx_data[5]= 0x00;
		test_tx_data[6]= 0x00;
		test_tx_data[7]= 0x00;

		/*Send test CAN Message*/
		local_satus = send_CAN_message(0x10, 8, &test_tx_data[0]);

		if(local_satus != STATUS_SUCCESS){

			debug_Error_Status++;
		}


		toggleLED = (rx_message.data[0] & (1 << 0));

		/*LED blink*/
		if(adc_threshold_exceeded)
		{
			//
			if(rx_message.id == 0x20 && toggleLED == 1 )
			{
				/*LED Toggle */
				TogglePins = !TogglePins;
				if(TogglePins)
				{
					LED(RED,ON);
				}
				else
				{
					LED(RED,OFF);
				}
			}
			else if (rx_message.id == 0x20 && toggleLED == 0)
			{
				LED(RED,ON);
			}
			else{}
		}
		else
		{
			LED(RED,OFF);
		}




	}
}

static void Task_200ms( void *pvParameters )
{


	TickType_t xNextWakeTime; //tick modeling

	/* Casting pvParameters to void because it is unused */
	(void)pvParameters;

	/* Initialise xNextWakeTime - this only needs to be done once. */
	/* The xLastWakeTime variable needs to be initialized with the current tickcount.
	 * Note that this is the only time the variable is explicitly written to. After this
	 * xLastWakeTime is managed automatically by the vTaskDelayUntil()API function. */
	xNextWakeTime = xTaskGetTickCount();


	for( ;; )
	{


		/* Place this task in the blocked state until it is time to run again.
		The block time is specified in ticks, the constant used converts ticks
		to ms.  While in the Blocked state this task will not consume any CPU
		time. */
		vTaskDelayUntil( &xNextWakeTime, Task_200ms_Period );



	}
}


