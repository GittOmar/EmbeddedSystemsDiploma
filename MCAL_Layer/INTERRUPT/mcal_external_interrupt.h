/*******************************************************************************
 * @file       mcal_external_interrupt.h
 * @brief      Driver/Module Description
 * @date       2025/08/18
 * @time       12:01
 * @author     Omar Ibrahim
 ******************************************************************************/

#ifndef mcal_external_interrupt_H_
#define mcal_external_interrupt_H_

/*****************************************
 *                 Includes              *
 *****************************************/
#include "D:\Courses\Embeded systems diploma\part 2\project(s)\app_1\sw\MCAL_Layer\GPIO\hal_gpio.h"
#include "mcal_interrupt_config.h"
/*****************************************
 *           Macro Declarations          *
 *****************************************/
#ifdef EXTERNAL_INTERRUPT_INTx_ENABLE
#ifdef EXTERNAL_INTERRUPT_INT0_ENABLE
/****************************
 *          IN0             *
 ****************************/

    #define EXT_IN0_InterruptEnable()     (INTCONbits.INT0E = 1)
    #define EXT_IN0_InterruptDisable()    (INTCONbits.INT0E = 0)

    #define EXT_IN0_FlagClear()           (INTCONbits.INT0F = 0)

    #define EXT_IN0_RisingEdgeTrigger()   (INTCON2bits.INTEDG0 = 1)
    #define EXT_IN0_FallingEdgeTrigger()   (INTCON2bits.INTEDG0 = 0)

#endif
#ifdef EXTERNAL_INTERRUPT_INT1_ENABLE
/****************************
 *          IN1             *
 ****************************/
    #define EXT_IN1_InterruptEnable()     (INTCON3bits.INT1E = 1)
    #define EXT_IN1_InterruptDisable()    (INTCON3bits.INT1E = 0)

    #define EXT_IN1_FlagClear()           (INTCON3bits.INT1F = 0)

    #define EXT_IN1_RisingEdgeTrigger()   (INTCON2bits.INTEDG1 = 1)
    #define EXT_IN1_FallingEdgeTrigger()  (INTCON2bits.INTEDG1 = 0)

#ifdef  PERIORITY_ENABLE

    #define EXT_IN1_SetHighPriority()     (INTCON3bits.INT1IP = 1)
    #define EXT_IN1_SetLowPriority()      (INTCON3bits.INT1IP = 0)
    
#endif
#endif
#ifdef EXTERNAL_INTERRUPT_INT2_ENABLE
/****************************
 *          IN2             *
 ****************************/

    #define EXT_IN2_InterruptEnable()     (INTCON3bits.INT2E = 1)
    #define EXT_IN2_InterruptDisable()    (INTCON3bits.INT2E = 0)

    #define EXT_IN2_FlagClear()           (INTCON3bits.INT2F = 0)

    #define EXT_IN2_RisingEdgeTrigger()   (INTCON2bits.INTEDG2 = 1)
    #define EXT_IN2_FallingEdgeTrigger()  (INTCON2bits.INTEDG2 = 0)

#ifdef PERIORITY_ENABLE

    #define EXT_IN2_SetHighPriority()     (INTCON3bits.INT2P = 1)
    #define EXT_IN2_SetLowPriority()      (INTCON3bits.INT2P = 0)

#endif
#endif
#endif
/****************************
 *           RBx             *
 ****************************/

#ifdef EXTERNAL_INTERRUPT_RBx_OnChange_ENABLE

    #define EXT_RBx_OnChange_InterruptEnable()      (INTCONbits.RBIE = 1)            
    #define EXT_RBx_OnChange_InterruptDisable()     (INTCONbits.RBIE = 0)   

    #define EXT_RBx_OnChange_FlagClear()            (INTCONbits.RBIF = 0)
#ifdef PERIORITY_ENABLE
    #define EXT_RBx_OnChange_SetHighPriority()      (INTCONbits.RBIE = 1)      
    #define EXT_RBx_OnChange_SetLowPriority()       (INTCONbits.RBIE = 0) 
#endif
#endif

/*****************************************
 *       Macro Function Declarations     *
 *****************************************/
/*****************************************
 *          Data Type Declarations       *
 *****************************************/
/****************************
 *          Enum            *
 ****************************/
#if  (EXTERNAL_INTERRUPT_INTx_ENABLE)                     
typedef enum{
#ifdef EXTERNAL_INTERRUPT_INT0_ENABLE    
    IN0,
#endif
#ifdef EXTERNAL_INTERRUPT_INT1_ENABLE
    IN1,
#endif
#ifdef EXTERNAL_INTERRUPT_INT2_ENABLE    
    IN2,
#endif
RBx_NULL,
}INx_t;                              
#endif                        

#if  (EXTERNAL_INTERRUPT_RBx_OnChange_ENABLE)                     
typedef enum{
#ifdef EXTERNAL_INTERRUPT_RB4_ENABLE         
RB_4,                     
#endif
#ifdef EXTERNAL_INTERRUPT_RB5_ENABLE                   
RB_5,                     
#endif    
#ifdef EXTERNAL_INTERRUPT_RB6_ENABLE         
RB_6,                                           
#endif 
#ifdef EXTERNAL_INTERRUPT_RB7_ENABLE                   
RB_7,                                             
#endif 
INX_NULL
}RBx_t;                              
#endif                        

/****************************
 *          Struct           *
 ****************************/
#if  (EXTERNAL_INTERRUPT_INTx_ENABLE)                     
typedef struct{
void ( *EXT_InterruptHandler)(void);    /**call back function*/ 
INx_t    source;
edge_t   edge;
#if (PERIORITY_ENABLE &&  (EXTERNAL_INTERRUPT_INT1_ENABLE || EXTERNAL_INTERRUPT_INT2_ENABLE))
priority_t priority;
#endif
}EXT_IN_INx_t;
                              
#endif                        

#if  (EXTERNAL_INTERRUPT_RBx_OnChange_ENABLE)                     
typedef struct{
void ( *EXT_InterruptHandler_RissingEdge)(void);    /**call back function*/
void ( *EXT_InterruptHandler_FallingEdge)(void);    /**call back function*/
RBx_t  InterruptPin;
#if (PERIORITY_ENABLE && EXTERNAL_INTERRUPT_RBx_OnChange_ENABLE)
priority_t priority;
#endif
}EXT_IN_RBx_t;                              
#endif                        

/****************************
 *          Typedef         *
 ****************************/
#if  (EXTERNAL_INTERRUPT_INTx_ENABLE)                     
typedef  Std_RetuenType INx_Function(const EXT_IN_INx_t *INx);                      
#endif          
#if  (EXTERNAL_INTERRUPT_RBx_OnChange_ENABLE)                     
typedef  Std_RetuenType RBx_Fuction(const EXT_IN_RBx_t *RBx);                            
#endif                                      
/*****************************************
 *        Function Declarations          *
 *****************************************/
#if  (EXTERNAL_INTERRUPT_INTx_ENABLE)                     
INx_Function interrupt_INx_intialize;
INx_Function interrupt_INx_deintialize; /** Interrupt Disable */                              
#endif
#if  (EXTERNAL_INTERRUPT_RBx_OnChange_ENABLE)                     
RBx_Fuction interrupt_RBx_intialize;
RBx_Fuction interrupt_RBx_deintialize; /** Interrupt Disable */                              
#endif                                                
#endif /* mcal_external_interrupt_H_ */