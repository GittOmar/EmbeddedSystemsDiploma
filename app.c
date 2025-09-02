/*******************************************************************************
 * @file       main.c
 * @brief      Driver/Module Description
 * @date       2025/07/12
 * @time       11:01
 * @author     Omar Ibrahim
 ******************************************************************************/

#ifndef main_H_
#define main_H_

/*****************************************
 *                Includes               *
 *****************************************/
#include "app.h"
/*****************************************
 *                Code                   *
 *****************************************/
/****************************
 *      ISR Functions        *
 ****************************/
void my_adc_isr(){
led_turn_toggle(&(led1));
__delay_ms(1000);
}
/****************************
 *          Main            *
 ****************************/
int main() {
    ret = application_instiallize();

    while (1) {
        hal_adc_read_analog_pin(&(adc_1), ADC_AN0, &(Value));

        voltage = (float)Value * 4.77 / 1023.0;
        voltage_a = (uint8)voltage;
        voltage_b = (uint8)((voltage - (float)voltage_a)*100.0);

        lcd_print_string_pos(&(view), 0, 0, "Voltage =  ");

        convert_uint8_to_str(voltage_a , pa);
        lcd_print_string(&(view), pa);  
        lcd_print_chr(&(view), '.');
       convert_uint8_to_str(voltage_b , pb);
        lcd_print_string(&(view), pb);

        __delay_ms(200);
        lcd_clear_display(&(view));
           
    }
    return ret;
}
/****************************
 *          Init            *
 ****************************/
Std_RetuenType application_instiallize(void) { 
   ret &= ecu_layer_initialize();
   ret &= mcal_layer_initialize();
   return ret;
}

#endif /* main_H_ */