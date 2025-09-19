/*******************************************************************************
 * @file       eusart.c
 * @brief      Driver/Module Description
 * @date       2025/09/15
 * @time       17:54
 * @author     Omar Ibrahim
 ******************************************************************************/

/*****************************************
 *                includes                *
 *****************************************/
#include "eusart.h" 
/*****************************************
 *            Defined Varibles           *
 *****************************************/
InterruotHandler  TX_CallbackFunction;
InterruotHandler  RX_CallbackFunction;
InterruotHandler  FERR_CallbackFunction;
InterruotHandler  OERR_CallbackFunction;
static volatile uint16   TX_value;
static volatile uint16  *RX_value;
static volatile uint8    TX_9th_BitFramming;
static volatile uint8    RX_9th_BitFramming;
/*****************************************
 *         Function Decleration          *
 *****************************************/
void RX_IN_init(priority_t RX_priority);
void TX_IN_init(priority_t RX_priority);
Std_RetuenType Module_INTERRUPT_ClEAR_FLAG(uint8 Reg,uint8 bit_pos);
void TX_VALUE_ASSIGN(void);
void RX_VALUE_ASSIGN(void);
/*****************************************
 *              Helper Functions         *
 *****************************************/
/****************************
 *          BaudRate        *
 ****************************/
  Std_RetuenType static inline BR_Value_Calauclate(const eusart_t* eusart ,  float *ValueStored){
    Std_RetuenType ret = E_OK;


    if(eusart == NULL){
        return E_NOT_OK;
    }else{

    if( (eusart->BaudRate.BR_CFG == EUSART_8BIT_ASYN_HIGH_SPEED)    ||
        (eusart->BaudRate.BR_CFG == EUSART_16BIT_ASYN_LOW_SPEED)    ){

        *ValueStored  =  ((_XTAL_FREQ / (float)eusart->BaudRate.BaudRate) / 16.0 ) - 1;

    }else if (eusart->BaudRate.BR_CFG == EUSART_8BIT_ASYN_LOW_SPEED){

        *ValueStored  =  ((_XTAL_FREQ / (float)eusart->BaudRate.BaudRate) / 64.0 ) - 1;

    }else {

        *ValueStored  =  ((_XTAL_FREQ / (float)eusart->BaudRate.BaudRate) / 4.0  ) - 1;
    }

    }
    return ret;
 }

  Std_RetuenType static inline BaudRate_Value(const eusart_t* eusart){
    Std_RetuenType ret = E_OK;
    
    float ValueStored;
    BR_Value_Calauclate(eusart,&ValueStored) ;  

    if(eusart == NULL){
        return E_NOT_OK;
    }else{
    /** BaudRate Value  */
    switch (eusart->BaudRate.BR_CFG) {
    case EUSART_8BIT_ASYN_LOW_SPEED   :  
    case EUSART_8BIT_ASYN_HIGH_SPEED  : 
            EUSART_BRG_8BIT();
            EUSART_BR_VALUE_lowBYTE = (uint8)ValueStored;
    break;
    case EUSART_16BIT_ASYN_LOW_SPEED  :  
    case EUSART_16BIT_ASYN_HIGH_SPEED : 
            EUSART_BRG_16BIT();
            EUSART_BR_VALUE_lowBYTE = (uint8)ValueStored;
            EUSART_BR_VALUE_higBYTE = (uint8)((uint16)ValueStored >> 8);
    break;
    default: return E_NOT_OK;
    }
    }
    return ret;
 }

  Std_RetuenType static inline BaudRate_Speed(const eusart_t* eusart){
    Std_RetuenType ret = E_OK;
    if(eusart == NULL){
        return E_NOT_OK;
    }else{
    /** BaudRate Speed  */
    switch (eusart->BaudRate.BR_CFG) {
    case EUSART_8BIT_ASYN_LOW_SPEED   :  
    case EUSART_16BIT_ASYN_LOW_SPEED  : 
            EUSART_BRG_LOW_SPEED();
    break;
    case EUSART_8BIT_ASYN_HIGH_SPEED   :  
    case EUSART_16BIT_ASYN_HIGH_SPEED  : 
            EUSART_BRG_HIGH_SPEED();
    break;
    default: return E_NOT_OK;
    }
    }
    return ret;
 }

 Std_RetuenType static inline EUSART_BaudRate_CFG(const eusart_t* eusart){
    Std_RetuenType ret = E_OK;
    if(eusart == NULL){
        return E_NOT_OK;
    }else{
     BaudRate_Speed(eusart);
     BaudRate_Value(eusart);
    }
    return ret;
 } 
 /****************************
  *          TX               *
  ****************************/
   Std_RetuenType static inline TX_Frame(const eusart_t* eusart){
    Std_RetuenType ret = E_OK;
    if(eusart == NULL){
        return E_NOT_OK;
    }else{
        if(eusart->TX.Eusart_Frame_size == EUSART_TX_9BIT_ENABLE_BIT) EUSART_TX_9BIT_ENABLE();
    }
    return ret;
 }

   Std_RetuenType static inline EUSART_TX_CFG(const eusart_t* eusart){
    Std_RetuenType ret = E_OK;

    priority_t TX_priotity = HIGH_PRIORITY;
    #if  (PERIORITY_ENABLE)                     
    TX_priotity = eusart->TX.TX_Priority;                              
    #endif             

    if(eusart == NULL){
        return E_NOT_OK;
    }else{
        EUSART_TX_ENABLE();
        EUSART_TX_PIN_CFG();
        TX_Frame(eusart);
        #if  (EUSART_IN_ENABLE)                     
        if(eusart->TX.EUSART_TX_IN_HANDLER == NULL){
        TX_CallbackFunction = &TX_VALUE_ASSIGN;
        }else{
        TX_CallbackFunction  = eusart->TX.EUSART_TX_IN_HANDLER ;
        } 
        TX_IN_init(TX_priotity);                          
        #endif                        
    }
    return ret;
 }
  /****************************
   *          RX               *
   ****************************/
    Std_RetuenType static inline RX_Frame(const eusart_t* eusart){
    Std_RetuenType ret = E_OK;
    if(eusart == NULL){
        return E_NOT_OK;
    }else{
        if(eusart->RX.Eusart_Frame_size == EUSART_RX_9BIT_ENABLE_BIT) EUSART_RX_9BIT_ENABLE();
    }
    return ret;
 }

   Std_RetuenType static inline EUSART_RX_CFG(const eusart_t* eusart){
    Std_RetuenType ret = E_OK;

    priority_t RX_priotity = HIGH_PRIORITY;
    #if  (PERIORITY_ENABLE)                     
    RX_priotity = eusart->RX.RX_Priority;                              
    #endif  

    if(eusart == NULL){
        return E_NOT_OK;
    }else{
        EUSART_RX_ENABLE();
        EUSART_RX_PIN_CFG();
        RX_Frame(eusart);
        #if  (EUSART_IN_ENABLE)                     
        if(eusart->RX.EUSART_RX_IN_HANDLER == NULL){
           RX_CallbackFunction   =   RX_VALUE_ASSIGN ;
        }else{
            RX_CallbackFunction  =  eusart->RX.EUSART_RX_IN_HANDLER ;  
        }
        RX_IN_init(RX_priotity);                                   
        #endif                        
    }
    return ret;
 }
 /****************************
  *     Errors Callback      *
  ****************************/
    Std_RetuenType static inline ErrorsCallBack(const eusart_t* eusart){
    Std_RetuenType ret = E_OK;
    if(eusart == NULL){
        return E_NOT_OK;
    }else{
        FERR_CallbackFunction = eusart->EUSART_FERR_IN_HANDLER ;
        OERR_CallbackFunction = eusart->EUSART_OERR_IN_HANDLER ;
    }
    return ret;
 }
 /*****************************************
  *         function definition          *
  *****************************************/
