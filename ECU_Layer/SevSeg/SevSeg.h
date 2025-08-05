/*******************************************************************************
 * @file       SevSeg.h
 * @brief      7seg module for Single Piece using decoder
 *             Common Anode     -> 7447 decoder ic
 *             Common Cathode   -> 7448 decoder ic
 * @date       2025/08/04
 * @time       09:03
 * @author     Omar Ibrahim
 ******************************************************************************/

#ifndef SevSeg_H_
#define SevSeg_H_

/*****************************************
 *                 Includes              *
 *****************************************/
 #include "./../../MCAL_Layer/GPIO/hal_gpio.h"
/*****************************************
 *                Global Var             *
 *****************************************/
logic_t seg_off_logic = LOW;
logic_t seg_on_logic = HIGH;
/*****************************************
 *           Macro Declarations          *
 *****************************************/

/*****************************************
 *       Macro Function Declarations     *
 *****************************************/

/*****************************************
 *          Data Type Declarations       *
 *****************************************/
typedef struct {
    pin_config_t pin[4];
} sev_seg_t;
/*****************************************
 *        Function Declarations          *
 *****************************************/
Std_RetuenType sev_seg_intialize(const sev_seg_t* seg);
Std_RetuenType sev_seg_write_num(const sev_seg_t* seg, uint8 number);

#endif /* SevSeg_H_ */