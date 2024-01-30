/* 
 * File:   hal_gpio.h
 * Author: Rahim_Mohamed
 *
 * Created on October 7, 2023, 9:48 PM
 */

#ifndef HAL_GPIO_H
#define	HAL_GPIO_H


/*section : Includes  */

#include <xc.h>
#include "../mcal_std_types.h"
#include "../device_config/device_config.h"


/*section : Macro Declaration  */

#define BIT_MASK    (uint_8)1


#define MAX_NUMBER_PIN    8
#define MAX_NUMBER_PORT    5


#define PORT_PIN_CONFIGURATIONS    ENABLE
#define PORT_CONFIGURATIONS    ENABLE
/*section : Macro Functions Declaration  */

#define HWREG*(_X)        (*((volatile uint_8 *)(_X)))

#define SET_BIT(REG,BIT_POSN)       (REG |= (BIT_MASK<<BIT_POSN))
#define CLEAR_BIT(REG,BIT_POSN)     (REG &= ~(BIT_MASK<<BIT_POSN))
#define TOGGLE_BIT(REG,BIT_POSN)    (REG ^= (BIT_MASK<<BIT_POSN))
#define READ_BIT(REG,BIT_POSN)      ((REG >> BIT_POSN)&BIT_MASK)


/*section : Data Type Declaration  */

typedef enum{ LOW=0,
              HIGH
}logic_t;

typedef enum{ GPIO_OUTPUT=0,
              GPIO_INPUT
}direction_t;

typedef enum{ PORTA_INDEX=0,
              PORTB_INDEX,
              PORTC_INDEX,
              PORTD_INDEX,
              PORTE_INDEX,
}Port_index_t;

typedef enum{ GPIO_PIN0=0,
              GPIO_PIN1,
              GPIO_PIN2,
              GPIO_PIN3,
              GPIO_PIN4,
              GPIO_PIN5,
              GPIO_PIN6,
              GPIO_PIN7,
}pin_index_t;

typedef struct {
                 uint_8 port :3;
                 uint_8 pin  :3;
                 uint_8 direction :1;
                 uint_8 logic :1;
}pin_config_t;

/*section : Macro Declaration  */



/*section :  Functions Declaration  */

Std_ReturnType gpio_pin_direction_intialize(const pin_config_t * _pin_config);
Std_ReturnType gpio_pin_intialize(const pin_config_t * _pin_config);
Std_ReturnType gpio_pin_direction_status(const pin_config_t * _pin_config, direction_t *dic_status);   
Std_ReturnType gpio_pin_Write_logic(const pin_config_t * _pin_config, logic_t logic);   
Std_ReturnType gpio_pin_Read_logic(const pin_config_t * _pin_config, logic_t* logic);   
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t * _pin_config);

Std_ReturnType gpio_port_direction_intialize(Port_index_t port,uint_8 direction);
Std_ReturnType gpio_port_get_direction_status(Port_index_t port,uint_8 *dic_status);
Std_ReturnType gpio_port_Write_logic(Port_index_t port, uint_8 logic);   
Std_ReturnType gpio_port_Read_logic(Port_index_t port, uint_8 *logic);   
Std_ReturnType gpio_port_toggle_logic(Port_index_t port);

#endif	/* HAL_GPIO_H */

