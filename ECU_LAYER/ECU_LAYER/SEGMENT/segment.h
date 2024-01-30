/* 
 * File:   segment.h
 * Author: gaming3
 *
 * Created on December 8, 2023, 3:06 AM
 */

#ifndef SEGMENT_H
#define	SEGMENT_H

/*section : Includes  */

#include "segment_cfg.h"
#include "../../MCAL_LAYER/GPIO/hal_gpio.h"

/*section : Macro Declaration  */


/*section : Macro Functions Declaration  */


/*section : Data Type Declaration  */

typedef enum {
    
    SEGMENT_COMMON_ANODE,
    SEGMENT_COMMON_CATHODE,      
    
}segment_type_t;

typedef struct {
    
    pin_config_t segment_pins[4];
    segment_type_t type;
    
}segment_t;

/*section : Macro Declaration  */


/*section :  Functions Declaration  */

Std_ReturnType segment_intialize(const segment_t* seg);
Std_ReturnType segment_write_number(const segment_t* seg,uint_8 number);

#endif	/* SEGMENT_H */

