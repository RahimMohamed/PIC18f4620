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
/* ----------------- Macro Declarations -----------------*/
/* Flash Program or Data EEPROM Memory Select  */
#define ACCESS_FLASH_PROGRAM_MEMORY       1
#define ACCESS_EEPROM_PROGRAM_MEMORY      0
/* Flash Program/Data EEPROM or Configuration Select */
#define ACCESS_CONFIG_REGISTERS           1
#define ACCESS_FLASH_EEPROM_MEMORY        0
/* Flash Program/Data EEPROM Write Enable */
#define ALLOW_WRITE_CYCLES_FLASH_EEPROM   1
#define INHIBTS_WRITE_CYCLES_FLASH_EEPROM 0
/* Write Control */
#define INITIATE_DATA_EEPROM_WRITE_ERASE  1
#define DATA_EEPROM_WRITE_ERASE_COMPLETED 0
/* Read Control */
#define INITIATE_DATA_EEPROM_READ         1

/*section : Macro Functions Declaration  */


/*section : Data Type Declaration  */


/*section : Macro Declaration  */


/*section :  Functions Declaration  */
Std_ReturnType Data_EEPROM_WriteByte (uint_16 bAdd, uint_16 bData);
Std_ReturnType Data_EEPROM_ReadByte (uint_16 bAdd, uint_16 *bData);
#endif	/* EEPROM_H */

