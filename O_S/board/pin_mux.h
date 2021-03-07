#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_

#include "pins_driver.h"

/***********************************************************************************************************************
 * Definitions
 **********************************************************************************************************************/

/*!
 * @addtogroup pin_mux
 * @{
 */

/***********************************************************************************************************************
 * API
 **********************************************************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif


/*! @brief Definitions/Declarations for BOARD_InitPins Functional Group */
/*! @brief User definition pins */
#define GREEN_LED_PORT    PTD
#define GREEN_LED_PIN     16U
#define RED_LED_PORT    PTD
#define RED_LED_PIN     15U
#define BLUE_LED_PORT    PTD
#define BLUE_LED_PIN     0U
#define ADC_01_PORT    PTC
#define ADC_01_PIN     14U
/*! @brief User number of configured pins */
#define NUM_OF_CONFIGURED_PINS0 7
/*! @brief User configuration structure */
extern pin_settings_config_t g_pin_mux_InitConfigArr0[NUM_OF_CONFIGURED_PINS0];


#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /* _PIN_MUX_H_ */

/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/

