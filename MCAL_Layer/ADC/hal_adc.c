/*******************************************************************************
 * @file       hal_adc.c
 * @brief      Driver/Module Description
 * @date       2025/08/28
 * @time       20:38
 * @author     Omar Ibrahim
 ******************************************************************************/

/*****************************************
 *                includes                *
 *****************************************/
#include "hal_adc.h"
/*****************************************
 *             Function Declare           *
 *****************************************/
  void GLOBAL_INTERUPT_DISABLE();
  Std_RetuenType GLOBAL_INTERRUPT_RETURN_STATE(uint8 PrevState);

  Std_RetuenType Module_INTERRUPT_ClEAR_FLAG(uint8 Reg,uint8 bit_pos);
  InterruotHandler  ADC_InterruptHandler;

void     ADC_INTERRUPT_INIT(priority_t adc_priority);
void     ADC_INTERRUPT_DEINIT(void);
/*****************************************
 *             Helper Functions          *
 *****************************************/
 static Std_RetuenType ADC_Voltage_source(const adc_cfg_t *ADC){
    Std_RetuenType ret = E_OK;
    if(ADC == NULL){
        ret = E_NOT_OK;
    }else{
        switch (ADC->adc_voltage_source) {
        case INTERNAL_VOLTAGE_SOURECE  :   ADC_Vref_VssVDD();                break;
        case EXTERNAL_VOLTAGE_SOURECE  :   ADC_Vref_EXTERNAL_SOURCE();       break;
        default: ret = E_NOT_OK;
        };
    }
    return ret;
 }
 static Std_RetuenType ADC_select_Chx(const adc_cfg_t *ADC){
    Std_RetuenType ret = E_OK;
    if(ADC == NULL){
        ret = E_NOT_OK;
    }else{
       ADC_CH_SELECT(ADC->channel);
    }
    return ret; 
 }
 static Std_RetuenType ADC_select_acquisition_time(const adc_cfg_t *ADC){
     Std_RetuenType ret = E_OK;
    if(ADC == NULL){
        ret = E_NOT_OK;
    }else{
       ADC_acquisition_time(ADC->acquisition_time);
    }
    return ret; 
 }
 static Std_RetuenType ADC_select_Clk_Conversion(const adc_cfg_t *ADC){
    Std_RetuenType ret = E_OK;
    if(ADC == NULL){
        ret = E_NOT_OK;
    }else{
       ADC_Clk_Conversion(ADC->clock_conversion);
    }
    return ret;   
 }
#if  (ADC_IN_ENABLE)                     
 static Std_RetuenType ADC_choose_IN_Hdnler(const adc_cfg_t *ADC){
    Std_RetuenType ret = E_OK;
    if(ADC == NULL){
        ret = E_NOT_OK;
    }else{
        ADC_InterruptHandler = ADC->ADC_IN_Handler;
    }
    return ret;     
 }                             
#endif                        
  /**      
           12  11  10  9   8   7   6   5   4   3   2   1   0  
(0)  0000  A   A   A   A   A   A   A   A   A   A   A   A   A
(1)  0001  A   A   A   A   A   A   A   A   A   A   A   A   A
(2)  0010  A   A   A   A   A   A   A   A   A   A   A   A   A
(3)  0011  D   A   A   A   A   A   A   A   A   A   A   A   A
(4)  0100  D   D   A   A   A   A   A   A   A   A   A   A   A
(5)  0101  D   D   D   A   A   A   A   A   A   A   A   A   A
(6)  0110  D   D   D   D   A   A   A   A   A   A   A   A   A
(7)  0111  D   D   D   D   D   A   A   A   A   A   A   A   A
(8)  1000  D   D   D   D   D   D   A   A   A   A   A   A   A
(9)  1001  D   D   D   D   D   D   D   A   A   A   A   A   A
(10) 1010  D   D   D   D   D   D   D   D   A   A   A   A   A
(11) 1011  D   D   D   D   D   D   D   D   D   A   A   A   A
(12) 1100  D   D   D   D   D   D   D   D   D   D   A   A   A
(13) 1101  D   D   D   D   D   D   D   D   D   D   D   A   A
(14) 1110  D   D   D   D   D   D   D   D   D   D   D   D   A
(15) 1111  D   D   D   D   D   D   D   D   D   D   D   D   D 
 */
 static Std_RetuenType ADC_choose_port_cfg(const adc_cfg_t *ADC){
    Std_RetuenType ret = E_OK;
    if(ADC == NULL){
        ret = E_NOT_OK;
    }else{
        ADC_PORT_AB_ANALOG_DIGITAL_CFG(SubtractionCOff - (uint8)ADC->channel);
    }
    return ret;     
 }
 static inline void ADC_get_value_from_reg(uint16 *AnalogValue){
     *(AnalogValue) = (uint16)((ADC_RESULT_MSByte<<One_Byte) + ADC_RESULT_LSByte);
 }
 static inline void ADC_Pin_Input_switch(adc_channel_t UsedChannel){
    switch (UsedChannel) {
    case ADC_AN0:SET_BIT(TRISA,    0 ); break;
    case ADC_AN1:SET_BIT(TRISA,    1 ); break;
    case ADC_AN2:SET_BIT(TRISA,    2 ); break;
    case ADC_AN3:SET_BIT(TRISA,    3 ); break;
    case ADC_AN4:SET_BIT(TRISA,    5 ); break;
    case ADC_AN5:SET_BIT(TRISE,    5 ); break;
    case ADC_AN6:SET_BIT(TRISE,    6 ); break;
    case ADC_AN7:SET_BIT(TRISE,    7 ); break;
    case ADC_AN8:SET_BIT(TRISB,    2 ); break;
    case ADC_AN9:SET_BIT(TRISB,    3 ); break;
    case ADC_AN10:SET_BIT(TRISB,   1 ); break;
    case ADC_AN11:SET_BIT(TRISB,   4 ); break;
    case ADC_AN12:SET_BIT(TRISB,   0 ); break;
    }
 }
