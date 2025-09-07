/*******************************************************************************
 * @file       hal_timer2.c
 * @brief      Driver/Module Description
 * @date       2025/09/05
 * @time       16:12
 * @author     Omar Ibrahim
 ******************************************************************************/

/*****************************************
 *                includes                *
 *****************************************/
#include "hal_timer2.h"
/*****************************************
 *                Varibles               *
 *****************************************/
  InterruotHandler Timer2_IN_Handler_Call;
  uint8 PreloadedValue;
/*****************************************
 *          Function Decleration         *
 *****************************************/
void GLOBAL_INTERUPT_DISABLE();
 Std_RetuenType Module_INTERRUPT_ClEAR_FLAG(uint8 Reg,uint8 bit_pos);
 void Timer2_IN_init(priority_t Timer2_priority);
/*****************************************
 *             Helper Functions          *
 *****************************************/
 static inline Std_RetuenType Timer2_Prescaler(const timer2_t *Timer2){
 Std_RetuenType ret = E_OK;
 if(Timer2 == NULL){
    return  E_NOT_OK;
 }else{
   TIMER2_PRESCALER_SELECT(Timer2->Timer2_Prescaler); 
 }
 return ret;
 }
 static inline Std_RetuenType Timer2_Postscaler(const timer2_t *Timer2){
 Std_RetuenType ret = E_OK;
 if(Timer2 == NULL){
    return  E_NOT_OK;
 }else{
   TIMER2_POSTSCALER_SELECT(Timer2->Timer2_Postscaler);
 } 
 return ret; 
 }
 static inline Std_RetuenType Timer2_IN_Handler(const timer2_t *Timer2){
 Std_RetuenType ret = E_OK;
 if(Timer2 == NULL){
    return  E_NOT_OK;
 }else{
  Timer2_IN_Handler_Call = Timer2->Timer2_IN_Handler; 
 }
 return ret;  
 }
/*****************************************
 *           function definition          *
 *****************************************/
Std_RetuenType hal_Timer2_init(const timer2_t *Timer2){
Std_RetuenType ret = E_OK;
priority_t Timer_priority = LOW_PRIORITY;
#if  (PERIORITY_ENABLE)                     
Timer_priority = Timer2->Timer2_priority;                              
#endif                        
if(Timer2 == NULL){
    return E_NOT_OK;
}else{
 GLOBAL_INTERUPT_DISABLE();
 TIMER2_ENABLE();
 ret &= Timer2_Prescaler(Timer2);
 ret &= Timer2_Postscaler(Timer2);

  TIMER2_PRELOAD_REGISTER = Timer2->Timer2_Preloaded_value;
  PreloadedValue          = Timer2->Timer2_Preloaded_value ;

 ret &= Timer2_IN_Handler(Timer2);
       Timer2_IN_init(Timer_priority);
}
return ret;
}

Std_RetuenType hal_Timer2_deinit(const timer2_t *Timer2){
Std_RetuenType ret = E_OK;
if(Timer2 == NULL){
    return E_NOT_OK;
}else{
TIMER2_DISABLE(); 
}
return ret;
}
Std_RetuenType hal_Timer2_Write_value(uint8 Value){
Std_RetuenType ret = E_OK;
if(Value > UINT8_MAX){
    return E_NOT_OK;
}else{
 TIMER2_PRELOAD_REGISTER = Value;
 PreloadedValue  = Value ;
}
return ret;
}

Std_RetuenType hal_Timer2_Read_value(uint8 *Value){
Std_RetuenType ret = E_OK;
if(Value == NULL){
    return E_NOT_OK;
}else{
 *Value = TIMER2_REGISTER;
}
return ret;
}
/*****************************************
 *                ISR                    *
 *****************************************/
 void TIMER2_ISR(){

   Module_INTERRUPT_ClEAR_FLAG(TIMER2_FLAG_REG,TIMER2_FLAG_BIT);  
   Timer2_IN_Handler_Call();
 }