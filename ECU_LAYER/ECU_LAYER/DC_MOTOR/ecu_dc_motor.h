/* 
 * File:   ecu_dc_motor.h
 * Author: gaming3
 *
 * Created on November 25, 2023, 1:31 AM
 */

#ifndef ECU_DC_MOTOR_H
#define	ECU_DC_MOTOR_H

/*section : Includes  */

#include "ecu_dc_motor_cfg.h"
#include "../../MCAL_LAYER/GPIO/hal_gpio.h"

/*section : Macro Declaration  */


/*section : Macro Functions Declaration  */


/*section : Data Type Declaration  */

typedef enum {
    MOTTOR_OFF_STATE=0,
    MOTTOR_ON_STATE   
}motor_state_t ;

typedef struct {
    
    pin_config_t motor_config[2]; 
}motor_t;

/*section : Macro Declaration  */


/*section :  Functions Declaration  */

Std_ReturnType motor_intialize(const motor_t* motor);
Std_ReturnType motor_move_right(const motor_t* motor);
Std_ReturnType motor_move_left(const motor_t* motor);
Std_ReturnType motor_stop(const motor_t* motor);

#endif	/* ECU_DC_MOTOR_H */

