/*******************************************************************************
 * @file       SevSeg.c
 * @brief      7seg module for Single Piece
 * @date       2025/08/04
 * @time       09:04
 * @author     Omar Ibrahim
 ******************************************************************************/

/*****************************************
 *                includes                *
 *****************************************/
#include "SevSeg.h"
/*****************************************
 *           function defnition           *
 *****************************************/

/**
 * @brief seg dir logic intillization 
 * 
 * @param seg 
 * @return Std_RetuenType 
 */
Std_RetuenType sev_seg_intialize(const sev_seg_t* seg) {
    Std_RetuenType ret = E_OK;
    if (seg == NULL) {
        E_NOT_OK;
    } else {
        /****************************
         *      dir initalize       *
         ****************************/
        for (uint8 i = 0; i < 4; i++) {
            ret = gpio_pin_write_direction(&(seg->pin[i]), OUTPUT);
        }
        /****************************
         *     logic intialize      *
         ****************************/
        for (uint8 i = 0; i < 4; i++) {
            ret = gpio_pin_write_logic(&(seg->pin[i]), LOW);
        }

    }
    return ret;
}

/**
 * @brief  write number on seg
 * 
 * @param seg 
 * @param number 
 * @return Std_RetuenType 
 */
Std_RetuenType sev_seg_write_num(const sev_seg_t* seg, uint8 number) {
    Std_RetuenType ret = E_OK;
    if ( (seg == NULL) || (number > 9) ) {
        ret = E_NOT_OK;
    } else {
        for (uint8 i = 0; i < 4; i++) {
            if (READ_BIT(number, i) == 1) {
                gpio_pin_write_logic(&(seg->pin[i]), HIGH);
            } else {
                gpio_pin_write_logic(&(seg->pin[i]), LOW);
            }
        }
    }
    return ret;
}