Std_RetuenType hal_EUSART_INIT(const eusart_t* eusart){
    Std_RetuenType ret = E_OK;
    if(eusart == NULL){
        return E_NOT_OK;
    }else{
        /** Main Cfg  */
        EUSART_SERIAL_PORT_DISABLE();
        EUSART_ASYN_MODE();
        /** Error callback  */
        ErrorsCallBack(eusart);
        /** BaudRate Cfg  */
        EUSART_BaudRate_CFG(eusart);
        /** TX Cfg  */
        if(eusart->TX.Eusart_TX_Enable)   EUSART_TX_CFG(eusart);
        /** RX Cfg  */
        if(eusart->RX.Eusart_RX_Enable)   EUSART_RX_CFG(eusart);

        EUSART_SERIAL_PORT_ENABLE();
    }
    return ret;
}
Std_RetuenType hal_EUSART_DEINIT(const eusart_t* eusart){
        Std_RetuenType ret = E_OK;
    if(eusart == NULL){
        return E_NOT_OK;
    }else{
        EUSART_SERIAL_PORT_DISABLE();
    }
    return ret;
}

/****************************
 *         Blockgin         *
 ****************************/
Std_RetuenType hal_EUSART_BLOCKING_READ(const eusart_t* eusart, uint16 *value){
    Std_RetuenType ret = E_OK;
    uint8 IN_Prev_state = EUSART_TX_IN_STATE;
    if((eusart == NULL) || (value == NULL)){
        return E_NOT_OK;
    }else{

        EUSART_RX_IN_STATE_ASSIGN(EUSART_INTERRUPT_DISABLE);

        while(EUSART_RX_STATUS  == RX_ACTIVE_STATE);

        *value =  EUSART_RX_REG + (((EUSART_RX_9BIT_DATA) && (eusart->RX.Eusart_Frame_size == EUSART_RX_9BIT_ENABLE_BIT)) ? 256 : 0 );
        
        EUSART_RX_IN_STATE_ASSIGN(IN_Prev_state);

    }
    return ret;
}

