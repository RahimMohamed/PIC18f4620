/* 
 * File:   TMR3.h
 * Author: Rahim Mohamed
 
 * Created on April 27, 2024, 12:58 PM
 */

#ifndef TMR3_H
#define	TMR3_H

/*section : Includes  */

#include "../xc.h"
#include "../mcal_std_types.h"
#include "../interrupt/mcal_internal_interrupt.h"

/*section : Macro Declaration  */

#define TMR3_TIMER_MODE_FLAG            0
#define TMR3_COUNTER_MODE_FLAG          1

#define TMR3_SYN_COUNTER_MODE           0
#define TMR3_ASYN_COUNTER_MODE          1

#define TMR3_OSC_ENABLE_FLAG            1
#define TMR3_OSC_DISABLE_FLAG           0

#define TMR3_RW_ONE_FLAG                1
#define TMR3_RW_TWO_FLAG                0

/*section : Macro Functions Declaration  */

/*--------------------------------------- To Enable & Disable  Timer3----------------------------------------------*/
#define TMR3_ENABLE()   (T3CONbits.TMR3ON=1)  
#define TMR3_DISABLE()  (T3CONbits.TMR3ON=0)
/*---------------------------------  Timer3 Clock Source (Mode) ----------------------------------------------*/
#define TMR3_COUNTER_MODE()   (T3CONbits.TMR3CS=1) // This is Counter mode: Timer3 count something happened, We connect on T0CKl pin (RA4)
#define TMR3_TIMER_MODE()     (T3CONbits.TMR3CS=0) // This is Timer mode: count Timer3 , Clock includes Primary,Secondery & Internal Osc1
/*---------------------------------------Timer3 External Clock Input Synchronization in counter mode ----------------------------------------------*/
#define TMR3_SYNCHRONOUS_COUNTER()     (T3CONbits.T3SYNC=0)  // Synchronous Counter Mode : Synchronize external clock input
#define TMR3_ASYNCHRONOUS_COUNTER()    (T3CONbits.T3SYNC=1)  // Asynchronous Counter Mode : Do not synchronize external clock input
/*---------------------------------Timer3 16 bits ----------------------------------------------*/
#define TMR3_RW_ONE_OPER()   (T3CONbits.RD16=1) // R/W TMR1L/H in one operation
#define TMR3_RW_TWO_OPER()   (T3CONbits.RD16=0) // R/W TMR1L/H in two operation

/*section : Data Type Declaration  */
typedef enum {
    
    TMR3_PSA_1=0,  // divide frequency value on 1 
    TMR3_PSA_2,    // divide frequency value on 2 
    TMR3_PSA_4,    // divide frequency value on 4 
    TMR3_PSA_8     // divide frequency value on 8 
}TMR3_PSA;

typedef struct {
    #if TMR3_INTERRUPT_ENABLE == 1
    void (* Timer3_InterruptHandler)(void); 
    priority_t priority;
#endif
    uint_8 RW_flag:1;
    uint_8 mode :1; 
    uint_8 Counter_mode :1; 
    TMR3_PSA PSA;
    uint_16 period;
}TMR3_t;
/*section :  Functions Declaration  */
Std_ReturnType TMR3_Init (const TMR3_t* obj);
Std_ReturnType TMR3_DeInit (const TMR3_t* obj);
Std_ReturnType TMR3_Read_Value (const TMR3_t* obj,uint_16 * value);
Std_ReturnType TMR3_Write_Value (const TMR3_t* obj,uint_16  value);
#endif	/* TMR3_H */

