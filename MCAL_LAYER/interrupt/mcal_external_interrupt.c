/* 
 * File:   mcal_external_interrupt.c
 * Author: gaming3
 *
 * Created on February 14, 2024, 1:33 PM
 */
#include "mcal_external_interrupt.h"

/****************************************************************************************************************************/

static void (*INT0_InterruptHandler) (void)=NULL;
static void (*INT1_InterruptHandler) (void)=NULL;
static void (*INT2_InterruptHandler) (void)=NULL;

static void (*RB4_InterruptHandler) (void)=NULL;
static void (*RB5_InterruptHandler) (void)=NULL;
static void (*RB6_InterruptHandler) (void)=NULL;
static void (*RB7_InterruptHandler) (void)=NULL;

static Std_ReturnType Interrupt_INTx_Enable   (const  interrupt_INTx_t * int_obj);
static Std_ReturnType Interrupt_INTx_Disable   (const  interrupt_INTx_t * int_obj);
static Std_ReturnType Interrupt_INTx_Priority_Init   (const  interrupt_INTx_t * int_obj);
static Std_ReturnType Interrupt_INTx_Edge_Init   (const  interrupt_INTx_t * int_obj);
static Std_ReturnType Interrupt_INTx_Pin_Init   (const  interrupt_INTx_t * int_obj);
static Std_ReturnType Interrupt_INTx_ClearFlag   (const  interrupt_INTx_t * int_obj);

static Std_ReturnType INT0_SetInterruptHandler (void (*INTx_InterruptHandeler) (void));
static Std_ReturnType INT1_SetInterruptHandler (void (*INTx_InterruptHandeler) (void));
static Std_ReturnType INT2_SetInterruptHandler (void (*INTx_InterruptHandeler) (void));
static Std_ReturnType SetInterruptHandler (const  interrupt_INTx_t * int_obj);

static Std_ReturnType Interrupt_RBx_Enable   (const  interrupt_RBx_t * int_obj);
static Std_ReturnType Interrupt_RBx_Disable   (const  interrupt_RBx_t * int_obj);
static Std_ReturnType Interrupt_RBx_Priority_Init   (const  interrupt_RBx_t * int_obj);
static Std_ReturnType Interrupt_RBx_Pin_Init   (const  interrupt_RBx_t * int_obj);

/****************************************************************************************************************************/

Std_ReturnType Interrupt_INTx_Init   (const  interrupt_INTx_t * int_obj){
    
    
      Std_ReturnType ret = E_OK;
    if (NULL == int_obj ){
        ret=E_NOT_OK;
    }
    else{
        /*To intialize interrupt must do following steps  */       
        Interrupt_INTx_Disable(int_obj); //disable the external interrupt
        Interrupt_INTx_ClearFlag(int_obj);//clear interrupt flag : External interrupt did not occur
        Interrupt_INTx_Edge_Init(int_obj); //configure external interrupt edge
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INERRUPT_FEAUTURE_ENABLE
         Interrupt_INTx_Priority_Init(int_obj);//configure external interrupt priority
#endif
        Interrupt_INTx_Pin_Init(int_obj);//configure external interrupt I/O
        SetInterruptHandler(int_obj);//configure default interrupt callback
        Interrupt_INTx_Enable(int_obj); //Enable the external interrupt
        
    }
    return ret;
    
    
    
}
/****************************************************************************************************************************/
void INT0_ISR (void){
    
    /*The INT0 external interrupt occurred (flag must be cleared)*/
    EXT_INT0_ClearFlag();
    
    /* code */
    
    /* Callback function */
    if (INT0_InterruptHandler){
        INT0_InterruptHandler();
    }
    
}

void INT1_ISR (void){
    
    /*The INT1 external interrupt occurred (flag must be cleared)*/
    EXT_INT1_ClearFlag();
    
    /* code */
    
    /* Callback function */
    if (INT1_InterruptHandler){
        INT1_InterruptHandler();
    }
    
}