/*****************************************
 *           function definition          *
 *****************************************/
Std_RetuenType hal_adc_init(const adc_cfg_t *ADC){
    Std_RetuenType ret  = E_OK;
    uint8 GIE_Pre_Satet = GIE_DISABLE;

    #if  (PERIORITY_ENABLE && ADC_IN_ENABLE)                     
    priority_t priority = ADC->ADC_priority;                            
    #else
    priority_t priority;                        
    #endif     

    if(ADC == NULL){
        ret = E_NOT_OK;
    }else{
        GLOBAL_INTERUPT_DISABLE();            /** Turn off GIE  */
        ADC_Voltage_source(ADC);             /** Configure analog pins, voltage reference anddigital I/O (ADCON1) */
        ADC_choose_port_cfg(ADC);          /** Port CFG  */
        ADC_select_acquisition_time(ADC); /** Select A/D acquisition time (ADCON2)  */
        ADC_select_Clk_Conversion(ADC);  /**   Select A/D conversion clock  */
        RESULT_FORMATE_RIGHT_justified(); /** Value Formate  */
        #if  (ADC_IN_ENABLE)                     
        ADC_choose_IN_Hdnler(ADC);      /** Interrupt Handling Function linkage*/                             
        #endif                        
        ADC_MODULE_ENABLE();           /** Turn on A/D module (ADCON0)  */
        GLOBAL_INTERRUPT_RETURN_STATE(GIE_Pre_Satet); /** Return GIE to init state  */

        #if  (ADC_IN_ENABLE)                     
        ADC_INTERRUPT_INIT(priority);           /** interupt init  */
        #endif                        
    }
    return ret;
}
Std_RetuenType hal_adc_deinit(const adc_cfg_t *ADC){
    Std_RetuenType ret  = E_OK;
    uint8 GIE_Pre_Satet = GIE_DISABLE;
    if(ADC == NULL){
        ret = E_NOT_OK;
    }else{
     ADC_MODULE_DISABLE();
    }
    return ret;    
}
Std_RetuenType hal_adc_read_analog_pin(const adc_cfg_t *ADC,adc_channel_t UsedChannel,uint16 *AnalogValue){
 Std_RetuenType ret = E_OK;
 if((ADC == NULL) || (AnalogValue == NULL)){
    ret = E_NOT_OK;
 }else{   
  ADC_CH_SELECT(UsedChannel);                                             /** MUX Selext Specific Channel  */
  ADC_Pin_Input_switch(UsedChannel);                                      /** Switch Into Input  */
  ADC_START_CONVERSION();                                                /** Start Conversion  */
  while(ADC_CONVERSION_STATE == ADC_STILL_CONVERT ){/** Nothing  */}    /** Wait for conversion  */
  ADC_get_value_from_reg(AnalogValue);                                 /** Read Value From the Reg  */
 }
 return ret;
}
/*****************************************
 *                ISR                    *
 *****************************************/
 #if  (ADC_IN_ENABLE)                     
 void ADC_ISR(){
   Module_INTERRUPT_ClEAR_FLAG(ADC_FLAG_REG,ADC_FLAG_BIT);               // flag clear
   ADC_InterruptHandler();
 }                              
 #endif                        
