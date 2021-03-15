/*
 * ConfigurationInfo.h
 *
 *  Created on: 14/03/2021
 *      Author: Marco
 */

#ifndef APP_LAYER_CONFIGURATIONINFO_H_
#define APP_LAYER_CONFIGURATIONINFO_H_

typedef enum{
	Driver_Door,
	Passenger_Door,
	Rear_Left_Door,
	Rear_Right_Door

}ConfigurationType;



extern void GetConfigurationType (ConfigurationType *DoorType);
extern void ConfigurationInfo_Init (void);

#endif /* APP_LAYER_CONFIGURATIONINFO_H_ */
