/*******************************************************************************
* Title                 :   CRC 
* Filename              :   CRC_program.c
* Author                :   Mohamed Hafez
* Origin Date           :   10/08/2020
* Version               :   1.0.0
* Compiler              :   TODO: COMPILER GOES HERE
* Target                :   TODO: MCU GOES HERE
* Notes                 :   None 
*
*****************************************************************************/
/*************** SOURCE REVISION LOG *****************************************
*
*    Date    Version   Author          Description 
*  10/08/20   1.0.0   Mohamed Hafez   Initial Release.
*
*******************************************************************************/
/** @file CRC_program.c
 *  @brief This is the source file for TODO: WHAT DO I DO? 
 */
/******************************************************************************
* Includes
*******************************************************************************/	

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <stdlib.h>
#include "CRC_interface.h"
#include "CRC_config.h"
#include "CRC_private.h"

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

void MCRC_u32CalculateCrcHw(u32 * Copy_u32WordArray, u8 Copy_u8ByteArraySize, u32 * Copy_u32PtrCrc)
{
   *Copy_u32PtrCrc = 0;
   if(Copy_u32WordArray != NULL)
   {
	   CRC_CR = CRC_RESRT;
      for(u32 Local_u32WordCounter = 0;Local_u32WordCounter < Copy_u8ByteArraySize;++Local_u32WordCounter)
      {
         CRC_DR = (u32)(Copy_u32WordArray[Local_u32WordCounter]);
      }
      *Copy_u32PtrCrc = CRC_DR;
   }
   else
   {
      /*!<TODO: Null pointer detected */
   }
}

void MCRC_voidCalculateCrcDirect(u32 Copy_u32BaseAddress, u32 Copy_u32WordNumber, u32 * Copy_u32PtrCrc)
{
   *Copy_u32PtrCrc = 0;
	 u32 Local_u32Crc = 0;
	 u16 Local_u16HalfWordH = 0 ;
	u16 Local_u16HalfWordL = 0 ;
   u32 * Local_u32PtrToInteger = (u32 *)(Copy_u32BaseAddress);
   if(Local_u32PtrToInteger != NULL)
   {
      CRC_CR = CRC_RESRT;
      for(u32 Local_u32WordCounter = 0;Local_u32WordCounter < Copy_u32WordNumber;Local_u32WordCounter++)
      {
				Local_u16HalfWordL = (*((volatile u8*)(Copy_u32BaseAddress))<<8) | (*((volatile u8*)(Copy_u32BaseAddress+1)));
				Local_u16HalfWordH = (*((volatile u8*)(Copy_u32BaseAddress+2))<<8) | (*((volatile u8*)(Copy_u32BaseAddress+3)));
				CRC_DR = (Local_u16HalfWordL<<16)|Local_u16HalfWordH;
				Local_u32Crc = CRC_DR;
				Copy_u32BaseAddress+=WORD_SIZE_IN_BYTE;
      }
	  *Copy_u32PtrCrc = CRC_DR;
   }
   else
   {
	  /*!<TODO: Null pointer detected */
   }
}


/*************** END OF FUNCTIONS ***************************************************************************/
