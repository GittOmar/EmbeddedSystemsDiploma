/*******************************************************************************
 * @file       ecu_layer_init.c
 * @brief      Driver/Module Description
 * @date       2025/08/05
 * @time       13:57
 * @author     Omar Ibrahim
 ******************************************************************************/

/*****************************************
 *                includes                *
 *****************************************/
#include"ecu_layer_init.h"
/*****************************************
 *           function definition          *
 *****************************************/
Std_RetuenType ecu_layer_initialize(){
     Std_RetuenType ret = E_OK;
     ret &= led_initialize(&led);
     return ret;
}
