/* 
 * File:   ecu_lcd.h
 * Author: gaming3
 *
 * Created on January 28, 2024, 1:37 PM
 */

#ifndef ECU_LCD_H
#define	ECU_LCD_H

/*section : Includes  */

#include "ecu_lcd_cfg.h"
#include "../../MCAL_LAYER/GPIO/hal_gpio.h"

/*section : Macro Declaration  */


/*section : Macro Functions Declaration  */


/*section : Data Type Declaration  */
typedef struct{
    pin_config_t lcd_rs;
    pin_config_t lcd_en;
    pin_config_t lcd_data[4];
}lcd_4bit_t;


typedef struct{
    pin_config_t lcd_rs;
    pin_config_t lcd_en;
    pin_config_t lcd_data[8];
}lcd_8bit_t;

/*section : Macro Declaration  */


#define _LCD_CLEAR                         0X01
#define _LCD_RETURN_HOME                   0X02
#define _LCD_ENTRY_MODE                    0X06  // cursor increment & shift off 
#define _LCD_CURSOR_OFF_DISPLAY_ON         0X0C  
#define _LCD_CURSOR_OFF_DISPLAY_OFF        0X08
#define _LCD_CURSOR_ON_BLINK_ON            0X0F
#define _LCD_CURSOR_ON_BLINK_OFF           0X0E
#define _LCD_DISPLAY_SHIFT_RIGHT           0X1C
#define _LCD_DISPLAY_SHIFT_LEFT            0X18
#define _LCD_8BIT_MODE_2_LINE              0X38
#define _LCD_4BIT_MODE_2_LINE              0X28
#define _LCD_CGRAM_START                   0X40
#define _LCD_DDRAM_START                   0X80

/*section :  Functions Declaration  */

Std_ReturnType lcd_4bit_intialize(const lcd_4bit_t *lcd );
Std_ReturnType lcd_4bit_send_command (const lcd_4bit_t *lcd, uint_8 command);
Std_ReturnType lcd_4bit_send_data (const lcd_4bit_t *lcd, uint_8 data);
Std_ReturnType lcd_4bit_send_data_pos (const lcd_4bit_t *lcd,uint_8 row,uint_8 column, uint_8 data);
Std_ReturnType lcd_4bit_send_string (const lcd_4bit_t *lcd, uint_8 *str);
Std_ReturnType lcd_4bit_send_string_pos (const lcd_4bit_t *lcd,uint_8 row,uint_8 column, uint_8 *str);
Std_ReturnType lcd_4bit_send_custom_char (const lcd_4bit_t *lcd,uint_8 row,uint_8 column, uint_8 chr[],uint_8 mem_pos);

Std_ReturnType lcd_8bit_intialize(const lcd_8bit_t *lcd );
Std_ReturnType lcd_8bit_send_command (const lcd_8bit_t *lcd, uint_8 command);
Std_ReturnType lcd_8bit_send_data (const lcd_8bit_t *lcd, uint_8 data);
Std_ReturnType lcd_8bit_send_data_pos (const lcd_8bit_t *lcd,uint_8 row,uint_8 column, uint_8 data);
Std_ReturnType lcd_8bit_send_string (const lcd_8bit_t *lcd, uint_8 *str);
Std_ReturnType lcd_8bit_send_string_pos (const lcd_8bit_t *lcd,uint_8 row,uint_8 column, uint_8 *str);
Std_ReturnType lcd_8bit_send_custom_char (const lcd_8bit_t *lcd,uint_8 row,uint_8 column, uint_8 chr[],uint_8 mem_pos);


void convert_byte_to_string (uint_8 value, uint_8 *str);
void convert_short_to_string (uint_16 value, uint_8 *str);
void convert_int_to_string (uint_32 value, uint_8 *str);
#endif	/* ECU_LCD_H */

