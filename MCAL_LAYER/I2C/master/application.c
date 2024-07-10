/* 
 * File:   application.c
 * Author: Ahmed.Elghafar
 * https://www.linkedin.com/in/ahmedabdelghafarmohammed/
 * Created on November 28, 2020, 8:43 PM
 */

#include "application.h"
#include "MCAL_Layer/I2C/hal_i2c.h"

mssp_i2c_t i2c_obj;
uint8 slave_ack;

uint32 app_counter = 0;

/* Address = 0x30 + W Bit (0) => 0x61 */
#define SLAVE_1 0x60
/* Address = 0x31 + W Bit (0) => 0x62 */
#define SLAVE_2 0x62

void MSSP_I2C_Send_1_Byte(uint8 slave_add, uint8 _data){
    Std_ReturnType ret = E_NOT_OK;
    ret = MSSP_I2C_Master_Send_Start(&i2c_obj);
    ret = MSSP_I2C_Master_Write_Blocking(&i2c_obj, slave_add, &slave_ack);
    ret = MSSP_I2C_Master_Write_Blocking(&i2c_obj, _data, &slave_ack);
    ret = MSSP_I2C_Master_Send_Stop(&i2c_obj);
}

int main() { 
    Std_ReturnType ret = E_NOT_OK;
    application_intialize();
    
    i2c_obj.i2c_clock = 100000;
    i2c_obj.i2c_cfg.i2c_mode = I2C_MSSP_MASTER_MODE;
    i2c_obj.i2c_cfg.i2c_mode_cfg = I2C_MASTER_MODE_DEFINED_CLOCK;
    i2c_obj.i2c_cfg.i2c_SMBus_control = I2C_SMBus_DISABLE;
    i2c_obj.i2c_cfg.i2c_slew_rate = I2C_SLEW_RATE_DISABLE;

    ret = MSSP_I2C_Init(&i2c_obj);

    while(1){
        MSSP_I2C_Send_1_Byte(SLAVE_1, 'a');
        __delay_ms(500);
        MSSP_I2C_Send_1_Byte(SLAVE_2, 'b');
        __delay_ms(500);
        MSSP_I2C_Send_1_Byte(SLAVE_1, 'c');
        __delay_ms(500);
        MSSP_I2C_Send_1_Byte(SLAVE_2, 'd');
        __delay_ms(500);
        app_counter++;
    }
    return (EXIT_SUCCESS);
}

void application_intialize(void){
    Std_ReturnType ret = E_NOT_OK;
    ecu_layer_intialize();
}


