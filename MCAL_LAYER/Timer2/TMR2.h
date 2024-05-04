/* 
 * File:   TMR2.h
 * Author: Rahim Mohamed
 *
 * Created on April 27, 2024, 10:54 AM
 */

#ifndef TMR2_H
#define	TMR2_H

/*section : Includes  */

#include "../xc.h"
#include "../mcal_std_types.h"
#include "../interrupt/mcal_internal_interrupt.h"

/*section : Macro Declaration  */


/*section : Macro Functions Declaration  */

/*--------------------------------------- To Enable & Disable  Timer2 ----------------------------------------------*/
#define TMR2_ENABLE()   (T2CONbits.TMR2ON=1)  
#define TMR2_DISABLE()  (T2CONbits.TMR2ON=0) 


/*section : Data Type Declaration  */

typedef enum {
    
    TMR2_PSA_1=0,  // divide frequency value on 1 
    TMR2_PSA_4,    // divide frequency value on 4 
    TMR2_PSA_16,   // divide frequency value on 16 
}TMR2_PSA;

typedef enum {
    
    TMR2_POS_1=0,   
    TMR2_POS_2,     
    TMR2_POS_3,     
    TMR2_POS_4,
    TMR2_POS_5,   
    TMR2_POS_6,     
    TMR2_POS_7,     
    TMR2_POS_8,
    TMR2_POS_9,   
    TMR2_POS_10,     
    TMR2_POS_11,     
    TMR2_POS_12,
    TMR2_POS_13,   
    TMR2_POS_14,     
    TMR2_POS_15,     
    TMR2_POS_16,        
}TMR2_POSTSCALE;


typedef struct {
#if TMR2_INTERRUPT_ENABLE == 1
    void (* Timer2_InterruptHandler)(void); 
    priority_t priority;
#endif   
    TMR2_PSA PSA;
    TMR2_POSTSCALE POS;
    uint_8 period;
}TMR2_t;


/*section :  Functions Declaration  */

Std_ReturnType TMR2_Init (const TMR2_t* obj);
Std_ReturnType TMR2_DeInit (const TMR2_t* obj);
Std_ReturnType TMR2_Read_Value (const TMR2_t* obj,uint_8 * value);
Std_ReturnType TMR2_Write_Value (const TMR2_t* obj,uint_8  value);

#endif	/* TMR2_H */

