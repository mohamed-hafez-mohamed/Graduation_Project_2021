/****************************************************************************
* Title                 :   DISPLAY   
* Filename              :   DISPLAY.h
* Author                :   Mohamed Hafez
* Origin Date           :   22/05/2021
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
*  22/05/21   1.0.0   Mohamed Hafez   Interface Created.
*
*****************************************************************************/
/** @file  DISPLAY_interface.h
 *  @brief This module TODO: WHAT DO I DO?
 * 
 *  This is the header file for the definition TODO: MORE ABOUT ME!
 */
//TODO: UPDATE MACRO BELOW
#ifndef DISPLAY_INTERFACE_H_
#define DISPLAY_INTERFACE_H_

/******************************************************************************
* Includes
*******************************************************************************/
#include "Std_Types.h"
#include "LCD.h"
/******************************************************************************
* Preprocessor Constants
*******************************************************************************/

/******************************************************************************
* Configuration Constants
*******************************************************************************/
#define TEMPERATURE_ROW                          0
#define TEMPERATURE_WORD_COLUMN                  0
#define TEMPERATURE_VALUE_COLUMN                 2
#define TEMPERATURE_END_VALUE_COLUMN             3
#define TEMPERATURE_DISCRIMINATION_UNIT_COLUMN   4

#define SPEED_ROW                                1   
#define SPEED_WORD_COLUMN                        0
#define SPEED_VALUE_COLUMN                       2
#define END_OF_SPEED_VALUE_COLUMN                4
#define SPEED_DISCRIMINATION_UNIT_COLUMN         5

#define TIME_ROW                                 2
#define TIME_WORD_COLUMN                         0
#define FIRST_COLON                              5

#define MINUTES_COLUMN                           6
#define MINUTES_END_COLUMN                       7
#define HOURS_COLUMN                             3
#define HOURS_END_COLUMN                         4

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

/******************************************************************************
* Function : HDISPLAY_InitializeModule()
*//** 
* \b Description:
*
* This function is used to initialize display.
*
* PRE-CONDITION:  None
*
* POST-CONDITION: None
*
* @param [in]     void
* 
* @return 		   Std_ReturnType
*
* \b Example Example:
* @code
* 	FunctionReturnStatus = HDISPLAY_u8InitializeModule();
*
* @endcode
*
* @see HDISPLAY_u8InitializeModule
*
*******************************************************************************/
Std_ReturnType HDISPLAY_u8InitializeModule(void);
/******************************************************************************
* Function : HDISPLAY_HDISPLAY_u8DisplayDataModule()
*//** 
* \b Description:
*
* This function is used to display sensors' data.
*
* PRE-CONDITION:  None
*
* POST-CONDITION: None
*
* @param [in]     void
* 
* @return 		   Std_ReturnType
*
* \b Example Example:
* @code
* 	FunctionReturnStatus = HDISPLAY_u8DisplayData();
*
* @endcode
*
* @see HDISPLAY_u8DisplayData
*
*******************************************************************************/
Std_ReturnType HDISPLAY_u8DisplayData(void);

#endif /*File_H_*/

/*** End of File **************************************************************/
