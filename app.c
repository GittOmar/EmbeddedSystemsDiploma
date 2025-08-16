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
#include "ECU_Layer/Lcd/lcd.h"
#include "ECU_Layer/ecu_layer_init.h"
/*****************************************
 *                Code                   *
 *****************************************/
int main() {
    ret = application_instiallize();
    while (1) {
      ret = lcd_print_custom_chr(&lcd, O, 1, 11, 1);
      //ret = lcd_print_custom_chr(&lcd, M, 1, 10, 2);
    // ret = lcd_print_custom_chr(&lcd, R, 1, 9, 3);
  //  lcd_print_chr_pos(&lcd, 0, 0, 'A');
    }
    return ret;
}


Std_RetuenType application_instiallize(void) { 
    ret = ecu_layer_initialize();
    return ret;
}


#endif /* main_H_ */