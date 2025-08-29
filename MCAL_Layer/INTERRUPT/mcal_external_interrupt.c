/*******************************************************************************
 * @file       mcal_external_interrupt.c
 * @brief      Driver/Module Description
 * @date       2025/08/18
 * @time       11:59
 * @author     Omar Ibrahim
 ******************************************************************************/

/*****************************************
 *                includes                *
 *****************************************/
#include "mcal_external_interrupt.h"
/*****************************************
 *                Varibles               *
 *****************************************/
 /****************************
  *    Pointer To Function   *
  ****************************/
/****************************
 *          INx             *
 ****************************/
#if  (EXTERNAL_INTERRUPT_INT0_ENABLE)                     
 static InterruotHandler  IN0_InterruotHandler = NULL;                          
#endif 
#if  (EXTERNAL_INTERRUPT_INT1_ENABLE)                     
 static InterruotHandler  IN1_InterruotHandler = NULL;                         
#endif 
#if  (EXTERNAL_INTERRUPT_INT2_ENABLE)                     
 static InterruotHandler  IN2_InterruotHandler = NULL;                            
#endif                                                                      
 /****************************
  *          RBx             *
  ****************************/
#if  (EXTERNAL_INTERRUPT_RB4_ENABLE)                     
 static InterruotHandler RB4_InterruotHandlerRissing = NULL;
 static InterruotHandler RB4_InterruotHandlerFalling = NULL;                              
#endif   
#if  (EXTERNAL_INTERRUPT_RB5_ENABLE)                     
  static InterruotHandler RB5_InterruotHandlerRissing = NULL;
 static InterruotHandler RB5_InterruotHandlerFalling = NULL;                              
#endif
#if  (EXTERNAL_INTERRUPT_RB6_ENABLE)                     
 static InterruotHandler RB6_InterruotHandlerRissing = NULL;
 static InterruotHandler RB6_InterruotHandlerFalling = NULL;                              
#endif 
#if  (EXTERNAL_INTERRUPT_RB7_ENABLE)                     
 static InterruotHandler RB7_InterruotHandlerRissing = NULL;
 static InterruotHandler RB7_InterruotHandlerFalling = NULL;                               
#endif                                                                      
/*****************************************
 *       Helper Function Definction      *
 *****************************************/
 /****************************
  *          INx              *
  ****************************/
#ifdef  EXTERNAL_INTERRUPT_INTx_ENABLE
static Std_RetuenType interrupt_INx_enable(const EXT_IN_INx_t *INx){
Std_RetuenType ret = E_OK;
if(INx == NULL){
    ret = E_NOT_OK;
}else{
 switch (INx->source) {
        #if EXTERNAL_INTERRUPT_INT0_ENABLE
        case IN0 :    EXT_IN0_InterruptEnable();   break;
        #endif
        #if EXTERNAL_INTERRUPT_INT1_ENABLE
        case IN1 :    EXT_IN1_InterruptEnable();   break;
        #endif
        #if EXTERNAL_INTERRUPT_INT2_ENABLE
        case IN2 :    EXT_IN2_InterruptEnable();   break;
        #endif
        default: ret = E_NOT_OK;
    }
}
return ret;
}

static Std_RetuenType interrupt_INx_disable(const EXT_IN_INx_t *INx){
Std_RetuenType ret = E_OK;
if(INx == NULL){
    ret = E_NOT_OK;
}else{
 switch (INx->source) {

        #if EXTERNAL_INTERRUPT_INT0_ENABLE
        case IN0 :    EXT_IN0_InterruptDisable();   break;
        #endif
        #if EXTERNAL_INTERRUPT_INT1_ENABLE
        case IN1 :    EXT_IN1_InterruptDisable();   break;
        #endif
        #if EXTERNAL_INTERRUPT_INT2_ENABLE
        case IN2 :    EXT_IN2_InterruptDisable();   break;
        #endif
        default: ret = E_NOT_OK;
    }
}
return ret;
}

