/* 
 * File:   adc.h
 * Author: Rahim mohamed
 *
 * Created on April 17, 2024, 2:38 PM
 */

#ifndef ADC_H
#define	ADC_H


/*section : Includes  */

#include "../xc.h"
#include "../mcal_std_types.h"
#include "../interrupt/mcal_internal_interrupt.h"
#include "adc_cfg.h"

/*section : Macro Declaration  */


#define ALL_CHANNELS_DIGIITAL_INPUT            0X0F
#define AN0_CHANNEL_ONLY_ANALOG_INPUT          0X0E
#define AN0_TO_AN1_CHANNELS_ANALOG_INPUT       0X0D
#define AN0_TO_AN2_CHANNELS_ANALOG_INPUT       0X0C
#define AN0_TO_AN3_CHANNELS_ANALOG_INPUT       0X0B
#define AN0_TO_AN4_CHANNELS_ANALOG_INPUT       0X0A
#define AN0_TO_AN5_CHANNELS_ANALOG_INPUT       0X09
#define AN0_TO_AN6_CHANNELS_ANALOG_INPUT       0X08
#define AN0_TO_AN7_CHANNELS_ANALOG_INPUT       0X07
#define AN0_TO_AN8_CHANNELS_ANALOG_INPUT       0X06
#define AN0_TO_AN9_CHANNELS_ANALOG_INPUT       0X05
#define AN0_TO_AN10_CHANNELS_ANALOG_INPUT      0X04
#define AN0_TO_AN11_CHANNELS_ANALOG_INPUT      0X03
#define ALL_CHANNELS_ANALOG_INPUT              0X02



/*section : Macro Functions Declaration  */

/*----------To enable & disable the A/D Converter module------*/
#define ENABLE_ADC()     (ADCON0bits.ADON =1) 
#define DISABLE_ADC()    (ADCON0bits.ADON =0) 


#define GET_ADC_CONVERSION_STATUS()    (ADCON0bits.GODONE)     // get status of ADC conversion process if it = 1 process is still running, if it =0 process is finished 
#define START_ADC_CONVERSION_PROCESS() (ADCON0bits.GODONE=1)   // To start the conversion make this bit =1 


/* To enable & disable external voltage reference : when VCFG1 & VCFG0 = 1, we connect external voltage source on AN2 as negative & AN3 as positive 
                                                         when VCFG1 & VCFG0 = 0 , Voltage reference is VDD(+) &VSS (-) */
#define ENABLE_EXTERNAL_VOLTAGE_REFERNCE()    do {ADCON1bits.VCFG0=1;ADCON1bits.VCFG1=1;}while(0)
#define DISABLE_EXTERNAL_VOLTAGE_REFERNCE()   do {ADCON1bits.VCFG0=0;ADCON1bits.VCFG1=0;}while(0)


#define SELECT_ADC_PORT_CONFIGURATION_CHANNEL (_config) (ADCON1bits.PCFG=_config)

/*Result register stored in 10 bits, so we need two registers 8 bits to stored result in.
 *  In Right form : we take all ADRESL register and first two bits from  ADRESH
 *  In left form : we take all ADRESR register and last two bits from  ADRESL
 * Right form is recommended as result = ADRESL+ADRESH*255 */

#define RIGHT_JUSTIFIED_ADC_RESULT_FORMAT() (ADCON2bits.ADFM=1)
#define LEFT_JUSTIFIED_ADC_RESULT_FORMAT() (ADCON2bits.ADFM=0)




/*section : Data Type Declaration  */


/*-------------to select input analog channel from ADCON0 register CHS3:CHS0 bits ---------------------*/
typedef enum {
    
    ADC_AN0=0,
    ADC_AN1,
    ADC_AN2,
    ADC_AN3,
    ADC_AN4,
    ADC_AN5,
    ADC_AN6,
    ADC_AN7,
    ADC_AN8,
    ADC_AN9,
    ADC_AN10,
    ADC_AN11,
    ADC_AN12
          
}AN_CHANNEL;


typedef enum {
    
    TAD_0=0,    //Automatic Acquisition Time
    TAD_2,      // Acquisition Time=2 * TAD
    TAD_4,      // Acquisition Time=4 * TAD
    TAD_6,      // Acquisition Time=6 * TAD 
    TAD_8,      // Acquisition Time=8 * TAD
    TAD_12,     // Acquisition Time=12 * TAD
    TAD_16,     // Acquisition Time=16 * TAD
    TAD_18,     // Acquisition Time=18 * TAD
}Acquisition_Time;

/* To set TAD you must select conversion clock */
typedef enum {
    
   FOSC_2=0,  // Conversion_Clock=FOSC/2
   FOSC_8,    // Conversion_Clock=FOSC/8
   FOSC_32,   // Conversion_Clock=FOSC/32
   FRC,
   FOSC_4,    // Conversion_Clock=FOSC/4
   FOSC_16,   // Conversion_Clock=FOSC/16
   FOSC_64,   // Conversion_Clock=FOSC/64
}Conversion_Clock;


typedef struct {
#if ADC_Enternal_INTERRUPT_ENABLE == 1
    void (* ADC_InterruptHandler)(void);
    priority_t priority_level;
#endif
    AN_CHANNEL ANT; /* @ref AN_CHANNEL */
    Conversion_Clock Clock;  /* @ref Conversion_Clock */
    Acquisition_Time Acq_Time;  /* @ref Acquisition_Time */
    uint_8 voltage_reference_flag ; // flag =1 : enable external source , flag=0 : disable external source 
    uint_8 Result_flag ;  // flag =1 : Right , flag=0 : left 
}ADC_PIN;
/*section :  Functions Declaration  */

Std_ReturnType ADC_Init (const ADC_PIN * pin);
Std_ReturnType ADC_DeInit (const ADC_PIN * pin);
Std_ReturnType ADC_Select_channel (const ADC_PIN * pin ,AN_CHANNEL channel );
Std_ReturnType ADC_StartConversion (const ADC_PIN * pin);
Std_ReturnType ADC_ConversionStatus (const ADC_PIN * pin, uint_8 * status);
Std_ReturnType ADC_GetResult (const ADC_PIN * pin, uint_16 * result);
Std_ReturnType ADC_GetConversion (const ADC_PIN * pin ,AN_CHANNEL channel , uint_8 * result);
Std_ReturnType ADC_GetConversion_Interrupt (const ADC_PIN * pin ,AN_CHANNEL channel );
#endif	/* ADC_H */

