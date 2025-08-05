/*******************************************************************************
 * @file       ecu_layer_init.h
 * @brief      Driver/Module Description
 * @date       2025/08/05
 * @time       13:14
 * @author     Omar Ibrahim
 ******************************************************************************/

#ifndef ecu_layer_init_H_
#define ecu_layer_init_H_
/*****************************************
 *                Includes               *
 *****************************************/
#include "./led/ecu_led_cfg.h"
#include "./push_button/push_button.h"
#include "./relay/ecu_relay.h"
#include "./H_Bridge/./H_Bridge.h"
#include "./SevSeg/SevSeg.h"
#include "./KeyPad/KeyPad.h"
/*****************************************
 *              Modeules                 *
 *****************************************/
keypad_t kp = {
       .col_pins = {
        [0] = {.pin =PIN0 , .port = PORTC_INDEX},
        [1] = {.pin =PIN1 , .port = PORTC_INDEX},
        [2] = {.pin =PIN2 , .port = PORTC_INDEX},
        [3] = {.pin =PIN3 , .port = PORTC_INDEX}
       },
      .row_pins = {
        [0] = {.pin =PIN0 , .port = PORTD_INDEX},
        [1] = {.pin =PIN1 , .port = PORTD_INDEX},
        [2] = {.pin =PIN2 , .port = PORTD_INDEX},
        [3] = {.pin =PIN3 , .port = PORTD_INDEX}
       },
};
/*****************************************
 *        Function Declarations          *
 *****************************************/
void ecu_layer_initialize();

#endif /* ecu_layer_init_H_ */