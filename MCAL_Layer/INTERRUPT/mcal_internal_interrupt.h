/*******************************************************************************
 * @file       mcal_internal_interrupt.h
 * @brief      Driver/Module Description
 * @date       2025/08/18
 * @time       12:02
 * @author     Omar Ibrahim
 ******************************************************************************/

#ifndef mcal_internal_interrupt_H_
#define mcal_internal_interrupt_H_

/*****************************************
 *                 Includes              *
 *****************************************/
#include "./../std_types.h"
#include "mcal_interrupt_config.h"
#include "../GPIO/hal_gpio.h"
#include "pic18f4620.h"
/*****************************************
 *           Macro Declarations          *
 *****************************************/
#define FIRST_REG      0x00
#define SECOND_REG     0x01
#define THIRD_REG      0x02

#define bit_0          0X00          
#define bit_1          0X01        
#define bit_2          0X02
#define bit_3          0X03
#define bit_4          0X04
#define bit_5          0X05
#define bit_6          0X06
#define bit_7          0X07
/****************************
 *          EEPROM          *
 ****************************/
#define  EEPROM_ENABLE_REG     FIRST_REG
#define  EEPROM_FLAG_REG       FIRST_REG
#define  EEPROM_PRIORITY_REG   FIRST_REG

#define  EEPROM_ENABLE_BIT     bit_4
#define  EEPROM_FLAG_BIT       bit_4
#define  EEPROM_PRIORITY_BIT   bit_4       
/****************************
 *             ADC          *
 ****************************/
#define  ADC_ENABLE_REG     SECOND_REG
#define  ADC_FLAG_REG       SECOND_REG
#define  ADC_PRIORITY_REG   SECOND_REG

#define  ADC_ENABLE_BIT     bit_6
#define  ADC_FLAG_BIT       bit_6
#define  ADC_PRIORITY_BIT   bit_6
/****************************
 *          Timer0          *
 ****************************/
#define  TIMER0_ENABLE_REG     THIRD_REG
#define  TIMER0_FLAG_REG       THIRD_REG

#define  TIMER0_ENABLE_BIT     bit_5
#define  TIMER0_FLAG_BIT       bit_2
/****************************
 *          TIMER1          *
 ****************************/
#define  TIMER1_ENABLE_REG     SECOND_REG
#define  TIMER1_FLAG_REG       SECOND_REG
#define  TIMER1_PRIORITY_REG   SECOND_REG

#define  TIMER1_ENABLE_BIT     bit_0
#define  TIMER1_FLAG_BIT       bit_0
#define  TIMER1_PRIORITY_BIT   bit_0
/****************************
 *          TIMER2          *
 ****************************/
#define  TIMER2_ENABLE_REG     SECOND_REG
#define  TIMER2_FLAG_REG       SECOND_REG
#define  TIMER2_PRIORITY_REG   SECOND_REG

#define  TIMER2_ENABLE_BIT     bit_1
#define  TIMER2_FLAG_BIT       bit_1
#define  TIMER2_PRIORITY_BIT   bit_1
/****************************
 *          TIMER3          *
 ****************************/
#define  TIMER3_ENABLE_REG     FIRST_REG
#define  TIMER3_FLAG_REG       FIRST_REG
#define  TIMER3_PRIORITY_REG   FIRST_REG

#define  TIMER3_ENABLE_BIT     bit_1
#define  TIMER3_FLAG_BIT       bit_1
#define  TIMER3_PRIORITY_BIT   bit_1
/****************************
 *           CCP1           *
 ****************************/
#define  CCP1_ENABLE_REG     SECOND_REG
#define  CCP1_FLAG_REG       SECOND_REG
#define  CCP1_PRIORITY_REG   SECOND_REG

#define  CCP1_ENABLE_BIT     bit_2
#define  CCP1_FLAG_BIT       bit_2
#define  CCP1_PRIORITY_BIT   bit_2
/*****************************************
 *       Macro Function Declarations     *
 *****************************************/        
/*****************************************
 *          Data Type Declarations       *
 *****************************************/
/****************************
 *          EEPROM          *
 ****************************/
 typedef struct{
 InterruotHandler EEPROM_InterruptHandler;
 #if  (PERIORITY_ENABLE)                     
 priority_t ee_priority;                               
 #endif                        
 }eeprom_IN_t;
/*****************************************
 *        Function Declarations          *
 *****************************************/
/****************************
 *          EEPROM          *
 ****************************/
Std_RetuenType EEPROM_INTERRUPT_INIT(const eeprom_IN_t *EEPROM);
void           EEPROM_INTERRUPT_DEINIT(void);
/****************************
 *             ADC          *
 ****************************/
#endif /* mcal_internal_interrupt_H_ */