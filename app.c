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
int main() {
    application_instiallize();
    while (1) {
     ret = keypad_get_coordinates(&(kp), &(value_recived));
    }
    return ret;
}


void application_instiallize(void) { 
    ecu_layer_initialize();
}


#endif /* main_H_ */