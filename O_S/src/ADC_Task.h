/*
 * ADC_Task.h
 *
 *  Created on: 04/03/2021
 *      Author: Marco
 */

#ifndef ADC_TASK_H_
#define ADC_TASK_H_


/*System Task Definitions*/
#define ADC_Task_20ms_Period			( 20 / portTICK_PERIOD_MS )
#define ADC_Task_20ms_Stack_Size		150
#define ADC_Task_20ms_priority			1

#define ADC_Task_200ms_Period			( 200 / portTICK_PERIOD_MS )
#define ADC_Task_200ms_Stack_Size		150
#define ADC_Task_200ms_priority			2

/*LEDs Definitions*/
#define RED 15
#define GREEN 16
#define BLUE 0

#define ON 1
#define OFF 0


/* Timeout for PDB in microseconds */
#define PDLY_TIMEOUT    10000UL   //This variable controls the sampling time in (us)

/*ADC Definitions*/
#define ADC_INSTANCE    0UL
#define ADC_CHN         ADC_INPUTCHAN_EXT12
#define ADC_VREFH       5.0f
#define ADC_VREFL       0.0f
#define PDB_INSTANCE    0UL



void ADC_Tasks_INIT(void);
void LED(uint8_t Color, bool State_LED);


#endif /* ADC_TASK_H_ */
