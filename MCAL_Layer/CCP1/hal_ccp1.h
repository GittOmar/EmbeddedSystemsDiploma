/*******************************************************************************
 * @file       hal_CCP1.h
 * @brief      Driver/Module Description
 * @date       2025/09/10
 * @time       15:32
 * @author     Omar Ibrahim
 ******************************************************************************/

#ifndef hal_CCP1_H_
#define hal_CCP1_H_

/*****************************************
 *                 Includes              *
 *****************************************/
#include "./../INTERRUPT/./mcal_internal_interrupt.h"
#include "../TIMER3/./hal_timer3.h"
#include "../TIMER2/./hal_timer2.h"
#include "../TIMER1/./hal_timer1.h"
#include "pic18f4620.h"
#include "../std_types.h"
#include "hal_ccp1_cfg.h"
#include "./../INTERRUPT/./mcal_internal_interrupt.h"
/*****************************************
 *           Macro Declarations          *
 *****************************************/
#define CCP1_CAPTURE_COMAPRE_PWM_DISABLE                       0
/**  COMPARE_MODE  */
#if  (CCP1_COMPARE_MODE)                     
    #define CCP1_COMPARE_MODE_TOOGLE_OUTPUT                        2
    #define CCP1_COMPARE_MODE_PIN_HIGH                             8
    #define CCP1_COMPARE_MODE_PIN_LOW                              9
    #define CCP1_COMPARE_MODE_SW_INTERRUPT                         10
    #define CCP1_COMPARE_MODE_TRIGGER_SPECIAL_EVENT                11                              
#endif                        
/**  CAPTURE_MODE  */
#if  (CCP1_CAPTURE_MODE)                     
    #define CCP1_CAPTURE_MODE_FALLING_EDGE                         4
    #define CCP1_CAPTURE_MODE_RISSING_EDGE                         5
    #define CCP1_CAPTURE_MODE_EVERY_4TH_RISSING_EDGE               6
    #define CCP1_CAPTURE_MODE_EVERY_16TH_RISSING_EDGE              7                        
#endif                        
/** PWM_MODE  */
#if  (CCP1_PWM_MODE)                     
    #define CCP1_PWM_MODE_SELECT                                   12                              
#endif                        

    
#if  (CCP1_CAPTURE_MODE || CCP1_COMPARE_MODE)                     
    #define CCP1_TIMER1_SELECT                                     0
    #define CCP1_TIMER3_SELECT                                     2                             
#endif                        

#if  (CCP1_PWM_MODE)                     
    #define CCP1_TIMER2_PR2                                            (PR2)
    #define CCP1_PWM_DUTY_CYCLE_LS2BITs                          (CCP1CONbits.DC1B)
    #define _XTAL_FREQ                                                8000000UL
    #define CCP1_TIMER2_SELECT                                           1
#endif                        
                                              
#define CCP1_LowBYTE_REG                                          (CCPR1L)
#define CCP1_HighBYTE_REG                                         (CCPR1H) 
#define CCP1_IN_FLAG                                          (PIR1bits.CCP1IF)
#define CCP1_READY                                                    1
#define CCP1_NOT_READY                                                0
/*****************************************     
 *       Macro Function Declarations     *     
 *****************************************/     
#define CCP1_MODE_SELECT(mode)                               (CCP1CONbits.CCP1M = mode) 
/****************************
 *   CCP1   COMP/CAP  R/W   *
 ****************************/
#if  (CCP1_CAPTURE_MODE || CCP1_COMPARE_MODE)                     
    #define CCP1_REG_WRITE_VALUE(value)                         \
        do {                                                    \
            CCPR1L = (uint8_t)((value) & 0xFF);                 \
            CCPR1H = (uint8_t)(((uint16_t)(value) >> 8) & 0xFF);\
        } while(0)

    #define CCP1_REG_READ_VALUE(value)                            (value = (uint16)CCP1_LowBYTE_REG + (uint16)(CCP1_HighBYTE_REG<<8))                        
