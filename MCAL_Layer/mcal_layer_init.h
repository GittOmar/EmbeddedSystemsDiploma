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
#include "INTERRUPT/mcal_external_interrupt.h"
#include "INTERRUPT/mcal_internal_interrupt.h"
#include "./EEPROM/./EEPROM.h"
#include "./ADC/hal_adc.h"
#include "./TIMER0/hal_timer0.h"
#include "./TIMER1/hal_timer1.h"
#include "./TIMER2/hal_timer2.h"
#include "TIMER3/hal_timer3.h"
/*****************************************
 *           Macro Declarations          *
 *****************************************/
/*****************************************
 *        Function Declarations          *
 *****************************************/
void my_t2();
Std_RetuenType mcal_layer_initialize(void);
/*****************************************
 *               Modules                 *
 *****************************************/
timer3_t t3 ={
   .Timer3_Mode = TIMER3_COUNTER_MODE,
   .Timer3_RW_Mode = TIMER3_RW_16BIT_MODE,
   .Timer3_Preloaded_value = 255,
   .Tiemr3_Syn_select=TIMER3_ASYNCHRONOUS_COUNTER
};

/*****************************************
 *          Data Type Declarations       *
 *****************************************/

#endif /* mcal_layer_init_H_ */