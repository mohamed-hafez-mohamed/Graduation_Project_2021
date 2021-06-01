/****************************************************************************
* Title                 :   FPEC   
* Filename              :   FPEC_interface.h
* Author                :   Mohamed Hafez
* Origin Date           :   13/10/2020
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
*  13/10/20   1.0.0   Mohamed Hafez   Interface Created.
*
*****************************************************************************/
/** @file  FPEC_interface.h
 *  @brief This module TODO: WHAT DO I DO?
 * 
 *  This is the header file for the definition TODO: MORE ABOUT ME!
 */
//TODO: UPDATE MACRO BELOW
#ifndef FPEC_INTERFACE_H_
#define FPEC_INTERFACE_H_

/******************************************************************************
* Includes
*******************************************************************************/

/******************************************************************************
* Preprocessor Constants
*******************************************************************************/

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
/******************************************************************************
* Function : MFPEC_uint8ProgramOneHalfWordFlash()
*//** 
* \b Description:
*
* This function is used to write code on the flash using flash driver peripheral. 
*
* PRE-CONDITION:  Internal clock cycle must be enabled.
* PRE-CONDITION:  App area must be erased before writing op.
* 
* POST-CONDITION: None
*
* @param [in]     The address of the code line.
* @param [in]     Bytes of the code line.
* 
* @return 		   The state of writing done ornot.
*
* \b Example Example:
* @code
* 	MFPEC_uint8ProgramOneHalfWordFlash(0x08001000, Code);
*
* @endcode
*
* @see MFPEC_uint8ProgramOneHalfWordFlash
*
*******************************************************************************/
/******************************************************************************
* Function : MFPEC_uint8ProgramFlash()
*//** 
* \b Description:
*
* This function is used to write code on the flash using flash driver peripheral. 
*
* PRE-CONDITION:  Internal clock cycle must be enabled.
* PRE-CONDITION:  App area must be erased before writing op.
* 
* POST-CONDITION: None
*
* @param [in]     The address of the beginning of the app area.
* @param [in]     An array that contain bytes that the code consists of.
* @param [in]     The number of half words that the array consists of.
* 
* @return 		   void.
*
* \b Example Example:
* @code
* 	MFPEC_uint8ProgramFlash(0x08001000, &Coderray, 16);
*
* @endcode
*
* @see MFPEC_uint8ProgramFlash
*
*******************************************************************************/
uint8   MFPEC_uint8ProgramOneWordFlash(uint32 Copy_uint32Address, uint32 Copy_uint32Data);

void MFPEC_uint8ProgramFlash(uint32 Copy_uint32Address, uint16 * Copy_uint16Code, uint8 Copy_uint8Length);
/******************************************************************************
* Function : MFPEC_voidErasePage()
*//** 
* \b Description:
*
* This function is used to erase page of the flash. 
*
* PRE-CONDITION:  Internal clock cycle must be enabled.
* 
* POST-CONDITION: None
*
* @param [in]     The page number.
* 
* @return 		   void.
*
* \b Example Example:
* @code
* 	MFPEC_voidErasePage(16);
*
* @endcode
*
* @see MFPEC_voidErasePage
*
*******************************************************************************/
void MFPEC_voidErasePage(uint16 Copy_uint16PageNumber);
/******************************************************************************
* Function : MFPEC_voidEraseAppArea()
*//** 
* \b Description:
*
* This function is used to erase the app area. 
*
* PRE-CONDITION:  Internal clock cycle must be enabled.
* PRE-CONDITION:  The first page number in app area must be defined in FPEC_config.
* PRE-CONDITION:  The last  page number in app area must be defined in FPEC_config.
* 
* POST-CONDITION: None
*
* @param [in]     void.
* 
* @return 		   void.
*
* \b Example Example:
* @code
* 	MFPEC_voidEraseAppArea();
*
* @endcode
*
* @see MFPEC_voidEraseAppArea
*
*******************************************************************************/
void MFPEC_voidEraseAppArea(uint16 Copy_uint16FirstPageNumber, uint16 Copy_uint16LastPageNumber);

uint32 MFPEC_voidReadWord(uint32 Copy_DataAddress);


void MFPEC_uint8ProgramHalfWordFlash(uint32 Copy_uint32Address, uint16 Copy_uint16Data);


#endif /*File_H_*/

/*** End of File **************************************************************/
