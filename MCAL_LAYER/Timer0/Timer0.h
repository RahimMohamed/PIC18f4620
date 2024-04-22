/* 
 * File:   Timer0.h
 * Author: Rahim mohamed
 *
 * Created on April 20, 2024, 3:14 PM
 */

#ifndef TIMER0_H
#define	TIMER0_H

/*section : Includes  */

#include "Timer0_cfg.h"
#include "../xc.h"
#include "../mcal_std_types.h"
#include "../interrupt/mcal_internal_interrupt.h"

/*section : Macro Declaration  */

#define TIMER0_8BIT_FLAG            1
#define TIMER0_16BIT_FLAG           0

#define TIMER0_RISING_FLAG          1
#define TIMER0_FALLING_FLAG         0


#define TIMER0_PSA_ON_FLAG          1
#define TIMER0_PSA_OFF_FLAG         0

/*section : Macro Functions Declaration  */

/*--------------------------------------- To Enable & Disable  Timer0 ----------------------------------------------*/

#define TIMER0_ENABLE()   (T0CONbits.TMR0ON=1)  
#define TIMER0_DISABLE()  (T0CONbits.TMR0ON=0) 

/*--------------------------------- To Configure Timer0 8 or 16 bits ----------------------------------------------*/

#define TIMER0_8BIT_CONFIGURE()   (T0CONbits.T08BIT=1) //8-bits configured
#define TIMER0_16BIT_CONFIGURE()  (T0CONbits.T08BIT=0) //16-bits configured


/*---------------------------------  Timer0 Clock Source ----------------------------------------------*/


#define TIMER0_COUNTER_MODE()   (T0CONbits.T0CS=1) // This is Counter mode: Timer0 count something happened, We connect on T0CKl pin (RA4)
#define TIMER0_TIMER_MODE()     (T0CONbits.T0CS=0) // This is Timer mode: count Time , Clock includes Primary,Secondery & Internal Osc


/*--------------------------------------- To Select Falling or Rising Edge this active in counter mode ----------------------------------------------*/

#define TIMER0_FAILLING_EDGE()   (T0CONbits.T0SE=1)  // High to Low
#define TIMER0_RISING_EDGE()     (T0CONbits.T0SE=0)  // Low to High 


/*--------------------------------------- Timer0 Prescaler Assignment ----------------------------------------------*/

#define TIMER0_PSA_ON()    (T0CONbits.PSA=0)  
#define TIMER0_PSA_OFF()   (T0CONbits.PSA=1)  




/*section : Data Type Declaration  */

typedef enum {
    
    PSA_2=0,  // divide frequency value on 2 
    PSA_4,  // divide frequency value on 4 
    PSA_8,  // divide frequency value on 8 
    PSA_16,  // divide frequency value on 16 
    PSA_32,  // divide frequency value on 32 
    PSA_64,  // divide frequency value on 64 
    PSA_128,  // divide frequency value on 128 
    PSA_256  // divide frequency value on 256          
    
    
}Prescaler_t;


typedef enum {
    
             
    Timer_mode=0,
    Counter_mode        
    
}Timer0_mode;


typedef struct {
    
    #if Timer0_INTERRUPT_ENABLE   == 1
    void (* Timer0_InterruptHandler)(void); 
    priority_t priority;
#endif
    uint_8 Register_Size_flag :1; 
    Timer0_mode mode;
    uint_8 Edge_flag :1; 
    uint_8 PSA_flag :1; 
    Prescaler_t PSA;
    uint_16 period;
}Timer0_t;

/*section :  Functions Declaration  */

Std_ReturnType Timer0_Init (const Timer0_t* obj);
Std_ReturnType Timer0_DeInit (const Timer0_t* obj);
Std_ReturnType Timer0_Read_Value (const Timer0_t* obj,uint_16 * value);
Std_ReturnType Timer0_Write_Value (const Timer0_t* obj,uint_16  value);
#endif	/* TIMER0_H */

