/*******************************************************************************
 * @file       hal_timer1.c
 * @brief      Driver/Module Description
 * @date       2025/09/04
 * @time       10:13
 * @author     Omar Ibrahim
 ******************************************************************************/

/*****************************************
 *                includes                *
 *****************************************/
 #include "hal_timer1.h"
/*****************************************
 *                Varibles               *
 *****************************************/
static uint16 Preloaded_Value;
static uint8 RW_Mode;
InterruotHandler Timer1_Interrupt_Handler_call;
/*****************************************
 *          Function Decleration         *
 *****************************************/
Std_RetuenType GLOBAL_INTERRUPT_RETURN_STATE(uint8 PrevState);
void GLOBAL_INTERUPT_DISABLE();
void Timer1_IN_init(priority_t Timer1_priority);
Std_RetuenType Module_INTERRUPT_ClEAR_FLAG(uint8 Reg,uint8 bit_pos);
/*****************************************
 *            Helper Functions           *
 *****************************************/
static inline Std_RetuenType Timer1_clk_source(const timer1_t *Timer1){
Std_RetuenType ret = E_OK;
if(Timer1 == NULL){
    return E_NOT_OK;
}else{
    switch (Timer1->Timer1_clk_source) {
    case TIMER1_PRIMARY_CLK_SOURCE   :
    TIMER1_OSCILLATOR_DISABLE();
    if(TIMER1_USED_CLK_SOUREC == TIMER1_SECONDARY_CLK_SOURCE) return E_NOT_OK;
    break;
    case TIMER1_SECONDARY_CLK_SOURCE :
    TIMER1_OSCILLATOR_ENABLE();
    if(TIMER1_USED_CLK_SOUREC == TIMER1_PRIMARY_CLK_SOURCE) return E_NOT_OK;
    break;
    default: return E_NOT_OK;
    }
}
return ret;
}

static inline Std_RetuenType Timer1_Prescaler(const timer1_t *Timer1){
Std_RetuenType ret = E_OK;
if(Timer1 == NULL){
    return E_NOT_OK;
}else{
    switch (Timer1->Timer1_Prescaler) {
    case TIMER1_PRESCALER_OFF     : TIMER1_CHOOSE_PRESCALER_VALUE(TIMER1_PRESCALER_OFF     ) ; break;
    case TIMER1_PRESCALER_1_div_2 : TIMER1_CHOOSE_PRESCALER_VALUE(TIMER1_PRESCALER_1_div_2 ) ; break;
    case TIMER1_PRESCALER_1_div_4 : TIMER1_CHOOSE_PRESCALER_VALUE(TIMER1_PRESCALER_1_div_4 ) ; break;
    case TIMER1_PRESCALER_1_div_8 : TIMER1_CHOOSE_PRESCALER_VALUE(TIMER1_PRESCALER_1_div_8 ) ; break;
    default: return E_NOT_OK;
    }
}
return ret;
}

static inline Std_RetuenType Timer1_Operation_Mode(const timer1_t *Timer1){
Std_RetuenType ret = E_OK;
if(Timer1 == NULL){
    return E_NOT_OK;
}else{
    switch (Timer1->Timer1_Operation_Mode) {
    case TIMER1_TIMER_MODE     : TIMER1_TIMER_MODE_SELECT()       ; break;
    case TIMER1_COUNTER_MODE   : TIMER1_COUNTER_MODE_SELECT()     ; break;
    default: return E_NOT_OK;
    }
}
return ret;
}

static inline Std_RetuenType Timer1_Counter_synchronization(const timer1_t *Timer1){
Std_RetuenType ret = E_OK;
if(Timer1 == NULL){
    return E_NOT_OK;
}else{
    switch (Timer1->Timer1_Counter_synchronization) {
    case Timer1_SYNCHRONOUS_COUNTER     : TIMER1_SYNCHRONOUS_COUNTER_ENABLE()       ; break;
    case Timer1_ASYNCHRONOUS_COUNTER   : TIMER1_ASYNCHRONOUS_COUNTER_ENABLE()       ; break;
    default: return E_NOT_OK;
    }
}
return ret;
}

