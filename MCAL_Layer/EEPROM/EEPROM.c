/*******************************************************************************
 * @file       EEPROM.c
 * @brief      Driver/Module Description
 * @date       2025/08/25
 * @time       11:51
 * @author     Omar Ibrahim
 ******************************************************************************/

/*****************************************
 *                includes                *
 *****************************************/
#include"EEPROM.h"
/*****************************************
 *            Function Decleration       *
 *****************************************/
void GLOBAL_INTERUPT_ENABLE(void);
void GLOBAL_INTERUPT_DISABLE(void);
Std_RetuenType GLOBAL_INTERRUPT_RETURN_STATE(uint8 PrevState);
/*****************************************
 *           Helper Function             *
 *****************************************/
 /**
 * @brief address handling and eeprom select operation
 * 
 * @param ADR 
 * @return Std_RetuenType 
 */
static Std_RetuenType EEPROM_CONF_INIT(uint16  ADR){
    Std_RetuenType ret = E_OK;
    if(ADR > UINT16_MAX){
        ret = E_NOT_OK;
    }else{
    /**a) ADR */
    EEPROM_ADR_H = (uint8)(((ADR)>>8) & (0x03)); 
    EEPROM_ADR_L = (uint8)(ADR & (0xFF)); 
    /**b) eeprom select operation */
    EEPROM_FLASH_MEMORY_SELECT();
    EEPROM_MEMORY_DATA_ACCESS(); 
    }
 return ret;
}
/*****************************************
 *           function definition          *
 *****************************************/

Std_RetuenType EEPROM_READ_BYTE    (uint16  ADR, uint8* DATA){
    Std_RetuenType ret = E_OK;
    if((DATA == NULL) || (ADR > UINT16_MAX)){
        ret = E_NOT_OK;
    }else{
    /**a) Init */
    ret &= EEPROM_CONF_INIT(ADR);
    /**b) RD Enable */
    SET_ReadBit();
    /**c) 2 NOP */
    WAIT_NO_OPERAION();
    WAIT_NO_OPERAION();
    /**d) DATA RETRIEVE */
    *DATA = EEPROM_DATA_REG;
    }
    return ret;
}

Std_RetuenType EEPROM_WRITE_BYTE   (uint16  ADR, uint8 DATA){
    Std_RetuenType ret = E_OK;
    uint8 GIE_Prev_Status = READ_INTRUPT_GlobalInterruptEnable();

    if((DATA > UINT8_MAX) || (ADR > UINT16_MAX)){
        ret = E_NOT_OK;
    }else{
    /**a) init */
    ret &= EEPROM_CONF_INIT(ADR);
    /**b) data hold */
    EEPROM_DATA_REG = DATA;
    /**c) write enable */
    WriteEn_SET();
    /**d) Diable GIE */
    GLOBAL_INTERUPT_DISABLE();
    /**e) Unlocking Sequance */
    EEPROM_UNLOCKING_SEQ_REG = 0x55;
    EEPROM_UNLOCKING_SEQ_REG = 0xAA;
    /**f) Set WR Bit */
    SET_WriteBit();
    /**g) wait WR to be cleared */
    while(READ_WriteBit() == STILL_WRITE){/**Nothing */};
    /**h)  clear WREN */
    WriteEn_RESET();
    /**i) Restore the GIE */
    ret &= GLOBAL_INTERRUPT_RETURN_STATE(GIE_Prev_Status);
    }
    return ret;
}