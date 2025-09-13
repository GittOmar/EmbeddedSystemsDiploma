/*******************************************************************************
 * @file       hal_ccp1.c
 * @brief      Driver/Module Description
 * @date       2025/09/10
 * @time       15:32
 * @author     Omar Ibrahim
 ******************************************************************************/

/*****************************************
 *                includes                *
 *****************************************/
#include "hal_CCP1.h"
/*****************************************
 *          Function Decleration         *
 *****************************************/
void GLOBAL_INTERUPT_DISABLE(void);
Std_RetuenType Module_INTERRUPT_ClEAR_FLAG(uint8 Reg,uint8 bit_pos);
void CCP1_IN_init(priority_t CCP1_priority);
void comp_PWMgenrator(void);
/*****************************************
 *                Varible                *
 *****************************************/
InterruotHandler    CCP1_INTERRUPT_HANDLER_CallBack;

volatile static uint8 dutycycle ;
volatile static uint32 cnt = 100000;
 /*****************************************
  *              Helper Functions         *
  *****************************************/
static inline Std_RetuenType CCP1_timer_select(const ccp1_t *ccp1){
Std_RetuenType ret = E_OK;
if(ccp1 == NULL){
    return E_NOT_OK;
}else{
    switch (ccp1->CCP1_Timer_select) {
    #if  (CCP1_COMPARE_MODE || CCP1_CAPTURE_MODE)                     
    case CCP1_TIMER1_SELECT : 
    hal_Timer1_init(&(ccp1->timer1));
    CCP1_TIMER1_USE();
    break;
    case CCP1_TIMER3_SELECT : 
    hal_Timer3_init(&(ccp1->timer3));
    CCP1_TIMER3_USE();
    break;                        
    #endif                        
    #if  (CCP1_PWM_MODE)                     
    case CCP1_TIMER2_SELECT :
    hal_Timer2_init(&(ccp1->timer2));
    break;                        
    #endif                        
    default: return E_NOT_OK;
    }
}
return ret ;
}


static inline Std_RetuenType CCP1_PinState(const ccp1_t *ccp1){
    Std_RetuenType ret = E_OK;
    if(ccp1 == NULL){
        return E_NOT_OK;
    }else{
        switch (ccp1->CCP1_Mode_select) {
        case 8 ... 12 :  case 2 : 
        CCP1_PIN_OUTPUT(); 
        break; 
        case 4 ... 7 : 
        CCP1_PIN_INPUT();
        break;
        default: return E_NOT_OK;
        }
    }
    return ret;
}

#if  (CCP1_PWM_MODE)                     
static inline void CCP1_Pre_PostScaler(const ccp1_t *ccp1,uint8 *prescaler , uint8 *postscaler){
switch (ccp1->timer2.Timer2_Prescaler) {
    case TIMER2_PRESCALER_1_DIV_1 : *prescaler = 1;   break;
    case TIMER2_PRESCALER_1_DIV_4 : *prescaler = 4;   break;
    case TIMER2_PRESCALER_1_DIV_16: *prescaler = 16;  break;
}

*postscaler = ccp1->timer2.Timer2_Postscaler + 1;
}

static inline void CCP1_PWM_Freq(const ccp1_t *ccp1){
    uint8 prescaler , postscaler;
    CCP1_Pre_PostScaler(ccp1,&prescaler,&postscaler);
    CCP1_TIMER2_PR2 = (uint8)(( _XTAL_FREQ / ((uint32)ccp1->CCP1_PWM_frequancy * 4UL * prescaler * postscaler)) - 1);
}                        
#endif                        
/*****************************************
 *           function definition          *
 *****************************************/
 Std_RetuenType hal_ccp1_init( ccp1_t *ccp1){

 Std_RetuenType ret = E_OK;

 priority_t CCP1_PRIORITY_default = HIGH_PRIORITY;
 #if  (PERIORITY_ENABLE)                     
 CCP1_PRIORITY_default = ccp1->CCP1_PRIORITY;                              
 #endif 

 if(ccp1 == NULL){
    return E_NOT_OK;
 }else{
  GLOBAL_INTERUPT_DISABLE();

 /** mode select  */
 CCP1_MODE_SELECT(ccp1->CCP1_Mode_select);/** Mode select  */
 ret &= CCP1_PinState(ccp1);      /** Pin state   */


 #if  (CCP1_PWM_MODE)                     
        CCP1_PWM_Freq(ccp1); /** PWM Freq assign  */
        ccp1->timer2.Timer2_Preloaded_value = CCP1_TIMER2_PR2;            
 #endif                         
 
 
 ret &= CCP1_timer_select(ccp1); /** Timer select  */
      
 /** Int handling  */
 CCP1_INTERRUPT_HANDLER_CallBack = ccp1->CCP1_INTERRUPT_HANDLER;
 CCP1_IN_init(CCP1_PRIORITY_default);

 }
 return ret;
 }
 void hal_ccp1_deinit(){
 CCP1_MODE_SELECT(CCP1_CAPTURE_COMAPRE_PWM_DISABLE);
 }
 /****************************
  *       Comparter          *
  ****************************/
