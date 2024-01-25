/* 
 * File:   mcal_std_types.h
 * Author: gaming3
 *
 * Created on October 7, 2023, 9:58 PM
 */

#ifndef MCAL_STD_TYPES_H
#define	MCAL_STD_TYPES_H


/*section : Includes  */

#include "compiler.h"
#include "std_libraries.h"

/*section : Data Type Declaration  */

typedef unsigned char  uint_8;
typedef unsigned short uint_16;
typedef unsigned int   uint_32;
typedef unsigned long  uint_64;

typedef signed char    sint_8;
typedef signed short   sint_16;
typedef signed int     sint_32;
typedef signed long    sint_64;

typedef  uint_8   Std_ReturnType;


/*section : Macro Declaration  */

#define STD_HIGH     0x01
#define STD_LOW      0x00

#define STD_ON       0x01
#define STD_OFF      0x00

#define ENABLE            0x01
#define DISABLE           0x00

#define STD_ACTIVE   0x01
#define STD_IDLE     0x00

#define E_OK        (Std_ReturnType) 0x01
#define E_NOT_OK    (Std_ReturnType) 0x00

/*section : Macro Functions Declaration  */

/*section : Macro Declaration  */


/*section :  Functions Declaration  */


#endif	/* MCAL_STD_TYPES_H */

