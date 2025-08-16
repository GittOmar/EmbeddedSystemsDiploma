/*******************************************************************************
 * @file       lcd.c
 * @brief      Driver/Module Description
 * @date       2025/08/12
 * @time       15:20
 * @author     Omar Ibrahim
 ******************************************************************************/

/*****************************************
 *                includes                *
 *****************************************/
#include "lcd.h"
/*****************************************
 *           Interfaceing function       *
 *****************************************/
Std_RetuenType lcd_inintialize(const lcd_t *lcd){
    Std_RetuenType ret = E_OK;
    if(lcd == NULL){
        ret = E_NOT_OK;
    }else{
    /****************************
     *    intializing pins      *
     ****************************/
    ret = gpio_pin_write_direction(&(lcd->RS),OUTPUT);
    ret = gpio_pin_write_logic(&(lcd->RS),LOW);

    ret = gpio_pin_write_direction(&(lcd->E),OUTPUT);
    ret = gpio_pin_write_logic(&(lcd->E),LOW);

    for(uint8 wire = ZERO_INIT; wire <LCD_BIT_MODE; wire++){
     ret = gpio_pin_write_direction(&(lcd->data_bus[wire]),OUTPUT);
     ret = gpio_pin_write_logic(&(lcd->data_bus[wire]),LOW);
    }
    /****************************
     *    intializing sequance  *
     ****************************/
    __delay_ms(15);
    ret = lcd_send_command(lcd, LCD_2_LINE_COMMAND);
    __delay_ms(5);
    ret = lcd_send_command(lcd, LCD_2_LINE_COMMAND);
    __delay_us(150);
    ret = lcd_send_command(lcd, LCD_2_LINE_COMMAND);
    /****************************
     * intializing environment  *
     ****************************/
    ret = lcd_send_command(lcd,LCD_CLEAR_DISPLAY);
    ret = lcd_send_command(lcd,LCD_CURSOR_HOME);
    ret = lcd_send_command(lcd, LCD_ENTRY_MODE_INC_SHIFT_OFF);
    ret = lcd_send_command(lcd,LCD_BLOCK_CURSOR_OFF_UNDERLINE_CURSOR_OFF);
    }
 return ret;
}

Std_RetuenType lcd_send_command(const lcd_t *lcd, uint8 command){
    Std_RetuenType ret = E_NOT_OK;
    if(lcd == NULL){
        ret = E_NOT_OK;
    }else{
        ret = gpio_pin_write_logic(&(lcd->RS), INSTRUCTION_LOGIC);
        #if (LCD_BIT_MODE == _4BIT_MODE)
        ret = send_nipple(lcd, command>>4);
        ret = send_enable_signal(lcd);
        ret = send_nipple(lcd, command);
        ret = send_enable_signal(lcd);
        #endif
        #if (LCD_BIT_MODE == _8BIT_MODE)
        ret = send_byte(lcd, command);
        ret = send_enable_signal(lcd);
        #endif
    }
    return ret;
}

Std_RetuenType lcd_print_chr(const lcd_t *lcd, uint8 character){
    Std_RetuenType ret = E_NOT_OK;
    if(lcd == NULL){
        ret = E_NOT_OK;
    }else{
        ret = gpio_pin_write_logic(&(lcd->RS), DATA_LOGIC);
        #if (LCD_BIT_MODE == _4BIT_MODE)
        ret = send_nipple(lcd, character>>4);
        ret = send_enable_signal(lcd);
        ret = send_nipple(lcd, character);
        ret = send_enable_signal(lcd);
        #endif
        #if (LCD_BIT_MODE == _8BIT_MODE)
        ret = send_byte(lcd, character);
        ret = send_enable_signal(lcd);
        #endif
    }
    return ret;
}

Std_RetuenType lcd_print_chr_pos(const lcd_t *lcd, uint8 row, uint8 col, uint8 character){
    Std_RetuenType ret = E_OK;
    if((lcd == NULL) || (row > LCD_ROW) || (col>LCD_COL)){
        ret = E_NOT_OK;
    }else{
     ret = lcd_set_cursor(lcd, row, col);
     ret = lcd_print_chr(lcd, character);
    }
    return ret;
}

Std_RetuenType lcd_print_string(const lcd_t *lcd, uint8 *string){
    Std_RetuenType ret = E_NOT_OK;
    if((lcd == NULL) || (string == NULL)){
        ret = E_NOT_OK;
    }else{
        while(*string != '\0'){
            lcd_print_chr(lcd, *string);
            string++;
        }
    }
    return ret;
}

