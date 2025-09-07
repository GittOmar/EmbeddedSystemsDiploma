/*******************************************************************************
 * @file       hal_timer3.h
 * @brief      Driver/Module Description
 * @date       2025/09/06
 * @time       15:43
 * @author     Omar Ibrahim
 ******************************************************************************/

#ifndef hal_timer3_H_
#define hal_timer3_H_

/*****************************************
 *                 Includes              *
 *****************************************/
#include "hal_timer3_cfg.h"
#include "pic18f4620.h"
#include "../std_types.h"
#include "./../INTERRUPT/./mcal_internal_interrupt.h"
/*****************************************
 *           Macro Declarations          *
 *****************************************/
#define Timer3_LOW_Byte                                      (TMR3L)
#define Timer3_HIGH_Byte                                     (TMR3H)

#define TIMER3_TIMER_MODE                                     0
#define TIMER3_COUNTER_MODE                                   1

#define TIMER3_SYNCHRONOUS_COUNTER                            0                         
#define TIMER3_ASYNCHRONOUS_COUNTER                           1

#define TIMER3_PRESCALER_1_DIV_1                              0
#define TIMER3_PRESCALER_1_DIV_2                              1
#define TIMER3_PRESCALER_1_DIV_4                              2
#define TIMER3_PRESCALER_1_DIV_8                              3

#define TIMER3_RW_8BIT_MODE                                   0
#define TIMER3_RW_16BIT_MODE                                  1

#define ONE_BYTE_SHIFT                                        8
/*****************************************
 *       Macro Function Declarations     *
 *****************************************/
#define TIMER3_ENABLE()                                     (T3CONbits.TMR3ON = 1)                               
#define TIMER3_DISABLE()                                    (T3CONbits.TMR3ON = 0)

#define TIMER3_MODE_SELECT(MODE)                            (T3CONbits.TMR3CS = MODE)

#define TIMER3_SYNCHRONOUS_COUNTER_SELECT(MODE)             (T3CONbits.nT3SYNC = MODE)

#define TIMER3_PRESCALER_SELECT(prescaler)                  (T3CONbits.T3CKPS = prescaler)

#define TIMER3_RW_MODE_SELECT(mode)                         (T3CONbits.RD16 = mode)
/*****************************************
 *          Data Type Declarations       *
 *****************************************/
typedef struct{
 #if  (TIMER3_IN_ENABLE)   
 InterruotHandler Timer3_IN_Handler;
 #if  (PERIORITY_ENABLE)                     
 priority_t Timer3_priority;                            
 #endif                                             
 #endif 
 uint8  Timer3_Mode               : 1 ;
 uint8  Timer3_Prescaler          : 2 ;
 uint8  Tiemr3_Syn_select         : 1 ;
 uint8  Timer3_RW_Mode            : 1 ;
 uint16 Timer3_Preloaded_value;
}timer3_t;

/*****************************************
 *        Function Declarations          *
 *****************************************/
Std_RetuenType hal_Timer3_init(const timer3_t *timer);
Std_RetuenType hal_Timer3_deinit(const timer3_t *timer);
Std_RetuenType hal_Timer3_Read_value(const timer3_t *timer , uint16 *Value);
Std_RetuenType hal_Timer3_Write_value(const timer3_t *timer , uint16  Value);

#endif /* hal_timer3_H_ */