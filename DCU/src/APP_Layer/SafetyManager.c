/*
 * SafetyManager.c
 *
 *  Created on: 14/03/2021
 *      Author: Marco
 */

#include "SensorManager.h"
#include "SafetyManager.h"
#include "WindowControlApp.h"

static WindowActuationState_Type *_WindowAtuationState;

void activity_SafetyDecisions(void);
void WriteWindowActuationState(WindowActuationState_Type * WindowAtuationState);

/*This function belongs to iSafety interface and gives us the window Actuation state */

void WriteWindowActuationState(WindowActuationState_Type * WindowAtuationState)
{
	_WindowAtuationState = WindowAtuationState;
}

/*This function makes the decisions of theSafyManager component*/

void activity_SafetyDecisions(void)
{
	if (*_WindowAtuationState == CLOSE_WINDOW_ACTUATION || *_WindowAtuationState == GLOBAL_CLOSE_WINDOW_ACTUTATION )
		{
			if(GetAdcCounts()> ANTIPINCH_THRESHOLD)
			{
				WriteCancelWindowOp(CANCEL_WINDOW_ACTUATION);
			}
			else
			{
			 //Do nothing
			}
		}
		else
		{
			//Do nothing
		}
}

