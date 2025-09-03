/*******************************************************************************
 * @file       mcal_internal_interrupt.c
 * @brief      Driver/Module Description
 * @date       2025/08/18
 * @time       11:59
 * @author     Omar Ibrahim
 ******************************************************************************/

/*****************************************
 *                includes                *
 *****************************************/
#include "mcal_internal_interrupt.h"
/*****************************************
 *           Function Decleration        *
 *****************************************/
void GLOBAL_INTERUPT_DISABLE(void);
void GLOBAL_INTERUPT_ENABLE(void);
/*****************************************
 *            User Definced Var          *
 *****************************************/
 volatile uint8 *E_Reg [] = {&PIE2, &PIE1,&INTCON};
 volatile uint8 *F_Reg [] = {&PIR2, &PIR1,&INTCON};
 volatile uint8 *P_Reg [] = {&IPR2, &IPR1};
/*****************************************
 *           INTERRUPT HANDLER           *
 *****************************************/
 InterruotHandler  EEPROM_InterruptHandler;
/*****************************************
 *            Helper Functions           *
 *****************************************/
Std_RetuenType Module_INTERRUPT_ENABLE(uint8 Reg,uint8 bit_pos){
  Std_RetuenType ret = E_OK;
  if((Reg > UINT8_MAX) || (bit_pos >UINT8_MAX)){
   ret = E_NOT_OK;
  }else{
   SET_BIT(*(E_Reg[Reg]),bit_pos);
  }
  return ret;
 }
Std_RetuenType Module_INTERRUPT_DISABLE(uint8 Reg,uint8 bit_pos){
  Std_RetuenType ret = E_OK;
  if((Reg > UINT8_MAX) || (bit_pos >UINT8_MAX)){
   ret = E_NOT_OK;
  }else{
   CLEAR_BIT(*(E_Reg[Reg]),bit_pos);
  }
  return ret;
 }
Std_RetuenType Module_INTERRUPT_SET_HIGH_PRIORITY(uint8 Reg,uint8 bit_pos){
  Std_RetuenType ret = E_OK;
  if((Reg > UINT8_MAX) || (bit_pos >UINT8_MAX)){
   ret = E_NOT_OK;
  }else{
   SET_BIT(*(P_Reg[Reg]),bit_pos);
  }
  return ret;
 }
Std_RetuenType Module_INTERRUPT_SET_LOW_PRIORITY(uint8 Reg,uint8 bit_pos){
  Std_RetuenType ret = E_OK;
  if((Reg > UINT8_MAX) || (bit_pos >UINT8_MAX)){
   ret = E_NOT_OK;
  }else{
   CLEAR_BIT(*(P_Reg[Reg]),bit_pos);
  }
  return ret;
 }
 Std_RetuenType Module_INTERRUPT_ClEAR_FLAG(uint8 Reg,uint8 bit_pos){
  Std_RetuenType ret = E_OK;
  if((Reg > UINT8_MAX) || (bit_pos >UINT8_MAX)){
   ret = E_NOT_OK;
  }else{
   CLEAR_BIT(*(F_Reg[Reg]),bit_pos);
  }
  return ret;
 }
 #if  (PERIORITY_ENABLE)                     
 static Std_RetuenType SET_Interrupt_PRIORITY(priority_t priority, uint8 Reg,uint8 bit_pos){
   Std_RetuenType ret = E_OK;
 if((Reg > UINT8_MAX) || (bit_pos >UINT8_MAX)){
    ret = E_NOT_OK;
 }else{
     switch (priority) {
       case HIGH_PRIORITY : Module_INTERRUPT_SET_HIGH_PRIORITY(Reg, bit_pos); break;
       case LOW_PRIORITY :  Module_INTERRUPT_SET_LOW_PRIORITY (Reg, bit_pos) ; break;
       default: ret = E_NOT_OK;
     }
 }
 return ret;
}                              
#endif 
/*****************************************
 *           function definition          *
 *****************************************/
 /****************************
  *          EEPROM           *
  ****************************/
 Std_RetuenType EEPROM_INTERRUPT_INIT(const eeprom_IN_t *EEPROM){
 Std_RetuenType ret = E_OK;
 if(EEPROM == NULL){
    ret = E_NOT_OK;
 }else{
        GLOBAL_INTERUPT_DISABLE();          // GIE disable
        ret &= Module_INTERRUPT_ClEAR_FLAG(EEPROM_FLAG_REG,EEPROM_FLAG_BIT);               // flag clear
        ret &= Module_INTERRUPT_ENABLE(EEPROM_ENABLE_REG,EEPROM_ENABLE_BIT);        // Interrupt enable
        #if  (PERIORITY_ENABLE)      
        INTERRUPT_PeriorityEnable();     // priority enable           
        ret &= SET_Interrupt_PRIORITY(EEPROM->ee_priority,EEPROM_PRIORITY_REG,EEPROM_PRIORITY_BIT);        // priority set 
        #endif                        
        EEPROM_InterruptHandler = EEPROM->EEPROM_InterruptHandler;   // ISR address
        GLOBAL_INTERUPT_ENABLE();          // GIE Enable
 }
 return ret;
}
void EEPROM_INTERRUPT_DEINIT(void){
   Module_INTERRUPT_DISABLE(EEPROM_ENABLE_REG,EEPROM_ENABLE_BIT);        // Interrupt enable
}
/****************************
 *          ADC              *
 ****************************/
void ADC_INTERRUPT_INIT(priority_t adc_priority){
        GLOBAL_INTERUPT_DISABLE();          // GIE disable
        Module_INTERRUPT_ClEAR_FLAG(ADC_FLAG_REG,ADC_FLAG_BIT);               // flag clear
        Module_INTERRUPT_ENABLE(ADC_ENABLE_REG,ADC_ENABLE_BIT);        // Interrupt enable
        #if  (PERIORITY_ENABLE)      
        INTERRUPT_PeriorityEnable();     // priority enable           
        SET_Interrupt_PRIORITY(adc_priority,ADC_PRIORITY_REG,ADC_PRIORITY_BIT);        // priority set 
        #endif                        
        GLOBAL_INTERUPT_ENABLE();          // GIE Enable
}
void           ADC_INTERRUPT_DEINIT(void){
   Module_INTERRUPT_DISABLE(ADC_ENABLE_REG,ADC_ENABLE_BIT);        // Interrupt enable
}
/****************************
 *          TIMER0          *
 ****************************/
 void TIMER0_IN_INT(){
 GLOBAL_INTERUPT_DISABLE();
 Module_INTERRUPT_ClEAR_FLAG(TIMER0_FLAG_REG,TIMER0_FLAG_BIT);                  
 Module_INTERRUPT_ENABLE(TIMER0_ENABLE_REG,TIMER0_ENABLE_BIT);
 #if  (PERIORITY_ENABLE)                     
 INTERRUPT_PeriorityEnable();                            
 #endif    
 GLOBAL_INTERUPT_ENABLE();          // GIE Enable
 }
 void TIMER0_IN_DEINIT(){
 Module_INTERRUPT_DISABLE(TIMER0_FLAG_REG,TIMER0_FLAG_BIT);
 }
/*****************************************
 *                ISR                    *
 *****************************************/
 void EEPROM_ISR(void); 
 void EEPROM_ISR(){
   Module_INTERRUPT_ClEAR_FLAG(EEPROM_FLAG_REG,EEPROM_FLAG_BIT);               // flag clear
   EEPROM_InterruptHandler();
 }


