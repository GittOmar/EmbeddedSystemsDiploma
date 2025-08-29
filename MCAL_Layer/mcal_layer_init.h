/*******************************************************************************
 * @file       mcal_layer_init.h
 * @brief      Driver/Module Description
 * @date       2025/08/21
 * @time       06:54
 * @author     Omar Ibrahim
 ******************************************************************************/

#ifndef mcal_layer_init_H_
#define mcal_layer_init_H_

/*****************************************
 *                 Includes              *
 *****************************************/
#include "INTERRUPT/mcal_external_interrupt.h"
#include "INTERRUPT/mcal_internal_interrupt.h"
#include "./EEPROM/./EEPROM.h"
#include "./ADC/hal_adc.h"
/*****************************************
 *           Macro Declarations          *
 *****************************************/
/*****************************************
 *        Function Declarations          *
 *****************************************/
void  my_adc_isr();
Std_RetuenType mcal_layer_initialize(void);
/*****************************************
 *               Modules                 *
 *****************************************/
 adc_cfg_t  adc_1 = {
    .acquisition_time = ADC_4_TAD,
    .adc_voltage_source = INTERNAL_VOLTAGE_SOURECE ,
    .channel = ADC_AN9,
    .clock_conversion = ADC_CONVERSION_CLK_FOSC_DIV_8
 };
adc_IN_t  adc_in = {
   .ADC_InterruptHandler = &my_adc_isr
};
/*****************************************
 *          Data Type Declarations       *
 *****************************************/

#endif /* mcal_layer_init_H_ */