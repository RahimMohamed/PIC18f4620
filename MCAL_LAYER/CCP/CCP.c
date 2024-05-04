
/* 
 * File:   CPP.h
 * Author: Rahim Mohamed
 *
 * Created on April 27, 2024, 3:01 PM
 */

#include "CCP.h"

/***********************************************************************************************************************************/
static void CCPx_SET_CAPTURE_MODE (const CCPx_t * ccp_obj);
static void CCPx_SET_COMPARE_MODE (const CCPx_t * ccp_obj);
static void CCPx_SET_PWM_MODE (const CCPx_t * ccp_obj);
static void CCPx_SET_TIMER_CONFIG (const CCPx_t * ccp_obj);

static void (*CCP1_InterruptHandler) (void)=NULL;
static void (*CCP2_InterruptHandler) (void)=NULL;


/***********************************************************************************************************************************/
/***********************************************************************************************************************************/
/***********************************************************************************************************************************/
Std_ReturnType CCPx_Init (const CCPx_t* ccp_obj){
    
       Std_ReturnType ret = E_OK;
    if (NULL ==ccp_obj){
        ret=E_NOT_OK;
    }
    else{
        
        /*============================================Disable Module===================================================*/
        if (ccp_obj->CCPx == CCP1_MODULE_CONFIG){CCP1_SET_MODE(CCPx_MODULE_DISABLE);}
        else if (ccp_obj->CCPx == CCP2_MODULE_CONFIG){CCP2_SET_MODE(CCPx_MODULE_DISABLE);}
        else {/*Nothing*/}
       /*==========================================Set Module Mode=====================================================*/ 
        switch(ccp_obj->mode){
           case   Capture_mode: CCPx_SET_CAPTURE_MODE(ccp_obj);
           break;
           case Compare_mode:CCPx_SET_COMPARE_MODE(ccp_obj);
           break;    
           case  PWM_mode: CCPx_SET_PWM_MODE (ccp_obj);
           break;
        }
        
        /*===================================================Timer Config=================================================*/
        CCPx_SET_TIMER_CONFIG (ccp_obj);
      /*===================================================Set Interrupt=================================================*/
        #if CCPx_INTERRUPT_ENABLE == 1
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE==0
         INTERRUPT_GlobalInterrupts_Enable();
         INTERRUPT_peripheralInterrupt_Enable();
        #endif
         if (ccp_obj->CCPx == CCP1_MODULE_CONFIG){
         CCP1_InterruptEnable();
         CCP1_InterruptClearFlag();
         CCP1_InterruptHandler=ccp_obj->CCPx_InterruptHandler;
         }
         else if (ccp_obj->CCPx == CCP2_MODULE_CONFIG){
         CCP2_InterruptEnable();
         CCP2_InterruptClearFlag();
         CCP2_InterruptHandler=ccp_obj->CCPx_InterruptHandler;    
         }
         else{/*Nothing*/}
         #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INERRUPT_FEAUTURE_ENABLE
         INTERRUPT_PriorityLevels_Enable();
         if (ccp_obj->priority == HIGH_priority){
             INTERRUPT_GlobalHighPriority_Enable();
              if (ccp_obj->CCPx == CCP1_MODULE_CONFIG){CCP1_Interrupt_HighPrioritySet();}
              else if (ccp_obj->CCPx == CCP2_MODULE_CONFIG){CCP2_Interrupt_HighPrioritySet();}
              else {/*Nothing*/}
         }
         else{
             INTERRUPT_GlobalLowPriority_Enable();
             if (ccp_obj->CCPx == CCP1_MODULE_CONFIG){CCP1_Interrupt_LowPrioritySet();}
             else if (ccp_obj->CCPx == CCP2_MODULE_CONFIG){CCP2_Interrupt_LowPrioritySet();}
             else {/*Nothing*/}
         }
         #endif
         
         #endif

      /*===================================================Pin Config=================================================*/
         gpio_pin_direction_intialize(&(ccp_obj->pin));
    }
    return ret;
    
}


/***********************************************************************************************************************************/

