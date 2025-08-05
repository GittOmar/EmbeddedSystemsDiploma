/*******************************************************************************
 * @file       KeyPad.c
 * @brief      keypad
 * @date       2025/08/05
 * @time       11:59
 * @author     Omar Ibrahim
 ******************************************************************************/

/*****************************************
 *                includes                *
 *****************************************/
#include "KeyPad.h"
/*****************************************
 *           function definition          *
 *****************************************/
Std_RetuenType keypad_initialize(const keypad_t *keypad){
    Std_RetuenType ret = E_OK;
    if(keypad == NULL){
        ret = E_NOT_OK;
    }else{
        /****************************
         * direction_logic_intialize *
         ****************************/
        for(uint8 row_counter = ZERO_INIT ;row_counter<ROW_NUM ;row_counter++){
            ret = gpio_pin_write_direction(&(keypad->row_pins[row_counter]),OUTPUT);
            ret = gpio_pin_write_logic(&(keypad->row_pins[row_counter]), LOW);
        }
        for(uint8 col_counetr = ZERO_INIT;col_counetr< COL_NUM;col_counetr++){
            ret = gpio_pin_write_direction(&(keypad->col_pins[col_counetr]),INPUT);
        }
    }
    return ret;
}


/**
 * @brief  coordinate recive the cordinate of pressed key in the keypad
 *         0x00 - > none key is pressed
 *         ex) 4*4 keypad coordinates
 *
 *              | 11  12  13  14 |
 *              | 21  22  23  24 |
 *              | 31  32  33  34 |
 *              | 41  42  43  44 |
 * 
 * @param keypad 
 * @param coordinates 
 * @return Std_RetuenType 
 */
Std_RetuenType keypad_get_coordinates(const keypad_t *keypad , uint8 *value){
    Std_RetuenType ret =E_OK;
    if( (keypad == NULL) || (value == NULL) ){
        ret = E_NOT_OK;
    }else{
        logic_t  col_pin_logic = LOW ;
        uint8 flag = FLAG_OFF ;
        for(uint8 row_counter = ZERO_INIT ;row_counter< ROW_NUM ;row_counter++){
            ret = gpio_pin_write_logic(&(keypad->row_pins[row_counter]), HIGH);
            for(uint8 col_counetr = ZERO_INIT ;col_counetr< COL_NUM; col_counetr++){
              ret = gpio_pin_Read_logic(&(keypad->col_pins[col_counetr]),&(col_pin_logic));
              if(col_pin_logic == HIGH){
                *value = keypad_values[row_counter][col_counetr];
                flag = FLAG_ON ;
                break;
              }
            }
            ret = gpio_pin_write_logic(&(keypad->row_pins[row_counter]), LOW);
            if(flag ==  FLAG_ON){
                break;
            }
        }
    }
    return ret ;
}