Std_RetuenType lcd_print_string_pos(const lcd_t *lcd, uint8 row, uint8 col, uint8 *string){
      Std_RetuenType ret = E_OK;
    if((lcd == NULL) || (row > LCD_ROW) || (col>LCD_COL)){
        ret = E_NOT_OK;
    }else{
     ret = lcd_set_cursor(lcd, row, col);
     ret = lcd_print_string(lcd, string);
    }
    return ret;
}


Std_RetuenType lcd_print_custom_chr(const lcd_t *lcd, const uint8 chr[],uint8 row, uint8 col ,uint8 mem_pos){
    Std_RetuenType ret =E_OK;
    if((lcd == NULL) || (mem_pos > _8BIT_MAX) || (mem_pos > 8) || (mem_pos < 1)){
        ret =E_NOT_OK;
    }else{
        ret = lcd_send_command(lcd, LCD_CGRAM_START + ((mem_pos-1)*8));
        for(uint8 cnt = ZERO_INIT ; cnt<8;cnt++){
            ret = lcd_print_chr(lcd,chr[cnt] );
        }
        ret = lcd_print_chr_pos(lcd, row, col, mem_pos -1);
    }
    return ret;
}
/*****************************************
 *    uint to string function convert    *
 *****************************************/
Std_RetuenType convert_uint8_to_str(uint8 value, uint8 *str){
    Std_RetuenType ret = E_OK;
    if((value > _8BIT_MAX) ||  (str == NULL)){
        ret =E_NOT_OK;
    }else{
        snprintf((char*)str, 4, "%u", (unsigned int)value);
    }
    return ret;
}

Std_RetuenType convert_uint16_to_str(uint16 value, uint8 *str){
    Std_RetuenType ret = E_OK;
    if((value > _16BIT_MAX) ||  (str == NULL)){
        ret =E_NOT_OK;
    }else{
        snprintf((char*)str, 6, "%u", (unsigned int)value);
    }
    return ret;
}

Std_RetuenType convert_uint32_to_str(uint32 value, uint8 *str){
   Std_RetuenType ret = E_OK;
    if((value > _32BIT_MAX) ||  (str == NULL)){
        ret =E_NOT_OK;
    }else{
        snprintf((char*)str, 11, "%u", (unsigned int)value);
    }
    return ret;  
}
/*****************************************
 *             helper funtions           *
 *****************************************/
static Std_RetuenType send_nipple(const lcd_t *lcd, uint8 command){
    Std_RetuenType ret = E_NOT_OK;
    if(lcd == NULL){
        ret = E_NOT_OK;
    }else{
    for(uint8 wire = ZERO_INIT; wire <LCD_BIT_MODE ; wire++){
      ret = gpio_pin_write_logic(&(lcd->data_bus[wire]), READ_BIT(command, wire));
    }        
    }
    return ret ;
}

static Std_RetuenType send_byte(const lcd_t *lcd, uint8 command){
    Std_RetuenType ret = E_NOT_OK;
    if(lcd == NULL){
        ret = E_NOT_OK;
    }else{
    for(uint8 wire = ZERO_INIT; wire <LCD_BIT_MODE ; wire++){
      ret = gpio_pin_write_logic(&(lcd->data_bus[wire]), READ_BIT(command, wire));
    }        
    }
    return ret ;
}

static Std_RetuenType send_enable_signal(const lcd_t *lcd){
      Std_RetuenType ret = E_NOT_OK;
    if(lcd == NULL){
        ret = E_NOT_OK;
    }else{
    ret = gpio_pin_write_logic(&(lcd->E), HIGH);
    __delay_us(5);        
    ret = gpio_pin_write_logic(&(lcd->E), LOW);
    }
    return ret;
}

static Std_RetuenType lcd_set_cursor(const lcd_t *lcd, uint8 row, uint8 col){
    Std_RetuenType ret = E_OK;
    if((lcd == NULL) || (row > LCD_ROW) || (col>LCD_COL)){
        ret = E_NOT_OK;
    }else{
        switch (row) {
        case ROW1 : ret = lcd_send_command(lcd, LCD_DDRAM_ROW1 + col); break;
        case ROW2 : ret = lcd_send_command(lcd, LCD_DDRAM_ROW2 + col); break;
        case ROW3 : ret = lcd_send_command(lcd, LCD_DDRAM_ROW3 + col); break;
        case ROW4 : ret = lcd_send_command(lcd, LCD_DDRAM_ROW4 + col); break;
        default: ret = E_NOT_OK;
        }
    }
    return ret;
}