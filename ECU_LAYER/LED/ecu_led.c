/* 
 * File:   ecu_led.c
 * Author: gaming3
 *
 * Created on October 7, 2023, 10:15 PM
 */
#include "ecu_led.h"
/******************************************************************************************/

Std_ReturnType led_initialize (const led_t *led){
    
    Std_ReturnType ret=E_OK;
    if (NULL == led){
        ret=E_NOT_OK;
    }
    else{
        
        pin_config_t pin_obj={
        
            .port=led->port_name,
            .pin=led->pin,
            .direction=GPIO_OUTPUT,
            .logic=led->led_ststus,
        };
        
        gpio_pin_direction_intialize(&pin_obj);
        
    }
    return ret;
};

/******************************************************************************************/


Std_ReturnType led_turn_on (const led_t *led){
    
    Std_ReturnType ret=E_OK;
    if (NULL == led){
           ret=E_NOT_OK;
    }
    else{
          pin_config_t pin_obj={
        
            .port=led->port_name,
            .pin=led->pin,
            .direction=GPIO_OUTPUT,
            .logic=led->led_ststus,
        };
        
        gpio_pin_Write_logic(&pin_obj,HIGH);
    }
    return ret;
};

/******************************************************************************************/

Std_ReturnType led_turn_off(const led_t *led){
    
    Std_ReturnType ret=E_OK;
    if (NULL == led){
           ret=E_NOT_OK;
    }
    else{
        
         pin_config_t pin_obj={
        
            .port=led->port_name,
            .pin=led->pin,
            .direction=GPIO_OUTPUT,
            .logic=led->led_ststus,
        };
        
        gpio_pin_Write_logic(&pin_obj,LOW);
    }
    return ret;
};


/******************************************************************************************/


Std_ReturnType led_toggle (const led_t *led){
    
    Std_ReturnType ret=E_OK;
    if (NULL == led){
           ret=E_NOT_OK;
    }
    else{
         pin_config_t pin_obj={
        
            .port=led->port_name,
            .pin=led->pin,
            .direction=GPIO_OUTPUT,
            .logic=led->led_ststus,
        };
        
        gpio_pin_toggle_logic(&pin_obj);
    }
    return ret;

};


/******************************************************************************************/