Std_RetuenType hal_EUSART_BLOCKING_WRITE(const eusart_t* eusart , uint16 value){
    Std_RetuenType ret = E_OK;
    uint8 IN_Prev_state = EUSART_TX_IN_STATE;
    if((eusart == NULL) || (value > TX_MAX_VALUE)){
        return E_NOT_OK;
    }else{

        EUSART_TX_IN_STATE_ASSIGN(EUSART_INTERRUPT_DISABLE);

        while(EUSART_TX_SHIFT_REG_STATUS == TX_SHIFT_REG_STILL_SHIFT);

        EUSART_TX_REG = (uint8)value;
        if(eusart->TX.Eusart_Frame_size == EUSART_TX_9BIT_ENABLE_BIT ){
        EUSART_TX_9BIT_DATA(READ_BIT(value, 8));
        }

        EUSART_TX_IN_STATE_ASSIGN(IN_Prev_state);
    }
    return ret;
}

Std_RetuenType hal_EUSART_BLOCKING_WRITE_String(const eusart_t* eusart , uint8 *chr , uint8 strlen){
    Std_RetuenType ret = E_OK;
    uint8 IN_Prev_state = EUSART_TX_IN_STATE;
    if((eusart == NULL) || (strlen > UINT8_MAX) || (chr == NULL)){
        return E_NOT_OK;
    }else{
        for(uint8 cnt = ZERO_INIT ; cnt < strlen ; cnt++){
            hal_EUSART_BLOCKING_WRITE(eusart,chr[cnt]);
        }
    }
    return ret;   
}
/****************************
 *       Non Blocking       *
 ****************************/
Std_RetuenType hal_EUSART_NON_BLOCKING_READ(const eusart_t* eusart, uint16 *value){
Std_RetuenType ret = E_OK;
if((eusart == NULL) || (value ==NULL)){
    return E_NOT_OK;
}else{
    RX_value = value;
    RX_9th_BitFramming = eusart->RX.Eusart_Frame_size;
}
return ret;
}

Std_RetuenType hal_EUSART_NON_BLOCKING_WRITE(const eusart_t* eusart , uint16 value){
Std_RetuenType ret = E_OK;
if((eusart == NULL) || (value > UINT16_MAX)){
    return E_NOT_OK;
}else{
    TX_value = value;
    TX_9th_BitFramming = eusart->TX.Eusart_Frame_size;
    EUSART_TX_IN_STATE_ASSIGN(EUSART_INTERRUPT_ENABLE);
}
return ret;
}

// Std_RetuenType hal_EUSART_NON_BLOCKING_WRITE_String(const eusart_t* eusart , uint8 *chr , uint8 strlen){
//     Std_RetuenType ret = E_OK;
//     uint8 IN_Prev_state = EUSART_TX_IN_STATE;
//     if((eusart == NULL) || (strlen > UINT8_MAX) || (chr == NULL)){
//         return E_NOT_OK;
//     }else{
//         for(uint8 cnt = ZERO_INIT ; cnt < strlen ; cnt++){
//             hal_EUSART_NON_BLOCKING_WRITE(eusart,chr[cnt]);
//         }
//     }
//     return ret;   
// }
/*****************************************
 *                ISR                    *
 *****************************************/
void TX_ISR(){
    if(TX_CallbackFunction){
        TX_CallbackFunction();
    }else{/*Nothing*/}

}

void RX_ISR(){
    if(RX_CallbackFunction){
        RX_CallbackFunction();
    }else{/*Nothing*/}

    if(FERR_CallbackFunction){
        FERR_CallbackFunction();
    }else{/*Nothing*/}

    if(OERR_CallbackFunction){
        OERR_CallbackFunction();
    }else{/*Nothing*/}
    
}
/*****************************************
 *         TX/RX  CaLLBackFunctions      *
 *****************************************/
void RX_VALUE_ASSIGN(){
 *RX_value =  EUSART_RX_REG + (((EUSART_RX_9BIT_DATA) && (RX_9th_BitFramming == EUSART_RX_9BIT_ENABLE_BIT)) ? 256 : 0 );  
}

void TX_VALUE_ASSIGN(){
    EUSART_TX_IN_STATE_ASSIGN(EUSART_INTERRUPT_DISABLE);
    EUSART_TX_REG = (uint8)TX_value;
    if(TX_9th_BitFramming == EUSART_TX_9BIT_ENABLE_BIT){
     EUSART_TX_9BIT_DATA(READ_BIT(TX_value, 8));
    }   
}