static inline Std_RetuenType Timer1_RW_BitMode(const timer1_t *Timer1){
Std_RetuenType ret = E_OK;
if(Timer1 == NULL){
    return E_NOT_OK;
}else{
    switch (Timer1->Timer1_RW_BitMode) {
    case TIMER1_16BIT_RW_MODE     : TIMER1_16BIT_RW_MODE_ENABLE()       ; break;
    case TIMER1_8BIT_RW_MODE      : TIMER1_8BIT_RW_MODE_ENABLE()        ; break;
    default: return E_NOT_OK;
    }
}
return ret;
}

#if  (TIMER1_IN_ENABLE)
static inline Std_RetuenType Timer1_Interrupt_Handler(const timer1_t *Timer1){
Std_RetuenType ret = E_OK;
if(Timer1 == NULL){
    return E_NOT_OK;
}else{
    Timer1_Interrupt_Handler_call = Timer1->Timer1_Interrupt_Handler;
}
return ret;
}
#endif

/*****************************************
 *           function definition          *
 *****************************************/
Std_RetuenType hal_Timer1_init(const timer1_t *Timer1){
Std_RetuenType ret = E_OK;
#if  (TIMER1_IN_ENABLE)
priority_t Timer1_priority_select = LOW_PRIORITY;
#if  (PERIORITY_ENABLE)
Timer1_priority_select = Timer1->Timer1_Priority;
#endif
#endif
if(Timer1 == NULL){
    return E_NOT_OK;
}else{
    GLOBAL_INTERUPT_DISABLE();                                                          /** GIE Disable */
    TIMER1_ENABLE();                                                                   /** Prephral enable */
    Timer1_Operation_Mode(Timer1);                                                    /** Operation Mode  */
    Timer1_clk_source(Timer1);                                                       /** Clk Source  */
    Timer1_Prescaler(Timer1);                                                       /** Prescaler Value  */
    Timer1_Counter_synchronization(Timer1);                                        /** CounterMode Sync/Async  */
    Timer1_RW_BitMode(Timer1);                                                    /** R/W  8/16 Bit  */
    hal_Timer1_Write_value(Timer1,Timer1->Timer1_Preloaded_value);         /**  Reloaded Value Reg Loading  */
    RW_Mode          = Timer1->Timer1_RW_BitMode;                               /** R/w Value copy  */

    /** IN init  */
    #if  (TIMER1_IN_ENABLE)
    Timer1_Interrupt_Handler(Timer1);
    Timer1_IN_init(Timer1_priority_select);
    #endif
}
return ret;
}

Std_RetuenType hal_Timer1_deinit(const timer1_t *Timer1){
Std_RetuenType ret = E_OK;
if(Timer1 == NULL){
    return E_NOT_OK;
}else{
  TIMER1_DISABLE();
}
return ret;
}

Std_RetuenType hal_Timer1_Read_value(const timer1_t *Timer1, uint16 *Value){
Std_RetuenType ret = E_OK;
if(Value == NULL){
    return E_NOT_OK;
}else{
     *Value = TIMER1_LOW_BYTE_REG;
     if(Timer1->Timer1_RW_BitMode == TIMER1_16BIT_RW_MODE){
     *Value += ((uint16)TIMER1_HIGH_BYTE_REG << ONE_BYTE_SHIFT);
      }
      Preloaded_Value  = Timer1->Timer1_Preloaded_value;                         /** Preloaded_Value Copy  */
}
return ret;
}

Std_RetuenType hal_Timer1_Write_value(const timer1_t *Timer1, uint16 Value){
Std_RetuenType ret = E_OK;
if(Value > UINT16_MAX){
    return E_NOT_OK;
}else{
    if(Timer1->Timer1_RW_BitMode == TIMER1_16BIT_RW_MODE){
      TIMER1_HIGH_BYTE_REG = (uint8)(Value >> ONE_BYTE_SHIFT);
    }
      TIMER1_LOW_BYTE_REG = (uint8)(Value);
   }
return ret;
}
/*****************************************
 *                ISR                    *
 *****************************************/
void TIMER1_ISR(){
    Module_INTERRUPT_ClEAR_FLAG(TIMER1_FLAG_REG,TIMER1_FLAG_BIT);

    if(RW_Mode == TIMER1_16BIT_RW_MODE){
      TIMER1_HIGH_BYTE_REG = (uint8)(Preloaded_Value >> ONE_BYTE_SHIFT);
    }
    TIMER1_LOW_BYTE_REG  = (uint8)(Preloaded_Value);

    Timer1_Interrupt_Handler_call();
}