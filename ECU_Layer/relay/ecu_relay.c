/*******************************************************************************
 * @file       ecu_relay.c
 * @brief      Driver/Module Description
 * @date       2025/07/16
 * @time       18:17
 * @author     Omar Ibrahim
 ******************************************************************************/

#include "ecu_relay.h"

/**
 * @brief intialize the replay pin the mc
 * 
 * @param relay 
 * @return Std_RetuenType 
 */
 #if RELAY_CONFIG == RELAY_ENABLE 
 Std_RetuenType relay_intialize(relay_t *relay){
   uint8 ret = E_OK;
   if(relay == NULL){
    ret = E_NOT_OK ;
   }else{
    pin_config_t  pin_config = {.pin =relay->pin , .port =relay->port ,.direction = OUTPUT};
    ret = gpio_pin_direction_intialize(&pin_config);
    if(relay->state == RELAY_ON){
        ret = relay_turn_on(relay);
    }else {
       ret = relay_turn_off(relay);
    }
   }
   
  return ret;
 }
 #endif
 


 /**
  * @brief comm connected to Normaly Open
  * 
  * @param relay 
  * @return Std_RetuenType 
  */
 #if RELAY_CONFIG == RELAY_ENABLE 
 Std_RetuenType relay_turn_on(relay_t *relay){
 uint8 ret = E_OK ;
 if(relay == NULL){
    ret = E_NOT_OK;
 }else{
    pin_config_t  pin_config = {.pin =relay->pin , .port =relay->port ,.direction = OUTPUT};
    ret = gpio_pin_write_logic(&pin_config, HIGH);
    relay->state = RELAY_ON ;
 }
 return ret;
 }
 #endif


/**
 * @brief connect the comm with the Normaly Colsed
 * 
 * @param relay 
 * @return Std_RetuenType 
 */
 #if  RELAY_CONFIG == RELAY_ENABLE
 Std_RetuenType relay_turn_off(relay_t *relay){
    uint8 ret = E_OK ;
 if(relay == NULL){
    ret = E_NOT_OK;
 }else{
    pin_config_t  pin_config = {.pin =relay->pin , .port =relay->port ,.direction = OUTPUT };
    ret = gpio_pin_write_logic(&pin_config, LOW);
    relay->state = RELAY_OFF ;
 }
 return ret;
 }
 #endif





