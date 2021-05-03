/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v01                                */
 /* date        : 20/9/2020                          */
/*****************************************************/

/***********************************************************
	* Pre conitions : 
		1 - Enable RCC for the used UART module 
		2 - Configure RX and TX pins as GPIO pins
			RX -> input floating 
			TX -> Alternative output
		3 - populate configuration table in config.c 
************************************************************/
		
#ifndef UART_INTERFACE_H
#define UART_INTERFACE_H

/******************* Public data types *******************/

/**** Timer channels ****/
typedef enum {
	UART1,
	UART2,
	UART3,
	MAX_TIMERS
}UART_Ch_t;

typedef void (*Uart_pFunc_t)(uint8 );



/********************* Prototypes **********************/

/*************************************************************************
 * Name : Uart_voidInit
 * Parameter in : -
 * Parameter out : -
 * Parameter in/out : -
 * Reentrancy: Non reentrant
 * Sync
 * Description: Initialize the Uart modules according to the Uart_Lcg.c file
 ***************************************************************************/
void Uart_voidInit(void);

/*************************************************************************
 * Name : Uart_voidTxSynch
 * Parameter in : Channel of the UART (UART_Ch_t)
 * Parameter out : -
 * Parameter in/out : Pointer to uint8 (the data)
 * Reentrancy: Non reentrant
 * Sync
 * Description: Send array of data 
 ***************************************************************************/
void Uart_voidTxSynch(UART_Ch_t copy_ch , uint8 *copy_u8data);

/*************************************************************************
 * Name : Uart_voidTxByteSynch
 * Parameter in : Channel of the UART (UART_Ch_t)
 *                Byte of Data (uint8) 
 * Parameter out : -
 * Parameter in/out : -
 * Reentrancy: Non reentrant
 * Sync
 * Description: Send Byte of Data 
 ***************************************************************************/
void Uart_voidTxByteSynch(UART_Ch_t copy_ch , uint8 copy_u8data);

/*************************************************************************
 * Name : Uart_voidRxSynch
 * Parameter in : Channel of the UART (UART_Ch_t)
 *                Length of the data to be received 
 * Parameter out : -
 * Parameter in/out : Pointer to uint8 (the data)
 * Reentrancy: Non reentrant
 * Sync
 * Description: Receive Number of bytes 
 ***************************************************************************/
void Uart_voidRxSynch (UART_Ch_t copy_ch , uint8 *copy_u8data , uint16 copy_u8DataLength);

/*************************************************************************
 * Name : Uart_voidRxAsynch
 * Parameter in : Channel of the UART (UART_Ch_t
 * Parameter out : -
 * Parameter in/out : Callback function for the uart receive interrupt (Uart_pFunc_t)
 * Reentrancy: Non reentrant
 * Async
 * Description: Receive Byte Asynchronous 
 ***************************************************************************/
void Uart_voidRxAsynch(UART_Ch_t copy_ch , Uart_pFunc_t func );

/*************************************************************************
 * Name : Uart_voidRxDisableInterrupt
 * Parameter in : -
 * Parameter out : -
 * Parameter in/out : -
 * Reentrancy: Non reentrant
 * Sync
 * Description: Disable the receive interrupt
 ***************************************************************************/
void Uart_voidRxDisableInterrupt (UART_Ch_t copy_ch);


#endif
