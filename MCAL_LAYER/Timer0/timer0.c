/* 
 * File:   Timer0.C
 * Author: Rahim mohamed
 *
 * Created on April 20, 2024, 3:14 PM
 */

#include"Timer0.h"


/***************************************************************************************************************/
/***************************************************************************************************************/

static void (*Timer0_InterruptHandler) (void)=NULL;
static uint_16 tmr0_preload =0;

/***************************************************************************************************************/

Std_ReturnType Timer0_Init (const Timer0_t* obj){
    
      Std_ReturnType ret = E_OK;
    if (NULL == obj){
        ret=E_NOT_OK;
    }
    else{
        
        
        /*------------------------------------Disable Timer0--------------------------*/
        
        TIMER0_DISABLE();
        
        /*--------------------------------Select Register size------------------------------*/
        
        if (obj->Register_Size_flag == TIMER0_8BIT_FLAG ){
            TIMER0_8BIT_CONFIGURE();
        }
        else if (obj->Register_Size_flag == TIMER0_16BIT_FLAG ){
            TIMER0_16BIT_CONFIGURE();
        }
        else{/*Nothing*/}
        
        /*-----------------------------------Select Timer Mode-------------------------------*/
        
        if (obj->mode == Timer_mode ){
            TIMER0_TIMER_MODE();
        }
        else if (obj->mode == Counter_mode){
            TIMER0_COUNTER_MODE();
            if (obj->Edge_flag == TIMER0_RISING_FLAG){TIMER0_RISING_EDGE();} 
            else if (obj->Edge_flag == TIMER0_FALLING_FLAG){TIMER0_FAILLING_EDGE();}
            else{/*Nothing*/}
        }
        else{/*Nothing*/}
        
       /*----------------------------------- Timer PSA-------------------------------*/ 
        
        if (obj->PSA_flag == TIMER0_PSA_ON_FLAG){
            TIMER0_PSA_ON();
            T0CONbits.T0PS=obj->PSA;
        }
        else if (obj->PSA_flag == TIMER0_PSA_OFF_FLAG) {TIMER0_PSA_OFF();}
        else{/*Nothing*/}
        
       /*----------------------------------- Timer0 Interrupt -------------------------------*/
        
          #if Timer0_INTERRUPT_ENABLE == 1  
         #if INTERRUPT_PRIORITY_LEVELS_ENABLE==0
         INTERRUPT_GlobalInterrupts_Enable();
         INTERRUPT_peripheralInterrupt_Enable();
        #endif
         TIMER0_InterruptEnable();
         TIMER0_InterruptClearFlag();
         #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INERRUPT_FEAUTURE_ENABLE
         INTERRUPT_PriorityLevels_Enable();
         if (obj->priority == HIGH_priority){
             INTERRUPT_GlobalHighPriority_Enable();
             TIMER0_Interrupt_HighPrioritySet();
         }
         else{
             INTERRUPT_GlobalLowPriority_Enable();
             TIMER0_Interrupt_LowPrioritySet();
         }
         #endif
         Timer0_InterruptHandler=obj->Timer0_InterruptHandler;
         #endif

         /*----------------------------------- Tim0L & Tim0h -------------------------------*/
         TMR0H=(obj->period) >> 8;
         TMR0L=(uint_8)(obj->period);
         tmr0_preload=obj->period;
          /*------------------------------------Enable Timer0--------------------------*/
         
         TIMER0_ENABLE();
    }
    return ret;
    
    
}

/***************************************************************************************************************/

Std_ReturnType Timer0_DeInit (const Timer0_t* obj){
    
    
    
      Std_ReturnType ret = E_OK;
    if (NULL == obj){
        ret=E_NOT_OK;
    }
    else{
          TIMER0_DISABLE();
        #if Timer0_INTERRUPT_ENABLE == 1
           TIMER0_InterruptDisable();
        #endif
    }
    return ret;
    
}

/***************************************************************************************************************/

Std_ReturnType Timer0_Read_Value (const Timer0_t* obj,uint_16 * value){
    
    
      Std_ReturnType ret = E_OK;
      uint_8 l_tmr0l=0,l_tmr0h=0;
    if (NULL == obj && NULL == value){
        ret=E_NOT_OK;
    }
    else{
        
        l_tmr0l=TMR0L;
        l_tmr0h=TMR0H;
        *value = ((l_tmr0h << 8)+l_tmr0l);
         
    }
    return ret;
    
    
}

/***************************************************************************************************************/

Std_ReturnType Timer0_Write_Value (const Timer0_t* obj,uint_16  value){
    
     
      Std_ReturnType ret = E_OK;
    if (NULL == obj){
        ret=E_NOT_OK;
    }
    else{
         TMR0H=value >> 8;
         TMR0L=(uint_8)(value);
         
    }
    return ret;
   
}

/****************************************************************************************************************************/


void Timer0_ISR  (void){
    
    TIMER0_InterruptClearFlag();
     TMR0H=(tmr0_preload) >> 8;
     TMR0L=(uint_8)(tmr0_preload);
    if(Timer0_InterruptHandler){
        Timer0_InterruptHandler();
    }
    
}