#ifdef PERIORITY_ENABLE
static Std_RetuenType interrupt_INx_periority_init(const EXT_IN_INx_t *INx){
 Std_RetuenType ret = E_OK;
if(INx == NULL){
    ret = E_NOT_OK;
}else{

     switch (INx->source) {
        #if EXTERNAL_INTERRUPT_INT1_ENABLE
        case IN1 :    (INx->priority)? EXT_IN1_SetHighPriority()   : EXT_IN1_SetLowPriority()   ;   break;
        #endif
        #if EXTERNAL_INTERRUPT_INT2_ENABLE
        case IN2 :    (INx->priority)? EXT_IN2_SetHighPriority()   : EXT_IN2_SetLowPriority()   ;   break;
        #endif
        default: ret = E_NOT_OK;
    }
}
return ret;
}
#endif

static Std_RetuenType interrupt_INx_EdgeTrigger_init(const EXT_IN_INx_t *INx){
    Std_RetuenType ret = E_OK;
if(INx == NULL){
    ret = E_NOT_OK;
}else{
switch (INx->source) {
        #if EXTERNAL_INTERRUPT_INT0_ENABLE
        case IN0 :    (INx->edge  == RISSING_EDGE)? EXT_IN0_RisingEdgeTrigger() : EXT_IN0_FallingEdgeTrigger()  ;   break;
        #endif
        #if EXTERNAL_INTERRUPT_INT1_ENABLE
        case IN1 :    (INx->edge  == RISSING_EDGE)? EXT_IN1_RisingEdgeTrigger() : EXT_IN1_FallingEdgeTrigger()  ;   break;
        #endif
        #if EXTERNAL_INTERRUPT_INT2_ENABLE
        case IN2 :    (INx->edge  == RISSING_EDGE)? EXT_IN2_RisingEdgeTrigger() : EXT_IN2_FallingEdgeTrigger()  ;   break;
        #endif
        default: ret = E_NOT_OK;
    }
}
return ret;

}

static Std_RetuenType interrupt_INx_clear_bit(const EXT_IN_INx_t *INx){
    Std_RetuenType ret = E_OK;
if(INx == NULL){
    ret = E_NOT_OK;
}else{
switch (INx->source) {
        #if  EXTERNAL_INTERRUPT_INT0_ENABLE
        case IN0 :   EXT_IN0_FlagClear()   ;   break;
        #endif
        #if EXTERNAL_INTERRUPT_INT1_ENABLE
        case IN1 :   EXT_IN1_FlagClear()   ;   break;
        #endif
        #if EXTERNAL_INTERRUPT_INT2_ENABLE
        case IN2 :   EXT_IN2_FlagClear()   ;   break;
        #endif
        default: ret = E_NOT_OK;
    }
}
return ret;
}

static Std_RetuenType interrupt_INx_CallBack(const EXT_IN_INx_t *INx){
    Std_RetuenType ret = E_OK;
if(INx == NULL){
    ret = E_NOT_OK;
}else{
switch (INx->source) {
        #if  EXTERNAL_INTERRUPT_INT0_ENABLE
        case IN0 :   IN0_InterruotHandler = INx->EXT_InterruptHandler     ;   break;
        #endif
        #if   EXTERNAL_INTERRUPT_INT1_ENABLE
        case IN1 :   IN1_InterruotHandler = INx->EXT_InterruptHandler     ;   break;
        #endif
        #if  EXTERNAL_INTERRUPT_INT2_ENABLE
        case IN2 :   IN2_InterruotHandler = INx->EXT_InterruptHandler     ;   break;
        #endif
        default: ret = E_NOT_OK;
    }
}
return ret;
}
#endif
/****************************
 *          RBx              *
 ****************************/
#if EXTERNAL_INTERRUPT_RBx_OnChange_ENABLE
static Std_RetuenType interrupt_RBx_enable(const EXT_IN_RBx_t *RBx){
      Std_RetuenType ret = E_OK;
    if(RBx  == NULL){
        ret = E_NOT_OK;
    }else{
        EXT_RBx_OnChange_InterruptEnable();
    }
    return ret;  
}

static Std_RetuenType interrupt_RBx_Disable(const EXT_IN_RBx_t *RBx){
      Std_RetuenType ret = E_OK;
    if(RBx  == NULL){
        ret = E_NOT_OK;
    }else{
        EXT_RBx_OnChange_InterruptDisable();
    }
    return ret;  
}

static Std_RetuenType interrupt_RBx_ClearBit(const EXT_IN_RBx_t *RBx){
      Std_RetuenType ret = E_OK;
    if(RBx  == NULL){
        ret = E_NOT_OK;
    }else{
        EXT_RBx_OnChange_FlagClear();
    }
    return ret;  
}

