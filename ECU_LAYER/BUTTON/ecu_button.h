/* 
 * File:   ecu_button.h
 * Author: gaming3
 *
 * Created on October 28, 2023, 11:00 PM
 */

#ifndef ECU_BUTTON_H
#define	ECU_BUTTON_H

/*section : Includes  */

#include "ecu_button_cfg.h"
#include "../../MCAL_LAYER/GPIO/hal_gpio.h"

/*section : Macro Declaration  */


/*section : Macro Functions Declaration  */


/*section : Data Type Declaration  */

typedef enum {
    
    BUTTON_PRESSED=0,
    BUTTON_RELEASD
}button_state_t;

typedef enum {
    
    BUTTON_ACTIVE_LOW=0,
    BUTTON_ACTIVE_HIGH
}button_active_t;


typedef struct {
    
    pin_config_t button_pin;
     button_state_t btn_status;
     button_active_t btn_connection;
   
}button_t;



/*section : Macro Declaration  */


/*section :  Functions Declaration  */


Std_ReturnType button_intialize(const button_t* _btn);
Std_ReturnType button_Read(const button_t * btn , button_state_t * btn_state);

#endif	/* ECU_BUTTON_H */

