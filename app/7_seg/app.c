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
#include "MCAL_Layer/GPIO/hal_gpio.h"
#include "MCAL_Layer/std_types.h"
#include <builtins.h>
#define _XTAL_FREQ 8000000UL

/*****************************************
 *                Modules                *
 *****************************************/

/****************************
 *         switches          *
 ****************************/
// active high
button_t sw_1 = {{.port = PORTD_INDEX,.pin = PIN0,.direction = INPUT,.logic = LOW},
                 .button_config = BUTTON_ACTIVE_HIGH,
                 .button_state = BUTTON_RELEASED};

// active low
button_t sw_2 = {{.port = PORTB_INDEX,.pin = PIN0,.direction = INPUT,.logic = HIGH},
                 .button_config = BUTTON_ACTIVE_LOW,
                 .button_state = BUTTON_RELEASED};
/****************************
 *         leds             *
 ****************************/
led_t led_1 = {.port = PORTC_INDEX, .pin = PIN0, .status = LED_OFF};
led_t led_2 = {.port = PORTA_INDEX, .pin = PIN1, .status = LED_OFF};


/****************************
 *          relay           *
 ****************************/
relay_t relay ={.port = PORTD_INDEX , .pin = PIN0 , .state = RELAY_OFF};


/****************************
 *          motors          *
 ****************************/
 motor_t  motor_1 = {
  .in[input_1].port = PORTD_INDEX,
  .in[input_1].pin = PIN0,
  .in[input_1].direction = OUTPUT,

  .in[input_2].port = PORTD_INDEX,
  .in[input_2].pin = PIN1,
  .in[input_2].direction = OUTPUT,

  .dir_statues = NO_MOVE
 };

  motor_t  motor_2 = {
  .in[input_1].port = PORTD_INDEX,
  .in[input_1].pin = PIN2,
  .in[input_1].direction = OUTPUT,

  .in[input_2].port = PORTD_INDEX,
  .in[input_2].pin = PIN3,
  .in[input_2].direction = OUTPUT,

  .dir_statues = NO_MOVE
 };
/*****************************************
 *         User Defined Varibles         *
 *****************************************/
Std_RetuenType ret = E_NOT_OK;
button_state_t button_state_1 = BUTTON_RELEASED;
button_state_t button_state_2 = BUTTON_RELEASED;

uint8 flag    = 0x00;
uint16 counter = 500;
  

uint8 SevSeg_NUMS_commA [10] = {0x3F , 0x06 , 0x5B ,  0x4F , 0x66 , 0x6D ,0x7D , 0x07 , 0x7F ,  0x6F };
#define  SevSeg_comA(x)     SevSeg_NUMS_commA [x] // common GND
#define  SevSeg_comC(x)    ~SevSeg_NUMS_commA [x] // common VCC
uint8 num = 45, bcd_binary;
/*****************************************
 *                Code                   *
 *****************************************/
 //   0000 0001
//    0111 0000 

 int main() {

  application_instiallize();
  while (1) {
    bcd_binary = ((uint8)(num/10)) | (uint8)((num%10)<<4);
    gpio_port_write_logic(PORTC_INDEX, bcd_binary);
  }
  return ret;
}

void application_instiallize(void) {
  // /****************************
  //  *          led             *
  //  ****************************/
 // ret = led_initialize(&led_1);
  //ret = led_initialize(&led_2);
  // /****************************
  //  *          switch           *
  //  ****************************/
  // ret = button_intialize(&sw_1);
  // ret = button_intialize(&sw_2);
  // /****************************
  //  *          relay            *
  //  ****************************/
  // ret = relay_intialize(&relay);
  // /****************************
  //  *          motor            *
  //  ****************************/
  // ret = motor_pin_intialize(&motor_1);
  // ret = motor_pin_intialize(&motor_2);
  /****************************
   *     7Seg_com_Cathode     *
   ****************************/
   gpio_port_direction_intialize(PORTC_INDEX, 0x00);
  //gpio_port_direction_intialize(PORTD_INDEX, 0x80);
}


#endif /* main_H_ */