/*******************************************************************************
 * @file       ecu_relay.h
 * @brief      Driver/Module Description
 * @date       2025/07/16
 * @time       18:11
 * @author     Omar Ibrahim
 ******************************************************************************/

#ifndef ecu_relay_H_
#define ecu_relay_H_

/*****************************************
 *                 Includes              *
 *****************************************/
#include "../../MCAL_Layer/./GPIO/hal_gpio.h"
#include "ecu_relay_cfg.h"
/*****************************************
 *           Macro Declarations          *
 *****************************************/
#define RELAY_CONFIG   0x01
/*****************************************
 *       Macro Function Declarations     *
 *****************************************/

/*****************************************
 *          Data Type Declarations       *
 *****************************************/
typedef enum{
RELAY_OFF,
RELAY_ON
}relay_state_t;


typedef struct{
uint8 port      : 3 ;
uint8 pin       : 3 ;
uint8 state     : 1 ;
uint8 reserved  : 1 ;
}relay_t;
/*****************************************
 *        Function Declarations          *
 *****************************************/
 Std_RetuenType relay_intialize(relay_t *relay);
 Std_RetuenType relay_turn_on(relay_t *relay);
 Std_RetuenType relay_turn_off(relay_t *relay);
#endif /* ecu_relay_H_ */