Std_ReturnType CCPx_DeInit (const CCPx_t* ccp_obj){
    
       Std_ReturnType ret = E_OK;
    if (NULL ==ccp_obj){
        ret=E_NOT_OK;
    }
    else{
          /*============================================Disable Module===================================================*/
        if (ccp_obj->CCPx == CCP1_MODULE_CONFIG){CCP1_SET_MODE(CCPx_MODULE_DISABLE);}
        else if (ccp_obj->CCPx == CCP2_MODULE_CONFIG){CCP2_SET_MODE(CCPx_MODULE_DISABLE);}
        else {/*Nothing*/}
        /*===================================================Set Interrupt=================================================*/
        #if CCPx_INTERRUPT_ENABLE == 1
      
         if (ccp_obj->CCPx == CCP1_MODULE_CONFIG){
         CCP1_InterruptDisable();
         }
         else if (ccp_obj->CCPx == CCP2_MODULE_CONFIG){
          CCP2_InterruptDisable();
         }
         else{/*Nothing*/}
         
         
         #endif
 
    }
    return ret;
    
}
/***********************************************************************************************************************************/
#if  CCPx_CFG_MODE_SELETED == CCPx_CAPTURE_MODE_SELETED
Std_ReturnType CCPx_IsCapturedDataReady(const CCPx_t* ccp_obj,uint_8 *_capture_status){
    
       Std_ReturnType ret = E_OK;
    if (NULL ==_capture_status || NULL == ccp_obj){
        ret=E_NOT_OK;
    }
    else{
          if (ccp_obj->CCPx == CCP1_MODULE_CONFIG){
              if (CCPx_CAPTURE_DONE ==PIR1bits.CCP1IF){
                  *_capture_status=CCPx_CAPTURE_DONE;
                    CCP1_InterruptClearFlag();
              }
              else if( CCPx_CAPTURE_NOT_DONE ==PIR1bits.CCP1IF){
                   *_capture_status=CCPx_CAPTURE_NOT_DONE;
              }
          }
        else if (ccp_obj->CCPx == CCP2_MODULE_CONFIG){
           if (CCPx_CAPTURE_DONE ==PIR2bits.CCP2IF){
                  *_capture_status=CCPx_CAPTURE_DONE;
                   CCP2_InterruptClearFlag();
              }
              else if( CCPx_CAPTURE_NOT_DONE ==PIR2bits.CCP2IF){
                   *_capture_status=CCPx_CAPTURE_NOT_DONE;
              }
        }
        else {/*Nothing*/}
         
    }
    return ret;
    
    
}

/***********************************************************************************************************************************/

Std_ReturnType CCPx_Capture_Mode_Read_Value(const CCPx_t* ccp_obj,uint_16 *capture_value){
    CCPx_REG ccp_temp={.CCPRH=0,.CCPRL=0};
       Std_ReturnType ret = E_OK;
    if (NULL ==capture_value || NULL == ccp_obj){
        ret=E_NOT_OK;
    }
    else{
        
         if (ccp_obj->CCPx == CCP1_MODULE_CONFIG){
             
             ccp_temp.CCPRL=CCPR1L;
             ccp_temp.CCPRH=CCPR1H;
             
             *capture_value=ccp_temp.CCPR_16bit;
             
          }
        else if (ccp_obj->CCPx == CCP2_MODULE_CONFIG){
           
             ccp_temp.CCPRL=CCPR2L;
             ccp_temp.CCPRH=CCPR2H;
             
             *capture_value=ccp_temp.CCPR_16bit;
            
        }
        else {/*Nothing*/}  
    }
    return ret;
    
}
#endif

/***********************************************************************************************************************************/
/***********************************************************************************************************************************/

#if  CCPx_CFG_MODE_SELETED ==  CCPx_COMPARE_MODE_SELETED   

Std_ReturnType CCP_IsCompareComplete(const CCPx_t *ccp_obj,uint_8 *_compare_status){
    
       Std_ReturnType ret = E_OK;
    if (_compare_status == NULL){
        ret=E_NOT_OK;
    }
    else{
         if (ccp_obj->CCPx == CCP1_MODULE_CONFIG){
              if (CCPx_COMPARE_DONE  ==PIR1bits.CCP1IF){
                  *_compare_status=CCPx_COMPARE_DONE ;
                    CCP1_InterruptClearFlag();
              }
              else if( CCPx_COMPARE_NOT_DONE  ==PIR1bits.CCP1IF){
                 *_compare_status=CCPx_COMPARE_NOT_DONE ;
              }
          }
        else if (ccp_obj->CCPx == CCP2_MODULE_CONFIG){
           if (CCPx_COMPARE_DONE  ==PIR2bits.CCP2IF){
                  *_compare_status=CCPx_COMPARE_DONE ;
                       CCP2_InterruptClearFlag();
              }
              else if( CCPx_COMPARE_NOT_DONE  ==PIR2bits.CCP2IF){
                   *_compare_status=CCPx_COMPARE_NOT_DONE ;
              }
        }
        else {/*Nothing*/}
         
    }
    return ret;
    
}

/***********************************************************************************************************************************/

