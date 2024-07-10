/* 
 * File:   mcal_interrupt_manager.c
 * Author: gaming3
 *
 * Created on February 14, 2024, 1:32 PM
 */
#include "mcal_interrupt_manager.h"

/***************************************************************************************************************************************/
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INERRUPT_FEAUTURE_ENABLE

void __interrupt() InterruptMangerHigh (void){
    
    
    if ((INTERRUPT_ENABLE == INTCONbits.INT0IE)&&(INTERRUPT_OCCUR == INTCONbits.INT0IF)){
        INT0_ISR();
    }
     if ((INTERRUPT_ENABLE == INTCON3bits.INT2IE)&&(INTERRUPT_OCCUR == INTCON3bits.INT2IF)){
        INT2_ISR();
    }
    if ((INTERRUPT_ENABLE ==INTCONbits.TMR0IE )&&(INTERRUPT_OCCUR ==INTCONbits.TMR0IF)){
        Timer0_ISR();
    }
     if ((INTERRUPT_ENABLE ==PIE1bits.TMR1IE )&&(INTERRUPT_OCCUR ==PIR1bits.TMR1IF)){
        TMR1_ISR();
    } 
     if ((INTERRUPT_ENABLE ==PIE1bits.TMR2IE )&&(INTERRUPT_OCCUR ==PIR1bits.TMR2IF)){
        TMR2_ISR();
    }
     if ((INTERRUPT_ENABLE ==PIE1bits.CCP1IE )&&(INTERRUPT_OCCUR ==PIR1bits.CCP1IF)){
      CCP1_ISR();
    }
  if ((INTERRUPT_ENABLE ==PIE2bits.CCP2IE )&&(INTERRUPT_OCCUR ==PIR2bits.CCP2IF)){
      CCP2_ISR();
    }
    
}


void __interrupt(low_priority) InterruptMangerLow (void){
    
      if ((INTERRUPT_ENABLE == INTCON3bits.INT1IE)&&(INTERRUPT_OCCUR == INTCON3bits.INT1IF)){
        INT1_ISR();
    }
    if ((INTERRUPT_ENABLE ==PIE1bits.ADIE )&&(INTERRUPT_OCCUR ==PIR1bits.ADIF )){
        ADC_ISR();
    }
       if ((INTERRUPT_ENABLE ==PIE2bits.TMR3IE )&&(INTERRUPT_OCCUR ==PIR2bits.TMR3IF)){
        TMR3_ISR();
    }  
   
}
#else

void __interrupt() InterruptManger (void){
    
    if ((INTERRUPT_ENABLE == INTCONbits.INT0IE)&&(INTERRUPT_OCCUR == INTCONbits.INT0IF)){
        INT0_ISR();
    }
     if ((INTERRUPT_ENABLE == INTCON3bits.INT1IE)&&(INTERRUPT_OCCUR == INTCON3bits.INT1IF)){
        INT1_ISR();
    }
     if ((INTERRUPT_ENABLE == INTCON3bits.INT2IE)&&(INTERRUPT_OCCUR == INTCON3bits.INT2IF)){
        INT2_ISR();
    }
    
    if ((INTERRUPT_ENABLE ==PIE1bits.ADIE )&&(INTERRUPT_OCCUR ==PIR1bits.ADIF )){
        ADC_ISR();
    }
    if ((INTERRUPT_ENABLE ==INTCONbits.TMR0IE )&&(INTERRUPT_OCCUR ==INTCONbits.TMR0IF)){
        Timer0_ISR();
    }
    if ((INTERRUPT_ENABLE ==PIE1bits.TMR1IE )&&(INTERRUPT_OCCUR ==PIR1bits.TMR1IF)){
        TMR1_ISR();
    }
     if ((INTERRUPT_ENABLE ==PIE1bits.TMR2IE )&&(INTERRUPT_OCCUR ==PIR1bits.TMR2IF)){
        TMR2_ISR();
    }
    if ((INTERRUPT_ENABLE ==PIE2bits.TMR3IE )&&(INTERRUPT_OCCUR ==PIR2bits.TMR3IF)){
        TMR3_ISR();
    }  
    if ((INTERRUPT_ENABLE ==PIE1bits.CCP1IE )&&(INTERRUPT_OCCUR ==PIR1bits.CCP1IF)){
      CCP1_ISR();
    }
  if ((INTERRUPT_ENABLE ==PIE2bits.CCP2IE )&&(INTERRUPT_OCCUR ==PIR2bits.CCP2IF)){
      CCP2_ISR();
    }
    if ((INTERRUPT_ENABLE ==PIE1bits.TXIE )&&(INTERRUPT_OCCUR ==PIR1bits.TXIF)){
      EUSART_TX_ISR();
    }
    if ((INTERRUPT_ENABLE ==PIE1bits.RCIE )&&(INTERRUPT_OCCUR ==PIR1bits.RCIF)){
      EUSART_RX_ISR();
    }
    if((INTERRUPT_ENABLE == PIE1bits.SSPIE) && (INTERRUPT_OCCUR == PIR1bits.SSPIF)){
        MSSP_I2C_ISR();
    }
    else{ /* Nothing */ }
    if((INTERRUPT_ENABLE == PIE2bits.BCLIE) && (INTERRUPT_OCCUR == PIR2bits.BCLIF)){
        MSSP_I2C_BC_ISR();
    }
    
    /*=====================================PORTB  External on change Interrupt start=============================================*/
#if EXTERNAL_INTERRUPT_OnCharge_ENABLE ==1   
     if ((INTERRUPT_ENABLE == INTCONbits.RBIE)&&(INTERRUPT_OCCUR == INTCONbits.RBIF)&&(PORTBbits.RB4 == HIGH)){
        RB4_ISR();
    }
    
    if ((INTERRUPT_ENABLE == INTCONbits.RBIE)&&(INTERRUPT_OCCUR == INTCONbits.RBIF)&&(PORTBbits.RB4 == LOW)){
        RB4_ISR();
    }
    /*=====================================PORTB  External on change Interrupt End=============================================*/ 
#endif
}


#endif