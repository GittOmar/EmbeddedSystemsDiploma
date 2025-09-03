/*******************************************************************************
 * @file       hal_timer0.h
 * @brief      Driver/Module Description
 * @date       2025/09/02
 * @time       15:05
 * @author     Omar Ibrahim
 ******************************************************************************/

#ifndef hal_timer0_H_
#define hal_timer0_H_

/*****************************************
 *                 Includes              *
 *****************************************/
#include "pic18f4620.h"
#include "../std_types.h"
#include "hal_timer0_cfg.h"
#include "./../INTERRUPT/./mcal_internal_interrupt.h"
/*****************************************
 *           Macro Declarations          *
 *****************************************/
#define TIMER0_LOW_BYTE_REG                     (TMR0L)        
#define TIMER0_HIGH_BYTE_REG                    (TMR0H)  

#define  TIMER0_COUNTER_MODE                   0x01
#define  TIMER0_TIMER_MODE                     0x00
  
#define  TIMER0_8BIT_REG_SIZE                   0x01  
#define  TIMER0_16BIT_REG_SIZE                  0x00

#define  TIMER0_RISSING_EDGE                   0x01  
#define  TIMER0_FALLING_EDGE                   0x00

#define  ONE_BYTE_SHIFT                         8
/*****************************************
 *       Macro Function Declarations     *
 *****************************************/    
#define TIMER0_ENABLE()                                           (T0CONbits.TMR0ON = 1)                      
#define TIMER0_DISABLE()                                          (T0CONbits.TMR0ON = 0)
          
#define TIMER0_COUNTER_REG_8Bit_SELECT()                           (T0CONbits.T08BIT = 1)
#define TIMER0_COUNTER_REG_16Bit_SELECT()                          (T0CONbits.T08BIT = 0)
          
#define TIMER0_COUNTER_MODE_SELECT()                               (T0CONbits.T0CS = 1)  
#define TIMER0_TIMER_MODE_SELECT()                                 (T0CONbits.T0CS = 0)

#define TIMER0_COUNTER_MODE_RISSING_EDGE_TRRIGER()                 (T0CONbits.T0SE = 1)
#define TIMER0_COUNTER_MODE_FALLING_EDGE_TRRIGER()                 (T0CONbits.T0SE = 0)

#define TIMER0_PRESCALER_ENABLE()                                  (T0CONbits.PSA = 0)   
#define TIMER0_PRESCALER_DISABLE()                                 (T0CONbits.PSA = 1)
#define TIMER0_CHOOSE_PRESCALER_VALUE(x)                           (T0CONbits.T0PS = x) 
/*****************************************
 *          Data Type Declarations       *
 *****************************************/
typedef enum{
TIMER0_PRESCALER_VAULE_1_div_2 = 0,
TIMER0_PRESCALER_VAULE_1_div_4,
TIMER0_PRESCALER_VAULE_1_div_8,
TIMER0_PRESCALER_VAULE_1_div_16,
TIMER0_PRESCALER_VAULE_1_div_32,
TIMER0_PRESCALER_VAULE_1_div_64,
TIMER0_PRESCALER_VAULE_1_div_128,
TIMER0_PRESCALER_VAULE_1_div_256,
TIMER0_PRESCALER_OFF
}timer0_prescaler_t;


typedef struct{
#if  (TIMER0_IN_ENABLE)                     
InterruotHandler    timer0_interupt_handler;                          
#endif                                       
uint8               timer0_operation_mode : 1; /** @brief TIMER0_COUNTER_MODE  TIMER0_TIMER_MODE  */
uint8               timer0_edge_trigger   : 1;
uint8               timer0_register_size  : 1;
timer0_prescaler_t  timer0_prescaler;
uint16              timer0_PreLoaded_Value;
}timer0_t;
/*****************************************
 *        Function Declarations          *
 *****************************************/
 Std_RetuenType hal_timer0_init(const timer0_t *timer0);
 Std_RetuenType hal_timer0_deinti(const timer0_t *timer0);
 Std_RetuenType hal_timer0_read_value(uint16 *Value);
 Std_RetuenType hal_timer0_write_value(uint16 Value);

#endif /* hal_timer0_H_ */