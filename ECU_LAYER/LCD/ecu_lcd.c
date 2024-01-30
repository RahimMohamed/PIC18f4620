/* 
 * File:   ecu_lcd.c
 * Author: gaming3
 *
 * Created on October 7, 2023, 10:15 PM
 */
#include "ecu_lcd.h"
uint_8 lcd_counter=0;
/*******************************************************************************************/
static void send_4bit (const lcd_4bit_t *lcd, uint_8 _data_command);
static void send_4bit_enable_signal (const lcd_4bit_t *lcd);
static void send_8bit_enable_signal (const lcd_8bit_t *lcd);
static void set_cursor_8bit (const lcd_8bit_t *lcd ,uint_8 row,uint_8 column);
static void set_cursor_4bit (const lcd_4bit_t *lcd ,uint_8 row,uint_8 column);

/*******************************************************************************************/

Std_ReturnType lcd_4bit_intialize(const lcd_4bit_t *lcd ){
    
    
    Std_ReturnType ret = E_OK;
    if (NULL == lcd ){
        ret=E_NOT_OK;
    }
    else{
        
        ret=gpio_pin_intialize(&(lcd->lcd_rs));
        ret=gpio_pin_intialize(&(lcd->lcd_en));
        for(lcd_counter=0;lcd_counter<4;lcd_counter++){
             ret=gpio_pin_intialize(&(lcd->lcd_data[lcd_counter]));
        }
        
         __delay_ms(20);
        lcd_4bit_send_command(lcd,_LCD_8BIT_MODE_2_LINE);
         __delay_ms(5);
        lcd_4bit_send_command(lcd,_LCD_8BIT_MODE_2_LINE);
         __delay_us(150);
        lcd_4bit_send_command(lcd,_LCD_8BIT_MODE_2_LINE);
        
         lcd_4bit_send_command(lcd,_LCD_CLEAR);
         lcd_4bit_send_command(lcd,_LCD_RETURN_HOME);
         lcd_4bit_send_command(lcd,_LCD_ENTRY_MODE);
         lcd_4bit_send_command(lcd,_LCD_CURSOR_OFF_DISPLAY_ON);
         //lcd_4bit_send_command(lcd,_LCD_CURSOR_ON_BLINK_ON);
         lcd_4bit_send_command(lcd,_LCD_4BIT_MODE_2_LINE);
         lcd_4bit_send_command(lcd,_LCD_DDRAM_START);
    }
    return ret;
    
}
/*******************************************************************************************/
Std_ReturnType lcd_4bit_send_command (const lcd_4bit_t *lcd, uint_8 command){
    
    
    
    Std_ReturnType ret = E_OK;
    if (NULL == lcd ){
        ret=E_NOT_OK;
    }
    else{
        gpio_pin_Write_logic(&(lcd->lcd_rs),LOW);
        send_4bit(lcd,command>>4);
        send_4bit_enable_signal(lcd);
        send_4bit(lcd,command);
        send_4bit_enable_signal(lcd);
    }
    return ret;
    
    
}
/*******************************************************************************************/
Std_ReturnType lcd_4bit_send_data (const lcd_4bit_t *lcd, uint_8 data){
    
    
    Std_ReturnType ret = E_OK;
    if (NULL == lcd ){
        ret=E_NOT_OK;
    }
    else{
      gpio_pin_Write_logic(&(lcd->lcd_rs),HIGH);
        send_4bit(lcd,data>>4);
        send_4bit_enable_signal(lcd);
        send_4bit(lcd,data);
        send_4bit_enable_signal(lcd);
    }
    return ret;
    
}
/*******************************************************************************************/
Std_ReturnType lcd_4bit_send_data_pos (const lcd_4bit_t *lcd,uint_8 row,uint_8 column, uint_8 data){
    
    
    Std_ReturnType ret = E_OK;
    if (NULL == lcd ){
        ret=E_NOT_OK;
    }
    else{
       set_cursor_4bit(lcd,row,column);
        lcd_4bit_send_data(lcd,data);
    }
    return ret;
    
}
/*******************************************************************************************/
Std_ReturnType lcd_4bit_send_string (const lcd_4bit_t *lcd, uint_8 *str){
    
    
    Std_ReturnType ret = E_OK;
    if (NULL == lcd ){
        ret=E_NOT_OK;
    }
    else{
        while(*str){
            lcd_4bit_send_data(lcd,*str++);
        }
    }
    return ret;
    
    
}
/*******************************************************************************************/
Std_ReturnType lcd_4bit_send_string_pos (const lcd_4bit_t *lcd,uint_8 row,uint_8 column, uint_8 *str){
    
    
    Std_ReturnType ret = E_OK;
    if (NULL == lcd ){
        ret=E_NOT_OK;
    }
    else{
        set_cursor_4bit(lcd,row,column);
        lcd_4bit_send_string(lcd,str);
    }
    return ret;
    
    
    
}
/*******************************************************************************************/
Std_ReturnType lcd_4bit_send_custom_char (const lcd_4bit_t *lcd,uint_8 row,uint_8 column, uint_8 chr[],uint_8 mem_pos){
    
    uint_8 cust_counter=0;
    
    
    Std_ReturnType ret = E_OK;
    if (NULL == lcd ){
        ret=E_NOT_OK;
    }
    else{
        lcd_4bit_send_command(lcd,(_LCD_CGRAM_START + (mem_pos*8)));
        for(cust_counter=0;cust_counter<=7;cust_counter++){
            lcd_4bit_send_data(lcd,chr[cust_counter]);
        }
        lcd_4bit_send_data_pos(lcd,row,column,mem_pos);
    }
    return ret;
    
    
}


