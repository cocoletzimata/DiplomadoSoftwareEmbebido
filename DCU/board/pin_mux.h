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
#define CLOSE_BTN_PORT    PTC
#define CLOSE_BTN_PIN     13U
#define PASSENGER_OPEN_BTN_PORT    PTC
#define PASSENGER_OPEN_BTN_PIN     0U
#define PASSENGER_CLOSE_BTN_PORT    PTC
#define PASSENGER_CLOSE_BTN_PIN     1U
#define BLUE_LED_PORT    PTD
#define BLUE_LED_PIN     0U
#define ADC_01_PORT    PTC
#define ADC_01_PIN     14U
#define CAN_TX_PORT    PTE
#define CAN_TX_PIN     5U
#define CAN_RX_PORT    PTE
#define CAN_RX_PIN     4U
#define OPEN_BTN_PORT    PTC
#define OPEN_BTN_PIN     12U
#define REARLEFT_OPEN_BTN_PORT    PTC
#define REARLEFT_OPEN_BTN_PIN     2U
#define REARLEFT_CLOSE_BTN_PORT    PTC
#define REARLEFT_CLOSE_BTN_PIN     3U
#define REARRIGHT_OPEN_BTN_PORT    PTC
#define REARRIGHT_OPEN_BTN_PIN     4U
#define REARRIGHT_CLOSE_BTN_PORT    PTC
#define REARRIGHT_CLOSE_BTN_PIN     5U
#define REAR_WINDOW_LOCK_BTN_PORT    PTC
#define REAR_WINDOW_LOCK_BTN_PIN     6U
#define LOCK_BTN_PORT    PTC
#define LOCK_BTN_PIN     7U
#define UNLOCK_BTN_PORT    PTC
#define UNLOCK_BTN_PIN     8U
#define MSB_SW_VARIANT_PORT    PTC
#define MSB_SW_VARIANT_PIN     9U
#define LSB_SW_VARIANT_PORT    PTC
#define LSB_SW_VARIANT_PIN     11U
#define LED_1_WINDOW_PORT    PTD
#define LED_1_WINDOW_PIN     1U
#define LED_2_WINDOW_PORT    PTD
#define LED_2_WINDOW_PIN     2U
#define LED_3_WINDOW_PORT    PTD
#define LED_3_WINDOW_PIN     3U
#define LED_4_WINDOW_PORT    PTD
#define LED_4_WINDOW_PIN     4U
#define LED_5_WINDOW_PORT    PTD
#define LED_5_WINDOW_PIN     5U
#define LED_6_WINDOW_PORT    PTD
#define LED_6_WINDOW_PIN     6U
#define LED_7_WINDOW_PORT    PTD
#define LED_7_WINDOW_PIN     7U
#define LED_8_WINDOW_PORT    PTD
#define LED_8_WINDOW_PIN     8U
#define LED_9_WINDOW_PORT    PTD
#define LED_9_WINDOW_PIN     9U
#define LED_10_WINDOW_PORT    PTD
#define LED_10_WINDOW_PIN     10U
#define SW_WINDOW_CLOSED_PORT    PTD
#define SW_WINDOW_CLOSED_PIN     11U
#define SW_WINDOW_OPEN_PORT    PTD
#define SW_WINDOW_OPEN_PIN     12U
#define SW_DOOR_LOCKED_PORT    PTD
#define SW_DOOR_LOCKED_PIN     13U
#define SW_DOOR_UNLOCKED_PORT    PTD
#define SW_DOOR_UNLOCKED_PIN     14U
/*! @brief User number of configured pins */
#define NUM_OF_CONFIGURED_PINS0 33
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

