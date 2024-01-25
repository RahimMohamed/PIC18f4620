/* 
 * File:   ecu_segment.c
 * Author: gaming3
 *
 * Created on October 7, 2023, 10:15 PM
 */
#include "segment.h"

Std_ReturnType segment_intialize(const segment_t* seg){
    
    
    Std_ReturnType ret=E_OK;
    if (NULL == seg){
        ret=E_NOT_OK;
    }
    else{
      ret=gpio_pin_direction_intialize(&(seg->segment_pins[0]));
      ret=gpio_pin_direction_intialize(&(seg->segment_pins[1]));
      ret=gpio_pin_direction_intialize(&(seg->segment_pins[2]));
      ret=gpio_pin_direction_intialize(&(seg->segment_pins[3]));
    }
    
     return ret;
    
}
/********************************************************************************************************/
Std_ReturnType segment_write_number(const segment_t* seg,uint_8 number){
    
      Std_ReturnType ret=E_OK;
    if (NULL == seg){
        ret=E_NOT_OK;
    }
    else{
        
        ret=gpio_pin_Write_logic(&(seg->segment_pins[0]),number & 0x01);
        ret=gpio_pin_Write_logic(&(seg->segment_pins[1]),(number>>1) & 0x01);
        ret=gpio_pin_Write_logic(&(seg->segment_pins[2]),(number>>2) & 0x01);
        ret=gpio_pin_Write_logic(&(seg->segment_pins[3]),(number>>3) & 0x01);
       
         
        
    }
    
     return ret;
    
}
