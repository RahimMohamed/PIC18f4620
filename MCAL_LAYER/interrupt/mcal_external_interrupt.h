/* 
 * File:   mcal_external_interrupt.h
 * Author: gaming3
 *
 * Created on February 14, 2024, 1:33 PM
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_H
#define	MCAL_EXTERNAL_INTERRUPT_H

/*section : Includes  */

#include "mcal_interrupt_config.h"


/*section : Macro Declaration  */


/*section : Macro Functions Declaration  */


#if EXTERNAL_INTERRUPT_INTx_ENABLE==INERRUPT_FEAUTURE_ENABLE

/*-----------------------------------INT0-----------------------------------------*/

#define EXT_INT0_Enable() (INTCONbits.INT0IE=1) // enable  external interrupt INT0 bit  
#define EXT_INT0_Disable() (INTCONbits.INT0IE=0) // disable external interrupt INT0 bit 

#define EXT_INT0_ClearFlag() (INTCONbits.INT0IF=0) // clear external interrupt INT0 flag 

#define EXT_INT0_RisingEdgeSet() (INTCON2bits.INTEDG0=1) // make  external interrupt INT0 detect at rising edge -Ex: when button is pressed - 
#define EXT_INT0_FalingEdgeSet() (INTCON2bits.INTEDG0=0) // make  external interrupt INT0 detect at falling edge -Ex: when button is released - 


// INT0 has always high priority level

/*-----------------------------------INT1-----------------------------------------*/

#define EXT_INT1_Enable() (INTCON3bits.INT1IE=1) // enable  external interrupt INT1 bit  
#define EXT_INT1_Disable() (INTCON3bits.INT1IE=0) // disable external interrupt INT1 bit 

#define EXT_INT1_ClearFlag() (INTCON3bits.INT1IF=0) // clear external interrupt INT1 flag 

#define EXT_INT1_RisingEdgeSet() (INTCON2bits.INTEDG1=1) // make  external interrupt INT1 detect at rising edge -Ex: when button is pressed - 
#define EXT_INT1_FalingEdgeSet() (INTCON2bits.INTEDG1=0) // make  external interrupt INT1 detect at falling edge -Ex: when button is released - 


/*-----------------------------------INT2-----------------------------------------*/

#define EXT_INT2_Enable() (INTCON3bits.INT2IE=1) // enable  external interrupt INT2 bit  
#define EXT_INT2_Disable() (INTCON3bits.INT2IE=0) // disable external interrupt INT2 bit 

#define EXT_INT2_ClearFlag() (INTCON3bits.INT2IF=0) // clear external interrupt INT2 flag 

#define EXT_INT2_RisingEdgeSet() (INTCON2bits.INTEDG2=1) // make  external interrupt INT2 detect at rising edge -Ex: when button is pressed - 
#define EXT_INT2_FalingEdgeSet() (INTCON2bits.INTEDG2=0) // make  external interrupt INT2 detect at falling edge -Ex: when button is released - 

/*-----------------------------------INT1&INT2 Priority-----------------------------------------*/

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INERRUPT_FEAUTURE_ENABLE 

#define EXT_INT1_HighPrioritySet() (INTCON3bits.INT1IP=1) // Set  external interrupt INT1 to be high Priority  
#define EXT_INT1_LowPrioritySet() (INTCON3bits.INT1IP=0) // Set  external interrupt INT1 to be low Priority 


#define EXT_INT2_HighPrioritySet() (INTCON3bits.INT2IP=1) // Set  external interrupt INT2 to be high Priority  
#define EXT_INT2_LowPrioritySet() (INTCON3bits.INT2IP=0) // Set  external interrupt INT2 to be low Priority 


#endif

#endif

#if EXTERNAL_INTERRUPT_OnCharge_ENABLE==INERRUPT_FEAUTURE_ENABLE

#define EXT_RBx_Enable() (INTCONbits.RBIE=1) // enable  external interrupt RBx bit  
#define EXT_RBx_Disable() (INTCONbits.RBIE=0) // disable external interrupt RBx bit 

#define EXT_RBx_ClearFlag() (INTCONbits.RBIF=0) // clear external interrupt RBx flag 

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INERRUPT_FEAUTURE_ENABLE 

#define EXT_RBx_HighPrioritySet() (INTCON2bits.RBIP=1) // Set  external interrupt RBx to be high Priority  
#define EXT_RBx_LowPrioritySet() (INTCON2bits.RBIP=0) // Set  external interrupt RBX to be low Priority 

#endif

#endif

/*section : Data Type Declaration  */

typedef enum {
    
    Failing_Edge=0,
    Rising_Edge=1,       
    
}edge_t;

typedef enum {
    
    EXT_INT0=0,
    EXT_INT1=1,      
    EXT_INT2=2,
}INTx;

typedef struct{
    
    
    void (*EXT_InterruptHandeler) (void) ;
    pin_config_t pin;
    edge_t edge;        
    INTx intx;
    priority_t priority_level;
}interrupt_INTx_t;

typedef struct{
    
    void (*EXT_InterruptHandeler) (void) ;
    pin_config_t pin;
    priority_t priority_level;
    
}interrupt_RBx_t;

/*section :  Functions Declaration  */

Std_ReturnType Interrupt_INTx_Init   (const  interrupt_INTx_t * int_obj);
Std_ReturnType Interrupt_INTx_DeInit (const  interrupt_INTx_t * int_obj);

Std_ReturnType Interrupt_RBx_Init   (const  interrupt_RBx_t * int_obj);
Std_ReturnType Interrupt_RBx_DeInit (const  interrupt_RBx_t * int_obj);

#endif	/* MCAL_EXTERNAL_INTERRUPT_H */

