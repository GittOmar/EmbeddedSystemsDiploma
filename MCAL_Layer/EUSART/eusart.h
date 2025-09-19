/*******************************************************************************
 * @file       eusart.h
 * @brief      Driver/Module Description
 * @date       2025/09/15
 * @time       17:54
 * @author     Omar Ibrahim
 ******************************************************************************/

#ifndef eusart_H_
#define eusart_H_

/*****************************************
 *                 Includes              *
 *****************************************/
#include"eusart_cfg.h"
#include"../std_types.h"
#include "./../INTERRUPT/./mcal_internal_interrupt.h"
#include "pic18f4620.h"
#include"../GPIO/hal_gpio.h"
/** EUSART  */
/*****************************************
 *           Macro Declarations          *
 *****************************************/
 #define _XTAL_FREQ 8000000UL

 /** TX & RX  */
#define EUSART_TX_ENABLE_SELECT                 1     
#define EUSART_TX_DISABLE_SELECT                0

#define EUSART_TX_REG                         (TXREG) 
#define EUSART_RX_REG                         (RCREG) 


#define EUSART_RX_ENABLE_SELECT                 1
#define EUSART_RX_DISABLE_SELECT                0

#define TX_MAX_VALUE                           511
 /** Flags  */

#define EUSART_RX_STATUS                  (BAUDCONbits.RCIDL)
#define EUSART_TX_SHIFT_REG_STATUS        (TXSTAbits.TRMT)

/** Flags Values  */

#define RX_ACTIVE_STATE                         0
#define TX_SHIFT_REG_STILL_SHIFT                0

/** status  */
#define EUSART_RX_IDLE_STATE                1
#define EUSART_TX_SHIFT_REG_EMPTY           1

/** 9th  bit  */
#define EUSART_RX_9BIT_ENABLE_BIT               1
#define EUSART_TX_9BIT_ENABLE_BIT               1

#define EUSART_RX_9BIT_DISABLE_BIT              0
#define EUSART_TX_9BIT_DISABLE_BIT              0

#define EUSART_RX_9BIT_DATA              (RCSTA1bits.RX9D)  /** Data of the 9th bit  */


/** Errors  */
#define EUSART_RX_FERR                   (RCSTA1bits.FERR)  /** Framming error  */
#define EUSART_RX_OERR                   (RCSTA1bits.OERR)  /** Over run error  */

/** TX RX Flags  */
#define EUSART_TX_IN_STATE                (PIE1bits.TXIE)
#define EUSART_RX_IN_STATE                (PIE1bits.RCIE)

#define EUSART_INTERRUPT_ENABLE                        1
#define EUSART_INTERRUPT_DISABLE                       0
/** Baud Rate  */

/** BaudRate Speed  */
    #define EUSART_BRG_HIGH_SPEED_SELECT        1
    #define EUSART_BRG_LOW_SPEED_SELECT         0
/** BaudRate Data Access  */
    #define EUSART_BRG_8BIT_SELECT              0
    #define EUSART_BRG_16BIT_SELECT             1

/**BaudRate DataBytes   */
    #define EUSART_BR_VALUE_lowBYTE                (SPBRG)
    #define EUSART_BR_VALUE_higBYTE                (SPBRGH)

/** BaudRate cfg     SYNC   BRG16   BRGH    */
    #define EUSART_8BIT_ASYN_LOW_SPEED             0
    #define EUSART_8BIT_ASYN_HIGH_SPEED            1
    #define EUSART_16BIT_ASYN_LOW_SPEED            2
    #define EUSART_16BIT_ASYN_HIGH_SPEED           3

