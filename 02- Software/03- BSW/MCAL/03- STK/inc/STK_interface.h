/****************************************************************************
* Title                 :   STK   
* Filename              :   STK_interface.h
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
*  26/8/20   1.0.0   Mohamed Hafez   Interface Created.
*
*****************************************************************************/
/** @file  STK_interface.h
 *  @brief This module TODO: WHAT DO I DO?
 * 
 *  This is the header file for the definition TODO: MORE ABOUT ME!
 */
//TODO: UPDATE MACRO BELOW
#ifndef STK_INTERFACE_H_
#define STK_INTERFACE_H_

/******************************************************************************
* Includes
*******************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
/******************************************************************************
* Preprocessor Constants
*******************************************************************************/

/******************************************************************************
* Configuration Constants
*******************************************************************************/

#define STK_AHB_CLOCK_SOURCE_DIV_8 0x00000000
#define STK_AHB_CLOCK_SOURCE       0x00000004
/******************************************************************************
* Macros
*******************************************************************************/
	
/******************************************************************************
* Typedefs
*******************************************************************************/

typedef void (*STK_PtrToFunction)(void * );
/******************************************************************************
* Variables
*******************************************************************************/

/******************************************************************************
* Function Prototypes
*******************************************************************************/

void MSTK_voidInit(void);
void MSTK_voidSetBusyWait_ms(u16 Copy_u16DelayMs);
void MSTK_voidSetBusyWait_us(u32 Copy_u32DelayUs);
void MSTK_voidSetIntervalSingle_ms(u16 Copy_u16DelayMs,   STK_PtrToFunction Copy_PtrFunction, void * Copy_Parameter);
void MSTK_voidSetIntervalSingle_us(u32 Copy_u32DelayUs,   STK_PtrToFunction Copy_PtrFunction, void * Copy_Parameter);
void MSTK_voidSetIntervalPeriodic_ms(u16 Copy_u16DelayMs, STK_PtrToFunction Copy_PtrFunction, void * Copy_Parameter);
void MSTK_voidSetIntervalPeriodic_us(u32 Copy_u32DelayUs, STK_PtrToFunction Copy_PtrFunction, void * Copy_Parameter);
void MSTK_voidStopStk(void);
void MSTK_voidResumeStk(void);
u32  MSTK_u32GetElapsedTime_us(void);
u32  MSTK_u32GetElapsedTime_ms(void);
u32  MSTK_u32GetRemainingTime_us(void);
u32  MSTK_u32GetRemainingTime_ms(void);

u32  MSTK_u32ReturnElapsedTicks(void);
void MSTK_voidDelayUsingInterrupt(u16 Copy_u16DelayMs);

#endif /*File_H_*/

/*** End of File **************************************************************/
