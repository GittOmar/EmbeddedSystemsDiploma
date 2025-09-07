/*******************************************************************************
 * @file       hal_timer3.c
 * @brief      Driver/Module Description
 * @date       2025/09/06
 * @time       15:43
 * @author     Omar Ibrahim
 ******************************************************************************/

/*****************************************
 *                includes                *
 *****************************************/
#include"hal_timer3.h"
/*****************************************
 *              Varibles                  *
 *****************************************/
InterruotHandler Timer3_IN_Handler_Call;
uint16 Preloaded_Value;
uint8  RW_State;
/*****************************************
 *        function Decleration           *
 *****************************************/
Std_RetuenType Module_INTERRUPT_ClEAR_FLAG(uint8 Reg,uint8 bit_pos);
void GLOBAL_INTERUPT_DISABLE();
void Timer3_IN_init(priority_t Timer3_priority);
/*****************************************
 *           function definition          *
 *****************************************/
Std_RetuenType hal_Timer3_init(const timer3_t *timer){
Std_RetuenType ret = E_OK;
priority_t Timer_priority = LOW_PRIORITY;
#if  (PERIORITY_ENABLE)                     
Timer_priority = timer->Timer3_priority;                              
#endif 
if(timer == NULL){
    return E_NOT_OK;
}else{
GLOBAL_INTERUPT_DISABLE();
TIMER3_ENABLE();
/** Timer Mode  */
TIMER3_MODE_SELECT(timer->Timer3_Mode);
TIMER3_PRESCALER_SELECT(timer->Timer3_Prescaler);
/** Counter Mode  */
TIMER3_SYNCHRONOUS_COUNTER_SELECT(timer->Tiemr3_Syn_select);
/** other  */
TIMER3_RW_MODE_SELECT(timer->Timer3_RW_Mode);
hal_Timer3_Write_value(timer,timer->Timer3_Preloaded_value);
Preloaded_Value        = timer->Timer3_Preloaded_value;
RW_State               = timer->Timer3_RW_Mode;
/** Interrupt  */
Timer3_IN_Handler_Call = timer->Timer3_IN_Handler;
Timer3_IN_init(Timer_priority);
}
return ret;
}

Std_RetuenType hal_Timer3_deinit(const timer3_t *timer){
Std_RetuenType ret = E_OK;
if(timer == NULL){
    return E_NOT_OK;
}else{
TIMER3_DISABLE();
}
return ret;
}

Std_RetuenType hal_Timer3_Read_value(const timer3_t *timer , uint16 *Value){
Std_RetuenType ret = E_OK;
if((timer == NULL) || (Value == NULL)){
    return E_NOT_OK;
}else{

*Value = (uint16)Timer3_LOW_Byte;
if(timer->Timer3_RW_Mode == TIMER3_RW_16BIT_MODE){
    *Value += ((uint16)Timer3_HIGH_Byte<<ONE_BYTE_SHIFT);  
}
}
return ret;
}

Std_RetuenType hal_Timer3_Write_value(const timer3_t *timer , uint16  Value){
Std_RetuenType ret = E_OK;
if(Value > UINT16_MAX){
    return E_NOT_OK;
}else{

Timer3_LOW_Byte  = (uint8)Value;
if(timer->Timer3_RW_Mode == TIMER3_RW_16BIT_MODE){
    Timer3_HIGH_Byte = (uint8)(Value>>ONE_BYTE_SHIFT);
}
Preloaded_Value = Value;
}
return ret;
}
/*****************************************
 *                ISR                     *
 *****************************************/
 void TIMER3_ISR(){
    Module_INTERRUPT_ClEAR_FLAG(TIMER3_FLAG_REG,TIMER3_FLAG_BIT);  

    Timer3_LOW_Byte  = (uint8)Preloaded_Value;
    if(RW_State == TIMER3_RW_16BIT_MODE){
        Timer3_HIGH_Byte = (uint8)(Preloaded_Value>>ONE_BYTE_SHIFT);
    }

    Timer3_IN_Handler_Call();
 }