/*
 * CAN_Drv.h
 *
 *  Created on: 09/03/2021
 *      Author: Marco
 */

#ifndef CAN_DRV_H_
#define CAN_DRV_H_

#include "sdk_project_config.h"

#define CAN_PAL_RX_BUFFER	0
#define CAN_PAL_TX_BUFFER	1

#define CAN_TX_MSG_DEFAULT_LEN 		8u
#define CAN_TX_MSG_DEFAULT_PAD 		0xffu

extern void app_init_CAN(void);
extern status_t send_CAN_message(uint32_t msg_id, uint8_t length, uint8_t * data);
extern can_message_t rx_message;

#endif /* CAN_DRV_H_ */
