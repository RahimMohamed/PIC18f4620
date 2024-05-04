/* 
 * File:   TMR3.c
 * Author: Rahim Mohamed
 
 * Created on April 27, 2024, 12:58 PM
 */

#include "TMR3.h"
/********************************************************************************************************/

static void (*TMR3_InterruptHandler) (void)=NULL;
static uint_16 TMR3_preload =0;

/********************************************************************************************************/
/********************************************************************************************************/

Std_ReturnType TMR3_Init (const TMR3_t* obj){
      Std_ReturnType ret = E_OK;
    if (NULL == obj){
        ret=E_NOT_OK;
    }
    else{
/*------------------------------------Disable Timer3--------------------------*/
        TMR3_DISABLE();
/*----------------------------------- Timer PSA-------------------------------*/ 
         T3CONbits.T3CKPS=obj->PSA;         
/*-----------------------------------Select Timer Mode-------------------------------*/
        if (obj->mode == TMR3_TIMER_MODE_FLAG){
            TMR3_TIMER_MODE(); 
        }
        else if (obj->mode ==  TMR3_COUNTER_MODE_FLAG ){
            TMR3_COUNTER_MODE();
              if (obj->Counter_mode==TMR3_SYN_COUNTER_MODE ){TMR3_SYNCHRONOUS_COUNTER();}
              else if (obj->Counter_mode==TMR3_ASYN_COUNTER_MODE ){TMR3_ASYNCHRONOUS_COUNTER();}
              else{/*Nothing*/}
        }
        else{/*Nothing*/}
         
/*----------------------------------- Tim1L & Tim1h -------------------------------*/
         TMR3H=(obj->period) >> 8;
         TMR3L=(uint_8)(obj->period);
         TMR3_preload=obj->period;        
/*--------------------------------Select R/W Operations Numbers------------------------------*/
        if (obj->RW_flag == TMR3_RW_ONE_FLAG ){
            TMR3_RW_ONE_OPER(); 
        }
        else if (obj->RW_flag == TMR3_RW_TWO_FLAG ){
           TMR3_RW_TWO_OPER(); 
        }
        else{/*Nothing*/}
/*----------------------------------- Timer3 Interrupt -------------------------------*/
        #if TMR3_INTERRUPT_ENABLE == 1
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE==0
         INTERRUPT_GlobalInterrupts_Enable();
         INTERRUPT_peripheralInterrupt_Enable();
        #endif
         TMR3_InterruptEnable();
         TMR3_InterruptClearFlag();
         #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INERRUPT_FEAUTURE_ENABLE
         INTERRUPT_PriorityLevels_Enable();
         if (obj->priority == HIGH_priority){
             INTERRUPT_GlobalHighPriority_Enable();
             TMR3_Interrupt_HighPrioritySet();
         }
         else{
             INTERRUPT_GlobalLowPriority_Enable();
             TMR3_Interrupt_LowPrioritySet();
         }
         #endif
         TMR3_InterruptHandler=obj->Timer3_InterruptHandler;
         #endif
  
  /*------------------------------------Enable Timer1--------------------------*/
         TMR3_ENABLE();
    }
    return ret;
    
}
/********************************************************************************************************/
Std_ReturnType TMR3_DeInit (const TMR3_t* obj){
    
       Std_ReturnType ret = E_OK;
    if (NULL == obj){
        ret=E_NOT_OK;
    }
    else{
          TMR3_DISABLE();
         #if TMR3_INTERRUPT_ENABLE == 1
           TMR3_InterruptDisable();
        #endif
    }
    return ret;
    
}
/********************************************************************************************************/
Std_ReturnType TMR3_Read_Value (const TMR3_t* obj,uint_16 * value){
    
       Std_ReturnType ret = E_OK;
      uint_8 l_tmr3l=0,l_tmr3h=0;
    if (NULL == obj && NULL == value){
        ret=E_NOT_OK;
    }
    else{
        
        l_tmr3l=TMR3L;
        l_tmr3h=TMR3H;
        *value = ((l_tmr3h << 8)+l_tmr3l);
         
    }
    return ret;
    
}
/********************************************************************************************************/
Std_ReturnType TMR3_Write_Value (const TMR3_t* obj,uint_16  value){
    
        
     Std_ReturnType ret = E_OK;
    if (NULL == obj){
        ret=E_NOT_OK;
    }
    else{
         TMR3H=value >> 8;
         TMR3L=(uint_8)(value);
         
    }
    return ret;
    
}

/*******************************************************************************************************************************/

void TMR3_ISR  (void){
    
    TMR3_InterruptClearFlag();
     TMR3H=(TMR3_preload) >> 8;
     TMR3L=(uint_8)(TMR3_preload);
    if(TMR3_InterruptHandler){
        TMR3_InterruptHandler();
    }
    
}