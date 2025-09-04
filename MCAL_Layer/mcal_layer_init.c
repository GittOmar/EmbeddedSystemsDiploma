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
    // hal_timer0_init(&(my_t));
    hal_Timer1_init(&(t1c));
   // hal_Timer1_init(&(t1c));
    return ret;
}
