/* 
 * File:   ecu_relay.c
 * Author: gaming3
 *
 * Created on October 7, 2023, 10:15 PM
 */
#include "ecu_relay.h"
/******************************************************************************************/
Std_ReturnType relay_initialize(const relay_t* relay){
    
     Std_ReturnType ret=E_OK;
    if (NULL == relay){
        ret=E_NOT_OK;
    }
    else{
        gpio_pin_intialize(&(relay->relay_config));
    }
    
     return ret;
    
}
/******************************************************************************************/

Std_ReturnType turn_on_relay (const relay_t* relay ){
    
    Std_ReturnType ret=E_OK;
    if (NULL == relay){
        ret=E_NOT_OK;
    }
    else{
        gpio_pin_Write_logic(&(relay->relay_config),HIGH);
    }
    
     return ret;
    
    
}
/******************************************************************************************/

Std_ReturnType turn_off_relay (const relay_t* relay ){
    
    Std_ReturnType ret=E_OK;
    if (NULL == relay){
        ret=E_NOT_OK;
    }
    else{
        gpio_pin_Write_logic(&(relay->relay_config),LOW);
    }
    
     return ret;
    
}
/******************************************************************************************/


