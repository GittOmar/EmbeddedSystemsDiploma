/*******************************************************************************
 * @file       H_Bridge.h
 * @brief      Driver/Module Description
 * @date       2025/07/17
 * @time       17:53
 * @author     Omar Ibrahim
 ******************************************************************************/

#ifndef H_Bridge_H_
#define H_Bridge_H_

/*****************************************
 *                 Includes              *
 *****************************************/
 #include "./../../MCAL_Layer/GPIO/hal_gpio.h"
 #include "./H_Bridge_cfg.h"
/*****************************************
 *           Macro Declarations          *
 *****************************************/
#define Function_STATES   0x01

#define input_1           0x00
#define input_2           0x01

#define input_1_F          0x01
#define input_2_F          0x00

#define input_1_B          0x00
#define input_2_B          0x01

#define input_1_S           0x00
#define input_2_S           0x00
/*****************************************
 *       Macro Function Declarations     *
 *****************************************/


/*****************************************
 *          Data Type Declarations       *
 *****************************************/
typedef enum{
NO_MOVE,
BACKWARD ,
FORWARD
}motor_direction_t;





typedef struct{  // 2byte
pin_config_t in[2];  
motor_direction_t dir_statues;
}motor_t;

/*****************************************
 *        Function Declarations          *
 *****************************************/
Std_RetuenType motor_pin_intialize(motor_t *motor);
Std_RetuenType motor_no_move(motor_t *motor);             // 0 0
Std_RetuenType motor_move_forward(motor_t *motor);    // 1 0
Std_RetuenType motor_move_backward(motor_t *motor);  // 0 1
//inline static void pin_config(motor_t *motor , pin_config_t *in1 , pin_config_t *in2);

#endif /* H_Bridge_H_ */