/*
 * ADC_Drv.h
 *
 *  Created on: 10/03/2021
 *      Author: Marco
 */

#ifndef ADC_DRV_H_
#define ADC_DRV_H_

/*ADC includes.*/
#include "peripherals_pdb_1.h"
#include "interrupt_manager.h"
#include "sdk_project_config.h"


/* Timeout for PDB in microseconds */
#define PDLY_TIMEOUT    10000UL   //This variable controls the sampling time in (us)

/*ADC Definitions*/
#define ADC_INSTANCE    0UL
#define ADC_CHN         ADC_INPUTCHAN_EXT12
#define ADC_VREFH       5.0f
#define ADC_VREFL       0.0f
#define PDB_INSTANCE    0UL

/*ADC functions*/
extern void ADC_IRQHandler(void);
extern void ADC_INIT(void);
extern uint16_t GetAdcCounts(void);

/* Flag used to store if an ADC IRQ was executed */
extern volatile bool adcConvDone;
/* Variable to store value from ADC conversion */
extern volatile uint16_t adcRawValue;


#endif /* ADC_DRV_H_ */
