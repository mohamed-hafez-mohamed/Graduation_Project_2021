/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v01                                */
 /* date        : 9/10/2020                          */
/*****************************************************/
/* Library includes */
#include "BIT_MATH.h"
#include "Std_Types.h"

/* Module includes */
#include "Fpec_Interface.h"
#include "Fpec_Cfg.h"
#include "Fpec_Private.h"

Std_ReturnType FPEC_u8WriteHalfWord( uint32 copy_u32Address, uint16 copy_u16Data)
{
	Std_ReturnType local_u8Error ; 
	/* Check on the lock bit */
	if (GET_BIT ((FPEC -> FLASH_CR ), LOCK )){
		/* if FPEC locked perform a lock sequence */
		FPEC -> FLASH_KEYR = FPEC_KEY1 ;
		FPEC -> FLASH_KEYR = FPEC_KEY2 ;
	}
	
	/* Enable program */
	SET_BIT ((FPEC -> FLASH_CR ), PG );
	
	/* Write byte at the desired place */
	 (*(uint16 *)copy_u32Address) = copy_u16Data ;
	
	/* Wait till the wirte is done */
	while (GET_BIT ((FPEC -> FLASH_SR ), BSY ));
	
	/* Disable PG */
	CLR_BIT ((FPEC -> FLASH_CR ), PG );

	/* Check on Data */
	if ((*(uint16 *)copy_u32Address) == copy_u16Data){
		local_u8Error = WRITE_DONE ;
	}
	else {
		local_u8Error = WRITE_ERROR ;
	}
	
	return local_u8Error ;
}

void FPEC_voidErasePage( uint32 copy_u32Address )
{ 
	/* Check on the lock bit */
	if (GET_BIT ((FPEC -> FLASH_CR ), LOCK )){
		/* if FPEC locked perform a lock sequence */
		FPEC -> FLASH_KEYR = FPEC_KEY1 ;
		FPEC -> FLASH_KEYR = FPEC_KEY2 ;
	}
	
	/* Enable erase for page */
	SET_BIT ((FPEC -> FLASH_CR ), PER );
	
	/* Set Address for page */
	FPEC -> FLASH_AR = copy_u32Address ;
	
	/* Start erase */
	SET_BIT ((FPEC -> FLASH_CR ), STRT );

	/* Wait till the erase is done */
	while (GET_BIT ((FPEC -> FLASH_SR ), BSY ));

	/* Disable erase for page */
	CLR_BIT ((FPEC -> FLASH_CR ), PER );
	
}

void FPEC_voidMassErase(void)
{
	/* Check on the lock bit */
	if (GET_BIT ((FPEC -> FLASH_CR ), LOCK )){
		/* if FPEC locked perform a lock sequence */
		FPEC -> FLASH_KEYR = FPEC_KEY1 ;
		FPEC -> FLASH_KEYR = FPEC_KEY2 ;
	}
	
	/* Enable erase for page */
	SET_BIT ((FPEC -> FLASH_CR ), MER );
	
	/* Start erase */
	SET_BIT ((FPEC -> FLASH_CR ), STRT );

	/* Wait till the erase is done */
	while (GET_BIT ((FPEC -> FLASH_SR ), BSY ));

}

