/****************************************************************************
* Title                 :   UART   
* Filename              :   UART_interface.h
* Author                :   Mohamed Hafez
* Origin Date           :   19/09/2020
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
*  19/09/20   1.0.0   Mohamed Hafez   Interface Created.
*
*****************************************************************************/
/** @file  UART_interface.h
 *  @brief This module TODO: WHAT DO I DO?
 * 
 *  This is the header file for the definition TODO: MORE ABOUT ME!
 */
//TODO: UPDATE MACRO BELOW
#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

/******************************************************************************
* Includes
*******************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
/******************************************************************************
* Preprocessor Constants
*******************************************************************************/
#define UART1                      0
// UART Pins Without Mapping.
#define UART_1_TX                  PINA9
#define UART_1_RX                  PINA10
#define UART_2_TX                  PINA2
#define UART_2_RX                  PINA3
#define UART_3_TX                  PINB10
#define UART_3_RX                  PINB11
// Flag states
#define FLAG_NOT_SET               0
#define FLAG_SET                   1


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
* Function : MUART_voidInit()
*//** 
* \b Description:
*
* This function is used to initialize the UART based on the configurations in UART_config. 
*
* PRE-CONDITION:  Configurations must be defined in UART_config.
*
* POST-CONDITION: None
*
* @param [in]     void
* 
* @return 		   void.
*
* \b Example Example:
* @code
* 	MUART_voidInit();
*
* @endcode
*
* @see MUART_voidInit
*
*******************************************************************************/
void MUART_voidInit(void);
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
void MUART_voidTransmitSynch(u8 Copy_u8DataArray[]);
void MUART_voidTransmitByteSynch(u8 Copy_u8Data);
/******************************************************************************
* Function : MUART_u8ReceiveSynch()
*//** 
* \b Description:
*
* This function is used to receive data from UART peripheral. 
*
* PRE-CONDITION:  MUART_voidInit function must be called to initialize UART peripheral.
*
* POST-CONDITION: None
*
* @param [in_out] The address of variable that store the received value.
* @return 		   The status of uart received value or not.
*
* \b Example Example:
* @code
* Local_u8RecordStatus = MUART_u8ReceiveSynch(&ReceivedValue);
*
* @endcode
*
* @see MUART_u8ReceiveSynch
*
*******************************************************************************/
u8   MUART_u8ReceiveSynch(u8 * Copy_u8Data);
u8   MUART_u8ReceiveByteSynch(void);

#endif /*File_H_*/

/*** End of File **************************************************************/
