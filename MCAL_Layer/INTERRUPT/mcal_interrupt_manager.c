/*******************************************************************************
 * @file       mcal_interrupt_manager.c
 * @brief      Driver/Module Description
 * @date       2025/08/18
 * @time       12:00
 * @author     Omar Ibrahim
 ******************************************************************************/

/*****************************************
 *                includes                *
 *****************************************/
#include "mcal_interrupt_manager.h"
/*****************************************
 *       User Defined Data Types         *
 *****************************************/
 static volatile uint8 RBflags[4] = {1 , 1 , 1, 1};
/*****************************************
 *           function definition          *
 *****************************************/
#if PERIORITY_ENABLE
/****************************
 *        HIGH PRIORITY     *
 ****************************/
void __interrupt()InterruptManaerHigh(void){
if((EXT_IN0_InterruptState == INTERRUPT_ENABLE) && (EXT_IN0_FlagState == INTERRUPR_OCUUR)){
 IN0_ISR();
}

if((EXT_IN2_InterruptState == INTERRUPT_ENABLE) && (EXT_IN2_FlagState == INTERRUPR_OCUUR)){
IN2_ISR();
}
}
/****************************
 *      LOW PRIORITY        *
 ****************************/
void __interrupt(low_priority)InterruptManaerLow(void){
if((EXT_IN1_InterruptState == INTERRUPT_ENABLE) && (EXT_IN1_FlagState == INTERRUPR_OCUUR)){
IN1_ISR();
}    
}
#else
/****************************
 *        NO PRIORITY       *
 ****************************/
