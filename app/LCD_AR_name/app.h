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
#include "MCAL_Layer/std_types.h"
/*****************************************
 *           Macro Declarations          *
 *****************************************/
#define _XTAL_FREQ 8000000UL
/*****************************************
 *       User Defined Varibles         *
 *****************************************/
uint8 value_recived;
char name[] = "omar";
uint8 cnt = 245;
uint8 chr[4];

const uint8 O[] = {
  0x00,
  0x07,
  0x04,
  0x1F,
  0x00,
  0x00,
  0x00,
  0x00
};
const uint8 M[] = {
  0x00,
  0x0E,
  0x0A,
  0x1B,
  0x0E,
  0x00,
  0x00,
  0x00
};

const uint8 R[] = {
  0x00,
  0x08,
  0x04,
  0x07,
  0x04,
  0x18,
  0x00,
  0x00
};

/*****************************************
 *          Data Type Declarations       *
 *****************************************/

/*****************************************
 *        Function Declarations          *
 *****************************************/
Std_RetuenType application_instiallize(void);

#endif /* APP_H */

