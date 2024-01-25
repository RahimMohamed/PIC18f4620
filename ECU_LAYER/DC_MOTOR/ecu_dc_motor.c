/* 
 * File:   ecu_dc_motor.c
 * Author: gaming3
 *
 * Created on October 7, 2023, 10:15 PM
 */
#include "ecu_dc_motor.h"

/***********************************************************************************************************/


Std_ReturnType motor_intialize(const motor_t* motor){
   
    
     Std_ReturnType ret=E_OK;
    if (NULL == motor){
        ret=E_NOT_OK;
    }
    else{
        
        gpio_pin_direction_intialize(&(motor->motor_config[0]));
        gpio_pin_direction_intialize(&(motor->motor_config[1]));
        
    }
    
     return ret;
      
    
    
}
/*********************************************************************************************************/

Std_ReturnType motor_move_right(const motor_t* motor){
    
    
     Std_ReturnType ret=E_OK;
    if (NULL == motor){
        ret=E_NOT_OK;
    }
    else{
        
        gpio_pin_Write_logic(&(motor->motor_config[0]),HIGH);
        gpio_pin_Write_logic(&(motor->motor_config[1]),LOW);
    }
    
     return ret;
    
}
/**************************************************************************************************************/

Std_ReturnType motor_move_left(const motor_t* motor){
    
     Std_ReturnType ret=E_OK;
    if (NULL == motor){
        ret=E_NOT_OK;
    }
    else{
            gpio_pin_Write_logic(&(motor->motor_config[0]),LOW);
             gpio_pin_Write_logic(&(motor->motor_config[1]),HIGH);
    }
    
     return ret;

}

/********************************************************************************************************************************/

Std_ReturnType motor_stop(const motor_t* motor){
    
     Std_ReturnType ret=E_OK;
    if (NULL == motor){
        ret=E_NOT_OK;
    }
    else{
            gpio_pin_Write_logic(&(motor->motor_config[0]),LOW);
             gpio_pin_Write_logic(&(motor->motor_config[1]),LOW);
    }
    
     return ret;
}
