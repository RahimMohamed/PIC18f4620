/* 
 * File:   ecu_relay.h
 * Author: gaming3
 *
 * Created on November 3, 2023, 2:42 AM
 */

#ifndef ECU_RELAY_H
#define	ECU_RELAY_H

/*section : Includes  */

#include "ecu_relay_cfg.h"
#include "../../MCAL_LAYER/GPIO/hal_gpio.h"

/*section : Macro Declaration  */


/*section : Macro Functions Declaration  */


/*section : Data Type Declaration  */

typedef enum {
    RELAY_OFF_STATE=0,
    RELAY_ON_STATE   
}relay_state_t ;

typedef struct {
    
    pin_config_t relay_config;
    relay_state_t status;
    
}relay_t;


/*section : Macro Declaration  */


/*section :  Functions Declaration  */


Std_ReturnType relay_initialize(const relay_t* relay);
Std_ReturnType turn_on_relay (const relay_t* relay );
Std_ReturnType turn_off_relay (const relay_t* relay );

#endif	/* ECU_RELAY_H */

