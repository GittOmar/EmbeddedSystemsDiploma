/*******************************************************************************
 * @file       mcal_interrupt_config.c
 * @brief      Driver/Module Description
 * @date       2025/08/26
 * @time       09:25
 * @author     Omar Ibrahim
 ******************************************************************************/

/*****************************************
 *                includes                *
 *****************************************/
#include "mcal_interrupt_config.h"
/*****************************************
 *           function definition          *
 *****************************************/
  void GLOBAL_INTERUPT_ENABLE(){
    #if  (PERIORITY_ENABLE)                     
    INTRUPT_GlobalInterruptHighEnable();  
    INTRUPT_GlobalInterruptLowEnable();                          
    #else
    INTRUPT_GlobalInterruptEnable();
    PrephralInterruptEnable();
    #endif
 }

  void GLOBAL_INTERUPT_DISABLE(){
    #if  (PERIORITY_ENABLE)                     
    INTRUPT_GlobalInterruptHighDisable(); 
    INTRUPT_GlobalInterruptLowDisable();                           
    #else
    INTRUPT_GlobalInterruptDisable();
    PrephralInterruptDisable();
    #endif
 }

 Std_RetuenType GLOBAL_INTERRUPT_RETURN_STATE(uint8 PrevState){
  Std_RetuenType ret =  E_OK;
  if(PrevState > UINT8_MAX ){
    ret = E_NOT_OK;
  }else{
    if(PrevState == GIE_ENABLE){
       GLOBAL_INTERUPT_ENABLE(); 
    }
    else{
       GLOBAL_INTERUPT_DISABLE();
    }
  }
  return ret;
 }