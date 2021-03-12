/*
 * Personal_EVB_Drv.c
 *
 *  Created on: 10/03/2021
 *      Author: Marco
 */

#include "Personal_EVB_Drv.h"



void LED(uint8_t Color, bool State_LED){

	 if(State_LED){

		 PINS_DRV_ClearPins(PTD, 1 << Color);
	 }else{
		 PINS_DRV_SetPins(PTD, 1 << Color);
	 }

}


bool Read_Pin(const GPIO_Type * const GPIO, uint8_t PIN){

     bool retval;

	if((PINS_DRV_ReadPins(GPIO) & (1 <<PIN))>=1){

		retval = 1;

	}else{

		retval = 0;
	}

    return retval;
}
