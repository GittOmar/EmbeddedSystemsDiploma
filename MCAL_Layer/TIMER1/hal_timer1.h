/*******************************************************************************
 * @file       hal_timer1.h
 * @brief      Driver/Module Description
 * @date       2025/09/04
 * @time       10:13
 * @author     Omar Ibrahim
 ******************************************************************************/

#ifndef hal_timer1_H_
#define hal_timer1_H_

/*****************************************
 *                 Includes              *
 *****************************************/
#include "pic18f4620.h"
#include "../std_types.h"
#include "hal_timer1_cfg.h"
#include "./../INTERRUPT/./mcal_internal_interrupt.h"
/*****************************************
 *           Macro Declarations          *
 *****************************************/
#define TIMER1_LOW_BYTE_REG                          (TMR1L)        
#define TIMER1_HIGH_BYTE_REG                         (TMR1H)

#define TIMER1_USED_CLK_SOUREC                       (T1RUN)

#define TIMER1_PRIMARY_CLK_SOURCE                     0x00
#define TIMER1_SECONDARY_CLK_SOURCE                   0x01
       
#define  TIMER1_COUNTER_MODE                          0x01
#define  TIMER1_TIMER_MODE                            0x00

#define  Timer1_SYNCHRONOUS_COUNTER                   0x00
#define  Timer1_ASYNCHRONOUS_COUNTER                  0x01

#define TIMER1_16BIT_RW_MODE                          0x01                                 
#define TIMER1_8BIT_RW_MODE                           0x00   

       
#define  ONE_BYTE_SHIFT                                8
/*****************************************
 *       Macro Function Declarations     *
 *****************************************/
#define TIMER1_ENABLE()                                                  (T1CONbits.TMR1ON = 1)                      
#define TIMER1_DISABLE()                                                 (T1CONbits.TMR1ON = 0)
       
#define TIMER1_OSCILLATOR_ENABLE()                                      (T1CONbits.T1OSCEN = 1)
#define TIMER1_OSCILLATOR_DISABLE()                                      (T1CONbits.T1OSCEN = 0)
       
#define TIMER1_COUNTER_MODE_SELECT()                                     (T1CONbits.TMR1CS = 1)  
#define TIMER1_TIMER_MODE_SELECT()                                       (T1CONbits.TMR1CS = 0)
       
#define TIMER1_CHOOSE_PRESCALER_VALUE(x)                                 (T1CONbits.T1CKPS = x) 
       
#define TIMER1_SYNCHRONOUS_COUNTER_ENABLE()                                     (T1CONbits.T1SYNC = 0)
#define TIMER1_ASYNCHRONOUS_COUNTER_ENABLE()                                    (T1CONbits.T1SYNC = 1)
       
#define TIMER1_16BIT_RW_MODE_ENABLE()                                           (T1CONbits.RD16 = 1)                                 
#define TIMER1_8BIT_RW_MODE_ENABLE()                                            (T1CONbits.RD16 = 0)   
/*****************************************
 *          Data Type Declarations       *
 *****************************************/
typedef enum{
TIMER1_PRESCALER_OFF,
TIMER1_PRESCALER_1_div_2,
TIMER1_PRESCALER_1_div_4,
TIMER1_PRESCALER_1_div_8
}timer1_prescaler_t;

typedef struct{
#if  (TIMER1_IN_ENABLE)                     
InterruotHandler      Timer1_Interrupt_Handler;  
#if  (PERIORITY_ENABLE)                     
priority_t            Timer1_Priority;                                                        
#endif                                                    
#endif                        
timer1_prescaler_t   Timer1_Prescaler;                   
uint8                Timer1_clk_source                      : 1;
uint8                Timer1_Operation_Mode                  : 1;
uint8                Timer1_RW_BitMode                      : 1;
uint8                Timer1_Counter_synchronization         : 1;
uint16               Timer1_Preloaded_value;
}timer1_t;

/*****************************************
 *        Function Declarations          *
 *****************************************/
Std_RetuenType hal_Timer1_init(const timer1_t *Timer1);
Std_RetuenType hal_Timer1_deinit(const timer1_t *Timer1);
Std_RetuenType hal_Timer1_Read_value(const timer1_t *Timer1, uint16 *Value);
Std_RetuenType hal_Timer1_Write_value(const timer1_t *Timer1, uint16 Value);

#endif /* hal_timer1_H_ */