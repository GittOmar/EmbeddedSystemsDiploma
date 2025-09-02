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
void           ADC_INTERRUPT_INIT(priority_t adc_priority);
void           ADC_INTERRUPT_DEINIT(void);
#endif /* mcal_internal_interrupt_H_ */