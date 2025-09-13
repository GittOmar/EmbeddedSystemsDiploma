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
volatile void comp_PWMgenrator(void);                  

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
     hal_ccp1_comparter_10HZ_wave(64);
    while (1) {

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