void INT2_ISR (void){
    
    /*The INT2 external interrupt occurred (flag must be cleared)*/
    EXT_INT2_ClearFlag();
    
    /* code */
    
    /* Callback function */
    if (INT2_InterruptHandler){
        INT2_InterruptHandler();
    }
    
}
#if EXTERNAL_INTERRUPT_OnCharge_ENABLE ==1
void RB4_ISR  (void){
    /*The INT2 external interrupt occurred (flag must be cleared)*/
    EXT_RBx_ClearFlag();
    
    /* code */
    
    /* Callback function */
    if (RB4_InterruptHandler){
        RB4_InterruptHandler();
    }
}


/****************************************************************************************************************************/

Std_ReturnType Interrupt_RBx_Init   (const  interrupt_RBx_t * int_obj){
    
       Std_ReturnType ret = E_OK;
    if (NULL == int_obj ){
        ret=E_NOT_OK;
    }
    else{
    
         /*To intialize interrupt must do following steps  */       
         EXT_RBx_Disable(); //disable the external interrupt
         EXT_RBx_ClearFlag();//clear interrupt flag : External interrupt did not occur
          # if INTERRUPT_PRIORITY_LEVELS_ENABLE == INERRUPT_FEAUTURE_ENABLE 
               INTERRUPT_PriorityLevels_Enable();
                    if (LOW_priority==int_obj->priority_level){
                        INTERRUPT_GlobalLowPriority_Enable();
                        EXT_RBx_LowPrioritySet();
                    }
                    else if (HIGH_priority==int_obj->priority_level){
                        INTERRUPT_GlobalHighPriority_Enable();
                        EXT_RBx_HighPrioritySet();
                    }
                    else { /*Nothing*/}
                    
            #else        
                    INTERRUPT_GlobalInterrupts_Enable();
                    INTERRUPT_peripheralInterrupt_Enable();
            #endif  
                    gpio_pin_direction_intialize(&(int_obj->pin));
             switch (int_obj->pin.pin){
                 case GPIO_PIN4:
                     RB4_InterruptHandler=int_obj->EXT_InterruptHandeler;
                     break;
                case GPIO_PIN5:
                     RB5_InterruptHandler=int_obj->EXT_InterruptHandeler;
                     break;
                case GPIO_PIN6:
                     RB6_InterruptHandler=int_obj->EXT_InterruptHandeler;
                     break;
                case GPIO_PIN7:
                     RB7_InterruptHandler=int_obj->EXT_InterruptHandeler;
                     break;    
             }   
             
                    
         EXT_RBx_Enable(); //Enable the external interrupt
        
       
    }
    return ret;
    
    
}





/****************************************************************************************************************************/

Std_ReturnType Interrupt_RBx_DeInit (const  interrupt_RBx_t * int_obj){
    
       Std_ReturnType ret = E_OK;
    if (NULL == int_obj ){
        ret=E_NOT_OK;
    }
    else{
    
       
    }
    return ret;
    
    
    
}
#endif

/****************************************************************************************************************************/

Std_ReturnType Interrupt_INTx_DeInit (const  interrupt_INTx_t * int_obj){
    
    
       Std_ReturnType ret = E_OK;
    if (NULL == int_obj ){
        ret=E_NOT_OK;
    }
    else{
           
        Interrupt_INTx_Disable(int_obj);
       
    }
    return ret;
    
    
    
}





/****************************************************************************************************************************/
/****************************************************************************************************************************/
/************************************************Helper functions section****************************************************/
/****************************************************************************************************************************/
/****************************************************************************************************************************/