static Std_RetuenType interrupt_RBx_CallBack(const EXT_IN_RBx_t *RBx){
      Std_RetuenType ret = E_OK;
    if(RBx  == NULL){
        ret = E_NOT_OK;
    }else{
       switch (RBx ->InterruptPin) {
 
       
       #ifdef  EXTERNAL_INTERRUPT_RB4_ENABLE                
       case RB_4 :
       RB4_InterruotHandlerRissing =  RBx->EXT_InterruptHandler_RissingEdge ; 
       RB4_InterruotHandlerFalling = RBx->EXT_InterruptHandler_FallingEdge   ; 
       break;                            
       #endif  

       #ifdef  EXTERNAL_INTERRUPT_RB5_ENABLE                
       case RB_5 :
       RB5_InterruotHandlerRissing =  RBx->EXT_InterruptHandler_RissingEdge ; 
       RB5_InterruotHandlerFalling =  RBx->EXT_InterruptHandler_FallingEdge   ; 
       break;                            
       #endif 

       #ifdef  EXTERNAL_INTERRUPT_RB6_ENABLE                
       case RB_6 :
       RB6_InterruotHandlerRissing =  RBx->EXT_InterruptHandler_RissingEdge ; 
       RB6_InterruotHandlerFalling = RBx->EXT_InterruptHandler_FallingEdge   ; 
       break;                            
       #endif 

       #ifdef  EXTERNAL_INTERRUPT_RB7_ENABLE                
       case RB_7 :
       RB7_InterruotHandlerRissing =  RBx->EXT_InterruptHandler_RissingEdge ; 
       RB7_InterruotHandlerFalling = RBx->EXT_InterruptHandler_FallingEdge   ; 
       break;                            
       #endif                  
       default: ret = E_NOT_OK;
       }
    }
    return ret;  
}
#ifdef PERIORITY_ENABLE
static Std_RetuenType interrupt_RBx_Pirority(const EXT_IN_RBx_t *ٌRBx){
      Std_RetuenType ret = E_OK;
    if(ٌRBx  == NULL){
        ret = E_NOT_OK;
    }else{
      switch (ٌRBx->priority) {
      case HIGH_PRIORITY : EXT_RBx_OnChange_SetHighPriority(); break;
      case LOW_PRIORITY  : EXT_RBx_OnChange_SetLowPriority();  break;
      default: ret = E_NOT_OK;
      }
    }
    return ret;  
}
#endif
#endif
#if  ((EXTERNAL_INTERRUPT_INTx_ENABLE) || (EXTERNAL_INTERRUPT_RBx_OnChange_ENABLE) )                     

static void Genral_Periphral_InterruptEnable(void){
    #ifdef PERIORITY_ENABLE
    INTERRUPT_PeriorityEnable();
    INTRUPT_GlobalInterruptHighEnable();
    INTRUPT_GlobalInterruptLowEnable();
    #else
    INTRUPT_GlobalInterruptEnable();
    PrephralInterruptEnable();
    #endif
}                              
#endif                        
/*****************************************
 *           function definition          *
 *****************************************/
#ifdef EXTERNAL_INTERRUPT_INTx_ENABLE
Std_RetuenType interrupt_INx_intialize(const EXT_IN_INx_t *INx){
Std_RetuenType ret = E_OK;
if(INx == NULL){
    ret = E_NOT_OK;
}else{
   ret &= interrupt_INx_disable(INx);                          /**Interrupt Disable */
   ret &= interrupt_INx_clear_bit(INx);                       /**clear bit */
   ret &= interrupt_INx_EdgeTrigger_init(INx);               /**EdgeTrigger*/
   #ifdef PERIORITY_ENABLE     
   ret &= interrupt_INx_periority_init(INx);               /**Priority */
   #endif  
   ret &= interrupt_INx_CallBack(INx);                   /**CallBack Function */
   ret &= interrupt_INx_enable(INx);                    /**Interrupt Enable */ 
   Genral_Periphral_InterruptEnable();                 /**GIE(GIEH) and PEIE(GIEL) Enable */
}
return ret;
}

