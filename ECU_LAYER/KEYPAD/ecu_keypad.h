/* 
 * File:   ecu_keypad.h
 * Author: gaming3
 *
 * Created on December 9, 2023, 5:28 PM
 */

#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H
/*section : Includes  */

#include "ecu_keypad_cfg.h"
#include "../../MCAL_LAYER/GPIO/hal_gpio.h"


/*section : Macro Declaration  */

#define ROWS_NUMBER 4
#define COLUMNS_NUMBER 4

/*section : Macro Functions Declaration  */


/*section : Data Type Declaration  */

typedef struct {

 pin_config_t rows_pins[ROWS_NUMBER];
  pin_config_t columns_pins[COLUMNS_NUMBER];
         
}keypad_t;


/*section :  Functions Declaration  */\

Std_ReturnType keypad_intialize(const keypad_t* keypad_obj);
Std_ReturnType keypad_get_value(const keypad_t* keypad_obj,uint_8 * value);


#endif	/* ECU_KEYPAD_H */