static Std_ReturnType Interrupt_INTx_Enable   (const  interrupt_INTx_t * int_obj){
    
        Std_ReturnType ret = E_OK;
    if (NULL == int_obj ){
        ret=E_NOT_OK;
    }
    else{
            switch (int_obj->intx){
                case EXT_INT0 : 
                    
            # if INTERRUPT_PRIORITY_LEVELS_ENABLE == INERRUPT_FEAUTURE_ENABLE
                     INTERRUPT_PriorityLevels_Enable();
            #else        
                    INTERRUPT_GlobalInterrupts_Enable();
                    INTERRUPT_peripheralInterrupt_Enable();
            #endif        
                    EXT_INT0_Enable();
                    ret=E_OK;break;
                case EXT_INT1 : 
            # if INTERRUPT_PRIORITY_LEVELS_ENABLE == INERRUPT_FEAUTURE_ENABLE 
               INTERRUPT_PriorityLevels_Enable();
                    if (LOW_priority==int_obj->priority_level){INTERRUPT_GlobalLowPriority_Enable();}
                    else if (HIGH_priority==int_obj->priority_level){INTERRUPT_GlobalHighPriority_Enable();}
                    else { /*Nothing*/}
                    
            #else        
                    INTERRUPT_GlobalInterrupts_Enable();
                    INTERRUPT_peripheralInterrupt_Enable();
            #endif        
                    EXT_INT1_Enable(); 
                    ret=E_OK;break;
                case EXT_INT2 : 
                     # if INTERRUPT_PRIORITY_LEVELS_ENABLE == INERRUPT_FEAUTURE_ENABLE 
              INTERRUPT_PriorityLevels_Enable();
                    if (LOW_priority==int_obj->priority_level){INTERRUPT_GlobalLowPriority_Enable();}
                    else if (HIGH_priority==int_obj->priority_level){INTERRUPT_GlobalHighPriority_Enable();}
                    else { /*Nothing*/}
                    
            #else        
                    INTERRUPT_GlobalInterrupts_Enable();
                    INTERRUPT_peripheralInterrupt_Enable();
            #endif        
                    EXT_INT2_Enable();
                    ret=E_OK;break;
                default :ret=E_NOT_OK;
            } 
       
    }
    return ret;
}

/****************************************************************************************************************************/

static Std_ReturnType Interrupt_INTx_Disable   (const  interrupt_INTx_t * int_obj){
    
        Std_ReturnType ret = E_OK;
    if (NULL == int_obj ){
        ret=E_NOT_OK;
    }
    else{
          
        switch (int_obj->intx){
                case EXT_INT0 : EXT_INT0_Disable(); ret=E_OK;break;
                case EXT_INT1 : EXT_INT1_Disable(); ret=E_OK;break;
                case EXT_INT2 : EXT_INT2_Disable(); ret=E_OK;break;
                default :ret=E_NOT_OK;
            } 
      
    }
    return ret;
}


/****************************************************************************************************************************/

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INERRUPT_FEAUTURE_ENABLE 
static Std_ReturnType Interrupt_INTx_Priority_Init   (const  interrupt_INTx_t * int_obj){
    
        Std_ReturnType ret = E_OK;
    if (NULL == int_obj ){
        ret=E_NOT_OK;
    }
    else{
              
            switch (int_obj->intx){
                
                case EXT_INT1 :
                    if (LOW_priority==int_obj->priority_level){EXT_INT1_LowPrioritySet();}
                    else if (HIGH_priority==int_obj->priority_level){EXT_INT1_HighPrioritySet();}
                    else { /*Nothing*/}
                    ret=E_OK;
                    break;
                case EXT_INT2 :
                    if (LOW_priority==int_obj->priority_level){EXT_INT2_LowPrioritySet();}
                    else if (HIGH_priority==int_obj->priority_level){EXT_INT2_HighPrioritySet();}
                    else { /*Nothing*/}
                    ret=E_OK;
                    break;
                default :
                    ret=E_NOT_OK;
            } 
        
       
    }
    return ret;
}
#endif
/****************************************************************************************************************************/

