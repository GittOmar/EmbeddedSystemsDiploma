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
#include "./TIMER3/hal_timer3.h"
#include"./CCP1/hal_ccp1.h"
/*****************************************
 *           Macro Declarations          *
 *****************************************/
/*****************************************
 *        Function Declarations          *
 *****************************************/
void my_t2();
void tm3();
Std_RetuenType mcal_layer_initialize(void);
/*****************************************
 *               Modules                 *
 *****************************************/
// ccp1_t myccp = {
//    .CCP1_Mode_select = CCP1_PWM_MODE_SELECT,
//    .CCP1_Timer_select = CCP1_TIMER2_SELECT,
//    .CCP1_PWM_frequancy = 12345,
//    .CCP1_INTERRUPT_HANDLER = NULL,
//    .timer2 = {
//    .Timer2_IN_Handler = NULL,
//    .Timer2_Postscaler = TIMER2_POSTSCALER_1_DIV_1,
//    .Timer2_Prescaler = TIMER2_PRESCALER_1_DIV_1,
//    }
// };

// ccp1_t cap = {
//    .CCP1_Mode_select =CCP1_CAPTURE_MODE_RISSING_EDGE,
//    .CCP1_Timer_select = CCP1_TIMER3_SELECT,
//    .CCP1_INTERRUPT_HANDLER = &my_t2,
//    .timer3 ={
//       .Timer3_IN_Handler = &tm3,
//       .Timer3_Mode = TIMER3_TIMER_MODE,
//       .Timer3_RW_Mode = TIMER3_RW_8BIT_MODE,
//       .Timer3_Preloaded_value = 0,
//       .Timer3_Prescaler = TIMER3_PRESCALER_1_DIV_1
//    }
// };

ccp1_t comp = {
   .CCP1_INTERRUPT_HANDLER = NULL,
   .CCP1_Timer_select = CCP1_TIMER3_SELECT,
   .CCP1_Mode_select = CCP1_COMPARE_MODE_TOOGLE_OUTPUT ,
   .timer3 ={
      .Timer3_IN_Handler = NULL,
      .Timer3_Mode = TIMER3_TIMER_MODE,
      .Timer3_RW_Mode = TIMER3_RW_16BIT_MODE,
      .Timer3_Preloaded_value = 0,
      .Timer3_Prescaler = TIMER3_PRESCALER_1_DIV_1
   }
};
/*****************************************
 *          Data Type Declarations       *
 *****************************************/

#endif /* mcal_layer_init_H_ */