Std_ReturnType CCP_Compare_Mode_Set_Value(const CCPx_t *ccp_obj, uint_16 compare_value){
    CCPx_REG ccp_temp={.CCPRH=0,.CCPRL=0};
       Std_ReturnType ret = E_OK;
    if (NULL ==ccp_obj){
        ret=E_NOT_OK;
    }
    else{
        ccp_temp.CCPR_16bit=compare_value;
        
         if (ccp_obj->CCPx == CCP1_MODULE_CONFIG){
             
             CCPR1L=ccp_temp.CCPRL;
             CCPR1H=ccp_temp.CCPRH;
            
          }
        else if (ccp_obj->CCPx == CCP2_MODULE_CONFIG){
           
            CCPR2L=ccp_temp.CCPRL;
            CCPR2H=ccp_temp.CCPRH;
            
        }
         
    }
    return ret;
    
}
#endif

/***********************************************************************************************************************************/
/***********************************************************************************************************************************/

#if  CCPx_CFG_MODE_SELETED ==  CCPx_PWM_MODE_SELETED

Std_ReturnType CCP_PWM_Set_Duty(const CCPx_t *ccp_obj, const uint_8 _duty){
       Std_ReturnType ret = E_OK;
       uint_16 duty_cyc=0;
    if (NULL ==ccp_obj){
        ret=E_NOT_OK;
    }
    else{
     duty_cyc= (uint_16)(4 * (PR2 + 1.0) * (_duty / 100.0));
     if (ccp_obj->CCPx == CCP1_MODULE_CONFIG){
         CCP1CONbits.DC1B= (uint_8) (duty_cyc & 0x0003);
         CCPR1L= (uint_8)(duty_cyc >>2 );
     }
        else if (ccp_obj->CCPx == CCP2_MODULE_CONFIG){
          CCP2CONbits.DC2B= (uint_8) (duty_cyc & 0x0003);
         CCPR2L= (uint_8)(duty_cyc >>2 );
        }
        else {/*Nothing*/}
         
    }
    return ret;
    
    
}
Std_ReturnType CCP_PWM_Start(const CCPx_t *ccp_obj){
    
     Std_ReturnType ret = E_OK;
    if (NULL ==ccp_obj){
        ret=E_NOT_OK;
    }
    else{
         if (ccp_obj->CCPx == CCP1_MODULE_CONFIG){CCP1_SET_MODE(CCPx_PWM_MODE );}
        else if (ccp_obj->CCPx == CCP2_MODULE_CONFIG){CCP2_SET_MODE(CCPx_PWM_MODE);}
        else {/*Nothing*/}
         
    }
    return ret;
    
}
Std_ReturnType CCP_PWM_Stop(const CCPx_t *ccp_obj){
    
     Std_ReturnType ret = E_OK;
    if (NULL ==ccp_obj){
        ret=E_NOT_OK;
    }
    else{
        
        if (ccp_obj->CCPx == CCP1_MODULE_CONFIG){CCP1_SET_MODE(CCPx_MODULE_DISABLE);}
        else if (ccp_obj->CCPx == CCP2_MODULE_CONFIG){CCP2_SET_MODE(CCPx_MODULE_DISABLE);}
        else {/*Nothing*/}
    }
    return ret;
    
}
#endif

/***********************************************************************************************************************************/
/***********************************************************Helper Functions********************************************************/
/***********************************************************************************************************************************/

static void CCPx_SET_CAPTURE_MODE (const CCPx_t * ccp_obj){
    
   if (ccp_obj->CCPx == CCP1_MODULE_CONFIG){
       switch (ccp_obj->sub_mode){
           case CCPx_CAPTURE_MODE_FALLING_EDGE: CCP1_SET_MODE(CCPx_CAPTURE_MODE_FALLING_EDGE);
           break;
           case CCPPx_CATURE_MODE_RISING_EDGE: CCP1_SET_MODE(CCPPx_CATURE_MODE_RISING_EDGE);
           break;
           case CCPx_CAPTURE_MODE_RISING_4_EDGE: CCP1_SET_MODE(CCPx_CAPTURE_MODE_RISING_4_EDGE);
           break;
           case CCPx_CAPTURE_MODE_RISING_16_EDGE: CCP1_SET_MODE(CCPx_CAPTURE_MODE_RISING_16_EDGE);
           break;
       }
   }
   else if (ccp_obj->CCPx == CCP2_MODULE_CONFIG){
        switch (ccp_obj->sub_mode){
           case CCPx_CAPTURE_MODE_FALLING_EDGE: CCP2_SET_MODE(CCPx_CAPTURE_MODE_FALLING_EDGE);
           break;
           case CCPPx_CATURE_MODE_RISING_EDGE: CCP2_SET_MODE(CCPPx_CATURE_MODE_RISING_EDGE);
           break;
           case CCPx_CAPTURE_MODE_RISING_4_EDGE: CCP2_SET_MODE(CCPx_CAPTURE_MODE_RISING_4_EDGE);
           break;
           case CCPx_CAPTURE_MODE_RISING_16_EDGE: CCP2_SET_MODE(CCPx_CAPTURE_MODE_RISING_16_EDGE);
           break;
       }
       
   }
   else {/*Nothing*/}
    
}

