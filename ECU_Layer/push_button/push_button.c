/*
 * File:   push button.c
 * Author: pc
 *
 * Created on July 5, 2025, 5:18 PM
 */

 
#include "./push_button.h"


/**
 * @brief
 *
 * @param button
 * @return Std_RetuenType
 */
Std_RetuenType button_intialize(const button_t *button) {
  Std_RetuenType ret = E_OK;
  if (button == NULL) {
    ret = E_NOT_OK;
  } else {
    ret &= gpio_pin_direction_intialize(&button->pin_cfg);
  }
  return ret;
}

/**
 * @brief
 *
 * @param button
 * @param button_state
 * @return Std_RetuenType
 */
Std_RetuenType button_read_state(const button_t *button,
                                 button_state_t *button_state) {
  Std_RetuenType ret = E_OK;
  logic_t pin_logic = LOW; // pin logic is 4 byte enum

  if ( (button == NULL) || (button_state == NULL) ) {
    ret = E_NOT_OK;
  } else {

    ret = gpio_pin_Read_logic(&(button->pin_cfg),&pin_logic);
    


    if(button->button_config == BUTTON_ACTIVE_HIGH){
      if(pin_logic == HIGH){
        *button_state = BUTTON_PRESSED;
      }else{
        *button_state = BUTTON_RELEASED;
      }
    }else{
        if(pin_logic == HIGH){
        *button_state = BUTTON_RELEASED;
      }else{
        *button_state = BUTTON_PRESSED;
      }
    }
  }

  return ret;
}

Std_RetuenType button_read_state_BS(const button_t *button, button_state_t *button_state){

/*****************************************
 *            varible  defintion          *
 *****************************************/
 Std_RetuenType ret = E_OK;
 button_state_t inst_state = BUTTON_RELEASED ;  
 uint32 cnt   = 0 ;
 uint32 timer = 0 ; 


 while(timer != period){
  ret = button_read_state(button, &inst_state);
  if(inst_state == BUTTON_PRESSED){
        cnt++;
        if(cnt > threshold){
            *button_state = BUTTON_PRESSED;
        }
        }else{
           cnt = 0;
           *button_state = BUTTON_RELEASED;
  }
  timer++;
}

return ret;
}

Std_RetuenType buttont_does_state_changes(const button_t *button , uint32* within_counter , uint8 *flag){

Std_RetuenType ret = E_OK ;
button_state_t intial_state = BUTTON_RELEASED;
button_state_t read_state  = BUTTON_RELEASED;
*flag = 0x00;

ret = button_read_state(button, &intial_state);
while((*within_counter)-- ){
ret = button_read_state(button, &read_state);
if(read_state != intial_state){
*flag = 0x01;
break;
}
}
return ret;
}