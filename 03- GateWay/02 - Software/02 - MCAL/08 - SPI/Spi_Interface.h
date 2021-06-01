/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v01                                */
 /* date        : 16/9/2020                          */
/*****************************************************/
/*
	Pre conditions : 
		1 - Enable RCC for used GPIO pins 
		2 - Enable RCC for use SPI
		3 - Configure pins of SPI as output and input
		4 - Enable NVIC in case of using interrupts	
*/


#ifndef SPI_INTERFACE_H
#define SPI_INTERFACE_H

#include "Spi_Lcfg.h"

/******************* Public data types *******************/

/**** Timer channels ****/
typedef enum {
	SPI1,
	SPI2,
	MAX_SPIS
}SPI_Ch_t;

/********************* Prototypes **********************/

/*************************************************************************
 * Name : SPI_uint8Configure
 * Parameter in : Channel  (SPI_Ch_t)
 * Parameter out : -
 * Parameter in/out : Pointer to a struct of configration
 * Reentrancy: Non reentrant
 * Sync
 * Description: Initialize SPI
 ***************************************************************************/
void SPI_uint8ConfigureCh(SPI_Ch_t copy_channel , SpiCfgType *copy_config);


/*************************************************************************
 * Name : SPI_uint16SendRecSynch
 * Parameter in : Channel  (SPI_Ch_t) , data to be sent 
 * Parameter out : -
 * Parameter in/out : 
 * Reentrancy: Non reentrant
 * Sync
 * Description: Initialize SPI
 ***************************************************************************/
uint16 SPI_uint16SendRecSynch (SPI_Ch_t copy_channel , uint16 copy_uint16SendData);

/*************************************************************************
 * Name : SPI_voidSendRecAsynch
 * Parameter in : Channel  (SPI_Ch_t) , data to be sent , pointer to call back function  
 * Parameter out : -
 * Parameter in/out : 
 * Reentrancy: Non reentrant
 * Async
 * Description: Initialize SPI
 ***************************************************************************/
void SPI_voidSendRecAsynch (SPI_Ch_t copy_channel , uint16 copy_uint16SendData , void (*func)(uint16));

#endif