#endif                        
/****************************            
 *     CCP1  PWM   ( W )     *            
 ****************************/   
 #if  (CCP1_PWM_MODE)                     
    #define CCP_PWM_DUTY_CYCLE_SET(value)                        do{ CCP1_PWM_DUTY_CYCLE_LS2BITs = (uint8) (value & 0b00000011);\
                                                                     CCP1_LowBYTE_REG            = (uint8) (value >> 2);}while(0)                              
 #endif                                 
/****************************
 *          Timers          *
 ****************************/  
#if  (CCP1_CAPTURE_MODE || CCP1_COMPARE_MODE)                     
    #define CCP1_TIMER1_USE()                                    do{ (T3CONbits.T3CCP1) = 0;\
                                                                      (T3CONbits.T3CCP2) = 0;\
                                                                    }while(0)
                                                                  
    #define CCP1_TIMER3_USE()                                        (T3CONbits.T3CCP2 = 1 )                          
#endif                        

#if  (CCP1_PWM_MODE)                     
    #define CCP1_TIMER2_PRESCALER_SELECT(prescaler)             (T2CONbits.T2CKPS = prescaler)
    #define CCP1_TIMER2_POSTSCALER_SELECT(postscaler)           (T2CONbits.TOUTPS = postscaler)  
    #define CCP1_TIMER2_RESET_ENABLE_BIT()                      (PIE1bits.TMR2IE = 0)                         
#endif                        
/****************************
 *        Pin State         *
 ****************************/
#define CCP1_PIN_INPUT()                                         (TRISCbits.RC2 = 1)                                                        
#define CCP1_PIN_OUTPUT()                                        (TRISCbits.RC2 = 0)                                                         
/*****************************************
 *          Data Type Declarations       *
 *****************************************/
typedef struct {
#if  (CCP1_IN_ENABLE) 
    InterruotHandler CCP1_INTERRUPT_HANDLER;                    
#if  (PERIORITY_ENABLE)                     
    priority_t CCP1_PRIORITY;                              
#endif                                                      
#endif  
#if  (CCP1_PWM_MODE)                     
    timer2_t  timer2;   
    uint16 CCP1_PWM_frequancy;
#endif   
#if  (CCP1_CAPTURE_MODE || CCP1_COMPARE_MODE)                     
    timer1_t  timer1;
    timer3_t  timer3;                        
#endif 
uint8 CCP1_Timer_select               : 2;                
uint8 CCP1_Mode_select                : 4;                    
}ccp1_t;
/*****************************************
 *        Function Declarations          *
 *****************************************/
 Std_RetuenType hal_ccp1_init( ccp1_t *ccp1);
 void hal_ccp1_deinit(void);
 /****************************
  *       Comparter          *
  ****************************/
#if  (CCP1_COMPARE_MODE)                     
Std_RetuenType hal_ccp1_IsCompareComplete(uint8 *status);     /** Polling  */
Std_RetuenType hal_ccp1_Comparter_WriteValue(const uint16 value);
Std_RetuenType hal_ccp1_Comparter_ChooseEvent(const uint8 event);  
Std_RetuenType hal_ccp1_comparter_10HZ_wave(uint8 dutyPercentage) ; 
#endif                        
 /****************************
  *          Captuer         *
  ****************************/
#if  (CCP1_CAPTURE_MODE)                     
Std_RetuenType hal_ccp1_IsCaptureComplete(uint8 *status);     /** Polling  */
Std_RetuenType hal_ccp1_CaptuerMode_Read_Value(uint16 *value);                        
Std_RetuenType hal_ccp1_Choose_CaptureMode(uint8 Mode);                        
#endif                        
 /****************************
  *          PWM              *
  ****************************/
#if  (CCP1_PWM_MODE)                     
  Std_RetuenType hal_ccp1_PWM_DutyCycle_cfg(uint8 dutyPercentage);
  void hal_ccp1_PWM_start(void);
  void hal_ccp1_PWM_stop(void);                        
#endif                        
#endif /* hal_CCP1_H_ */