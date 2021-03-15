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
#include "ConfigurationInfo.h"


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
	LED_RGB(RED,OFF);
	LED_RGB(GREEN,OFF);
	LED_RGB(BLUE,OFF);

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



		if( *DoorConfiguration == Rear_Right_Door)
		{
			      LED_RGB(RED,OFF);
				  LED_RGB(GREEN,ON);
				  LED_RGB(BLUE,OFF);
		}
		else
		{
			      LED_RGB(RED,OFF);
			      LED_RGB(GREEN,OFF);
			      LED_RGB(BLUE,OFF);
		}

		//ConfigurationInfo_Init ();

	}
}

static void Task_100ms( void *pvParameters )
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
		vTaskDelayUntil( &xNextWakeTime, Task_100ms_Period );







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


