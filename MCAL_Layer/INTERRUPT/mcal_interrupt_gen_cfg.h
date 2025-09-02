/*******************************************************************************
 * @file       mcal_interrupt_gen_cfg.h
 * @brief      Driver/Module Description
 * @date       2025/08/18
 * @time       16:21
 * @author     Omar Ibrahim
 ******************************************************************************/

#ifndef mcal_interrupt_gen_cfg_H_
#define mcal_interrupt_gen_cfg_H_

/*****************************************
 *                 Includes              *
 *****************************************/
/*****************************************
 *           Macro Declarations          *
 *****************************************/
 /****************************
  *     priority control     *
  ****************************/
  #define PERIORITY_ENABLE                0x01
 /****************************
  *      EXT_INX control      *
  ****************************/
/** genral */
#define EXTERNAL_INTERRUPT_INTx_ENABLE    0x01
/**specific */
#define EXTERNAL_INTERRUPT_INT0_ENABLE    0x01   
//#define EXTERNAL_INTERRUPT_INT1_ENABLE    0x01
//#define EXTERNAL_INTERRUPT_INT2_ENABLE    0x01
/****************************
 *      PORTB_OnChangeIN    *
 ****************************/
 /** genral */
#define EXTERNAL_INTERRUPT_RBx_OnChange_ENABLE  0x01
// #define EXTERNAL_INTERRUPT_RBx_HighPriority     0x01
/**specific */
#define EXTERNAL_INTERRUPT_RB4_ENABLE    0x01   
#define EXTERNAL_INTERRUPT_RB5_ENABLE    0x01
#define EXTERNAL_INTERRUPT_RB6_ENABLE    0x01
// #define EXTERNAL_INTERRUPT_RB7_ENABLE    0x01
/****************************
 *          ADC             *
 ****************************/
#define ADC_IN_ENABLE   0x01
/*****************************************
 *       Macro Function Declarations     *
 *****************************************/
/*****************************************
 *          Data Type Declarations       *
 *****************************************/
/*****************************************
 *        Function Declarations          *
 *****************************************/


#endif /* mcal_interrupt_gen_cfg_H_ */