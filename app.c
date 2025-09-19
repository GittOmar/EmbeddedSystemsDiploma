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
#include "ECU_Layer/led/led.h"
#include "MCAL_Layer/EUSART/eusart.h"
#include <builtins.h>

/*****************************************
 *                Code                   *
 *****************************************/

/****************************
 *      ISR Functions        *
 ****************************/
void my_t2(){
    

}



/****************************
 *          Main            *
 ****************************/
int main() {
    ret = application_instiallize();
    while (1) {
        hal_EUSART_NON_BLOCKING_READ(&(tr), &value);
        if(value == 'T'){
        led_turn_toggle(&(led));  
        hal_EUSART_NON_BLOCKING_WRITE(&(tr), 'R');
        value = 0 ;
        }
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