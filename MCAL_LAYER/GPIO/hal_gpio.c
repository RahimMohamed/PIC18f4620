/* 
 * File:   hal_gpio.c
 * Author: Rahim_Mohamed
 *
 * Created on October 7, 2023, 9:48 PM
 */
#include "hal_gpio.h"
/*Reference to The Data Direction control Registers*/
volatile uint_8 *tris_registers[]={&TRISA ,&TRISB,&TRISC,&TRISD,&TRISE};
/*Reference to The Data Latch  Registers (Read and Write to Data latch)*/
volatile uint_8 *lat_registers[]={&LATA ,&LATB,&LATC,&LATD,&LATE};
/*Reference to The Port Status Registers */
volatile uint_8 *port_registers[]={&PORTA ,&PORTB,&PORTC,&PORTD,&PORTE};
/************************************************************************************************************************/
#if PORT_PIN_CONFIGURATIONS == ENABLE
Std_ReturnType gpio_pin_Read_logic(const pin_config_t * _pin_config, logic_t* logic){
    
    Std_ReturnType ret = E_OK;
    if (NULL == _pin_config ||  _pin_config->pin > (MAX_NUMBER_PIN-1)){
        ret=E_NOT_OK;
    }
    else{
        *logic=READ_BIT(*port_registers[_pin_config->port],_pin_config->pin);
        *logic=READ_BIT(*port_registers[_pin_config->port],_pin_config->pin);
        
    }
    return ret;
}
#endif
/************************************************************************************************************************/
#if PORT_PIN_CONFIGURATIONS == ENABLE
Std_ReturnType gpio_pin_Write_logic(const pin_config_t * _pin_config, logic_t logic){

Std_ReturnType ret = E_OK;
    if (NULL == _pin_config ||  _pin_config->pin > (MAX_NUMBER_PIN-1)){
        ret=E_NOT_OK;
    }
    else{
           
         switch(logic){
            
            case  LOW :
                
              CLEAR_BIT(*lat_registers[_pin_config->port],_pin_config->pin);
           
              break;
            
            case  HIGH :
                
            SET_BIT(*lat_registers[_pin_config->port],_pin_config->pin);
          
              break;
              
            default:ret=E_NOT_OK;
        }
    }

return ret;
}
#endif
/************************************************************************************************************************/
#if PORT_PIN_CONFIGURATIONS == ENABLE
Std_ReturnType gpio_pin_direction_intialize(const pin_config_t * _pin_config){
    
    Std_ReturnType ret = E_OK;
    if (NULL == _pin_config ||  _pin_config->pin > (MAX_NUMBER_PIN-1)){
        ret=E_NOT_OK;
    }
    else{
        switch(_pin_config->direction){
            
            case GPIO_OUTPUT :
                
              CLEAR_BIT(*tris_registers[_pin_config->port],_pin_config->pin);
              
              break;
            
            case GPIO_INPUT :
                
            SET_BIT(*tris_registers[_pin_config->port],_pin_config->pin);
              break;
              
            default:ret=E_NOT_OK;
        }
    }
    return ret;
}
#endif
/************************************************************************************************************************/

#if PORT_PIN_CONFIGURATIONS == ENABLE
Std_ReturnType gpio_pin_direction_status(const pin_config_t * _pin_config, direction_t *dic_status){
 Std_ReturnType ret = E_OK;
    if (NULL == _pin_config ||  _pin_config->pin > (MAX_NUMBER_PIN-1)){
        ret=E_NOT_OK;
    }
    else{
        *dic_status=READ_BIT(*tris_registers[_pin_config->port],_pin_config->pin);
    }
    
 return ret;
}
#endif
/************************************************************************************************************************/



#if PORT_PIN_CONFIGURATIONS == ENABLE
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t * _pin_config){
    
    Std_ReturnType ret = E_OK;
    if (NULL == _pin_config ||  _pin_config->pin > (MAX_NUMBER_PIN-1)){
        ret=E_NOT_OK;
    }
    else{
        
       TOGGLE_BIT(*lat_registers[_pin_config->port],_pin_config->pin) ;
    }
    return ret;
}
#endif
/************************************************************************************************************************/
#if PORT_CONFIGURATIONS == ENABLE

Std_ReturnType gpio_port_direction_intialize(Port_index_t port,uint_8 direction){
    
 Std_ReturnType ret = E_OK;
    if ( port > (MAX_NUMBER_PORT-1)){
        ret=E_NOT_OK;
    }
    else{
        *tris_registers[port]= direction;
    }  
return ret; 
}
#endif
/************************************************************************************************************************/
#if PORT_CONFIGURATIONS == ENABLE

Std_ReturnType gpio_port_get_direction_status(Port_index_t port,uint_8 *dic_status){
    
 Std_ReturnType ret = E_OK;
    if ( port > (MAX_NUMBER_PORT-1) || NULL == dic_status){
        ret=E_NOT_OK;
    }
    else{
        *dic_status=*tris_registers[port];
    }
 return ret;
}

#endif
/************************************************************************************************************************/
#if PORT_CONFIGURATIONS == ENABLE
Std_ReturnType gpio_port_Write_logic(Port_index_t port, uint_8 logic){
    
    Std_ReturnType ret = E_OK;
    if ( port > (MAX_NUMBER_PORT-1)){
        ret=E_NOT_OK;
    }
    else{
        *lat_registers[port]=logic;    
    }
    return ret;
 
}
#endif
/*************************************************************************************************************************/
#if PORT_CONFIGURATIONS == ENABLE
Std_ReturnType gpio_port_Read_logic(Port_index_t port, uint_8 *logic){
Std_ReturnType ret = E_OK;
    if ( port > (MAX_NUMBER_PORT-1)){
        ret=E_NOT_OK;
    }
    else{
        *logic=*lat_registers[port];
    }
return ret;
}
#endif
/*************************************************************************************************************************/
#if PORT_CONFIGURATIONS == ENABLE
Std_ReturnType gpio_port_toggle_logic(Port_index_t port){
    Std_ReturnType ret = E_OK;
    if ( port > (MAX_NUMBER_PORT-1)){
        ret=E_NOT_OK;
    }
    else{
        *lat_registers[port]^=0xFF;
    }
    return ret;
}

#endif
/*************************************************************************************************************************/
#if PORT_PIN_CONFIGURATIONS == ENABLE
Std_ReturnType gpio_pin_intialize(const pin_config_t * _pin_config){

    Std_ReturnType ret = E_OK;
    if (NULL == _pin_config ||  _pin_config->pin > (MAX_NUMBER_PIN-1)){
        ret=E_NOT_OK;
    }
    else{
        gpio_pin_direction_intialize(_pin_config);
        gpio_pin_Write_logic(_pin_config,LOW);
        }
    
    return ret;

}
#endif

