/* 
 * File:   eeprom.h
 * Author: gaming3
 *
 * Created on February 29, 2024, 8:53 PM
 */

#ifndef EEPROM_H
#define	EEPROM_H

/*section : Includes  */

#include "../xc.h"
#include "../mcal_std_types.h"
#include "../interrupt/mcal_internal_interrupt.h"

/*section : Macro Declaration  */


/*section : Macro Functions Declaration  */


/*section : Data Type Declaration  */


/*section : Macro Declaration  */


/*section :  Functions Declaration  */
Std_ReturnType Data_EEPROM_WriteByte (uint_16 bAdd, uint_16 bData);
Std_ReturnType Data_EEPROM_ReadByte (uint_16 bAdd, uint_16 *bData);
#endif	/* EEPROM_H */