/** BaudRate Values  */
#define EUSART_BR_300                         300  
#define EUSART_BR_1200                        1200
#define EUSART_BR_2400                        2400 
#define EUSART_BR_9600                        9600 
#define EUSART_BR_19200                       19200  
#define EUSART_BR_57600                       57600  
#define EUSART_BR_115200                      115200  
/*****************************************
 *       Macro Function Declarations     *
 *****************************************/
 /** Genral  */
 #define EUSART_SERIAL_PORT_ENABLE()        (RCSTA1bits.SPEN = 1)
 #define EUSART_SERIAL_PORT_DISABLE()       (RCSTA1bits.SPEN = 0)
 #define EUSART_ASYN_MODE()                 (TXSTAbits.SYNC = 0)
 /** BaudRate  */
    #define EUSART_BRG_8BIT()                  (BAUDCONbits.BRG16 = 0)
    #define EUSART_BRG_16BIT()                 (BAUDCONbits.BRG16 = 1)
    #define EUSART_BRG_HIGH_SPEED()            (TXSTAbits.BRGH = 1)
    #define EUSART_BRG_LOW_SPEED()             (TXSTAbits.BRGH = 0)
 /** RX  */
#define EUSART_RX_ENABLE()                  (RCSTA1bits.CREN = 1)
#define EUSART_RX_9BIT_ENABLE()             (RCSTA1bits.RX9 = 1)
#define EUSART_RX_PIN_CFG()                 (TRISCbits.RC7 = 1)
 /** TX  */
#define EUSART_TX_ENABLE()                   (TXSTAbits.TXEN = 1)
#define EUSART_TX_9BIT_ENABLE()              (TXSTAbits.TX9 = 1)
#define EUSART_TX_PIN_CFG()                 (TRISCbits.RC6 = 1)
#define EUSART_TX_9BIT_DATA(x)               (TXSTAbits.TX9D = x)   

/** TX RX Flags  */
#define EUSART_TX_IN_STATE_ASSIGN(x)                (PIE1bits.TXIE = x)
#define EUSART_RX_IN_STATE_ASSIGN(x)                (PIE1bits.RCIE = x)
/*****************************************
 *          Data Type Declarations       *
 *****************************************/
typedef union{
struct{
uint8 FERR : 1;

uint8 OERR : 1;

uint8      : 6;
};

uint8 err;

}eusart_err_t;

typedef struct{
uint8  BR_CFG;
uint32 BaudRate;
}BaudRate_t;  

typedef struct{
#if  (EUSART_IN_ENABLE)                     
InterruotHandler EUSART_RX_IN_HANDLER; 
#if  (PERIORITY_ENABLE)                     
priority_t RX_Priority;                            
#endif                                                 
#endif   
uint8 Eusart_RX_Enable  : 1;
uint8 Eusart_Frame_size : 1;
}RX_t;

typedef struct{
#if  (EUSART_IN_ENABLE)                     
InterruotHandler EUSART_TX_IN_HANDLER;  
#if  (PERIORITY_ENABLE)                     
priority_t TX_Priority;                                                 
#endif                                                
#endif                        
uint8 Eusart_TX_Enable  : 1;
uint8 Eusart_Frame_size : 1;
}TX_t;

typedef struct{
BaudRate_t      BaudRate;
RX_t            RX;
TX_t            TX;
eusart_err_t    err;
InterruotHandler EUSART_FERR_IN_HANDLER;
InterruotHandler EUSART_OERR_IN_HANDLER;
}eusart_t;
/*****************************************
 *        Function Declarations          *
 *****************************************/
Std_RetuenType hal_EUSART_INIT(const eusart_t* eusart);
Std_RetuenType hal_EUSART_DEINIT(const eusart_t* eusart);

Std_RetuenType hal_EUSART_BLOCKING_READ(const eusart_t* eusart, uint16 *value);
Std_RetuenType hal_EUSART_BLOCKING_WRITE(const eusart_t* eusart , uint16 value);
Std_RetuenType hal_EUSART_BLOCKING_WRITE_String(const eusart_t* eusart , uint8 *chr , uint8 strlen);

Std_RetuenType hal_EUSART_NON_BLOCKING_READ(const eusart_t* eusart, uint16 *value);
Std_RetuenType hal_EUSART_NON_BLOCKING_WRITE(const eusart_t* eusart , uint16 value);
// Std_RetuenType hal_EUSART_NON_BLOCKING_WRITE_String(const eusart_t* eusart , uint8 *chr , uint8 strlen);

#endif /* eusart_H_ */