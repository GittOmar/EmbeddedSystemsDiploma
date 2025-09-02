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
#include "ECU_Layer/ecu_layer_init.h"
#include "MCAL_Layer/mcal_layer_init.h"
#include "MCAL_Layer/std_types.h"
/*****************************************
 *           Macro Declarations          *
 *****************************************/
#define _XTAL_FREQ 8000000UL
/*****************************************
 *       User Defined Varibles         *
 *****************************************/ 
 Std_RetuenType ret = E_OK; 
uint16 Value;    
float voltage;    
uint8 voltage_a;    
uint8 voltage_b;

uint8 adc_value[]={};
uint8 pa[]={};
uint8 pb[]={};
/*****************************************
 *          Data Type Declarations       *
 *****************************************/
/*****************************************
 *        Function Declarations          *
 *****************************************/
Std_RetuenType application_instiallize(void);



#endif /* APP_H */

