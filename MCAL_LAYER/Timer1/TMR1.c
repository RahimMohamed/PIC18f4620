/* 
 * File:   TMR1.c
 * Author: Rahim Mohamed
 *
 * Created on April 25, 2024, 5:14 PM
 */

#include "TMR1.h"
/***************************************************************************************************************/
/***************************************************************************************************************/

static void (*TMR1_InterruptHandler) (void)=NULL;
static uint_16 TMR1_preload =0;
/*******************************************************************************************************************************/

Std_ReturnType TMR1_Init (const TMR1_t* obj){
    
      Std_ReturnType ret = E_OK;
    if (NULL == obj){
        ret=E_NOT_OK;
    }
    else{
/*------------------------------------Disable Timer1--------------------------*/
        TMR1_DISABLE();
/*----------------------------------- Timer PSA-------------------------------*/ 
         T1CONbits.T1CKPS=obj->PSA;         
/*-----------------------------------Select Timer Mode-------------------------------*/
        if (obj->mode == TMR1_TIMER_MODE_FLAG){
            TMR1_TIMER_MODE(); 
        }
        else if (obj->mode ==  TMR1_COUNTER_MODE_FLAG ){
            TMR1_COUNTER_MODE();
              if (obj->Counter_mode==TMR1_SYN_COUNTER_MODE ){TMR1_SYNCHRONOUS_COUNTER();}
              else if (obj->Counter_mode==TMR1_ASYN_COUNTER_MODE ){TMR1_ASYNCHRONOUS_COUNTER();}
              else{/*Nothing*/}
        }
        else{/*Nothing*/}
         
/*----------------------------------- Tim1L & Tim1h -------------------------------*/
         TMR1H=(obj->period) >> 8;
         TMR1L=(uint_8)(obj->period);
         TMR1_preload=obj->period;        
/*--------------------------------Select R/W Operations Numbers------------------------------*/
        if (obj->RW_flag == TMR1_RW_ONE_FLAG ){
            TMR1_RW_ONE_OPER(); 
        }
        else if (obj->RW_flag == TMR1_RW_TWO_FLAG ){
           TMR1_RW_TWO_OPER(); 
        }
        else{/*Nothing*/}
          /*--------------------------------Select OSC ------------------------------*/
        if (obj->OSC_mode == TMR1_OSC_ENABLE_FLAG){
           TMR1_OSC_ENABLE();  
        }
        else if (obj->OSC_mode == TMR1_OSC_DISABLE_FLAG){
        TMR1_OSC_DISABLE();  
        }
        else{/*Nothing*/}
 
       /*----------------------------------- Timer1 Interrupt -------------------------------*/
        #if TMR1_INTERRUPT_ENABLE == 1
         #if INTERRUPT_PRIORITY_LEVELS_ENABLE==0
         INTERRUPT_GlobalInterrupts_Enable();
         INTERRUPT_peripheralInterrupt_Enable();
        #endif
         TMR1_InterruptEnable();
         TMR1_InterruptClearFlag();
         #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INERRUPT_FEAUTURE_ENABLE
         INTERRUPT_PriorityLevels_Enable();
         if (obj->priority == HIGH_priority){
             INTERRUPT_GlobalHighPriority_Enable();
             TMR1_Interrupt_HighPrioritySet();
         }
         else{
             INTERRUPT_GlobalLowPriority_Enable();
             TMR1_Interrupt_LowPrioritySet();
         }
         #endif
         TMR1_InterruptHandler=obj->Timer1_InterruptHandler;
         #endif
  
  /*------------------------------------Enable Timer1--------------------------*/
         TMR1_ENABLE();
    }
    return ret;
    
}

/*******************************************************************************************************************************/
Std_ReturnType TMR1_DeInit (const TMR1_t* obj){
    
       Std_ReturnType ret = E_OK;
    if (NULL == obj){
        ret=E_NOT_OK;
    }
    else{
          TMR1_DISABLE();
         #if TMR1_INTERRUPT_ENABLE == 1
           TMR1_InterruptDisable();
        #endif
    }
    return ret;
    
    
}

/*******************************************************************************************************************************/
Std_ReturnType TMR1_Read_Value (const TMR1_t* obj,uint_16 * value){
    
    
    Std_ReturnType ret = E_OK;
      uint_8 l_tmr1l=0,l_tmr1h=0;
    if (NULL == obj && NULL == value){
        ret=E_NOT_OK;
    }
    else{
        
        l_tmr1l=TMR1L;
        l_tmr1h=TMR1H;
        *value = ((l_tmr1h << 8)+l_tmr1l);
         
    }
    return ret;
    
    
}

/*******************************************************************************************************************************/
Std_ReturnType TMR1_Write_Value (const TMR1_t* obj,uint_16  value){
    
    
     Std_ReturnType ret = E_OK;
    if (NULL == obj){
        ret=E_NOT_OK;
    }
    else{
         TMR1H=value >> 8;
         TMR1L=(uint_8)(value);
         
    }
    return ret;
    
}

/*******************************************************************************************************************************/

void TMR1_ISR  (void){
    
    TMR1_InterruptClearFlag();
     TMR1H=(TMR1_preload) >> 8;
     TMR1L=(uint_8)(TMR1_preload);
    if(TMR1_InterruptHandler){
        TMR1_InterruptHandler();
    }
    
}