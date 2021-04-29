/*****************************************************/
 /* Author      : Mosad                              */
 /* Version     : v01                                */
 /* date        : 29/4/2020                          */
/*****************************************************/
/* Library includes */
#include "BIT_MATH.h"
#include "Std_Types.h"

/* Module includes */
#include "Nvm_Interface.h"
#include "Nvm_Cfg.h"
#include "Nvm_Private.h"

/* Other Modules */
#include "Fpec_Interface.h"
#include "RCC_interface.h"

uint32 Global_WriteAddress ; 
uint32 Global_ReadAddress ;

void Nvm_voidInitVariables (void)
{
	Global_WriteAddress = NVM_STORE_AREA_START_ADDRESS ; 
	Global_ReadAddress  = NVM_STORE_AREA_START_ADDRESS ;
}

void Nvm_voidInit( void)
{
	/* Enable clock for the FPEC module */
	RCC_VoidEnableClock (RCC_AHB_EN , RCC_FLITF);
	
	/* Init Variables */
	Nvm_voidInitVariables();
}

Std_ReturnType Nvm_WriteBlock(const uint8 *Cpy_DataPtr , uint16 Cpy_DataLength )
{ 
	/* Local Variables */
	Std_ReturnType Local_ReturnError = E_OK;
	uint8 Local_PageNumber = INITIAL_ZERO ;
	uint16 Local_Word = INITIAL_ZERO ;
	uint16 Local_Counter = INITIAL_ZERO;
	
	/* Check on Null pointer */
	if (NULL_PTR == Cpy_DataPtr)
	{
		Local_ReturnError = E_NOT_OK ;
	}
	else 
	{
		/* Get page number */
		Local_PageNumber = (uint8) (( Global_WriteAddress - NVM_FLASH_START_ADDRESS ) /FPEC_FLASH_PAGE_SIZE );
		
		/* Erase the page first */ 
		FPEC_voidErasePage (Local_PageNumber) ;
		
		/* Write to flash */
		for (Local_Counter = INITIAL_ZERO ; Local_Counter < Cpy_DataLength  ;  Local_Counter+= READ_ADDRESS_STEP )
		{
			Local_Word = Cpy_DataPtr[Local_Counter] | (Cpy_DataPtr[Local_Counter+1] << SHIFT_RIGHT_8) ;
			FPEC_WriteHalfWord (Global_WriteAddress , Local_Word);
			Global_WriteAddress += READ_ADDRESS_STEP ;
		}
	}
	
	return Local_ReturnError ;
}

Std_ReturnType Nvm_ReadBlock(uint8 *Cpy_DataPtr , uint16 Cpy_DataLength)
{
	/* Local Variables */
	Std_ReturnType Local_ReturnError = E_OK;
	uint16 Local_Counter = INITIAL_ZERO;
	
	/* Check on Null pointer */
	if (NULL_PTR == Cpy_DataPtr)
	{
		Local_ReturnError = E_NOT_OK ;
	}
	else 
	{
		for (Local_Counter = INITIAL_ZERO ; Local_Counter < Cpy_DataLength ; Local_Counter++)
		{
			Cpy_DataPtr[Local_Counter] = (* (volatile uint8 *) Global_ReadAddress ) ;
			Global_ReadAddress++;
		}
	}
	
	return Local_ReturnError ;

}


