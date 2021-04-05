/*******************************************************************************
* Title                 :   UDS 
* Filename              :   UDS_program.c
* Author                :   Mohamed Hafez
* Origin Date           :   25/12/2020
* Version               :   1.0.0
* Compiler              :   TODO: COMPILER GOES HERE
* Target                :   TODO: MCU GOES HERE
* Notes                 :   None 
*
*****************************************************************************/
/*************** SOURCE REVISION LOG *****************************************
*
*    Date    Version   Author          Description 
*  25/12/20   1.0.0   Mohamed Hafez   Initial Release.
*
*******************************************************************************/
/** @file UDS_program.c
 *  @brief This is the source file for TODO: WHAT DO I DO? 
 */
/******************************************************************************
* Includes
*******************************************************************************/	

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "UDS_interface.h"
#include "FPEC_interface.h"
/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/

/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/

/******************************************************************************
* Module Typedefs
*******************************************************************************/

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/

/******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************
* Function Definitions
*******************************************************************************/
void FEE_voidEraseRestoreHeaderPage(u32 Copy_u32Address, u32 Copy_u32NewData)
{
	u32 Local_u32AddressArray[NUMBER_OF_FLAGS]; 
	u32 Local_u32DataArray[NUMBER_OF_FLAGS]; 
	u16 Local_u16DataIndex        = 0;
	u16 Local_u16DataCounter      = 0;
	u32 Local_u32AddressCounter   = 0;
	for ( Local_u32AddressCounter = START_OF_AREA ;Local_u32AddressCounter < END_OF_AREA;)
	{
		if( (Local_u32AddressCounter != Copy_u32Address) & (*((u32*)(Local_u32AddressCounter)) != ERASED_VALUE))	
		{
			Local_u32AddressArray[Local_u16DataIndex] = Local_u32AddressCounter; 
			Local_u32DataArray[Local_u16DataIndex] = *((u32*)(Local_u32AddressCounter)); 
			Local_u16DataIndex++ ;
		}
		Local_u32AddressCounter = Local_u32AddressCounter + WORD_SIZE_IN_BYTE; 
	}
	
	MFPEC_voidErasePage(HEADER_PAGE_NUMBER); // erase after save
	
	for (Local_u16DataCounter = 0 ; Local_u16DataCounter < Local_u16DataIndex ;Local_u16DataCounter++ )
	{
		MFPEC_u8ProgramOneWordFlash(Local_u32AddressArray[Local_u16DataCounter], Local_u32DataArray[Local_u16DataCounter] );
	}
	MFPEC_u8ProgramOneWordFlash(Copy_u32Address, Copy_u32NewData);
}



/*************** END OF FUNCTIONS ***************************************************************************/
