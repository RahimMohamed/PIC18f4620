/* 
 * File:   ecu_button.c
 * Author: gaming3
 *
 * Created on October 7, 2023, 10:15 PM
 */
#include "ecu_button.h"

Std_ReturnType button_intialize(const button_t* _btn){
    
    
    Std_ReturnType ret = E_OK;
    if (NULL == _btn ){
        ret=E_NOT_OK;
    }
    else{
    
        gpio_pin_direction_intialize(&(_btn->button_pin));
    }
    return ret;
    
}

/*************************************************************************************************************************************/
Std_ReturnType button_Read(const button_t * btn , button_state_t * btn_state){
    
    Std_ReturnType ret = E_OK;
    logic_t status=LOW;
    if (NULL ==  btn  || NULL == btn_state){
        ret=E_NOT_OK;
    }
    else{
        ret=gpio_pin_Read_logic(&(btn->button_pin),&status);
        if(btn->btn_connection == BUTTON_ACTIVE_HIGH){
            
            if(status == HIGH){
                *btn_state=BUTTON_PRESSED;
            }
            else if (LOW == status){
                *btn_state=BUTTON_RELEASD;
            }
            
        }
        if (btn->btn_connection == BUTTON_ACTIVE_LOW){
            
            if(status == LOW){
                *btn_state=BUTTON_PRESSED;
            }
            else if (HIGH == status){
                *btn_state=BUTTON_RELEASD;
            }
            
            
        }
            
        
    }
    return ret;
}
