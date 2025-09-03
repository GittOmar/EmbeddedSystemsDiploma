/*******************************************************************************
 * @file       hal_timer0.c
 * @brief      Driver/Module Description
 * @date       2025/09/02
 * @time       15:05
 * @author     Omar Ibrahim
 ******************************************************************************/

/*****************************************
 *                includes                *
 *****************************************/
#include "hal_timer0.h"
/*****************************************
 *         UserDefined Data Type         *
 *****************************************/
 InterruotHandler timer0_interupt_handler;
 static volatile uint16 PreLoaded_Value;
/*****************************************
 *             Function Decleration      *
 *****************************************/
void GLOBAL_INTERUPT_DISABLE();
Std_RetuenType Module_INTERRUPT_ClEAR_FLAG(uint8 Reg,uint8 bit_pos);
void TIMER0_IN_INT(void);
void TIMER0_IN_DEINIT(void);
/*****************************************
 *           Helper Functions             *
 *****************************************/
static inline Std_RetuenType timer0_register_size(const timer0_t *timer0){
if(timer0 == NULL){
    return E_NOT_OK;
}else{
   switch (timer0->timer0_operation_mode) {
   case TIMER0_8BIT_REG_SIZE  : TIMER0_COUNTER_REG_8Bit_SELECT();  break;
   case TIMER0_16BIT_REG_SIZE : TIMER0_COUNTER_REG_16Bit_SELECT(); break;
   default: return E_NOT_OK;
   }
}
return E_OK;
}
static inline Std_RetuenType timer0_operation_mode(const timer0_t *timer0){
if(timer0 == NULL){
    return  E_NOT_OK;
}else{
   switch (timer0->timer0_operation_mode) {
   case TIMER0_COUNTER_MODE  : TIMER0_COUNTER_MODE_SELECT();  break;
   case TIMER0_TIMER_MODE    : TIMER0_TIMER_MODE_SELECT();    break;
   default: return E_NOT_OK;
   }
}
return E_OK;
}
static inline Std_RetuenType timer0_edge_trigger(const timer0_t *timer0){
if(timer0 == NULL){
    return  E_NOT_OK;
}else{
   switch (timer0->timer0_operation_mode) {
   case TIMER0_RISSING_EDGE    : TIMER0_COUNTER_MODE_RISSING_EDGE_TRRIGER();  break;
   case TIMER0_FALLING_EDGE    : TIMER0_COUNTER_MODE_FALLING_EDGE_TRRIGER(); break;
   default: return E_NOT_OK;
   }
}
return E_OK;
}
 static inline Std_RetuenType timer0_prescaler(const timer0_t *timer0){
if(timer0 == NULL){
    return  E_NOT_OK;
}else{
    if(timer0->timer0_prescaler == TIMER0_PRESCALER_OFF ){
      TIMER0_PRESCALER_DISABLE();  
    }
    else{
   TIMER0_PRESCALER_ENABLE();   
   switch (timer0->timer0_prescaler) {
   case TIMER0_PRESCALER_VAULE_1_div_2    :  TIMER0_CHOOSE_PRESCALER_VALUE(TIMER0_PRESCALER_VAULE_1_div_2); break;
   case TIMER0_PRESCALER_VAULE_1_div_4    :  TIMER0_CHOOSE_PRESCALER_VALUE(TIMER0_PRESCALER_VAULE_1_div_4); break;
   case TIMER0_PRESCALER_VAULE_1_div_8    :  TIMER0_CHOOSE_PRESCALER_VALUE(TIMER0_PRESCALER_VAULE_1_div_8); break;
   case TIMER0_PRESCALER_VAULE_1_div_16   :  TIMER0_CHOOSE_PRESCALER_VALUE(TIMER0_PRESCALER_VAULE_1_div_16); break;
   case TIMER0_PRESCALER_VAULE_1_div_32   :  TIMER0_CHOOSE_PRESCALER_VALUE(TIMER0_PRESCALER_VAULE_1_div_32); break;
   case TIMER0_PRESCALER_VAULE_1_div_64   :  TIMER0_CHOOSE_PRESCALER_VALUE(TIMER0_PRESCALER_VAULE_1_div_64); break;
   case TIMER0_PRESCALER_VAULE_1_div_128  :  TIMER0_CHOOSE_PRESCALER_VALUE(TIMER0_PRESCALER_VAULE_1_div_128); break;
   case TIMER0_PRESCALER_VAULE_1_div_256  :  TIMER0_CHOOSE_PRESCALER_VALUE(TIMER0_PRESCALER_VAULE_1_div_256); break;
   default: return E_NOT_OK;
}
    }

return E_OK;
}  
}
static inline Std_RetuenType timer0_interupt_handler_set(const timer0_t *timer0){
if(timer0 == NULL){
    return  E_NOT_OK;
}else{
 timer0_interupt_handler = timer0->timer0_interupt_handler;
}
return E_OK;
}  
/*****************************************
 *           function definition          *
 *****************************************/
 Std_RetuenType hal_timer0_init(const timer0_t *timer0){
    Std_RetuenType ret = E_OK;
  if(timer0 == NULL){
      return E_NOT_OK;
  }else{
    /** Prephral init  */
    GLOBAL_INTERUPT_DISABLE(); /** GIE Disable  */
    TIMER0_ENABLE(); /** Timer0_enable  */
    ret &= timer0_operation_mode(timer0);
    ret &= timer0_register_size(timer0);
    ret &= timer0_prescaler(timer0);
    ret &= timer0_edge_trigger(timer0);
    PreLoaded_Value = timer0->timer0_PreLoaded_Value;
    ret &= hal_timer0_write_value(PreLoaded_Value);
    /** Interrupt init  */
    ret &= timer0_interupt_handler_set(timer0);
    TIMER0_IN_INT();
  }
  return ret;
 }

 Std_RetuenType hal_timer0_deinti(const timer0_t *timer0){
  if(timer0 == NULL){
    return E_NOT_OK;
  }else{
    TIMER0_DISABLE();
  }
  return E_OK;
 }

 Std_RetuenType hal_timer0_read_value(uint16 *Value){
    if(Value == NULL){
        return E_NOT_OK;
    }else{
     *Value = ((uint16)(TIMER0_LOW_BYTE_REG)+((uint16)TIMER0_HIGH_BYTE_REG<<ONE_BYTE_SHIFT));
    }
    return E_OK;
 }

 Std_RetuenType hal_timer0_write_value(uint16 Value){
if(Value > UINT16_MAX){
        return E_NOT_OK;
    }else{
     TIMER0_HIGH_BYTE_REG =  (uint8)(Value>>ONE_BYTE_SHIFT); 
     TIMER0_LOW_BYTE_REG  = (uint8)Value;
    }
    return E_OK;
 }
/*****************************************
 *                ISR                    *
 *****************************************/
 void TIMER0_ISR(){
    Module_INTERRUPT_ClEAR_FLAG(TIMER0_FLAG_REG,TIMER0_FLAG_BIT); 
    hal_timer0_write_value(PreLoaded_Value);                 
    timer0_interupt_handler();     /** call the isr definction   */
 }