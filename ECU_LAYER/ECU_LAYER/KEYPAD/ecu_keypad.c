/* 
 * File:   ecu_keypad.c
 * Author: gaming3
 *
 * Created on October 7, 2023, 10:15 PM
 */
#include "ecu_keypad.h"

static const uint_8 keypad_value [ROWS_NUMBER][COLUMNS_NUMBER]={      {7,8,9,'/'},
                                                                      {4,5,6,'*'},
                                                                      {1,2,3,'-'},
                                                                      {'#',0,'=','+'}, 
};
/*******************************************************************************************************************/
Std_ReturnType keypad_intialize(const keypad_t* keypad_obj){
    uint_8 rows_counter=0,columns_counter=0;
    Std_ReturnType ret = E_OK;
    if (NULL == keypad_obj ){
        ret=E_NOT_OK;
    }
    else{
        for(rows_counter=0;rows_counter<ROWS_NUMBER;rows_counter++){
        ret=gpio_pin_direction_intialize(&(keypad_obj->rows_pins[rows_counter]));
        }
        for(columns_counter=0;columns_counter<COLUMNS_NUMBER;columns_counter++){
        ret=gpio_pin_direction_intialize(&(keypad_obj->columns_pins[columns_counter]));
        }
    }
    return ret;
    
    
    
    
}
/********************************************************************************************************************/
Std_ReturnType keypad_get_value(const keypad_t* keypad_obj,uint_8 * value){
    
    
    Std_ReturnType ret = E_OK;
       uint_8 rows_counter=0, rows_counter2=0,columns_counter=0,col_val=0;
    if (NULL == keypad_obj && (NULL == value)){
        ret=E_NOT_OK;
    }
    else{
     for(rows_counter=0;rows_counter<ROWS_NUMBER;rows_counter++){
         for(rows_counter2=0;rows_counter2<ROWS_NUMBER;rows_counter2++){
          ret=gpio_pin_Write_logic(&(keypad_obj->rows_pins[rows_counter2]),LOW);
        }
        ret=gpio_pin_Write_logic(&(keypad_obj->rows_pins[rows_counter]),HIGH);
         for(columns_counter=0;columns_counter<COLUMNS_NUMBER;columns_counter++){
             ret=gpio_pin_Read_logic(&(keypad_obj->columns_pins[columns_counter]),&col_val);
             if (HIGH == col_val){
                 *value= keypad_value[rows_counter][columns_counter];
             }
        }
     }
       
    }
    return ret;
    
    
}
