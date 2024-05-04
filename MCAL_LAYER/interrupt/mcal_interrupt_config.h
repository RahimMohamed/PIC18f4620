/* 
 * File:   mcal_interrupt_config.h
 * Author: gaming3
 *
 * Created on February 14, 2024, 1:31 PM
 */

#ifndef MCAL_INTERRUPT_CONFIG_H
#define	MCAL_INTERRUPT_CONFIG_H

/*section : Includes  */

#include <xc.h>
#include "../mcal_std_types.h"
#include "mcal_interrupt_gen_cfg.h"
#include "../GPIO/hal_gpio.h"
/*section : Macro Declaration  */

#define INTERRUPT_ENABLE            1
#define INTERRUPT_DISABLE           0
#define INTERRUPT_OCCUR             1
#define INTERRUPT_NOT_OCCUR         0
#define INTERRUPT_PRIORITY_ENABLE   1
#define INTERRUPT_PRIORITY_DISABLE  0

/*section : Macro Functions Declaration  */

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INERRUPT_FEAUTURE_ENABLE 

/*---------------------------------------PRIORITY MODE-----------------------------------*/
#define INTERRUPT_PriorityLevels_Enable() (RCONbits.IPEN=1) // enable  priority mode  
#define INTERRUPT_PriorityLevels_Disable() (RCONbits.IPEN=0) // disable priority mode-active compatibility mode 


#define INTERRUPT_GlobalHighPriority_Enable() (INTCONbits.GIEH=1) // enable all high priority interrupts  
#define INTERRUPT_GlobalHighPriority_Disable() (INTCONbits.GIEH=0) // disable all high priority interrupts 

#define INTERRUPT_GlobalLowPriority_Enable() (INTCONbits.GIEL=1) // enable all low priority interrupts  
#define INTERRUPT_GlobalLowPriority_Disable() (INTCONbits.GIEL=0) // disable all low priority interrupts 

#else
/*---------------------------------------COMPATIBILITY MODE-----------------------------------*/

#define INTERRUPT_peripheralInterrupt_Enable() (INTCONbits.PEIE=1) // enable all  peripheral interrupts  
#define INTERRUPT_peripheralInterrupt_Disable() (INTCONbits.PEIE=0) // disable all peripheral interrupts 
#define INTERRUPT_GlobalInterrupts_Enable() (INTCONbits.GIE=1) // enable all  global interrupts  
#define INTERRUPT_GlobalInterrupts_Disable() (INTCONbits.GIE=0) // disable all global interrupts 

#endif




/*section : Data Type Declaration  */

typedef enum {
    
    LOW_priority=0,
    HIGH_priority=1,       
    
}priority_t;


/*section :  Functions Declaration  */


#endif	/* MCAL_INTERRUPT_CONFIG_H */

