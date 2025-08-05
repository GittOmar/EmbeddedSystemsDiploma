/*
 * File:   app.h
 * Author: pc
 *
 * Created on June 21, 2025, 11:11 AM
 */

#ifndef APP_H
#define APP_H

/*****************************************
 *                 Includes              *
 *****************************************/
#include "./ECU_Layer/led/led.h"
#include "/ECU_Layer//push_button//push_button.h"
#include "./ECU_Layer/./relay/./ecu_relay.h"
#include "./ECU_Layer/./H_Bridge/./H_Bridge.h"
/*****************************************
 *           Macro Declarations          *
 *****************************************/

/*****************************************
 *       Macro Function Declarations     *
 *****************************************/

/*****************************************
 *          Data Type Declarations       *
 *****************************************/

/*****************************************
 *        Function Declarations          *
 *****************************************/
void application_instiallize(void);

#endif /* APP_H */
