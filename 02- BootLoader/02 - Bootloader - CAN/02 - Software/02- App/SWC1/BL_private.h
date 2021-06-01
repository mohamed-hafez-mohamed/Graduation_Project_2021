/****************************************************************************
* Title                 :   BL   
* Filename              :   BL_private.h
* Author                :   Mohamed Hafez
* Origin Date           :   14/10/2020
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
*  14/10/20   1.0.0   Mohamed Hafez   Interface Created.
*
*****************************************************************************/
/** @file  BL_private.h
 *  @brief This module TODO: WHAT DO I DO?
 * 
 *  This is the header file for the definition TODO: MORE ABOUT ME!
 */
//TODO: UPDATE MACRO BELOW
#ifndef BL_PRIVATE_H_
#define BL_PRIVATE_H_

/******************************************************************************
* Includes
*******************************************************************************/

/******************************************************************************
* Typedefs
*******************************************************************************/

/******************************************************************************
* Preprocessor Constants
*******************************************************************************/

/******************************************************************************
* Configuration Constants
*******************************************************************************/
// Auxaliary constants.
#define ADD_NULL_CHARACTER_PLACE                1
#define ONE_BYTE_SIZE_IN_BITS_TO_DIGIT          2
#define HALF_BYTE_SIZE_IN_BITS                  4
#define ONE_BYTE_SIZE_IN_BITS                   8
#define ONE_HALF_BYTE_SIZE_IN_BITS              12
#define TWO_BYTE_SIZE_IN_BITS                   16   
#define NUMBER_OF_DATA_BYTES_IN_RECORD          16
#define NUMBER_OF_DATA_HALF_WORD_IN_RECORD      8
#define SUBTRACT_NULL_CHARACTER                      1
#define FIRST_DATA_DIGIT                        0  
#define SECOND_DATA_DIGIT                       1  
#define THIRD_DATA_DIGIT                        2
#define FOURTH_DATA_DIGIT                       3
#define SCB_VTOR_ADDRESS                        0xE000ED08
#define PACKET_SIZE                             64
// For converting ascii to hex
#define ZERO_IN_ASCII                           48
#define NINE_IN_ASCII                           57
#define CONVERT_NUMBERS_UNDER_NINE_ASCII_TO_HEX 48
#define CONVERT_NUMBERS_ABOVE_NINE_TO_HEX       55
/******************************************************************************
* Module Variable Definitions
*******************************************************************************/

/******************************************************************************
* Function Prototypes
*******************************************************************************/
static u8 ABL_u8AsciiToHex(u8 Copy_u8Ascii);
#endif
/*** End of File **************************************************************/
