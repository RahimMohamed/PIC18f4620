/* 
 * File:   TMR2.c
 * Author: Rahim Mohamed
 *
 * Created on April 27, 2024, 10:54 AM
 */

#include "TMR2.h"


static void (*TMR2_InterruptHandler) (void)=NULL;
static uint_8 TMR2_preload =0;

/***************************************************************************************************************/
/***************************************************************************************************************/
/***************************************************************************************************************/

Std_ReturnType TMR2_Init (const TMR2_t* obj){
    
    Std_ReturnType ret = E_OK;
    if (NULL == obj){
        ret=E_NOT_OK;
    }
    else{
/*------------------------------------Disable Timer2--------------------------*/
        TMR2_DISABLE();
/*----------------------------------- Timer PSA-------------------------------*/ 
         T2CONbits.T2CKPS=obj->PSA; 
/*----------------------------------- Timer POS-------------------------------*/ 
         T2CONbits.TOUTPS=obj->POS;         
/*-----------------------------------  -------------------------------*/
         TMR2=obj->period;
         TMR2_preload=obj->period;        
/*----------------------------------- Timer2 Interrupt -------------------------------*/
     #if TMR1_INTERRUPT_ENABLE == 1
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE==0
         INTERRUPT_GlobalInterrupts_Enable();
         INTERRUPT_peripheralInterrupt_Enable();
        #endif
         TMR2_InterruptEnable();
         TMR2_InterruptClearFlag();
         #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INERRUPT_FEAUTURE_ENABLE
         INTERRUPT_PriorityLevels_Enable();
         if (obj->priority == HIGH_priority){
             INTERRUPT_GlobalHighPriority_Enable();
             TMR2_Interrupt_HighPrioritySet();
         }
         else{
             INTERRUPT_GlobalLowPriority_Enable();
             TMR2_Interrupt_LowPrioritySet();
         }
         #endif
         TMR2_InterruptHandler=obj->Timer2_InterruptHandler;
         #endif
  
  /*------------------------------------Enable Timer2--------------------------*/
         TMR2_ENABLE();
    }
    return ret;
    
    
}
/***************************************************************************************************************/
Std_ReturnType TMR2_DeInit (const TMR2_t* obj){
    
      Std_ReturnType ret = E_OK;
    if (NULL == obj){
        ret=E_NOT_OK;
    }
    else{
          TMR2_DISABLE();
         #if TMR2_INTERRUPT_ENABLE == 1
           TMR2_InterruptDisable();
        #endif
    }
    return ret;
    
    
}
/***************************************************************************************************************/
Std_ReturnType TMR2_Read_Value (const TMR2_t* obj,uint_8 * value){
    
    
     Std_ReturnType ret = E_OK;
    if (NULL == obj){
        ret=E_NOT_OK;
    }
    else{
        *value=TMR2;  
    }
    return ret;
    
    
}
/***************************************************************************************************************/
Std_ReturnType TMR2_Write_Value (const TMR2_t* obj,uint_8  value){
    
      Std_ReturnType ret = E_OK;
    if (NULL == obj){
        ret=E_NOT_OK;
    }
    else{
          TMR2=value; 
    }
    return ret;
    
    
}

/*******************************************************************************************************************************/

void TMR2_ISR  (void){
    
    TMR2_InterruptClearFlag();
    TMR2=TMR2_preload;
    if(TMR2_InterruptHandler){
        TMR2_InterruptHandler();
    }
    
}