/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/

Std_ReturnType lcd_8bit_intialize(const lcd_8bit_t *lcd ){
    
    
    Std_ReturnType ret = E_OK;
    if (NULL == lcd ){
        ret=E_NOT_OK;
    }
    else{
           ret=gpio_pin_intialize(&(lcd->lcd_rs));
        ret=gpio_pin_intialize(&(lcd->lcd_en));
        for(lcd_counter=0;lcd_counter<8;lcd_counter++){
             ret=gpio_pin_intialize(&(lcd->lcd_data[lcd_counter]));
        }
        
        __delay_ms(20);
        lcd_8bit_send_command(lcd,_LCD_8BIT_MODE_2_LINE);
         __delay_ms(5);
        lcd_8bit_send_command(lcd,_LCD_8BIT_MODE_2_LINE);
         __delay_us(150);
        lcd_8bit_send_command(lcd,_LCD_8BIT_MODE_2_LINE);
        
         lcd_8bit_send_command(lcd,_LCD_CLEAR);
         lcd_8bit_send_command(lcd,_LCD_RETURN_HOME);
         lcd_8bit_send_command(lcd,_LCD_ENTRY_MODE);
         lcd_8bit_send_command(lcd,_LCD_CURSOR_OFF_DISPLAY_ON);
         //lcd_8bit_send_command(lcd,_LCD_CURSOR_ON_BLINK_ON);
         lcd_8bit_send_command(lcd,_LCD_8BIT_MODE_2_LINE);
         lcd_8bit_send_command(lcd,_LCD_DDRAM_START);
        
    }
    return ret;
    
    
    
}

/*******************************************************************************************/


Std_ReturnType lcd_8bit_send_command (const lcd_8bit_t *lcd, uint_8 command){
    
    
    
    Std_ReturnType ret = E_OK;
    if (NULL == lcd ){
        ret=E_NOT_OK;
    }
    else{
        gpio_pin_Write_logic(&(lcd->lcd_rs),LOW);
        for(lcd_counter=0;lcd_counter<8;lcd_counter++){
          gpio_pin_Write_logic(&(lcd->lcd_data[lcd_counter]),(command>>lcd_counter)&0x01);
        }
        send_8bit_enable_signal(lcd);
    }
    return ret;
    
    
}
/*******************************************************************************************/


Std_ReturnType lcd_8bit_send_data (const lcd_8bit_t *lcd, uint_8 data){
    
    
    
    Std_ReturnType ret = E_OK;
    if (NULL == lcd ){
        ret=E_NOT_OK;
    }
    else{
          gpio_pin_Write_logic(&(lcd->lcd_rs),HIGH);
        for(lcd_counter=0;lcd_counter<8;lcd_counter++){
          gpio_pin_Write_logic(&(lcd->lcd_data[lcd_counter]),(data>>lcd_counter)&0x01);
        }
        send_8bit_enable_signal(lcd);
    }
    return ret;
    
    
}

/*******************************************************************************************/

Std_ReturnType lcd_8bit_send_data_pos (const lcd_8bit_t *lcd,uint_8 row,uint_8 column, uint_8 data){
    
    
    Std_ReturnType ret = E_OK;
    if (NULL == lcd ){
        ret=E_NOT_OK;
    }
    else{
        set_cursor_8bit(lcd,row,column);
        lcd_8bit_send_data(lcd,data);
    }
    return ret;
    
    
    
}
/*******************************************************************************************/


