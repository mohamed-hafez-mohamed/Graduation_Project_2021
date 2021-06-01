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

#include "STD_TYPES.h"
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

void MFPEC_u8ProgramHalfWordFlash(u32 Copy_u32Address, u16 Copy_u16Data)
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
   *((volatile u16*)(Copy_u32Address)) = Copy_u16Data;
   // Wait for the BSY bit to be reset.
   while(GET_BIT(FPEC->SR, BSY) == SET);
   // EOP
	 SET_BIT(FPEC->SR, EOP);
   CLR_BIT(FPEC->CR, PG);
	 SET_BIT(FPEC->CR, LOCK);
}

u8 MFPEC_u8ProgramOneWordFlash(u32 Copy_u32Address, u32 Copy_u32Data)
{
	 u32  Local_u32StoredData = 0;
	 u32 Local_u32Address = Copy_u32Address;
	 u16 Local_u16LeastHalfWord = (u16)(FPEC_CATCH_LEAST_HALF_WORD)  & (Copy_u32Data);
	 u16 Local_u16MostHalfWord  = (u16)(((FPEC_CATCH_MOST_HALF_WORD) & (Copy_u32Data)) >> TWO_BYTES_IN_BITS);
	 // Check that no main Flash memory operation is ongoing.
	 MFPEC_u8ProgramHalfWordFlash(Copy_u32Address, Local_u16LeastHalfWord);
	 MFPEC_u8ProgramHalfWordFlash(Copy_u32Address + TWO_BYTE, Local_u16MostHalfWord);
	 Local_u32StoredData = *((volatile u16*)(Local_u32Address));
}


void MFPEC_u8ProgramFlashBuffer(u32 Copy_u32Address, u8* Copy_u16Code, u16 Copy_u16Length)
{
	u16 Local_Word = 0 ;
	u16 Local_Counter = 0;
	
	/* Write to flash */
	for (Local_Counter = 0 ; Local_Counter < Copy_u16Length  ;  Local_Counter+= 2 )
	{
		Local_Word = Copy_u16Code[Local_Counter] | (Copy_u16Code[Local_Counter+1] << 8) ;
		MFPEC_u8ProgramHalfWordFlash (Copy_u32Address , Local_Word);
		Copy_u32Address += 2 ;
	}

}

void MFPEC_u8ProgramFlash(u32 Copy_u32Address, u16 * Copy_u16Code, u8 Copy_u8Length)
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
   for(u8 Local_u8Index = 0;Local_u8Index < Copy_u8Length;Local_u8Index++)
   {
     // Set the PG bit in the FLASH_CR register to write on the flash.
     SET_BIT(FPEC->CR, PG);
     // Half word write operation.
     *((volatile u16*)(Copy_u32Address)) = Copy_u16Code[Local_u8Index];
     Copy_u32Address += TWO_BYTE;
     // Wait for the BSY bit to be reset.
     while(GET_BIT(FPEC->SR, BSY) == SET);
     // EOP
	   SET_BIT(FPEC->SR, EOP);
     CLR_BIT(FPEC->CR, PG);
   }
	 SET_BIT(FPEC->CR, LOCK);
}

void MFPEC_voidErasePage(u16 Copy_u16PageNumber)
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
   FPEC->AR = FLASH_START_ADDRESS + (u32)(Copy_u16PageNumber * PAGE_SIZE);
   // Set the STRT bit in the FLASH_CR register to start erase operation.
   SET_BIT(FPEC->CR, STRT);
   /*Wait for the BSY bit to be reset*/
   while(GET_BIT(FPEC->SR, BSY) == SET);
   // EOP
   SET_BIT(FPEC->SR, EOP);
   CLR_BIT(FPEC->CR, PER);
	 SET_BIT(FPEC->CR, LOCK);
}

void MFPEC_voidEraseAppArea(u16 Copy_u16FirstPageNumber, u16 Copy_u16LastPageNumber)
{
   for(u16 Local_u8Page = Copy_u16FirstPageNumber;Local_u8Page <= Copy_u16LastPageNumber;Local_u8Page++)
   {
      MFPEC_voidErasePage(Local_u8Page);
   }
}

u32 MFPEC_voidReadWord(u32 Copy_DataAddress)
{
	u32 Local_u32Data = 0;
	Local_u32Data = *((volatile u32*)(Copy_DataAddress));
	return Local_u32Data;
}

/*************** END OF FUNCTIONS ***************************************************************************/
