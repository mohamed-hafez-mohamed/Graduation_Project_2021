/****************************************************************************
* Title                 :   STK   
* Filename              :   STK_private.h
* Author                :   Mohamed Hafez
* Origin Date           :   26/08/2020
* Version               :   1.0.0
* Compiler              :   TODO: COMPILER GOES HERE
* Target                :   TODO: MCU GOES HERE
* Notes                 :   None
*
*****************************************************************************/
/****************************************************************************
* Doxygen C Template 
*
*****************************************************************************/
/*************** INTERFACE CHANGE LIST **************************************
*
*    Date    Version   Author          Description 
*  26/08/20   1.0.0   Mohamed Hafez   Interface Created.
*
*****************************************************************************/
/** @file  STK_private.h
 *  @brief This module TODO: WHAT DO I DO?
 * 
 *  This is the header file for the definition TODO: MORE ABOUT ME!
 */
//TODO: UPDATE MACRO BELOW
#ifndef STK_PRIVATE_H_
#define STK_PRIVATE_H_

/******************************************************************************
* Includes
*******************************************************************************/
#include "BIT_MATH.h"
#include "Std_Types.h"
/******************************************************************************
* Typedefs
*******************************************************************************/
typedef struct 
{
    volatile uint32 CTRL;
    volatile uint32 LOAD;
    volatile uint32 VAL;
    volatile uint32 CALIB;
}STK_t;

/******************************************************************************
* Preprocessor Constants
*******************************************************************************/
#define STK_CLR_REG            0x00000000
#define STK_GENERATE_1_MS      1000
#define STK_GENERATE_1_US      1000000
#define STK_SUB_1_FOR_PERIODIC 1
#define STK_DIVIDE_AHP_BY_8    8
/******************************************************************************
* Configuration Constants
*******************************************************************************/
//Register Definition
#define STK_BASE_ADDRESS   0xE000E010
#define STK                ((volatile STK_t * const)(STK_BASE_ADDRESS))
//Bits Definitions
#define ENABLE      0
#define TICKINT     1
#define CLKSOURCE   2
#define COUNTFLAG   16

/******************************************************************************
* Function Prototypes
*******************************************************************************/
static uint16 STK_u16ConfigIntervalMs(void);
static uint8  STK_u8ConfigIntervalUs(void);


#endif
/*** End of File **************************************************************/
