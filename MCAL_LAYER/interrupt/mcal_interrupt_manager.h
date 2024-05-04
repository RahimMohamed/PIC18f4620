/* 
 * File:   mcal_interrupt_manager.h
 * Author: gaming3
 *
 * Created on February 14, 2024, 1:32 PM
 */

#ifndef MCAL_INTERRUPT_MANAGER_H
#define	MCAL_INTERRUPT_MANAGER_H

/*section : Includes  */

#include "mcal_interrupt_config.h"

/*section : Macro Declaration  */


/*section : Macro Functions Declaration  */


/*section : Data Type Declaration  */


/*section : Macro Declaration  */


/*section :  Functions Declaration  */
void INT0_ISR (void);
void INT1_ISR (void);
void INT2_ISR (void);
void RB4_ISR  (void);
void ADC_ISR  (void);
void Timer0_ISR  (void);
void TMR1_ISR  (void);
void TMR2_ISR  (void);
void TMR3_ISR  (void);
void CCP1_ISR  (void);
void CCP2_ISR  (void);
#endif	/* MCAL_INTERRUPT_MANAGER_H */

