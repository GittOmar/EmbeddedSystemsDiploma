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
  void GLOBAL_INTERUPT_ENABLE();
  void GLOBAL_INTERUPT_DISABLE();
  Std_RetuenType GLOBAL_INTERRUPT_RETURN_STATE(uint8 PrevState);
/*****************************************
 *                ISR                    *
 *****************************************/
 InterruotHandler  ADC_INTERRUPT_Handdler;
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
 static Std_RetuenType ADC_choose_IN_Hdnler(const adc_cfg_t *ADC){
    Std_RetuenType ret = E_OK;
    if(ADC == NULL){
        ret = E_NOT_OK;
    }else{
        ADC_INTERRUPT_Handdler = ADC->InterruotHandler;
    }
    return ret;     
 }
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

 static void ADC_get_value_from_reg(uint16 *AnalogValue){
  *(AnalogValue)  =   (uint16)((ADC_RESULT_LSByte) & 0xFFFF);   /** 0000 0000  LSbyte  */
  *(AnalogValue) |=  ((uint16)ADC_RESULT_MSByte<<One_Byte);     /**  0000 0000  LSbyte   |   MSbyte 0000 0000 = MSB LSB  */

 }

/*****************************************
 *           function definition          *
 *****************************************/
Std_RetuenType hal_adc_init(const adc_cfg_t *ADC){
    Std_RetuenType ret  = E_OK;
    uint8 GIE_Pre_Satet = GIE_DISABLE;
    if(ADC == NULL){
        ret = E_NOT_OK;
    }else{
        GLOBAL_INTERUPT_DISABLE();            /** Turn off GIE  */
        ADC_Voltage_source(ADC);             /** Configure analog pins, voltage reference anddigital I/O (ADCON1) */
        ADC_choose_port_cfg(ADC);          /** Port CFG  */
        ADC_select_acquisition_time(ADC); /** Select A/D acquisition time (ADCON2)  */
        ADC_select_Clk_Conversion(ADC);  /**   Select A/D conversion clock  */
            RESULT_FORMATE_RIGHT_justified(); /** Value Formate  */
        ADC_choose_IN_Hdnler(ADC);      /** Interrupt Handling Function  */
        ADC_MODULE_ENABLE();           /** Turn on A/D module (ADCON0)  */
        GLOBAL_INTERRUPT_RETURN_STATE(GIE_Pre_Satet); /** Return GIE to init state  */
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
  ADC_START_CONVERSION();                                                /** Start Conversion  */
  while(ADC_CONVERSION_STATE == ADC_STILL_CONVERT ){/** Nothing  */}    /** Wait for conversion  */
  ADC_get_value_from_reg(AnalogValue);                                 /** Read Value From the Reg  */
 }
 return ret;
}
