/*******************************************************************************
 * @file       mcal_interrupt_manager.h
 * @brief      Driver/Module Description
 * @date       2025/08/18
 * @time       12:02
 * @author     Omar Ibrahim
 ******************************************************************************/

#ifndef mcal_interrupt_manager_H_
#define mcal_interrupt_manager_H_

/*****************************************
 *                 Includes              *
 *****************************************/
#include "mcal_interrupt_config.h"
/*****************************************
 *           Macro Declarations          *
 *****************************************/
 /****************************
  *          EXTERNAL        *
  ****************************/
#define  EXT_IN0_InterruptState         INTCONbits.INT0E
#define  EXT_IN0_FlagState              INTCONbits.INT0F

#define  EXT_IN1_InterruptState         INTCON3bits.INT1E
#define  EXT_IN1_FlagState              INTCON3bits.INT1F

#define  EXT_IN2_InterruptState         INTCON3bits.INT2E
#define  EXT_IN2_FlagState              INTCON3bits.INT2F

#define EXT_RBx_OnChange_InterruptState  INTCONbits.RBIE
#define EXT_RBx_OnChange_FlagState       INTCONbits.RBIF
/****************************
 *          INTERNAL        *
 ****************************/
#define  EEPROM_FLAG                      (PIR2bits.EEIF)  
#define  EEPROM_Enable                    (PIE2bits.EEIE)

#define  ADC_FLAG                         (PIR1bits.ADIF)  
#define  ADC_Enable                       (PIE1bits.ADIE)

#define  TIMER0_FLAG                      (INTCONbits.TMR0IF)  
#define  TIMER0_Enable                    (INTCONbits.TMR0IE)  
/*****************************************
 *       Macro Function Declarations     *
 *****************************************/
/****************************
 *          EXTERNAL         
 ****************************/
#define  EXT_RBx_PinState(x)             PORTBbits.RB##x
#define  RB_FLAG(x)     (x-4)
/*****************************************
 *          Data Type Declarations       *
 *****************************************/
/*****************************************
 *        Function Declarations          *
 *****************************************/
/****************************
 *          INx_ISR         *
 ****************************/
void IN0_ISR(void);
void IN1_ISR(void);
void IN2_ISR(void);
/****************************
 *          RBx_ISR         *
 ****************************/
void RB4_R_ISR(void);
void RB4_F_ISR(void);

void RB5_R_ISR(void);
void RB5_F_ISR(void);

void RB6_R_ISR(void);
void RB6_F_ISR(void);

void RB7_R_ISR(void);
void RB7_F_ISR(void);
/****************************
 *          Interanl           *
 ****************************/
 void EEPROM_ISR(void);
 void ADC_ISR(void);
 void TIMER0_ISR(void);
#endif /* mcal_interrupt_manager_H_ */