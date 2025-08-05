/*******************************************************************************
 * @file       KeyPad.h
 * @brief      keypad driver
 *             1 key pressed once
 * @date       2025/08/05
 * @time       11:59
 * @author     Omar Ibrahim
 ******************************************************************************/

#ifndef KeyPad_H_
#define KeyPad_H_

/*****************************************
 *                 Includes              *
 *****************************************/
#include "./../../MCAL_Layer/GPIO/hal_gpio.h"
/*****************************************
 *           Macro Declarations          *
 *****************************************/
#define ROW_NUM    4
#define COL_NUM    4

#define FLAG_ON           0x01
#define FLAG_OFF       0x00
/*****************************************
 *          User Defined Varible         *
 *****************************************/
uint8 keypad_values[ROW_NUM][COL_NUM] = {
{'7' , '8' ,'9' ,'/'},
{'4' , '5' ,'6' ,'*'},
{'1' , '2' ,'3' ,'-'},
{'C' , '0' ,'=' ,'+'}
};

/*****************************************
 *          Data Type Declarations       *
 *****************************************/
typedef struct{
    pin_config_t row_pins[ROW_NUM];
    pin_config_t col_pins[ROW_NUM];
}keypad_t;

/*****************************************
 *        Function Declarations          *
 *****************************************/
Std_RetuenType keypad_initialize(const keypad_t *keypad);
Std_RetuenType keypad_get_coordinates(const keypad_t *keypad , uint8 *value);
#endif /* KeyPad_H_ */