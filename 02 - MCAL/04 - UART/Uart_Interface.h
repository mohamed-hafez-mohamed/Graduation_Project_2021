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

/* 
  * UART_voidInit - > Intialize UART module  
*/
void Uart_voidInit(void);

/* 
  * UART_voidSendDataSynch - > send a character or string to uart  
  * I/P : UART_Ch_t   /  pointer to (uint8)
*/
void Uart_voidTxSynch(UART_Ch_t copy_ch , uint8 *copy_u8data);

/* 
  * UART_voidRecDataSynch - > receive a character or string to uart  
  * I/P : UART_Ch_t   /  pointer to (uint8)  /   (uint8) length of data 
*/
void Uart_voidRxSynch (UART_Ch_t copy_ch , uint8 *copy_u8data , uint8 copy_u8DataLength);

void Uart_voidRxAsynch(UART_Ch_t copy_ch , Uart_pFunc_t func );

void Uart_voidRxDisableInterrupt (UART_Ch_t copy_ch);


#endif
