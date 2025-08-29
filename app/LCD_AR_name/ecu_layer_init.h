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
#include "./Lcd/lcd.h"
/*****************************************
 *       User Defined Varibles         *
 *****************************************/
Std_RetuenType ret = E_OK;
/*****************************************
 *              Modeules                 *
 *****************************************/
#if LCD_BIT_MODE == _8BIT_MODE
lcd_t lcd ={ .E.port   = PORTC_INDEX, .E.pin  = PIN0, 
             .RS.port  = PORTC_INDEX, .RS.pin = PIN1, 
             .data_bus = {
                [0] = {.port = PORTC_INDEX , .pin = PIN2}, 
                [1] = {.port = PORTC_INDEX , .pin = PIN3}, 
                [2] = {.port = PORTC_INDEX , .pin = PIN4}, 
                [3] = {.port = PORTC_INDEX , .pin = PIN5},
                [4] = {.port = PORTC_INDEX , .pin = PIN6},
                [5] = {.port = PORTC_INDEX , .pin = PIN7},
                [6] = {.port = PORTD_INDEX , .pin = PIN0},                
                [7] = {.port = PORTD_INDEX , .pin = PIN1}              
             }};

#elif LCD_BIT_MODE == _4BIT_MODE
lcd_t lcd ={ .E.port   = PORTC_INDEX, .E.pin  = PIN0, 
.RS.port  = PORTC_INDEX, .RS.pin = PIN1, 
.data_bus = {
   [0] = {.port = PORTC_INDEX , .pin = PIN6}, 
   [1] = {.port = PORTC_INDEX , .pin = PIN7}, 
   [2] = {.port = PORTD_INDEX , .pin = PIN0}, 
   [3] = {.port = PORTD_INDEX , .pin = PIN1}           
}};
#endif
/*****************************************
 *        Function Declarations          *
 *****************************************/
Std_RetuenType ecu_layer_initialize();

#endif /* ecu_layer_init_H_ */