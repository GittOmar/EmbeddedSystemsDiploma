/*
 * File:   led.h
 * Author: pc
 *
 * Created on June 21, 2025, 11:30 AM
 */

#ifndef LED_H
#define LED_H

/*****************************************
 *                 Includes              *
 *****************************************/
#include "./../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_led_cfg.h"

/*****************************************
 *           Macro Declarations          *
 *****************************************/
#define LED_CONFIGRATION LED_FUN_ENABLE

/*****************************************
 *       Macro Function Declarations     *
 *****************************************/

/*****************************************
 *          Data Type Declarations       *
 *****************************************/
typedef enum { LED_OFF, LED_ON } led_status_t;

typedef struct {
  uint8 port : 3;
  uint8 pin : 3;
  uint8 status : 1;
  uint8 reserved : 1;
} led_t;

/*****************************************
 *        Function Declarations          *
 *****************************************/
Std_RetuenType led_initialize(const led_t *led_config);
Std_RetuenType led_turn_on(const led_t *led_config);
Std_RetuenType led_turn_off(const led_t *led_config);
Std_RetuenType led_turn_toggle(const led_t *led_config);

#endif /* LED_H */