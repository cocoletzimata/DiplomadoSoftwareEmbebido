/*
 * ADC_Task.c
 *
 *  Created on: 04/03/2021
 *      Author: Marco
 */
/* SDK includes. */

#include "sdk_project_config.h"

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

/*Local includes.*/
#include "ADC_Task.h"

/* SDK includes. */
#include "BoardDefines.h"

/*ADC includes.*/
#include "helper_functions.h"
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "interrupt_manager.h"
#include "sdk_project_config.h"


/*LEDs Handler*/
void LED(uint8_t Color, bool State_LED);

/*ADC functions*/
static void ADC_IRQHandler(void);
static void ADC_INIT(void);

/*system tasks*/
static void ADC_Task_20ms( void *pvParameters ); //Private function, Only the xTaskCreate call it
static void ADC_Task_200ms( void *pvParameters ); //Private function, Only the xTaskCreate call it

/*FRTOs variable*/
volatile int exit_code = 0;


/* Flag used to store if an ADC IRQ was executed */
volatile bool adcConvDone;
/* Variable to store value from ADC conversion */
volatile uint16_t adcRawValue;

/* @brief: ADC Interrupt Service Routine.
 *        Read the conversion result, store it
 *        into a variable and set a specified flag.
 */

/*-----------------------------------------------------------*/

int adc_threshold_exceeded;
int TogglePins = 1;


void ADC_Tasks_INIT(void){

	/*Init Task 20ms*/
	xTaskCreate( ADC_Task_20ms, "Task_20ms", ADC_Task_20ms_Stack_Size, NULL, ADC_Task_20ms_priority, NULL );
	/*Init Task 200ms*/
	xTaskCreate( ADC_Task_200ms, "Task_200ms", ADC_Task_200ms_Stack_Size, NULL, ADC_Task_200ms_priority, NULL );
}


void LED(uint8_t Color, bool State_LED){

	 if(State_LED){

		 PINS_DRV_ClearPins(PTD, 1 << Color);
	 }else{
		 PINS_DRV_SetPins(PTD, 1 << Color);
	 }

}


void ADC_IRQHandler(void)
{
    /* Get channel result from ADC channel */
    ADC_DRV_GetChanResult(ADC_INSTANCE, 0U, (uint16_t *)&adcRawValue);
    /* Set ADC conversion complete flag */
    adcConvDone = true;
}

void ADC_INIT(void)
{
	    uint16_t delayValue = 0;
	    status_t status;

	    /* Variables in which we store data from ADC */
	    uint16_t adcMax;
	    float adcValue;

	    (void) adcMax;
	    (void) adcValue;

	    adcConvDone = false;

	    /* Configure clocks for PORT */
	    status = CLOCK_DRV_Init(&clockMan1_InitConfig0);
	    DEV_ASSERT(status == STATUS_SUCCESS);

	    /* Set pins as GPIO */
	    status = PINS_DRV_Init(NUM_OF_CONFIGURED_PINS0, g_pin_mux_InitConfigArr0);
	    DEV_ASSERT(status == STATUS_SUCCESS);

	    /* Get ADC max value from the resolution */
	    if (ADC_0_ConvConfig0.resolution == ADC_RESOLUTION_8BIT)
	        adcMax = (uint16_t) (1 << 8);
	    else if (ADC_0_ConvConfig0.resolution == ADC_RESOLUTION_10BIT)
	        adcMax = (uint16_t) (1 << 10);
	    else
	        adcMax = (uint16_t) (1 << 12);


	    /* Configure and calibrate the ADC converter
	     *  -   See ADC component for the configuration details
	     */

	    DEV_ASSERT(ADC_0_ChnConfig0.channel == ADC_CHN);

	    ADC_DRV_ConfigConverter(ADC_INSTANCE, &ADC_0_ConvConfig0);
	    ADC_DRV_AutoCalibration(ADC_INSTANCE);
	    ADC_DRV_ConfigChan(ADC_INSTANCE, 0UL, &ADC_0_ChnConfig0);

	    IRQn_Type adcIRQ;

	    switch(ADC_INSTANCE)
	    {
	    case 0UL:
	        adcIRQ = ADC0_IRQn;
	        break;
	    case 1UL:
	        adcIRQ = ADC1_IRQn;
	        break;
	    default:
	        adcIRQ = ADC1_IRQn;
	        break;
	    }

	    INT_SYS_InstallHandler(adcIRQ, &ADC_IRQHandler, (isr_t*) 0);

	     /* Calculate the value needed for PDB instance
	     * to generate an interrupt at a specified timeout.
	     * If the value can not be reached, stop the application flow
	     */
	    if (!calculateIntValue(&pdb_1_timerConfig0, PDLY_TIMEOUT, &delayValue))
	    {
	        /* Stop the application flow */
	        while(1);
	    }
	    /* Setup PDB instance
	     *  -   See PDB component for details
	     *  Note: Pre multiplier and Prescaler values come from
	     *        calculateIntValue function.
	     */
	    PDB_DRV_Init(PDB_INSTANCE, &pdb_1_timerConfig0);
	    PDB_DRV_Enable(PDB_INSTANCE);
	    PDB_DRV_ConfigAdcPreTrigger(PDB_INSTANCE, 0UL, &pdb_1_adcTrigConfig0);
	    PDB_DRV_SetTimerModulusValue(PDB_INSTANCE, (uint32_t) delayValue);
	    PDB_DRV_SetAdcPreTriggerDelayValue(PDB_INSTANCE, 0UL, 0UL,
	            (uint32_t) delayValue);
	    PDB_DRV_LoadValuesCmd(PDB_INSTANCE);
	    PDB_DRV_SoftTriggerCmd(PDB_INSTANCE);

	    /* Enable ADC 1 interrupt */
	    INT_SYS_EnableIRQ(adcIRQ);

}
//---------------------------------------------------------

static void ADC_Task_20ms( void *pvParameters )
{

	ADC_INIT();
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
		vTaskDelayUntil( &xNextWakeTime, ADC_Task_20ms_Period );

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

static void ADC_Task_200ms( void *pvParameters )
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
		vTaskDelayUntil( &xNextWakeTime, ADC_Task_200ms_Period );

		/*LED blink*/
		if(adc_threshold_exceeded)
		{
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
		else
		{
			LED(RED,OFF);
		}

	}
}
