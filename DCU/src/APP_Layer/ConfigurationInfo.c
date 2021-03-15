/*
 * ConfigurationInfo.c
 *
 *  Created on: 14/03/2021
 *      Author: Marco
 */
#include "ConfigurationInfo.h"
#include "Personal_EVB_Drv.h"




void GetConfigurationType (ConfigurationType *DoorType);
void ConfigurationInfo_Init (void);


static ConfigurationType *DoorConfiguration;

void GetConfigurationType (ConfigurationType *DoorType)
{

	*DoorType = *DoorConfiguration;


}


void ConfigurationInfo_Init (void)
{
	 //ConfigurationType *DoorConfiguration;

	 bool MSB_SW_VARIANT = Read_Pin(PTC, 9);//Read_Pin(PTC, 13);//
	 bool LSB_SW_VARIANT = Read_Pin(PTC, 11);//Read_Pin(PTC, 12);//

     volatile uint8_t PINS = (MSB_SW_VARIANT<< 1)|LSB_SW_VARIANT; // Bit masking to combine the two inputs

     if(PINS == 0)
     {

    	 *DoorConfiguration = Driver_Door;

     }else if(PINS == 1)
     {

    	 *DoorConfiguration = Passenger_Door;

     }else if(PINS == 2)
     {

    	 *DoorConfiguration = Rear_Left_Door;

     }else
     {

    	 *DoorConfiguration = Rear_Right_Door;

     }


}
