/* 
 * File:   TMR1.h
 * Author: Rahim Mohamed
 *
 * Created on April 25, 2024, 5:14 PM
 */

#ifndef TMR1_H
#define	TMR1_H


/*section : Includes  */

#include "../xc.h"
#include "../mcal_std_types.h"
#include "../interrupt/mcal_internal_interrupt.h"

/*section : Macro Declaration  */
#define TMR1_TIMER_MODE_FLAG            0
#define TMR1_COUNTER_MODE_FLAG          1

#define TMR1_SYN_COUNTER_MODE           0
#define TMR1_ASYN_COUNTER_MODE          1

#define TMR1_OSC_ENABLE_FLAG            1
#define TMR1_OSC_DISABLE_FLAG           0

#define TMR1_RW_ONE_FLAG                1
#define TMR1_RW_TWO_FLAG                0


/*section : Macro Functions Declaration  */

/*--------------------------------------- To Enable & Disable  Timer1 ----------------------------------------------*/
#define TMR1_ENABLE()   (T1CONbits.TMR1ON=1)  
#define TMR1_DISABLE()  (T1CONbits.TMR1ON=0) 
/*---------------------------------------  System Clock Status ----------------------------------------------*/
#define READ_SYSTEM_CLOCK()          (T1CONbits.T1RUN)
/*--------------------------------------- To Enable & Disable  Timer1 OSC ----------------------------------------------*/
#define TMR1_OSC_ENABLE()   (T1CONbits.T1OSCEN=1)  
#define TMR1_OSC_DISABLE()  (T1CONbits.T1OSCEN=0) 
/*---------------------------------Timer1 16 bits ----------------------------------------------*/
#define TMR1_RW_ONE_OPER()   (T1CONbits.RD16=1) // R/W TMR1L/H in one operation
#define TMR1_RW_TWO_OPER()   (T1CONbits.RD16=0) // R/W TMR1L/H in two operation
/*---------------------------------  Timer1 Clock Source (Mode) ----------------------------------------------*/
#define TMR1_COUNTER_MODE()   (T1CONbits.TMR1CS=1) // This is Counter mode: Timer1 count something happened, We connect on T0CKl pin (RA4)
#define TMR1_TIMER_MODE()     (T1CONbits.TMR1CS=0) // This is Timer mode: count Time , Clock includes Primary,Secondery & Internal Osc1
/*---------------------------------------Timer1 External Clock Input Synchronization in counter mode ----------------------------------------------*/
#define TMR1_SYNCHRONOUS_COUNTER()     (T1CONbits.T1SYNC=0)  // Synchronous Counter Mode : Synchronize external clock input
#define TMR1_ASYNCHRONOUS_COUNTER()    (T1CONbits.T1SYNC=1)  // Asynchronous Counter Mode : Do not synchronize external clock input

/*section : Data Type Declaration  */
typedef enum {
    
    TMR1_PSA_1=0,  // divide frequency value on 1 
    TMR1_PSA_2,    // divide frequency value on 2 
    TMR1_PSA_4,    // divide frequency value on 4 
    TMR1_PSA_8     // divide frequency value on 8 
}TMR1_PSA;

typedef struct {
    #if TMR1_INTERRUPT_ENABLE == 1
    void (* Timer1_InterruptHandler)(void); 
    priority_t priority;
#endif
    uint_8 RW_flag:1;
    uint_8 mode :1; 
    uint_8 Counter_mode :1; 
    uint_8 OSC_mode :1; 
    TMR1_PSA PSA;
    uint_16 period;
}TMR1_t;


/*section :  Functions Declaration  */


Std_ReturnType TMR1_Init (const TMR1_t* obj);
Std_ReturnType TMR1_DeInit (const TMR1_t* obj);
Std_ReturnType TMR1_Read_Value (const TMR1_t* obj,uint_16 * value);
Std_ReturnType TMR1_Write_Value (const TMR1_t* obj,uint_16  value);

#endif	/* TMR1_H */

