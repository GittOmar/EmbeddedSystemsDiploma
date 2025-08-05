/*******************************************************************************
 * @file       H_Bridge.c
 * @brief      Driver/Module Description
 * @date       2025/07/17
 * @time       17:53
 * @author     Omar Ibrahim
 ******************************************************************************/
#include "./H_Bridge.h"

/** @note  for this line  ->   static pin_config_t IN_1 ,  IN_2;  
*1- statics for private usage 
*2- gloabal to be seen for all functions here in H_Bridge.c
** @problem 
*1- satic varibles if used in functions make them store in flash so if called again overwrite will hapen 
*/
// static pin_config_t IN_1 ,  IN_2;  


/**
 * @brief intialize the motor pins using struct motor 
 * 
 * @param motor 
 * @return Std_RetuenType 
 */
Std_RetuenType motor_pin_intialize(motor_t *motor){
Std_RetuenType  ret = E_OK ;
if(motor == NULL){
    ret = E_NOT_OK;
}else {

/****************************
 *       pins matching      *
 ****************************/    

ret = gpio_pin_direction_intialize(&motor->in[input_1]);
ret = gpio_pin_direction_intialize(&motor->in[input_2]);

/****************************
 *       intial state       *
 ****************************/
switch(motor->dir_statues){
  case FORWARD : 
  motor_move_forward(motor);
  break;

  case BACKWARD : 
  motor_move_backward(motor);
  break;

  case NO_MOVE : 
  motor_no_move(motor);
  break;
 
  default : 
  ret = E_NOT_OK;
  break;
}
}
return ret ;
}


/**
 * @brief motor_STOP
 * 
 * @param motor 
 * @return Std_RetuenType 
 */
Std_RetuenType motor_no_move(motor_t *motor){
Std_RetuenType  ret = E_OK ;
if(motor == NULL){
    ret = E_NOT_OK;
}else {
ret = gpio_pin_write_logic(&motor->in[input_1], input_1_S);
ret = gpio_pin_write_logic(&motor->in[input_2], input_2_S);
motor->dir_statues = NO_MOVE ;
}
return ret ;
}



/**
 * @brief motor_FORWARD
 * 
 * @param motor 
 * @return Std_RetuenType 
 */
Std_RetuenType motor_move_forward(motor_t *motor){
Std_RetuenType  ret = E_OK ;
if(motor == NULL){
    ret = E_NOT_OK;
}else {
ret = gpio_pin_write_logic(&motor->in[input_1], input_1_F);
ret = gpio_pin_write_logic(&motor->in[input_2], input_2_F);
motor->dir_statues = FORWARD ;
}
return ret ;
}


/**
 * @brief motor_BACKWARD
 * 
 * @param motor 
 * @return Std_RetuenType 
 */
Std_RetuenType motor_move_backward(motor_t *motor){
    Std_RetuenType  ret = E_OK ;
if(motor == NULL){
    ret = E_NOT_OK;
}else {
ret = gpio_pin_write_logic(&motor->in[input_1], input_1_B);
ret = gpio_pin_write_logic(&motor->in[input_2], input_2_B);
motor->dir_statues = BACKWARD ;
}
return ret ;
}

