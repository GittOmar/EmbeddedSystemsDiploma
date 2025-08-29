/*******************************************************************************
 * @file       EEPROM.h
 * @brief      Driver/Module Description
 * @date       2025/08/25
 * @time       12:08
 * @author     Omar Ibrahim
 ******************************************************************************/

#ifndef EEPROM_H_
#define EEPROM_H_
/*****************************************
 *                 Includes              *
 *****************************************/
 #include "./../INTERRUPT/./mcal_internal_interrupt.h"
 #include "./../std_types.h"
 #include "pic18f4620.h"
/*****************************************
 *           Macro Declarations          *
 *****************************************/
/****************************
 *          IMP. REG        *
 ****************************/
#define EEPROM_DATA_REG                     (EEDATA)
#define EEPROM_ADR_H                        (EEADRH)
#define EEPROM_ADR_L                        (EEADR)
#define EEPROM_UNLOCKING_SEQ_REG            (EECON2)

#define STILL_READ                           0X01
#define STILL_WRITE                          0X01

#define READ_FINISH                          0x00
#define WRITE_FINISH                         0x00
/*****************************************
 *       Macro Function Declarations     *
 *****************************************/
/****************************
 *          INIT            *
 ****************************/
#define EEPROM_FLASH_MEMORY_SELECT()        (EECON1bits.CFGS = 0)
#define EEPROM_MEMORY_DATA_ACCESS()         (EECON1bits.EEPGD = 0)
/****************************
 *          WRITE           *
 ****************************/
#define WriteEn_SET()                       (EECON1bits.WREN = 1)
#define WriteEn_RESET()                     (EECON1bits.WREN = 0)

#define  SET_WriteBit()                     (EECON1bits.WR = 1)
#define  READ_WriteBit()                    (EECON1bits.WR)
/****************************
 *          READ            *
 ****************************/
#define  SET_ReadBit()                      (EECON1bits.RD = 1)
#define  READ_ReadBit()                     (EECON1bits.RD)
/****************************
 *          OTHER           *
 ****************************/
#define WAIT_NO_OPERAION()                   NOP()
/*****************************************
 *          Data Type Declarations       *
 *****************************************/
 
/*****************************************
 *        Function Declarations          *
 *****************************************/
Std_RetuenType EEPROM_READ_BYTE    (uint16  ADR, uint8* DATA);
Std_RetuenType EEPROM_WRITE_BYTE   (uint16  ADR, uint8 DATA);
#endif /* EEPROM_H_ */