Std_RetuenType interrupt_INx_Disable(const EXT_IN_INx_t *INx){
Std_RetuenType ret = E_OK;
if(INx == NULL){
    ret = E_NOT_OK;
}else{
    ret = interrupt_INx_disable(INx);
}
return  ret;
}
#endif
#if EXTERNAL_INTERRUPT_RBx_OnChange_ENABLE
Std_RetuenType interrupt_RBx_intialize(const EXT_IN_RBx_t *ٌRBx){
    Std_RetuenType ret = E_OK;
    if(ٌRBx  == NULL){
        ret = E_NOT_OK;
    }else{
        interrupt_RBx_Disable(ٌRBx);             /** Interrupt disable */
        interrupt_RBx_ClearBit(ٌRBx);           /**clear Bit */
        #ifdef PERIORITY_ENABLE  
        interrupt_RBx_Pirority(ٌRBx);         /**set pirority */
        #endif
        interrupt_RBx_CallBack(ٌRBx);          /**callBack function */
        interrupt_RBx_enable(ٌRBx);           /** Interrupt enable */
        Genral_Periphral_InterruptEnable();
    }
    return ret;
}

Std_RetuenType interrupt_RBx_deintialize(const EXT_IN_RBx_t *ٌRBx){
       Std_RetuenType ret = E_OK;
    if(ٌRBx  == NULL){
        ret = E_NOT_OK;
    }else{
        interrupt_RBx_Disable(ٌRBx);
    }
    return ret; 
}
#endif
/*****************************************
 *                ISR                    *
 *****************************************/
/****************************
 *          INx              *
 ****************************/
#if EXTERNAL_INTERRUPT_INT0_ENABLE
    void IN0_ISR(void){
    EXT_IN0_FlagClear();

    if(IN0_InterruotHandler != NULL){
        IN0_InterruotHandler(); /**CallBack Function*/
    }
}   
#endif                   
                  
#if  (EXTERNAL_INTERRUPT_INT1_ENABLE)                     
void IN1_ISR(void){
    EXT_IN1_FlagClear();

    if(IN1_InterruotHandler != NULL){
        IN1_InterruotHandler();
    }
}                                           
#endif                        

#if  (EXTERNAL_INTERRUPT_INT2_ENABLE)                     
void IN2_ISR(void){
    EXT_IN2_FlagClear();
    
    if(IN2_InterruotHandler != NULL){
        IN2_InterruotHandler();
    }
}                              
#endif                        
/****************************
 *           RBx            *
 ****************************/
#if  (EXTERNAL_INTERRUPT_RB4_ENABLE)                     
void RB4_R_ISR(){
    EXT_RBx_OnChange_FlagClear();

    if(RB4_InterruotHandlerRissing != NULL){
        RB4_InterruotHandlerRissing();
    }
}
void RB4_F_ISR(){
    EXT_RBx_OnChange_FlagClear();

    if(RB4_InterruotHandlerFalling != NULL){
       RB4_InterruotHandlerFalling();
    }
}                               
#endif                        
                         
#if  (EXTERNAL_INTERRUPT_RB5_ENABLE)                     
void RB5_R_ISR(){
    EXT_RBx_OnChange_FlagClear();

    if(RB5_InterruotHandlerRissing != NULL){
        RB5_InterruotHandlerRissing();
    }
}
void RB5_F_ISR(){
    EXT_RBx_OnChange_FlagClear();

    if(RB5_InterruotHandlerFalling != NULL){
        RB5_InterruotHandlerFalling();
    }
}                          
                              
#endif                                          

#if  (EXTERNAL_INTERRUPT_RB6_ENABLE)                     
void RB6_R_ISR(){
    EXT_RBx_OnChange_FlagClear();

    if(RB6_InterruotHandlerRissing != NULL){
        RB6_InterruotHandlerRissing();
    }
}
void RB6_F_ISR(){
    EXT_RBx_OnChange_FlagClear();

    if(RB6_InterruotHandlerFalling != NULL){
        RB6_InterruotHandlerFalling();
    }
}                              
#endif                        

#if  (EXTERNAL_INTERRUPT_RB7_ENABLE)                     
void RB7_R_ISR(){
    EXT_RBx_OnChange_FlagClear();

    if(RB7_InterruotHandlerRissing != NULL){
        RB7_InterruotHandlerRissing();
    }
}
void RB7_F_ISR(){
    EXT_RBx_OnChange_FlagClear();

    if(RB7_InterruotHandlerFalling != NULL){
        RB7_InterruotHandlerFalling();
    }
}                                
#endif                        

                        

