/* 
 * File:   adc.c
 * Author: Rahim mohamed
 *
 * Created on April 17, 2024, 2:38 PM
 */
#include "adc.h"

/****************************************************************************************************************************/
static void (*ADC_InterruptHandler) (void)=NULL;


/****************************************************************************************************************************/


static void ADC_Set_bit (AN_CHANNEL channel );

/****************************************************************************************************************************/
/****************************************************************************************************************************/

Std_ReturnType ADC_Init (const ADC_PIN * pin){
    
    
    Std_ReturnType ret = E_OK;
    if (NULL == pin){
        ret=E_NOT_OK;
    }
    else{
        
        /* Disable ADC  */
        
        DISABLE_ADC();
        
        /* Configure the  Acquisition_Time  */
        
        ADCON2bits.ACQT=pin->Acq_Time;
        /* Configure the  Conversion_Clock   */
         ADCON2bits.ADCS=pin->Clock;
        
        /* Configure the  AN_CHANNEL */
          ADCON0bits.CHS=pin->ANT;
         ADC_Set_bit(pin->ANT);
        
         /* Configure Interrupt */
         #if ADC_Enternal_INTERRUPT_ENABLE == 1 
         #if INTERRUPT_PRIORITY_LEVELS_ENABLE==0
         INTERRUPT_GlobalInterrupts_Enable();
         INTERRUPT_peripheralInterrupt_Enable();
         #endif
         ADC_InterruptEnable();
         ADC_InterruptClearFlag();
         #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INERRUPT_FEAUTURE_ENABLE
            INTERRUPT_PriorityLevels_Enable();
         if (pin->priority_level == HIGH_priority){
              INTERRUPT_GlobalHighPriority_Enable();
             ADC_Interrupt_HighPrioritySet();
         }
         else{
             INTERRUPT_GlobalLowPriority_Enable();
             ADC_Interrupt_LowPrioritySet();
         }
         #endif
         ADC_InterruptHandler=pin->ADC_InterruptHandler;
         #endif
         
         /* Configure the  Result_flag */
         
         if (pin->Result_flag == 1){RIGHT_JUSTIFIED_ADC_RESULT_FORMAT();}
         else {LEFT_JUSTIFIED_ADC_RESULT_FORMAT(); }
        
         /* Configure the  voltage reference */
        
           
         if (&(pin->voltage_reference_flag) == 1){ENABLE_EXTERNAL_VOLTAGE_REFERNCE();}
         else {DISABLE_EXTERNAL_VOLTAGE_REFERNCE(); }
        
        
       /* Enable ADC  */
        ENABLE_ADC();
        
    }
    return ret;
}

/****************************************************************************************************************************/

Std_ReturnType ADC_DeInit (const ADC_PIN * pin){
    
     Std_ReturnType ret = E_OK;
    if (NULL == pin){
        ret=E_NOT_OK;
    }
    else{
        
            /* Disable ADC  */
        
        DISABLE_ADC();
        
         /* Disable Interrupt */
        
        #if ADC_Enternal_INTERRUPT_ENABLE == 1
        ADC_InterruptDisable();
        #endif
    }
    return ret;
    
}

/****************************************************************************************************************************/

Std_ReturnType ADC_Select_channel (const ADC_PIN * pin ,AN_CHANNEL channel ){
    
     Std_ReturnType ret = E_OK;
    if (NULL == pin){
        ret=E_NOT_OK;
    }
    else{
        
        ADCON0bits.CHS=channel;
         ADC_Set_bit(channel);
        
    }
    return ret;
    
}

/****************************************************************************************************************************/


Std_ReturnType ADC_StartConversion (const ADC_PIN * pin){
    
     Std_ReturnType ret = E_OK;
    if (NULL == pin){
        ret=E_NOT_OK;
    }
    else{
        
        START_ADC_CONVERSION_PROCESS();
        
    }
    return ret;
    
}


/****************************************************************************************************************************/


Std_ReturnType ADC_ConversionStatus (const ADC_PIN * pin, uint_8 * status){
    
     Std_ReturnType ret = E_OK;
    if (NULL == pin && NULL == status ){
        ret=E_NOT_OK;
    }
    else{
        
        *status=!(GET_ADC_CONVERSION_STATUS());
        
        /* status   0: conversion did not done  */
        /* status   1: conversion done  */ 
        
    }
    return ret;
    
}


/****************************************************************************************************************************/


Std_ReturnType ADC_GetResult (const ADC_PIN * pin, uint_16 * result){
    
    
     Std_ReturnType ret = E_OK;
    if (NULL == pin && NULL == result ){
        ret=E_NOT_OK;
    }
    else{
        
        if (pin->Result_flag == 1){ // right
            
            *result= (uint_16)(ADRESL + (ADRESH << 8));
        }
        else{
             *result= (uint_16) (((ADRESH << 8)+ADRESL)>>6);
        }
        
    }
    return ret;
    
}

/****************************************************************************************************************************/


Std_ReturnType ADC_GetConversion (const ADC_PIN * pin ,AN_CHANNEL channel , uint_8 * result){
    
    
     Std_ReturnType ret = E_OK;
    if (NULL == pin && NULL == result){
        ret=E_NOT_OK;
    }
    else{
        
        ADC_Select_channel(pin,channel);
        
        ADC_StartConversion(pin);
        
        while (ADCON0bits.GODONE){}
            
       ADC_GetResult(pin,result);
        
        
    }
    return ret;
    
}

/****************************************************************************************************************************/

Std_ReturnType ADC_GetConversion_Interrupt (const ADC_PIN * pin ,AN_CHANNEL channel ){
    Std_ReturnType ret = E_OK;
    if (NULL == pin ){
        ret=E_NOT_OK;
    }
    else{
        
        ADC_Select_channel(pin,channel);
        
        ADC_StartConversion(pin);
        
       
    }
    return ret;
    
    
    
}
/****************************************************************************************************************************/
/****************************************************************************************************************************/
/****************************************************************************************************************************/

static void ADC_Set_bit (AN_CHANNEL channel ){
    switch (channel){
        
        case  ADC_AN0  : SET_BIT(TRISA,_TRISA_RA0_POSN);break;
        case  ADC_AN1  : SET_BIT(TRISA,_TRISA_RA1_POSN);break;
        case  ADC_AN2  : SET_BIT(TRISA,_TRISA_RA2_POSN);break;
        case  ADC_AN3  : SET_BIT(TRISA,_TRISA_RA3_POSN);break;
        case  ADC_AN4  : SET_BIT(TRISA,_TRISA_RA5_POSN);break;
        case  ADC_AN5  : SET_BIT(TRISE,_TRISE_RE0_POSN);break;
        case  ADC_AN6  : SET_BIT(TRISE,_TRISE_RE1_POSN);break;
        case  ADC_AN7  : SET_BIT(TRISE,_TRISE_RE2_POSN);break;
        case  ADC_AN8  : SET_BIT(TRISB,_TRISB_RB2_POSN);break;
        case  ADC_AN9  : SET_BIT(TRISB,_TRISB_RB3_POSN);break;
        case  ADC_AN10 : SET_BIT(TRISB,_TRISB_RB1_POSN);break;
        case  ADC_AN11 : SET_BIT(TRISB,_TRISB_RB4_POSN);break;
        case  ADC_AN12 : SET_BIT(TRISB,_TRISB_RB0_POSN);break; 
    }
}
/****************************************************************************************************************************/


void ADC_ISR  (void){
    
    ADC_InterruptClearFlag();
    
    if(ADC_InterruptHandler){
        ADC_InterruptHandler();
    }
    
}