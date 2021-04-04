/****************************************************************************
* Title                 :   STK   
* Filename              :   STK_config.h
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
/** @file  STK_STK_config.h
 *  @brief This module TODO: WHAT DO I DO?
 * 
 *  This is the header file for the definition TODO: MORE ABOUT ME!
 */
//TODO: UPDATE MACRO BELOW
#ifndef STK_CONFIG_H_
#define STK_CONFIG_H_

/******************************************************************************
* Includes
*******************************************************************************/

/******************************************************************************
* Preprocessor Constants
*******************************************************************************/

/******************************************************************************
* Configuration Constants
*******************************************************************************/

/*Chooce the AHP Frequency*/
#define AHP_CLOCK_FREQ (8000000)

/* Choose The Clock Source
STK_AHB_CLOCK_SOURCE_DIV_8 0x00000000
STK_AHB_CLOCK_SOURCE       0x00000004
*/
#define STK_CLOCK_SOURCE    STK_AHB_CLOCK_SOURCE_DIV_8

#endif /*File_H_*/

/*** End of File **************************************************************/
