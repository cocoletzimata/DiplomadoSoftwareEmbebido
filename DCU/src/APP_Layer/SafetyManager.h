/*
 * SafetyManager.h
 *
 *  Created on: 14/03/2021
 *      Author: Marco
 */

#ifndef APP_LAYER_SAFETYMANAGER_H_
#define APP_LAYER_SAFETYMANAGER_H_

#define ANTIPINCH_THRESHOLD 820

typedef enum{
	OPEN_WINDOW_ACTUATION,
	CLOSE_WINDOW_ACTUATION,
	GLOBAL_OPEN_WINDOW_ACTUATION,
	GLOBAL_CLOSE_WINDOW_ACTUTATION,
	CANCEL_WINDOW_ACTUATION

}WindowActuationState_Type;



/*This function belongs to iSafety interface and gives us the window Actuation state */
extern void activity_SafetyDecisions(void);

/*This function makes the decisions of theSafyManager component*/
extern void WriteWindowActuationState(WindowActuationState_Type * WindowAtuationState);

#endif /* APP_LAYER_SAFETYMANAGER_H_ */
