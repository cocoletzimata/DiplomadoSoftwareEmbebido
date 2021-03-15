/*
 * Personal_EVB_Drv.h
 *
 *  Created on: 10/03/2021
 *      Author: Marco
 */

#ifndef PERSONAL_EVB_DRV_H_
#define PERSONAL_EVB_DRV_H_

#include "sdk_project_config.h"

/*LEDs Definitions*/
#define RED 15
#define GREEN 16
#define BLUE 0

#define ON 1
#define OFF 0

#define SW2 12
#define SW3 13

extern void LED_RGB(uint8_t Color, bool State_LED);
extern bool Read_Pin(const GPIO_Type * const GPIO, uint8_t PIN);
extern void LED_State(bool State_LED, const GPIO_Type * const GPIO, uint8_t PIN);

#endif /* PERSONAL_EVB_DRV_H_ */
