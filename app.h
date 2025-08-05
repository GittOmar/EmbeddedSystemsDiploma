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
#include "./ECU_Layer/ecu_layer_init.h"
/*****************************************
 *           Macro Declarations          *
 *****************************************/
#define _XTAL_FREQ 8000000UL
/*****************************************
 *       User Defined Varibles         *
 *****************************************/
Std_RetuenType ret = E_NOT_OK;
uint8 value_recived;
/*****************************************
 *          Data Type Declarations       *
 *****************************************/

/*****************************************
 *        Function Declarations          *
 *****************************************/
void application_instiallize(void);

#endif /* APP_H */
