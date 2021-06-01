/****************************************************************************
* Title                 :   LCD   
* Filename              :   LCD_private.h
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
/** @file  LCD_private.h
 *  @brief This module TODO: WHAT DO I DO?
 * 
 *  This is the header file for the definition TODO: MORE ABOUT ME!
 */
//TODO: UPDATE MACRO BELOW
#ifndef LCD_PRIVATE_H_
#define LCD_PRIVATE_H_

/******************************************************************************
* Includes
*******************************************************************************/
#include "Std_Types.h"
/******************************************************************************
* Typedefs
*******************************************************************************/

/******************************************************************************
* Preprocessor Constants
*******************************************************************************/
#define SET                             1
#define LCD_CLEAR_SCREEN_CMD            0x01
#define LCD_4BIT_MODE_CMD               0x02
#define LCD_ENTRY_DEC_CMD   				 0x04
#define LCD_ENTRY_DEC_SHIFT_CMD   		 0x05
#define LCD_ENTRY_MODE_CMD              0x06
#define LCD_ENTRY_INC_SHIFT_CMD   		 0x07
#define LCD_DISPLAY_OFF_CMD             0x08
#define LCD_CURSOR_OFF_CMD              0x0C
#define LCD_DISP_ON_BLINK_CMD   			 0x0D
#define LCD_CURSOR_ON_CMD               0x0E
#define LCD_CURSOR_BLINK_CMD            0x0F
#define LCD_MOVE_CURSOR_LEFT_CMD 	    0x10
#define LCD_MOVE_CURSOR_RIGHT_CMD   	 0x14
#define LCD_MOVE_DISP_LEFT_CMD   		 0x18
#define LCD_MOVE_DISP_RIGHT_CMD       	 0x1C
#define LCD_4BIT_MODE_2_LINE_CMD        0x28
#define LCD_8BIT_MODE_2_LINE_CMD        0x38

#define LCD_BEGIN_AT_FIRST_RAW_CMD		 0x80
#define LCD_BEGIN_AT_SECOND_RAW_CMD		 0x90
#define LCD_BEGIN_AT_THIRD_RAW_CMD		 0x88
#define LCD_BEGIN_AT_FOURTH_RAW_CMD		 0x98
/******************************************************************************
* Configuration Constants
*******************************************************************************/

/******************************************************************************
* Function Prototypes
*******************************************************************************/
static void HLCD_voidkick(uint8 Copy_u8Character);

#endif
/*** End of File **************************************************************/
