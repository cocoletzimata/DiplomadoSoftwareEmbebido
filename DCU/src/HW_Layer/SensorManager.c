/*
 * ADC_Drv.c
 *
 *  Created on: 10/03/2021
 *      Author: Marco
 */

#include <HW_Layer/SensorManager.h>

/*ADC functions declaration*/
 void ADC_IRQHandler(void);
 void ADC_INIT(void);
 uint16_t GetAdcCounts(void);

 static bool calculateIntValue(const pdb_timer_config_t *pdbConfig, uint32_t uSec, uint16_t *intValue);


 /* Flag used to store if an ADC IRQ was executed */
 volatile bool adcConvDone;
 /* Variable to store value from ADC conversion */
  volatile uint16_t adcRawValue;

 /* @brief: ADC Interrupt Service Routine.
  *        Read the conversion result, store it
  *        into a variable and set a specified flag.
  */



  bool calculateIntValue(const pdb_timer_config_t *pdbConfig, uint32_t uSec, uint16_t * intVal)
  {
      /* Local variables used to store different parameters
       * such as frequency and prescalers
       */
      uint32_t    intVal_l            = 0;
      uint8_t     pdbPrescaler        = (1 << pdbConfig->clkPreDiv);
      uint8_t     pdbPrescalerMult    = 0;
      uint32_t    pdbFrequency;

      bool resultValid = false;

      /* Get the Prescaler Multiplier from the configuration structure */
      switch (pdbConfig->clkPreMultFactor)
      {
          case PDB_CLK_PREMULT_FACT_AS_1:
              pdbPrescalerMult    =   1U;
              break;
          case PDB_CLK_PREMULT_FACT_AS_10:
              pdbPrescalerMult    =   10U;
              break;
          case PDB_CLK_PREMULT_FACT_AS_20:
              pdbPrescalerMult    =   20U;
              break;
          case PDB_CLK_PREMULT_FACT_AS_40:
              pdbPrescalerMult    =   40U;
              break;
          default:
              /* Defaulting the multiplier to 1 to avoid dividing by 0*/
              pdbPrescalerMult    =   1U;
              break;
      }

      /* Get the frequency of the PDB clock source and scale it
       * so that the result will be in microseconds.
       */
      CLOCK_SYS_GetFreq(CORE_CLOCK, &pdbFrequency);
      pdbFrequency /= 1000000;

      /* Calculate the interrupt value for the prescaler, multiplier, frequency
       * configured and time needed.
       */
      intVal_l = (pdbFrequency * uSec) / (pdbPrescaler * pdbPrescalerMult);

      /* Check if the value belongs to the interval */
      if((intVal_l == 0) || (intVal_l >= (1 << 16)))
      {
          resultValid = false;
          (*intVal) = 0U;
      }
      else
      {
          resultValid = true;
          (*intVal) = (uint16_t)intVal_l;
      }

      return resultValid;
  }



  void ADC_IRQHandler(void)
 {
     /* Get channel result from ADC channel */
     ADC_DRV_GetChanResult(ADC_INSTANCE, 0U, (uint16_t *)&adcRawValue);
     /* Set ADC conversion complete flag */
     adcConvDone = true;
 }

  uint16_t GetAdcCounts(void)
  {
	  if (adcConvDone == true)
	   	{
	   			adcConvDone = false;
	   			PDB_DRV_SoftTriggerCmd(PDB_INSTANCE);
	   	}

	  return adcRawValue;
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

 /*use this condition in the main code to update the ADC value correctly*/

 /*if (adcConvDone == true)
 	{
 			adcConvDone = false;
 			PDB_DRV_SoftTriggerCmd(PDB_INSTANCE);
 	}*/

