/*******************************************************************************
 * @file       lcd_cfg.h
 * @brief      Driver/Module Description
 * @date       2025/08/12
 * @time       15:59
 * @author     Omar Ibrahim
 ******************************************************************************/

#ifndef lcd_cfg_H_
#define lcd_cfg_H_

/*****************************************
 *                 Includes              *
 *****************************************/


/*****************************************
 *           Macro Declarations          *
 *****************************************/
#define _4BIT_MODE   0x04
#define _8BIT_MODE   0x08

/*
* Choose the LCD Sending Data Mode 
* 1)  _4BIT_MODE
* 2)  _8BIT_MODE
*/
#define LCD_BIT_MODE   _8BIT_MODE  

#define LCD_8BIT_MODE_2_LINE                          0x38
#define LCD_4BIT_MODE_2_LINE                          0x03

#if (LCD_BIT_MODE == _4BIT_MODE)
#define LCD_2_LINE_COMMAND   LCD_4BIT_MODE_2_LINE
#elif  (LCD_BIT_MODE == _8BIT_MODE)
#define LCD_2_LINE_COMMAND   LCD_8BIT_MODE_2_LINE
#endif


#define LCD_ROW   4
#define LCD_COL   20

/*****************************************
 *       Macro Function Declarations     *
 *****************************************/


/*****************************************
 *          Data Type Declarations       *
 *****************************************/


/*****************************************
 *        Function Declarations          *
 *****************************************/


#endif /* lcd_cfg_H_ */