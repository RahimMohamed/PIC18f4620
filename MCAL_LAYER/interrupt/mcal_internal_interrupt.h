/* 
 * File:   mcal_internal_interrupt.h
 * Author: gaming3
 *
 * Created on February 14, 2024, 1:34 PM
 */

#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H

/*section : Includes  */
#include "mcal_interrupt_config.h"
/*section : Macro Declaration  */


/*section : Macro Functions Declaration  */

/*----------------------------------------------ADC----------------------------------------------------*/
#if ADC_Enternal_INTERRUPT_ENABLE == 1
    
#define ADC_InterruptEnable()       (PIE1bits.ADIE=1) //   enable ADC enternal interrupt bit  
#define ADC_InterruptDisable()      (PIE1bits.ADIE=0) // disable ADC enternal interrupt  bit 

#define ADC_InterruptClearFlag()    (PIR1bits.ADIF=0)  // clear ADC enternal interrupt  flag 

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INERRUPT_FEAUTURE_ENABLE 

#define ADC_Interrupt_HighPrioritySet()  (IPR1bits.ADIP=1) // Set ADC enternal interrupt  to be high Priority  
#define ADC_Interrupt_LowPrioritySet()   (IPR1bits.ADIP=0) // Set  ADC enternal interrupt  to be low Priority 

#endif
#endif

/*--------------------------------------------------TIMER0---------------------------------------------------*/

#if Timer0_INTERRUPT_ENABLE == 1

#define TIMER0_InterruptEnable()       (INTCONbits.TMR0IE =1) //   enable timer0 interrupt bit  
#define TIMER0_InterruptDisable()      (INTCONbits.TMR0IE =0) // disable timer0 interrupt  bit 

#define TIMER0_InterruptClearFlag()    (INTCONbits.TMR0IF =0)  // clear timer0 interrupt  flag 

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INERRUPT_FEAUTURE_ENABLE 

#define TIMER0_Interrupt_HighPrioritySet()  (INTCON2bits.TMR0IP=1) // Set Timer0 interrupt  to be high Priority  
#define TIMER0_Interrupt_LowPrioritySet()   (INTCON2bits.TMR0IP=0) // Set Timer0 interrupt  to be low Priority

#endif
#endif

/*--------------------------------------------------TIMER1---------------------------------------------------*/

#if TMR1_INTERRUPT_ENABLE  == 1

#define TMR1_InterruptEnable()       (PIE1bits.TMR1IE=1) //   enable timer1 interrupt bit  
#define TMR1_InterruptDisable()      (PIE1bits.TMR1IE=0) // disable timer1 interrupt  bit 

#define TMR1_InterruptClearFlag()    (PIR1bits.TMR1IF=0)  // clear timer1 interrupt  flag 

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INERRUPT_FEAUTURE_ENABLE 

#define TMR1_Interrupt_HighPrioritySet()  (IPR1bits.TMR1IP=1) // Set Timer1 interrupt  to be high Priority  
#define TMR1_Interrupt_LowPrioritySet()   (IPR1bits.TMR1IP=0) // Set Timer1 interrupt  to be low Priority

#endif
#endif

/*--------------------------------------------------TIMER2---------------------------------------------------*/

#if TMR2_INTERRUPT_ENABLE  == 1

#define TMR2_InterruptEnable()       (PIE1bits.TMR2IE=1) //   enable timer2 interrupt bit  
#define TMR2_InterruptDisable()      (PIE1bits.TMR2IE=0) // disable timer2 interrupt  bit 

#define TMR2_InterruptClearFlag()    (PIR1bits.TMR2IF=0)  // clear timer2 interrupt  flag 

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INERRUPT_FEAUTURE_ENABLE 

#define TMR2_Interrupt_HighPrioritySet()  (IPR1bits.TMR2IP=1) // Set Timer2 interrupt  to be high Priority  
#define TMR2_Interrupt_LowPrioritySet()   (IPR1bits.TMR2IP=0) // Set Timer2 interrupt  to be low Priority

#endif
#endif

/*--------------------------------------------------TIMER3---------------------------------------------------*/

#if TMR3_INTERRUPT_ENABLE  == 1

#define TMR3_InterruptEnable()       (PIE2bits.TMR3IE=1) // enable timer3 interrupt bit  
#define TMR3_InterruptDisable()      (PIE2bits.TMR3IE=0) // disable timer3 interrupt  bit 

#define TMR3_InterruptClearFlag()    (PIR2bits.TMR3IF=0)  // clear timer3 interrupt  flag 

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INERRUPT_FEAUTURE_ENABLE 

#define TMR3_Interrupt_HighPrioritySet()  (IPR2bits.TMR3IP=1) // Set Timer3 interrupt  to be high Priority  
#define TMR3_Interrupt_LowPrioritySet()   (IPR2bits.TMR3IP=0) // Set Timer3 interrupt  to be low Priority

#endif
#endif


/*--------------------------------------------------CCPx---------------------------------------------------*/

#if CCPx_INTERRUPT_ENABLE  == 1

#define CCP1_InterruptEnable()       (PIE1bits.CCP1IE=1) // enable CCP1 interrupt bit  
#define CCP1_InterruptDisable()      (PIE1bits.CCP1IE=0) // disable CCP1 interrupt  bit 

#define CCP1_InterruptClearFlag()    (PIR1bits.CCP1IF=0)  // clear CCP1 interrupt  flag 



#define CCP2_InterruptEnable()       (PIE2bits.CCP2IE=1) // enable CCP2 interrupt bit  
#define CCP2_InterruptDisable()      (PIE2bits.CCP2IE=0) // disable CCP2 interrupt  bit 

#define CCP2_InterruptClearFlag()    (PIR2bits.CCP2IF=0)  // clear CCP2 interrupt  flag 

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INERRUPT_FEAUTURE_ENABLE 

#define CCP1_Interrupt_HighPrioritySet()  (IPR1bits.CCP1IP=1) // Set CCP1 interrupt  to be high Priority  
#define CCP1_Interrupt_LowPrioritySet()   (IPR1bits.CCP1IP=0) // Set CCP1 interrupt  to be low Priority

#define CCP2_Interrupt_HighPrioritySet()  (IPR2bits.CCP2IP=1) // Set CCP1 interrupt  to be high Priority  
#define CCP2_Interrupt_LowPrioritySet()   (IPR2bits.CCP2IP=0) // Set CCP1 interrupt  to be low Priority

#endif
#endif



/*section : Data Type Declaration  */


/*section :  Functions Declaration  */


#endif	/* MCAL_INTERNAL_INTERRUPT_H */