/********************************************************************************************************************************/

static void CCPx_SET_COMPARE_MODE (const CCPx_t * ccp_obj){
     if (ccp_obj->CCPx == CCP1_MODULE_CONFIG){
       switch (ccp_obj->sub_mode){
           case CCPx_COMPARE_MODE_SET_PIN_HIGH: CCP1_SET_MODE(CCPx_COMPARE_MODE_SET_PIN_HIGH);
           break;
           case CCPx_COMPARE_MODE_SET_PIN_LOW: CCP1_SET_MODE(CCPx_COMPARE_MODE_SET_PIN_LOW );
           break;
           case  CCPx_COMPARE_MODE_TOGGLE_ON_MATCH: CCP1_SET_MODE( CCPx_COMPARE_MODE_TOGGLE_ON_MATCH);
           break;
           case CCPx_COMPARE_MODE_GENERATE_INTERRUPT: CCP1_SET_MODE(CCPx_COMPARE_MODE_GENERATE_INTERRUPT );
           break;
           case CCPx_COMPARE_MODE_TRIGGER_SPECIAL_EVENT: CCP1_SET_MODE(CCPx_COMPARE_MODE_TRIGGER_SPECIAL_EVENT  );
           break;
       }
   }
   else if (ccp_obj->CCPx == CCP2_MODULE_CONFIG){
        switch (ccp_obj->sub_mode){
           case CCPx_COMPARE_MODE_SET_PIN_HIGH : CCP2_SET_MODE(CCPx_COMPARE_MODE_SET_PIN_HIGH);
           break;
           case CCPx_COMPARE_MODE_SET_PIN_LOW : CCP2_SET_MODE(CCPx_COMPARE_MODE_SET_PIN_LOW );
           break;
           case  CCPx_COMPARE_MODE_TOGGLE_ON_MATCH: CCP2_SET_MODE( CCPx_COMPARE_MODE_TOGGLE_ON_MATCH);
           break;
           case CCPx_COMPARE_MODE_GENERATE_INTERRUPT : CCP2_SET_MODE(CCPx_COMPARE_MODE_GENERATE_INTERRUPT );
           break;
           case CCPx_COMPARE_MODE_TRIGGER_SPECIAL_EVENT : CCP2_SET_MODE(CCPx_COMPARE_MODE_TRIGGER_SPECIAL_EVENT  );
           break;
       }
       
   }
   else {/*Nothing*/}
}

/**************************************************************************************************************************************/

static void CCPx_SET_PWM_MODE (const CCPx_t * ccp_obj){
    
     if (ccp_obj->CCPx == CCP1_MODULE_CONFIG){
       CCP1_SET_MODE(CCPx_PWM_MODE);
   }
   else if (ccp_obj->CCPx == CCP2_MODULE_CONFIG){
      CCP2_SET_MODE(CCPx_PWM_MODE);
   }
   else {/*Nothing*/}
 #if  CCPx_CFG_MODE_SELETED ==  CCPx_PWM_MODE_SELETED    
  PR2=(uint_8)( (_XTAL_FREQ / (ccp_obj->PWM_Frequency * 4.0 * ccp_obj->timer2_Pos * ccp_obj->timer2_Prescaler))-1  );
 #endif 
}

/**************************************************************************************************************************************/
static void CCPx_SET_TIMER_CONFIG (const CCPx_t * ccp_obj){
    switch(ccp_obj->timer_mode){
       case  Timer1_Config_For_Module: T3CONbits.T3CCP1=0;
                                       T3CONbits.T3CCP2=0;
                                       break;
       case Timer1CCP1_Timer3CCP2:T3CONbits.T3CCP1=1;
                                       T3CONbits.T3CCP2=0;
                                       break;
            
       case  Timer3_Config_For_Module:T3CONbits.T3CCP1=0;
                                       T3CONbits.T3CCP2=1;
                                       break;   
    }
}

/**************************************************************************************************************************************/

void CCP1_ISR  (void){
      CCP1_InterruptClearFlag();
    if(CCP1_InterruptHandler){
        CCP1_InterruptHandler();
    }
}

/**************************************************************************************************************************************/

void CCP2_ISR  (void){
    CCP2_InterruptClearFlag();
    if(CCP2_InterruptHandler){
        CCP2_InterruptHandler();
    }
}