Std_ReturnType lcd_8bit_send_string (const lcd_8bit_t *lcd, uint_8 *str){
    
    
    Std_ReturnType ret = E_OK;
    if (NULL == lcd ){
        ret=E_NOT_OK;
    }
    else{
        while(*str){
            lcd_8bit_send_data(lcd,*str++);
        }
    }
    return ret;
    
    
    
    
    
}


/*******************************************************************************************/


Std_ReturnType lcd_8bit_send_string_pos (const lcd_8bit_t *lcd,uint_8 row,uint_8 column, uint_8 *str){
    
    
     Std_ReturnType ret = E_OK;
    if (NULL == lcd ){
        ret=E_NOT_OK;
    }
    else{
        set_cursor_8bit(lcd,row,column);
        lcd_8bit_send_string(lcd,str);
    }
    return ret;
    
    
}

/*******************************************************************************************/
Std_ReturnType lcd_8bit_send_custom_char (const lcd_8bit_t *lcd,uint_8 row,uint_8 column, uint_8 chr[],uint_8 mem_pos){
    
    uint_8 cust_counter=0;
    Std_ReturnType ret = E_OK;
    if (NULL == lcd ){
        ret=E_NOT_OK;
    }
    else{
        lcd_8bit_send_command(lcd,(_LCD_CGRAM_START + (mem_pos*8)));
        for(cust_counter=0;cust_counter<=7;cust_counter++){
            lcd_8bit_send_data(lcd,chr[cust_counter]);
        }
        lcd_8bit_send_data_pos(lcd,row,column,mem_pos);
    }
    return ret;
    
    
    
    
    
}

/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/


void convert_byte_to_string (uint_8 value, uint_8 *str){
    
    
    Std_ReturnType ret = E_OK;
    if (NULL == str ){
        ret=E_NOT_OK;
    }
    else{
        memset(str,'\0',4);
        sprintf(str,"%i",value);
    }
    
    
    
}

/*******************************************************************************************/
void convert_short_to_string (uint_16 value, uint_8 *str){
    
    
    Std_ReturnType ret = E_OK;
    if (NULL == str ){
        ret=E_NOT_OK;
    }
    else{
        memset(str,'\0',6);
        sprintf(str,"%i",value);
    }
    
    
    
}
/*******************************************************************************************/
void convert_int_to_string (uint_32 value, uint_8 *str){
    
    
    Std_ReturnType ret = E_OK;
    if (NULL == str ){
        ret=E_NOT_OK;
    }
    else{
        memset(str,'\0',11);
        sprintf(str,"%i",value);
    }
   
    
    
}

/********************************************************************************************/
/*********************************************************************************************/
/********************************************************************************************/

static void send_4bit (const lcd_4bit_t *lcd, uint_8 _data_command){
    gpio_pin_Write_logic(&(lcd->lcd_data[0]),(_data_command>>0)&0x01);
    gpio_pin_Write_logic(&(lcd->lcd_data[1]),(_data_command>>1)&0x01);
    gpio_pin_Write_logic(&(lcd->lcd_data[2]),(_data_command>>2)&0x01);
    gpio_pin_Write_logic(&(lcd->lcd_data[3]),(_data_command>>3)&0x01);
}


/**********************************************************************************************/

static void send_4bit_enable_signal (const lcd_4bit_t *lcd){
    
    gpio_pin_Write_logic(&(lcd->lcd_en),HIGH);
    __delay_us(5);
    gpio_pin_Write_logic(&(lcd->lcd_en),LOW);
}

/**********************************************************************************************/

static void send_8bit_enable_signal (const lcd_8bit_t *lcd){
    
    gpio_pin_Write_logic(&(lcd->lcd_en),HIGH);
     __delay_us(5);
    gpio_pin_Write_logic(&(lcd->lcd_en),LOW);
}

/**********************************************************************************************/

static void set_cursor_8bit (const lcd_8bit_t *lcd ,uint_8 row,uint_8 column){
    column--;
    switch (row){
        case 1: lcd_8bit_send_command(lcd,(0x80+column));break;
        case 2: lcd_8bit_send_command(lcd,(0xc0+column));break;
        case 3: lcd_8bit_send_command(lcd,(0x94+column));break;
        case 4: lcd_8bit_send_command(lcd,(0xd4+column));break;
        default : ;
    }
}
/**********************************************************************************************/

static void set_cursor_4bit (const lcd_4bit_t *lcd ,uint_8 row,uint_8 column){
    column--;
    switch (row){
        case 1: lcd_4bit_send_command(lcd,(0x80+column));break;
        case 2: lcd_4bit_send_command(lcd,(0xc0+column));break;
        case 3: lcd_4bit_send_command(lcd,(0x94+column));break;
        case 4: lcd_4bit_send_command(lcd,(0xd4+column));break;
        default : ;
    }
}