/*******************************************************************************
 * @file       mcal_layer_init.c
 * @brief      Driver/Module Description
 * @date       2025/08/21
 * @time       06:55
 * @author     Omar Ibrahim
 ******************************************************************************/

/*****************************************
 *                includes                *
 *****************************************/
#include "mcal_layer_init.h"
/*****************************************
 *           function definition          *
 *****************************************/
Std_RetuenType mcal_layer_initialize(void){
    Std_RetuenType ret = E_OK;
    hal_adc_init(&(adc_1));
    // ADC_INTERRUPT_INIT(&(adc_in));
    return ret;
}
