/*
 * File:   push button.h
 * Author: pc
 *
 * Created on July 5, 2025, 5:18 PM
 */

#ifndef PUSH_BUTTON_H
#define PUSH_BUTTON_H

/*****************************************
 *                 Includes              *
 *****************************************/
#include "./../../MCAL_Layer/GPIO/hal_gpio.h"
#include "./push_button cfg.h"
#include "../../MCAL_Layer/std_types.h"

/*****************************************
 *           Macro Declarations          *
 *****************************************/
#define threshold   550
#define period      1000
/*****************************************
 *       Macro Function Declarations     *
 *****************************************/

/*****************************************
 *          Data Type Declarations       *
 *****************************************/
typedef enum { BUTTON_RELEASED, BUTTON_PRESSED } button_state_t;

typedef enum { BUTTON_ACTIVE_HIGH, BUTTON_ACTIVE_LOW } button_config_t;

typedef struct {
  pin_config_t pin_cfg; // 1 byte
  button_state_t button_state;
  button_config_t button_config;
} button_t;

/*****************************************
 *        Function Declarations          *
 *****************************************/
Std_RetuenType button_intialize(const button_t *button);
Std_RetuenType button_read_state(const button_t *button,button_state_t *button_state); // why send  button state in pointer
Std_RetuenType button_read_state_BS(const button_t *button, button_state_t *button_state); // Bounse Skip < BS >
Std_RetuenType buttont_does_state_changes(const button_t *button , uint32* within_counter, uint8* flag);
#endif /* PUSH_BUTTON_H */
