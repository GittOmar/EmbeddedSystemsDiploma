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
#include "MCAL_Layer/std_types.h"
#include <builtins.h>
/*****************************************
 *                Code                   *
 *****************************************/
 uint16 cnt = 0;
/****************************
 *      ISR Functions        *
 ****************************/
void my_tt(){
//  led_turn_toggle(&(led1));
}
/****************************
 *          Main            *
 ****************************/
int main() {
    ret = application_instiallize();
    while (1) {
    hal_timer0_write_value(0);
    __delay_ms(1000);
    hal_timer0_read_value(&(cnt));
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