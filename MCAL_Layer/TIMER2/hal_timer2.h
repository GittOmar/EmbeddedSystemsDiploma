/*******************************************************************************
 * @file       hal_timer2.h
 * @brief      Driver/Module Description
 * @date       2025/09/05
 * @time       16:12
 * @author     Omar Ibrahim
 ******************************************************************************/

#ifndef hal_timer2_H_
#define hal_timer2_H_

/*****************************************
 *                 Includes              *
 *****************************************/
#include "haL_tiemr2_cfg.h"
#include "pic18f4620.h"
#include "../std_types.h"
#include "./../INTERRUPT/./mcal_internal_interrupt.h"
/*****************************************
 *           Macro Declarations          *
 *****************************************/
#define TIMER2_PRELOAD_REGISTER                   (PR2)
#define TIMER2_REGISTER                           (TMR2)

#define TIMER2_PRESCALER_1_DIV_1           0x00
#define TIMER2_PRESCALER_1_DIV_4           0x01
#define TIMER2_PRESCALER_1_DIV_16          0x02


#define TIMER2_POSTSCALER_1_DIV_1               0
#define TIMER2_POSTSCALER_1_DIV_2               1
#define TIMER2_POSTSCALER_1_DIV_3               2
#define TIMER2_POSTSCALER_1_DIV_4               3
#define TIMER2_POSTSCALER_1_DIV_5               4
#define TIMER2_POSTSCALER_1_DIV_6               5
#define TIMER2_POSTSCALER_1_DIV_7               6
#define TIMER2_POSTSCALER_1_DIV_8               7
#define TIMER2_POSTSCALER_1_DIV_9               8
#define TIMER2_POSTSCALER_1_DIV_10              9
#define TIMER2_POSTSCALER_1_DIV_11              10
#define TIMER2_POSTSCALER_1_DIV_12              11
#define TIMER2_POSTSCALER_1_DIV_13              12
#define TIMER2_POSTSCALER_1_DIV_14              13
#define TIMER2_POSTSCALER_1_DIV_15              14
#define TIMER2_POSTSCALER_1_DIV_16              15
/*****************************************
 *       Macro Function Declarations     *
 *****************************************/
#define TIMER2_ENABLE()                                (T2CONbits.TMR2ON = 1)
#define TIMER2_DISABLE()                               (T2CONbits.TMR2ON = 0)

#define TIMER2_PRESCALER_SELECT(prescaler)             (T2CONbits.T2CKPS = prescaler)
#define TIMER2_POSTSCALER_SELECT(postscaler)           (T2CONbits.TOUTPS = postscaler)
/*****************************************
 *          Data Type Declarations       *
 *****************************************/
 typedef struct{
 #if  (TIMER2_IN_ENABLE)   
 InterruotHandler Timer2_IN_Handler;
 #if  (PERIORITY_ENABLE)                     
 priority_t Timer2_priority;                            
 #endif                                             
 #endif                        
 uint8 Timer2_Prescaler           : 2;
 uint8 Timer2_Postscaler          : 4;
 uint8 Timer2_Preloaded_value ;
 }timer2_t;

/*****************************************
 *        Function Declarations          *
 *****************************************/
Std_RetuenType hal_Timer2_init(const timer2_t *Timer2);
Std_RetuenType hal_Timer2_deinit(const timer2_t *Timer2);
Std_RetuenType hal_Timer2_Write_value(uint8 Value);
Std_RetuenType hal_Timer2_Read_value(uint8 *Value);

#endif /* hal_timer2_H_ */