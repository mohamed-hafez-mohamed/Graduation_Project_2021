/*******************************************************************************
* Title                 :   UART 
* Filename              :   UART_program.c
* Author                :   Mohamed Hafez
* Origin Date           :   19/09/2020
* Version               :   1.0.0
* Compiler              :   TODO: COMPILER GOES HERE
* Target                :   TODO: MCU GOES HERE
* Notes                 :   None 
*
*****************************************************************************/
/*************** SOURCE REVISION LOG *****************************************
*
*    Date    Version   Author          Description 
*  19/09/20   1.0.0   Mohamed Hafez   Initial Release.
*
*******************************************************************************/
/** @file UART_program.c
 *  @brief This is the source file for TODO: WHAT DO I DO? 
 */
/******************************************************************************
* Includes
*******************************************************************************/	

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GPIO_interface.h"
#include "UART_interface.h"
#include "UART_config.h"
#include "UART_private.h"

/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/

/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/
// Polling UART1 Flags
#define UART_WAIT_TO_TRANSMIT   (GET_BIT(UARTChannel[UART1]->SR, TC)   == FLAG_NOT_SET)
#define UART_WAIT_TO_RECEIVE    (GET_BIT(UARTChannel[UART1]->SR, RXNE) == FLAG_NOT_SET)
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

void MUART_voidInit(void)
{
	// Configure uart1.
	// Reset registers to be ready for configuration.
	UARTChannel[UART1]->CR1  = CLR_REGISTER;
   UARTChannel[UART1]->CR2  = CLR_REGISTER;
   UARTChannel[UART1]->SR   = CLR_REGISTER;
   UARTChannel[UART1]->CR1 |= (UART_Enable_TX_RX << RE);
	// Configure clock phase and polarity.
	UARTChannel[UART1]->CR2 |= ((UART_CLOCK_PHASE << CPHA) | (UART_CLOCK_POLARITY << CPOL));
	// Define Baud Rate 
   UARTChannel[UART1]->BRR  = UART_BAUDRATE;
	// Enable Baud Rate.
   UARTChannel[UART1]->CR1 |= (ENABLE_UART << UE);
}

/******************************************************************************
* Function : MUART_voidTransmitSynch()
*//** 
* \b Description:
*
* This function is used to transmit an array by UART peripheral. 
*
* PRE-CONDITION:  MUART_voidInit function must be called to initialize UART peripheral.
*
* POST-CONDITION: None
*
* @param [in]     Array address tha contain data that will be sent.
* 
* @return 		   void.
*
* \b Example Example:
* @code
* 	MUART_voidTransmitSynch(&Local_u8DataArray);
*
* @endcode
*
* @see MUART_voidTransmitSynch
*
*******************************************************************************/
void MUART_voidTransmitSynch(u8 Copy_u8DataArray[])
{
  u8 Local_u8Counter = 0;
	while(Copy_u8DataArray[Local_u8Counter] != '\0')
	{
		// Put data in DR register to be transmitted.
	   UARTChannel[UART1]->DR = Copy_u8DataArray[Local_u8Counter];
		// Wait untill transmition finished.
		while(UART_WAIT_TO_TRANSMIT);
		CLR_BIT(UARTChannel[UART1]->CR1, TC);
		Local_u8Counter++;
	} 
}

void MUART_voidTransmitByteSynch(u8 Copy_u8Data)
{
	  // Put data in DR register to be transmitted.
	  UARTChannel[UART1]->DR = Copy_u8Data;
		// Wait untill transmition finished.
		while(UART_WAIT_TO_TRANSMIT);
	  CLR_BIT(UARTChannel[UART1]->CR1, TC);
}

u8 MUART_u8ReceiveSynch( u8 * Copy_u8Data)
{
	u8 Local_u8State = 1;
	// Chek is there data received.
	if(GET_BIT(UARTChannel[UART1]->SR, RXNE) == FLAG_SET)
	{
		// Get the least significant byte.
		*Copy_u8Data = ((ONE_BYTE) & (UARTChannel[UART1]->DR));
	}
	else
	{
		Local_u8State = FLAG_NOT_SET;
	}
	return Local_u8State;
}

u8 MUART_u8ReceiveByteSynch(void)
{
	u8 Local_u8Data;
	// Wait untill receiving finished.
	while(UART_WAIT_TO_RECEIVE);
	// Getting the first byte of the register to be returned.
	Local_u8Data = ((ONE_BYTE) & (UARTChannel[UART1]->DR));
   return Local_u8Data;
}
/*************** END OF FUNCTIONS ***************************************************************************/
