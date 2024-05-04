/* 
 * File:   CPP.h
 * Author: Rahim Mohamed
 *
 * Created on April 27, 2024, 3:01 PM
 */

#ifndef CCP_H
#define	CCP_H

/*section : Includes  */

#include "../xc.h"
#include "../mcal_std_types.h"
#include "../interrupt/mcal_internal_interrupt.h"
#include "CCP_cfg.h"
/*section : Macro Declaration  */

#define CCPx_MODULE_DISABLE                              ((uint_8)0x00)


#define CCP1_MODULE_CONFIG                                   1
#define CCP2_MODULE_CONFIG                                   2 
/*==============================Capture Modes ===============================*/
#define CCPx_CAPTURE_MODE_FALLING_EDGE                  ((uint_8) 0x04)
#define CCPPx_CATURE_MODE_RISING_EDGE                   ((uint_8) 0x05)
#define CCPx_CAPTURE_MODE_RISING_4_EDGE                 ((uint_8) 0x06)
#define CCPx_CAPTURE_MODE_RISING_16_EDGE                ((uint_8) 0x07)

#define CCPx_CAPTURE_DONE                                0x01
#define CCPx_CAPTURE_NOT_DONE                            0x00
/*==============================Compare Modes ===============================*/
#define CCPx_COMPARE_MODE_SET_PIN_HIGH                  ((uint_8)  0x08)
#define CCPx_COMPARE_MODE_SET_PIN_LOW                   ((uint_8)  0x09)
#define CCPx_COMPARE_MODE_TOGGLE_ON_MATCH               ((uint_8)  0x02)
#define CCPx_COMPARE_MODE_GENERATE_INTERRUPT            ((uint_8) 0x0A)
#define CCPx_COMPARE_MODE_TRIGGER_SPECIAL_EVENT         ((uint_8) 0x0B)

#define CCPx_COMPARE_DONE                                0x01
#define CCPx_COMPARE_NOT_DONE                            0x00
/*=================================PWM Modes =================================*/
#define CCPx_PWM_MODE                                   ((uint_8) 0x0C)


/*section : Macro Functions Declaration  */

#define CCP1_SET_MODE(_CONFIG)  (CCP1CONbits.CCP1M=_CONFIG)
#define CCP2_SET_MODE(_CONFIG)  (CCP2CONbits.CCP2M=_CONFIG)

/*section : Data Type Declaration  */

typedef enum {
    Capture_mode=0,
    Compare_mode,
    PWM_mode        
}CCPx_mode;


typedef enum {
    Timer1_Config_For_Module=0,//Timer1 is the capture/compare clock source for the CCP modules
    Timer1CCP1_Timer3CCP2,     //Timer3 is the capture/compare clock source for CCP2;Timer1 is the capture/compare clock source for CCP1   
    Timer3_Config_For_Module, //Timer3 is the capture/compare clock source for the CCP modules       
}CCPx_Timer_mode;

typedef union{
    
    struct {
        uint_8 CCPRL;
        uint_8 CCPRH;
    };
    struct {
        uint_16 CCPR_16bit;
    };
    
}CCPx_REG;


typedef struct {
    uint_8 CCPx; // CCP1_MODULE_CONFIG = CCP1 or CCP2_MODULE_CONFIG = CCP2
    CCPx_mode mode;
    uint_8 sub_mode;
    pin_config_t pin;
    CCPx_Timer_mode timer_mode;
#if  CCPx_CFG_MODE_SELETED ==  CCPx_PWM_MODE_SELETED   
    uint_32 PWM_Frequency;
    uint_8 timer2_Prescaler;
    uint_8 timer2_Pos;
#endif   
#if CCPx_INTERRUPT_ENABLE == 1
    void (*CCPx_InterruptHandler)(void); 
    priority_t priority;
#endif
    
}CCPx_t;

/*section :  Functions Declaration  */

Std_ReturnType CCPx_Init (const CCPx_t* ccp_obj);
Std_ReturnType CCPx_DeInit (const CCPx_t* ccp_obj);

#if  CCPx_CFG_MODE_SELETED == CCPx_CAPTURE_MODE_SELETED
Std_ReturnType CCPx_IsCapturedDataReady(const CCPx_t* ccp_obj,uint_8 *_capture_status);
Std_ReturnType CCPx_Capture_Mode_Read_Value(const CCPx_t* ccp_obj,uint_16 *capture_value);
#endif

#if  CCPx_CFG_MODE_SELETED ==  CCPx_COMPARE_MODE_SELETED   

Std_ReturnType CCP_IsCompareComplete(const CCPx_t *_ccp_obj,uint_8 *_compare_status);
Std_ReturnType CCP_Compare_Mode_Set_Value(const CCPx_t *_ccp_obj, uint_16 compare_value);
#endif

#if  CCPx_CFG_MODE_SELETED ==  CCPx_PWM_MODE_SELETED

Std_ReturnType CCP_PWM_Set_Duty(const CCPx_t *_ccp_obj, const uint_8 _duty);
Std_ReturnType CCP_PWM_Start(const CCPx_t *_ccp_obj);
Std_ReturnType CCP_PWM_Stop(const CCPx_t *_ccp_obj);
#endif
#endif	/* CCP_H */

