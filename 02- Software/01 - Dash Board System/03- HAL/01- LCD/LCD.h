/****************************************************************************
* Title                 :   LCD   
* Filename              :   LCD_interface.h
* Author                :   Mohamed Hafez
* Origin Date           :   22/09/2020
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
*  22/09/20   1.0.0   Mohamed Hafez   Interface Created.
*
*****************************************************************************/
/** @file  LCD_interface.h
 *  @brief This module TODO: WHAT DO I DO?
 * 
 *  This is the header file for the definition TODO: MORE ABOUT ME!
 */
//TODO: UPDATE MACRO BELOW
#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

/******************************************************************************
* Includes
*******************************************************************************/
#include "Std_Types.h"
/******************************************************************************
* Preprocessor Constants
*******************************************************************************/
#define LCD_DECIMAL                   10
#define LCD_NUMBER_TYPE_AFTER_POINT   100
/******************************************************************************
* Configuration Constants
*******************************************************************************/

/******************************************************************************
* Macros
*******************************************************************************/
	
/******************************************************************************
* Typedefs
*******************************************************************************/

/******************************************************************************
* Variables
*******************************************************************************/

/******************************************************************************
* Function Prototypes
*******************************************************************************/
Std_ReturnType HLCD_u8Init(void);
Std_ReturnType HLCD_u8CMD(uint8 Copy_u8Command);
Std_ReturnType HLCD_u8SetCursor(uint8 Copy_u8Row, uint8 Copy_u8Col);
Std_ReturnType HLCD_u8ClearSreen(void);
Std_ReturnType HLCD_u8TurnOffDisplay(void);
Std_ReturnType HLCD_u8WriteChar(uint8 Copy_u8Character);
Std_ReturnType HLCD_u8WriteString(uint8 * Copy_u8String);
Std_ReturnType HLCD_u8WriteIntNum(uint8 Copy_u8Number);
Std_ReturnType HLCD_u8WriteFloatNum(float32 Copy_floatNumber);

#endif /*File_H_*/

/*** End of File **************************************************************/
