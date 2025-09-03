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
/*****************************************
 *           Macro Declarations          *
 *****************************************/
/*****************************************
 *        Function Declarations          *
 *****************************************/
void  my_adc_isr();
void my_tt(void);
Std_RetuenType mcal_layer_initialize(void);
/*****************************************
 *               Modules                 *
 *****************************************/
timer0_t my_t = {
   .timer0_operation_mode = TIMER0_COUNTER_MODE,
   .timer0_register_size  = TIMER0_8BIT_REG_SIZE,
   .timer0_prescaler = TIMER0_PRESCALER_OFF,
   .timer0_interupt_handler = &my_tt,
   .timer0_PreLoaded_Value = 0x00
};

/*****************************************
 *          Data Type Declarations       *
 *****************************************/

#endif /* mcal_layer_init_H_ */