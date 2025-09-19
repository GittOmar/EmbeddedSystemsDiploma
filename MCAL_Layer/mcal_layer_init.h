/*******************************************************************************
 * @file       mcal_layer_init.h
 * @brief      Driver/Module Description
 * @date       2025/08/21
 * @time       06:54
 * @author     Omar Ibrahim
 ******************************************************************************/

#ifndef mcal_layer_init_H_
#define mcal_layer_init_H_

/*****************************************
 *                 Includes              *
 *****************************************/
#include "../MCAL_Layer/EUSART/eusart.h"
#include "GPIO/hal_gpio.h"
#include "INTERRUPT/mcal_external_interrupt.h"
#include "INTERRUPT/mcal_internal_interrupt.h"
#include "./EEPROM/./EEPROM.h"
#include "./ADC/hal_adc.h"
#include "./TIMER0/hal_timer0.h"
#include "./TIMER1/hal_timer1.h"
#include "./TIMER2/hal_timer2.h"
#include "./TIMER3/hal_timer3.h"
#include"./CCP1/hal_ccp1.h"
/*****************************************
 *           Macro Declarations          *
 *****************************************/
/*****************************************
 *        Function Declarations          *
 *****************************************/
Std_RetuenType mcal_layer_initialize(void);
/*****************************************
 *               Modules                 *
 *****************************************/
eusart_t tr ={
   .EUSART_FERR_IN_HANDLER =NULL,
   .EUSART_FERR_IN_HANDLER = NULL,
   .BaudRate ={
      .BaudRate = EUSART_BR_9600,
      .BR_CFG   = EUSART_8BIT_ASYN_LOW_SPEED,
   },
   .TX = {
      .Eusart_Frame_size =   EUSART_TX_9BIT_DISABLE_BIT,
      .Eusart_TX_Enable  =   EUSART_TX_ENABLE_SELECT,
      .EUSART_TX_IN_HANDLER = NULL,
   },
   .RX = {
      .Eusart_Frame_size = EUSART_RX_9BIT_DISABLE_BIT,
      .Eusart_RX_Enable = EUSART_RX_ENABLE_SELECT,
      .EUSART_RX_IN_HANDLER = NULL
   }
};
/*****************************************
 *          Data Type Declarations       *
 *****************************************/

#endif /* mcal_layer_init_H_ */