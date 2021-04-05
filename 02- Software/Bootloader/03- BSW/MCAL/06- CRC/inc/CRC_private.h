/****************************************************************************
* Title                 :   CRC   
* Filename              :   CRC_private.h
* Author                :   Mohamed Hafez
* Origin Date           :   10/08/2020
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
*  10/08/20   1.0.0   Mohamed Hafez   Interface Created.
*
*****************************************************************************/
/** @file  CRC_private.h
 *  @brief This module TODO: WHAT DO I DO?
 * 
 *  This is the header file for the definition TODO: MORE ABOUT ME!
 */
//TODO: UPDATE MACRO BELOW
#ifndef CRC_PRIVATE_H_
#define CRC_PRIVATE_H_

/******************************************************************************
* Includes
*******************************************************************************/

/******************************************************************************
* Typedefs
*******************************************************************************/

/******************************************************************************
* Preprocessor Constants
*******************************************************************************/
// CRC base address.
#define CRC_BASE_ADDRESS     0x40023000
/*!<**************************Offset Definition********************************/
#define DR                   0X00
#define IDR                  0X04
#define CR                   0X08
/*!<***************************Register Address for PORTA**********************/
#define CRC_DR           *((volatile u32 *)(CRC_BASE_ADDRESS + DR))
#define CRC_IDR          *((volatile u32 *)(CRC_BASE_ADDRESS + IDR))
#define CRC_CR           *((volatile u32 *)(CRC_BASE_ADDRESS + CR))
/******************************************************************************
* Configuration Constants
*******************************************************************************/
// Register bits definition.
// CR bits register definition.
#define RESET                    0
#define WORD_SIZE_IN_BYTE        4
/******************************************************************************
* Module Variable Definitions
*******************************************************************************/

/******************************************************************************
* Function Prototypes
*******************************************************************************/

#endif
/*** End of File **************************************************************/
