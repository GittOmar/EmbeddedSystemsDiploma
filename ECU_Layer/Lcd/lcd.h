/*******************************************************************************
 * @file       lcd.h
 * @brief      Driver/Module Description
 * @date       2025/08/12
 * @time       15:20
 * @author     Omar Ibrahim
 ******************************************************************************/

#ifndef lcd_H_
#define lcd_H_

/*****************************************
 *                 Includes              *
 *****************************************/
#include "./../../MCAL_Layer/GPIO/hal_gpio.h"
#include "lcd_cfg.h"
#include <math.h>
/*****************************************
 *           Macro Declarations          *
 *****************************************/
/****************************
 *     Screen Settings      *
 ****************************/
#define LCD_CLEAR_DISPLAY                             0x01
#define LCD_CURSOR_HOME                               0x02
/****************************
 *         Entry Mode       *
 ****************************/
#define LCD_ENTRY_MODE_DEC_SHIFT_OFF                  0x04
#define LCD_ENTRY_MODE_DEC_SHIFT_ON                   0x05
#define LCD_ENTRY_MODE_INC_SHIFT_OFF                  0x06
#define LCD_ENTRY_MODE_INC_SHIFT_ON                   0x07
/****************************
 * Move Cursor & Shift Displa *
 ****************************/              
#define LCD_CURSOR_MOVE_SHIFT_LEFT                    0x10
#define LCD_CURSOR_MOVE_SHIFT_RIGHT                   0x14
#define LCD_DISPLAY_SHIFT_RIGHT                       0x18
#define LCD_DISPLAY_SHIFT_LEFT                        0x1C
/****************************
 *     Cursor settings      *
 ****************************/
#define LCD_DISPLAY_OFF                               0x08             
#define LCD_BLOCK_CURSOR_OFF_UNDERLINE_CURSOR_OFF     0x0C
#define LCD_BLOCK_CURSOR_ON_UNDERLINE_CURSOR_OFF      0x0D
#define LCD_BLOCK_CURSOR_OFF_UNDERLINE_CURSOR_ON      0x0E
#define LCD_BLOCK_CURSOR_ON_UNDERLINE_CURSOR_ON       0x0F
/****************************
 *   Memory Start Address   *
 ****************************/
#define LCD_CGRAM_START                               0x40

#define LCD_DDRAM_ROW1                                0x80
#define LCD_DDRAM_ROW2                                0xC0
#define LCD_DDRAM_ROW3                                0x94
#define LCD_DDRAM_ROW4                                0xD4
/****************************
 *          Other           *
 ****************************/
#define ROW1                                           0
#define ROW2                                           1
#define ROW3                                           2
#define ROW4                                           3

#define INSTRUCTION_LOGIC             0x00
#define DATA_LOGIC                    0x01

#define NULL_TERMINATION               '\0'

#define _XTAL_FREQ 8000000UL
/*****************************************
 *       Macro Function Declarations     *
 *****************************************/
/*****************************************
 *          Data Type Declarations       *
 *****************************************/
typedef struct {
pin_config_t RS,E;
pin_config_t data_bus[LCD_BIT_MODE]; 
}lcd_t;
/*****************************************
 *        Function Declarations          *
 *****************************************/
Std_RetuenType lcd_inintialize(const lcd_t *lcd);
Std_RetuenType lcd_clear_display(const lcd_t *lcd);

Std_RetuenType lcd_send_command(const lcd_t *lcd, uint8 command);
Std_RetuenType lcd_print_chr(const lcd_t *lcd, uint8 character);
Std_RetuenType lcd_print_chr_pos(const lcd_t *lcd, uint8 row, uint8 col, uint8 character);
Std_RetuenType lcd_print_string(const lcd_t *lcd, uint8 *string);
Std_RetuenType lcd_print_string_pos(const lcd_t *lcd, uint8 row, uint8 col, uint8 *string);
Std_RetuenType lcd_print_custom_chr(const lcd_t *lcd, const uint8 chr[],uint8 row, uint8 col ,uint8 mem_pos);

Std_RetuenType convert_uint8_to_str(uint8 value, uint8 *str);
Std_RetuenType convert_uint16_to_str(uint16 value, uint8 *str);
Std_RetuenType convert_uint32_to_str(uint32 value, uint8 *str);


static Std_RetuenType send_nipple(const lcd_t *lcd, uint8 command);
static Std_RetuenType send_byte(const lcd_t *lcd, uint8 command);
static Std_RetuenType send_enable_signal(const lcd_t *lcd);
static Std_RetuenType lcd_set_cursor(const lcd_t *lcd, uint8 row, uint8 col);

#endif /* lcd_H_ */