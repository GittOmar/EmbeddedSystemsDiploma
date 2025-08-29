/*******************************************************************************
 * @file       mcal_interrupt_config.h
 * @brief      Driver/Module Description
 * @date       2025/08/18
 * @time       12:00
 * @author     Omar Ibrahim
 ******************************************************************************/

#ifndef mcal_interrupt_config_H_
#define mcal_interrupt_config_H_
/*****************************************
 *                 Includes              *
 *****************************************/
 #include "pic18f4620.h"
#include "../std_types.h"
#include "mcal_interrupt_gen_cfg.h"
/*****************************************
 *           Macro Declarations          *
 *****************************************/
 /****************************
  *          GIE             *
  ****************************/
  #define  GIE_ENABLE                  0x01
  #define  GIE_DISABLE                 0x00
 /****************************
  *          Enable Bit      *
  ****************************/
 #define INTERRUPT_ENABLE               0x01
 #define INTERRUPT_DISABLE              0x00
 /****************************
  *          Flag Bit        *
  ****************************/
 #define INTERRUPR_OCUUR                 0x01
 #define INTERRUPR_NOT_OCUUR             0x00
/****************************
 *        Periority Bit     *
 ****************************/
#define INTERRUPT_PERIORITY_ENABLE        0x01
#define INTERRUPT_PERIORITY_DISABLE       0x00
/*****************************************
 *       Macro Function Declarations     *
 *****************************************/
#define READ_INTRUPT_GlobalInterruptEnable()        (INTCONbits.GIE)
#ifdef PERIORITY_ENABLE

#define INTRUPT_GlobalInterruptHighEnable()         (INTCONbits.GIEH = 1)
#define INTRUPT_GlobalInterruptHighDisable()        (INTCONbits.GIEH = 0)
 
#define INTRUPT_GlobalInterruptLowEnable()          (INTCONbits.GIEL = 1)
#define INTRUPT_GlobalInterruptLowDisable()         (INTCONbits.GIEL = 0)

#define INTERRUPT_PeriorityEnable()                 (RCONbits.IPEN = 1)
#define INTERRUPT_PeriorityDisable()                (RCONbits.IPEN = 0)

#else   

#define INTRUPT_GlobalInterruptEnable()             (INTCONbits.GIE = 1)
#define INTRUPT_GlobalInterruptDisable()            (INTCONbits.GIE = 0)

#define PrephralInterruptEnable()                   (INTCONbits.PEIE = 1)
#define PrephralInterruptDisable()                  (INTCONbits.PEIE = 0)

#endif
/*****************************************
 *          Data Type Declarations       *
 *****************************************/
/****************************
 *          typedef         *
 ****************************/
typedef  void(*InterruotHandler)(void);
/****************************
 *          Enum            *
 ****************************/
typedef enum{
FLAG_LOW,
FLAG_HIGH
}flag_t;

typedef enum{
FALLING_EDGE,
RISSING_EDGE
}edge_t;

#ifdef  PERIORITY_ENABLE
typedef enum{
LOW_PRIORITY,
HIGH_PRIORITY
}priority_t;
#endif
/*****************************************
 *        Function Declarations          *
 *****************************************/
 
#endif /* mcal_interrupt_config_H_ */