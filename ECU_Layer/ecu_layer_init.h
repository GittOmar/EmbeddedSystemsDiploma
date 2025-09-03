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
#include "./led/led.h"
#include "./push_button/push_button.h"
#include "./relay/ecu_relay.h"
#include "./H_Bridge/./H_Bridge.h"
#include "./SevSeg/SevSeg.h"
#include "./KeyPad/KeyPad.h"
#include "./Lcd/lcd.h"
/*****************************************
 *       User Defined Varibles         *
 *****************************************/
/*****************************************
 *              Modeules                 *
 *****************************************/
led_t  led1 = {.port = PORTC_INDEX, 
               .pin = PIN0, 
               .status = LED_OFF};
/*****************************************
 *        Function Declarations          *
 *****************************************/
Std_RetuenType ecu_layer_initialize();

#endif /* ecu_layer_init_H_ */