#if  (CCP1_COMPARE_MODE)                     
Std_RetuenType hal_ccp1_IsCompareComplete(uint8 *status){
Std_RetuenType ret = E_OK;
if(status == NULL){
    return E_NOT_OK;
}else{
 *status = CCP1_IN_FLAG;
  if(*status == CCP1_READY){
   Module_INTERRUPT_ClEAR_FLAG(CCP1_FLAG_REG,CCP1_FLAG_BIT);
  }
}
return ret;
}


Std_RetuenType hal_ccp1_Comparter_WriteValue(const uint16 value){
Std_RetuenType ret = E_OK;
if(value > UINT16_MAX){
    return E_NOT_OK;
}else{
CCP1_REG_WRITE_VALUE(value); 
}
return ret;   
}


Std_RetuenType hal_ccp1_Comparter_ChooseEvent(const uint8 event){
Std_RetuenType ret = E_OK;
if(event > UINT8_MAX){
    return E_NOT_OK;
}else{
CCP1_MODE_SELECT(event);
}
return ret;     
}   

Std_RetuenType hal_ccp1_comparter_10HZ_wave(uint8 dutyPercentage){
    Std_RetuenType ret = E_OK;
    if(dutyPercentage > UINT8_MAX){
        return E_NOT_OK;
    }else{
        CCP1_INTERRUPT_HANDLER_CallBack = &comp_PWMgenrator;
        dutycycle = dutyPercentage;
    }
    return ret;
}               

#endif                        
 /****************************
  *          Captuer         *
  ****************************/
#if  (CCP1_CAPTURE_MODE)                     
Std_RetuenType hal_ccp1_IsCaptureComplete(uint8 *status){  /** Polling  */
Std_RetuenType ret = E_OK;
if(status == NULL){
    return E_NOT_OK;
}else{
 *status = CCP1_IN_FLAG;
  if(*status == CCP1_READY){
   Module_INTERRUPT_ClEAR_FLAG(CCP1_FLAG_REG,CCP1_FLAG_BIT);
  }
}
return ret;
}     

Std_RetuenType hal_ccp1_CaptuerMode_Read_Value(uint16 *value){
Std_RetuenType ret = E_OK;
if(value == NULL){
    return E_NOT_OK;
}else{
CCP1_REG_READ_VALUE(*value);
}
return ret;
}    

Std_RetuenType hal_ccp1_Choose_CaptureMode(uint8 Mode){
Std_RetuenType ret = E_OK;
if(Mode > UINT8_MAX){
 return E_NOT_OK;
}else{
CCP1_MODE_SELECT(Mode);
}
return ret;
}
#endif                        
 /****************************
  *          PWM              *
  ****************************/
#if  (CCP1_PWM_MODE)                     
Std_RetuenType hal_ccp1_PWM_DutyCycle_cfg(const uint8 dutyPercentage){
Std_RetuenType ret = E_OK;
if(dutyPercentage > UINT8_MAX){
    return E_NOT_OK;
}else{
uint16 MaxDuty   = ( PR2 + 1 ) * 4 ;
uint16 DutyValue = (uint16)(MaxDuty * (dutyPercentage / 100.0));
CCP_PWM_DUTY_CYCLE_SET(DutyValue);
}
return ret;
}

void hal_ccp1_PWM_start(void){
 CCP1_MODE_SELECT(CCP1_PWM_MODE_SELECT);
}

 void hal_ccp1_PWM_stop(void){
    CCP1_MODE_SELECT(CCP1_CAPTURE_COMAPRE_PWM_DISABLE);
}                        
#endif                        
/*****************************************
 *                ISR                    *
 *****************************************/
void CCP1_ISR(){
    Module_INTERRUPT_ClEAR_FLAG(CCP1_FLAG_REG,CCP1_FLAG_BIT);
    CCP1_INTERRUPT_HANDLER_CallBack();
}
/*****************************************
 *                ISR APP                *
 *****************************************/

void comp_PWMgenrator(){
    volatile static  uint8 stage = 0;
    TMR3L = 0;   TMR3H = 0;
    if(stage == 0){
    hal_ccp1_Comparter_WriteValue(cnt * ( 1  - ( dutycycle / 100.0)));
    stage = 1;
    }else if(stage == 1){
    hal_ccp1_Comparter_WriteValue( cnt * ( dutycycle / 100.0 ));
    stage = 0;
    }
}