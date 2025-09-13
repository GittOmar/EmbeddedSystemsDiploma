/*
 * File:   std_types.h
 * Author: pc
 * used for all modules
 * Created on June 21, 2025, 11:22 AM
 */

#ifndef STD_TYPES_H
#define STD_TYPES_H

/*****************************************
 *                 Includes              *
 *****************************************/
#include "compilar.h"
#include "std_libraries.h"
/*****************************************
 *           Macro Declarations          *
 *****************************************/
#define STD_ON 0x01
#define STD_OFF 0x00

#define STD_HIGH 0x01
#define STD_LOW 0x00

#define STD_ACTICE 0x01
#define STD_IDLE 0x00

#define E_OK (Std_RetuenType)0x01
#define E_NOT_OK (Std_RetuenType)0x00

#define ZERO_INIT   0x00

#define  _8BIT_MAX   (uint8)  (0xFF)
#define  _16BIT_MAX  (uint16) (0xFFFF)
#define  _32BIT_MAX  (uint32) (0xFFFFFFFF)
/*****************************************
 *       Macro Function Declarations     *
 *****************************************/

/*****************************************
 *          Data Type Declarations       *
 *****************************************/


// Unsigned types (stdint.h style)
typedef unsigned char        uint8;   // Range: 0 to 255
typedef unsigned short       uint16;  // Range: 0 to 65,535
typedef unsigned long int    uint32;  // Range: 0 to 4,294,967,295

// Signed types (stdint.h style)
typedef signed char          sint8;   // Range: -128 to +127
typedef signed short         sint16;  // Range: -32,768 to +32,767
typedef signed long int      sint32;  // Range: -2,147,483,648 to +2,147,483,647

typedef uint8 Std_RetuenType;
/*****************************************
 *        Function Declarations          *
 *****************************************/

#endif /* STD_TYPES_H */
