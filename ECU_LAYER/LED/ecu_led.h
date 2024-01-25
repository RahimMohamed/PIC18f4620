/* 
 * File:   ecu_led.h
 * Author: gaming3
 *
 * Created on October 7, 2023, 10:15 PM
 */

#ifndef ECU_LED_H
#define	ECU_LED_H

/*section : Includes  */
#include "../../MCAL_LAYER/GPIO/hal_gpio.h"
#include "ecu_led_cfg.h"

/*section : Macro Declaration  */


/*section : Macro Functions Declaration  */


/*section : Data Type Declaration  */
typedef enum{
    LED_OFF, 
    LED_ON        
}ledd_status;

typedef struct {
    
    uint_8 port_name : 4;
    uint_8 pin: 3;
    uint_8 led_ststus:1;
    
}led_t;

/*section : Macro Declaration  */


/*section :  Functions Declaration  */


Std_ReturnType led_initialize (const led_t *led);
Std_ReturnType led_turn_on (const led_t *led);
Std_ReturnType led_turn_off(const led_t *led);
Std_ReturnType led_toggle (const led_t *led);

#endif	/* ECU_LED_H */