void __interrupt()InterruptManaerHigh(void){
/****************************
 *          INx             *
 ****************************/
#ifdef EXTERNAL_INTERRUPT_INT0_ENABLE    
if((EXT_IN0_InterruptState == INTERRUPT_ENABLE) && (EXT_IN0_FlagState == INTERRUPR_OCUUR) ){
 IN0_ISR();
}
#endif
#ifdef EXTERNAL_INTERRUPT_INT1_ENABLE
if((EXT_IN1_InterruptState == INTERRUPT_ENABLE) && (EXT_IN1_FlagState == INTERRUPR_OCUUR)){
IN1_ISR();
}
#endif
#ifdef EXTERNAL_INTERRUPT_INT2_ENABLE
if((EXT_IN2_InterruptState == INTERRUPT_ENABLE) && (EXT_IN2_FlagState == INTERRUPR_OCUUR)){
IN2_ISR();
}
#endif
/****************************
 *           RBx            *
 ****************************/
#ifdef EXTERNAL_INTERRUPT_RB4_ENABLE
if((EXT_RBx_OnChange_InterruptState == INTERRUPT_ENABLE) && (EXT_RBx_OnChange_FlagState == INTERRUPR_OCUUR) && (EXT_RBx_PinState(4) == RISSING_EDGE) && (RBflags[RB_FLAG(4)] == FLAG_HIGH)){
RBflags[RB_FLAG(4)] = FLAG_LOW;    
RB4_R_ISR();
}

if((EXT_RBx_OnChange_InterruptState == INTERRUPT_ENABLE) && (EXT_RBx_OnChange_FlagState == INTERRUPR_OCUUR) && (EXT_RBx_PinState(4) == FALLING_EDGE) && (RBflags[RB_FLAG(4)] == FLAG_LOW) ){
RBflags[RB_FLAG(4)] = FLAG_HIGH;    
RB4_F_ISR();
}
#endif

#ifdef EXTERNAL_INTERRUPT_RB5_ENABLE
if((EXT_RBx_OnChange_InterruptState == INTERRUPT_ENABLE) && (EXT_RBx_OnChange_FlagState == INTERRUPR_OCUUR) && (EXT_RBx_PinState(5) == RISSING_EDGE) && (RBflags[RB_FLAG(5)] == FLAG_HIGH)){
RBflags[RB_FLAG(5)] = FLAG_LOW;
RB5_R_ISR();
}

if((EXT_RBx_OnChange_InterruptState == INTERRUPT_ENABLE) && (EXT_RBx_OnChange_FlagState == INTERRUPR_OCUUR) && (EXT_RBx_PinState(5) == FALLING_EDGE)&& (RBflags[RB_FLAG(5)] == FLAG_LOW)){
RBflags[RB_FLAG(5)] = FLAG_HIGH;
RB5_F_ISR();
}
#endif

#ifdef EXTERNAL_INTERRUPT_RB6_ENABLE
if((EXT_RBx_OnChange_InterruptState == INTERRUPT_ENABLE) && (EXT_RBx_OnChange_FlagState == INTERRUPR_OCUUR) && (EXT_RBx_PinState(6) == RISSING_EDGE) && (RBflags[RB_FLAG(6)] == FLAG_HIGH)){
RBflags[RB_FLAG(6)] = FLAG_LOW;
RB6_R_ISR();
}

if((EXT_RBx_OnChange_InterruptState == INTERRUPT_ENABLE) && (EXT_RBx_OnChange_FlagState == INTERRUPR_OCUUR) && (EXT_RBx_PinState(6) == FALLING_EDGE) && (RBflags[RB_FLAG(6)] == FLAG_LOW) ){
RBflags[RB_FLAG(6)] = FLAG_HIGH;
RB6_F_ISR();
}
#endif

#ifdef EXTERNAL_INTERRUPT_RB7_ENABLE
if((EXT_RBx_OnChange_InterruptState == INTERRUPT_ENABLE) && (EXT_RBx_OnChange_FlagState == INTERRUPR_OCUUR) && (EXT_RBx_PinState(7) == RISSING_EDGE) && (RBflags[RB_FLAG(7)] == FLAG_LOW)){
RBflags[RB_FLAG(7)] = FLAG_LOW;
RB7_R_ISR();
}

if((EXT_RBx_OnChange_InterruptState == INTERRUPT_ENABLE) && (EXT_RBx_OnChange_FlagState == INTERRUPR_OCUUR) && (EXT_RBx_PinState(7) == FALLING_EDGE) && (RBflags[RB_FLAG(7)] == FLAG_LOW) ){
RBflags[RB_FLAG(7)] = FLAG_HIGH;
RB7_F_ISR();
}
#endif
/****************************
 *          EEPROM          *
 ****************************/
 if((EEPROM_FLAG == INTERRUPR_OCUUR) && (EEPROM_Enable == INTERRUPT_ENABLE)){
    EEPROM_ISR();
 }
 /****************************
  *          ADC             *
  ****************************/
 if((ADC_FLAG == INTERRUPR_OCUUR) && (ADC_Enable == INTERRUPT_ENABLE)){
    ADC_ISR();
 }
 /****************************
  *          TIMER0          *
  ****************************/
 if((TIMER0_FLAG == INTERRUPR_OCUUR) && (TIMER0_Enable == INTERRUPT_ENABLE)){
   TIMER0_ISR();
 }
 /****************************
  *          TIMER1          *
  ****************************/
  if((TIMER1_FLAG == INTERRUPR_OCUUR) && (TIMER1_Enable == INTERRUPT_ENABLE)){
   TIMER1_ISR();
 }
  /****************************
  *          TIMER2          *
  ****************************/
  if((TIMER2_FLAG == INTERRUPR_OCUUR) && (TIMER2_Enable == INTERRUPT_ENABLE)){
   TIMER2_ISR();
 }
  /****************************
  *          TIMER3          *
  ****************************/
  if((TIMER3_FLAG == INTERRUPR_OCUUR) && (TIMER3_Enable == INTERRUPT_ENABLE)){
   TIMER3_ISR();
 }
  /****************************
  *          CPP1          *
  ****************************/
  if((CCP1_FLAG == INTERRUPR_OCUUR) && (CCP1_Enable == INTERRUPT_ENABLE)){
   CCP1_ISR();
 }
}
#endif