/*******************************************************************************
* Title                 :   FPEC 
* Filename              :   FPEC_program.c
* Author                :   Mohamed Hafez
* Origin Date           :   13/10/2020
* Version               :   1.0.0
* Compiler              :   TODO: COMPILER GOES HERE
* Target                :   TODO: MCU GOES HERE
* Notes                 :   None 
*
*****************************************************************************/
/*************** SOURCE REVISION LOG *****************************************
*
*    Date    Version   Author          Description 
*  13/10/20   1.0.0   Mohamed Hafez   Initial Release.
*
*******************************************************************************/
/** @file FPEC_program.c
 *  @brief This is the source file for TODO: WHAT DO I DO? 
 */
/******************************************************************************
* Includes
*******************************************************************************/	

#include "Std_Types.h"
#include "BIT_MATH.h"
#include "FPEC_interface.h"
#include "FPEC_config.h"
#include "FPEC_private.h"

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


void MFPEC_uint8ProgramHalfWordFlash(uint32 Copy_uint32Address, uint16 Copy_uint16Data)
{
	// Check that no main Flash memory operation is ongoing.
   while(GET_BIT(FPEC->SR, BSY) == SET);
   // Check if the flash locked or not.
   if(GET_BIT(FPEC->CR, LOCK) == SET)
   {
      // Perform Unlock Sequence To Unlock FPEC Peripheral.
      FPEC->KEYR = FPEC_KEY_1;
      FPEC->KEYR = FPEC_KEY_2;
   }
   // Set the PG bit in the FLASH_CR register.
   SET_BIT(FPEC->CR, PG);
   // Perform the data write (half-word) at the desired address.
   *((volatile uint16*)(Copy_uint32Address)) = Copy_uint16Data;
   // Wait for the BSY bit to be reset.
   while(GET_BIT(FPEC->SR, BSY) == SET);
   // EOP
	 SET_BIT(FPEC->SR, EOP);
   CLR_BIT(FPEC->CR, PG);
	 SET_BIT(FPEC->CR, LOCK);
}

uint8 MFPEC_uint8ProgramOneWordFlash(uint32 Copy_uint32Address, uint32 Copy_uint32Data)
{
	 uint32  Local_uint32StoredData = 0;
	 uint32 Local_uint32Address = Copy_uint32Address;
	 uint16 Local_uint16LeastHalfWord = (uint16)(FPEC_CATCH_LEAST_HALF_WORD)  & (Copy_uint32Data);
	 uint16 Local_uint16MostHalfWord  = (uint16)(((FPEC_CATCH_MOST_HALF_WORD) & (Copy_uint32Data)) >> TWO_BYTES_IN_BITS);
	 // Check that no main Flash memory operation is ongoing.
	 MFPEC_uint8ProgramHalfWordFlash(Copy_uint32Address, Local_uint16LeastHalfWord);
	 MFPEC_uint8ProgramHalfWordFlash(Copy_uint32Address + TWO_BYTE, Local_uint16MostHalfWord);
	 Local_uint32StoredData = *((volatile uint16*)(Local_uint32Address));
}

void MFPEC_uint8ProgramFlash(uint32 Copy_uint32Address, uint16 * Copy_uint16Code, uint8 Copy_uint8Length)
{
   // Check that no main Flash memory operation is ongoing.
   while(GET_BIT(FPEC->SR, BSY) == SET);
   // Check if the flash locked or not.
   if(GET_BIT(FPEC->CR, LOCK) == SET)
   {
     // Perform Unlock Sequence To Unlock FPEC Peripheral.
     FPEC->KEYR = FPEC_KEY_1;
     FPEC->KEYR = FPEC_KEY_2;
   }
   for(uint8 Local_uint8Index = 0;Local_uint8Index < Copy_uint8Length;Local_uint8Index++)
   {
     // Set the PG bit in the FLASH_CR register to write on the flash.
     SET_BIT(FPEC->CR, PG);
     // Half word write operation.
     *((volatile uint16*)(Copy_uint32Address)) = Copy_uint16Code[Local_uint8Index];
     Copy_uint32Address += TWO_BYTE;
     // Wait for the BSY bit to be reset.
     while(GET_BIT(FPEC->SR, BSY) == SET);
     // EOP
	   SET_BIT(FPEC->SR, EOP);
     CLR_BIT(FPEC->CR, PG);
   }
	 SET_BIT(FPEC->CR, LOCK);
}

void MFPEC_voidErasePage(uint16 Copy_uint16PageNumber)
{
	 SET_BIT(FPEC->CR,LOCK);
   // Check that no main Flash memory operation is ongoing.
   while(GET_BIT(FPEC->SR, BSY) == SET);
   // Check if the flash locked or not.
   if(GET_BIT(FPEC->CR, LOCK) == SET)
   {
      // Perform Unlock Sequence To Unlock FPEC Peripheral.
      FPEC->KEYR = FPEC_KEY_1;
      FPEC->KEYR = FPEC_KEY_2;
   }
   // Set the PER bit in the FLASH_CR register to erase page.
   SET_BIT(FPEC->CR, PER);
   // Program the FLASH_AR register to select a page to erase.
   FPEC->AR = FLASH_START_ADDRESS + (uint32)(Copy_uint16PageNumber * PAGE_SIZE);
   // Set the STRT bit in the FLASH_CR register to start erase operation.
   SET_BIT(FPEC->CR, STRT);
   /*Wait for the BSY bit to be reset*/
   while(GET_BIT(FPEC->SR, BSY) == SET);
   // EOP
   SET_BIT(FPEC->SR, EOP);
   CLR_BIT(FPEC->CR, PER);
	 SET_BIT(FPEC->CR, LOCK);
}

void MFPEC_voidEraseAppArea(uint16 Copy_uint16FirstPageNumber, uint16 Copy_uint16LastPageNumber)
{
   for(uint8 Local_uint8Page = Copy_uint16FirstPageNumber;Local_uint8Page <= Copy_uint16LastPageNumber;Local_uint8Page++)
   {
      MFPEC_voidErasePage(Local_uint8Page);
   }
}

uint32 MFPEC_voidReadWord(uint32 Copy_DataAddress)
{
	uint32 Local_uint32Data = 0;
	Local_uint32Data = *((volatile uint32*)(Copy_DataAddress));
	return Local_uint32Data;
}

/*************** END OF FUNCTIONS ***************************************************************************/
