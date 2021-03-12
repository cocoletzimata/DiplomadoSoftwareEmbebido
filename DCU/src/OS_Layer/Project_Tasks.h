/*
 * Project_Tasks.h
 *
 *  Created on: 10/03/2021
 *      Author: Marco
 */

#ifndef PROJECT_TASKS_H_
#define PROJECT_TASKS_H_

/*System Task Definitions*/
#define Task_20ms_Period			( 20 / portTICK_PERIOD_MS )
#define Task_20ms_Stack_Size		150
#define Task_20ms_priority			1

#define Task_100ms_Period			( 100 / portTICK_PERIOD_MS )
#define Task_100ms_Stack_Size		200
#define Task_100ms_priority			2

#define Task_200ms_Period			( 200 / portTICK_PERIOD_MS )
#define Task_200ms_Stack_Size		150
#define Task_200ms_priority			3

#define BIT0 1

 //void LED(uint8_t Color, bool State_LED);
 void Tasks_INIT(void);


#endif /* PROJECT_TASKS_H_ */
