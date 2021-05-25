/****************************************************************************
* Title                 :   UDS   
* Filename              :   UDS_interface.h
* Author                :   Mohamed Hafez
* Origin Date           :   25/12/2020
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
*  25/12/20   1.0.0   Mohamed Hafez   Interface Created.
*
*****************************************************************************/
/** @file  UDS_interface.h
 *  @brief This module TODO: WHAT DO I DO?
 * 
 *  This is the header file for the definition TODO: MORE ABOUT ME!
 */
//TODO: UPDATE MACRO BELOW
#ifndef NVM_INTERFACE_H_
#define NVM_INTERFACE_H_

/******************************************************************************
* Includes
*******************************************************************************/

/******************************************************************************
* Preprocessor Constants
*******************************************************************************/
#define UDS_CONTROL_SEESION                   0X10
#define UDS_PROGRAM_CONTROL_SESSION           0x03
#define HEADER_PAGE_NUMBER                    63
#define ALIGNMENT_IMAGE_1_ELEMENTS            1
#define ALIGNMENT_IMAGE_2_ELEMENTS            6
#define NUMBER_OF_HEADER_WORD                 11
#define NUMBER_OF_HEADER_WORD_PER_IMAGE       5
#define WORD_SIZE_IN_BYTE                     4
#define BL_BRANCHING_FLAG_ADDRESS_HEX         0x0800FC00
#define BL_BRANCHING_FLAG_ADDRESS_DECIMAL     134282240
#define ADRESS_OF_IMAGE_1_HEADER_DECIMAL      134282256
#define ADRESS_OF_IMAGE_2_HEADER_DECIMAL      134282288
#define SET_BRANCHING_FLAG                    0x00000000

#define NUMBER_OF_FLAGS                       20
#define HEADER_PAGE_NUMBER                    63
#define WORD_SIZE_IN_BYTE                     4
#define START_OF_AREA                         0x0800FC00
#define END_OF_AREA                           0x0800FC50
#define ERASED_VALUE                          0xffffffff
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

void UDS_voidDetectNewCode(u8 Copy_u8ReceivedValue);

void FEE_voidEraseRestoreHeaderPage(u32 Copy_u32Address, u32 Copy_u32NewData);

#endif /*File_H_*/

/*** End of File **************************************************************/