static Std_ReturnType Interrupt_INTx_Edge_Init   (const  interrupt_INTx_t * int_obj){
    
        Std_ReturnType ret = E_OK;
    if (NULL == int_obj ){
        ret=E_NOT_OK;
    }
    else{
        
        
          switch (int_obj->intx){
                case EXT_INT0 :
                    if (Failing_Edge==int_obj->edge){EXT_INT0_FalingEdgeSet();}
                    else if (Rising_Edge==int_obj->edge){EXT_INT0_RisingEdgeSet();}
                    else { /*Nothing*/}
                    ret=E_OK;
                    break;
                case EXT_INT1 :
                    if (Failing_Edge==int_obj->edge){EXT_INT1_FalingEdgeSet();}
                    else if (Rising_Edge==int_obj->edge){EXT_INT1_RisingEdgeSet();}
                    else { /*Nothing*/}
                    ret=E_OK;
                    break;
                case EXT_INT2 :
                     if (Failing_Edge==int_obj->edge){EXT_INT2_FalingEdgeSet();}
                    else if (Rising_Edge==int_obj->edge){EXT_INT2_RisingEdgeSet();}
                    else { /*Nothing*/}
                    ret=E_OK;
                    break;
                default :
                    ret=E_NOT_OK;
            } 
       
    }
    return ret;
}

/****************************************************************************************************************************/


static Std_ReturnType Interrupt_INTx_Pin_Init   (const  interrupt_INTx_t * int_obj){
 
        Std_ReturnType ret = E_OK;
    if (NULL == int_obj ){
        ret=E_NOT_OK;
    }
    else{
    
      gpio_pin_direction_intialize(&(int_obj->pin)); 
    }
    return ret;
}


/****************************************************************************************************************************/

static Std_ReturnType Interrupt_INTx_ClearFlag   (const  interrupt_INTx_t * int_obj){
    
    
       Std_ReturnType ret = E_OK;
    if (NULL == int_obj ){
        ret=E_NOT_OK;
    }
    else{
          
        switch (int_obj->intx){
                case EXT_INT0 : EXT_INT0_ClearFlag(); ret=E_OK;break;
                case EXT_INT1 : EXT_INT1_ClearFlag(); ret=E_OK;break;
                case EXT_INT2 : EXT_INT2_ClearFlag(); ret=E_OK;break;
                default :ret=E_NOT_OK;
            } 
      
    }
    return ret;
    
}
/****************************************************************************************************************************/
/****************************************************************************************************************************/

static Std_ReturnType INT0_SetInterruptHandler (void (*INTx_InterruptHandeler) (void)){
    
         Std_ReturnType ret = E_OK;
    if (NULL == INTx_InterruptHandeler ){
        ret=E_NOT_OK;
    }
    else{
      INT0_InterruptHandler=INTx_InterruptHandeler;
        ret=E_OK;
    }
    return ret;
    
}

/****************************************************************************************************************************/


static Std_ReturnType INT1_SetInterruptHandler (void (*INTx_InterruptHandeler) (void)){
    
        Std_ReturnType ret = E_OK;
    if (NULL == INTx_InterruptHandeler ){
        ret=E_NOT_OK;
    }
    else{
      INT1_InterruptHandler=INTx_InterruptHandeler;
       ret=E_OK;
    }
    return ret;
}

/****************************************************************************************************************************/
static Std_ReturnType INT2_SetInterruptHandler (void (*INTx_InterruptHandeler) (void)){
    
        Std_ReturnType ret = E_OK;
    if (NULL == INTx_InterruptHandeler ){
        ret=E_NOT_OK;
    }
    else{
      INT2_InterruptHandler=INTx_InterruptHandeler;
       ret=E_OK;
    }
    return ret;
    
}

/****************************************************************************************************************************/
static Std_ReturnType SetInterruptHandler (const  interrupt_INTx_t * int_obj){
    
    
        Std_ReturnType ret = E_OK;
    if (NULL == int_obj ){
        ret=E_NOT_OK;
    }
    else{
          
        switch (int_obj->intx){
                case EXT_INT0 : INT0_SetInterruptHandler(int_obj->EXT_InterruptHandeler); ret=E_OK;break;
                case EXT_INT1 : INT1_SetInterruptHandler(int_obj->EXT_InterruptHandeler); ret=E_OK;break;
                case EXT_INT2 : INT2_SetInterruptHandler(int_obj->EXT_InterruptHandeler); ret=E_OK;break;
                default :ret=E_NOT_OK;
            } 
      
    }
    return ret;
    
}