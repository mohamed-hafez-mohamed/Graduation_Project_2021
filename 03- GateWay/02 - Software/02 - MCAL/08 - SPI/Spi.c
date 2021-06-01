/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v01                                */
 /* date        : 14/9/2020                          */
/*****************************************************/
/* Library includes */
#include "BIT_MATH.h"
#include "Std_Types.h"

/* Module includes */
#include "Spi_Interface.h"
#include "Spi_Cfg.h"
#include "Spi_Private.h"

/* Global variables */
void (*callBackFunc[SPI_MAX_CH])(uint16);

/****** Public fucntions *******/

void SPI_uint8ConfigureCh(SPI_Ch_t copy_channel , SpiCfgType *copy_config)
{
	/* Intialize the register */
	(*(SPI[copy_channel] + CR1 ))  = 0;
	
	/* Configure polarity in in idle */
	switch (copy_config -> uint8CPOL){
		case 1  :
			SET_BIT  ((*(SPI[copy_channel] + CR1 )) , CPOL);
			break ;
		case 0  :
			CLR_BIT((*(SPI[copy_channel] + CR1 )) , CPOL);
			break;
		default :
			/* Error */
		break ;
	}

	/* Configure phase */
	switch (copy_config -> uint8CPHA){
		case 1  :
			SET_BIT  ((*(SPI[copy_channel] + CR1 )) , CPHA);
			break ;
		case 0  :
			CLR_BIT((*(SPI[copy_channel] + CR1 )) , CPHA);
			break;
		default :
			/* Error */
		break ;
	}

	/* Configure Frame format MSB or LSB first */
	switch (copy_config -> uint8FrameFormat){
		case 1  :
			SET_BIT  ((*(SPI[copy_channel] + CR1 )) , LSBFIRST);
			break ;
		case 0  :
			CLR_BIT((*(SPI[copy_channel] + CR1 )) , LSBFIRST);
			break;
		default :
			/* Error */
		break ;
	}

	/* Configure Frame size 8 or 16 bit */
	switch (copy_config -> uint8FrameSize){
		case 1  :
			SET_BIT  ((*(SPI[copy_channel] + CR1 )) , DFF);
			break ;
		case 0  :
			CLR_BIT((*(SPI[copy_channel] + CR1 )) , DFF);
			break;
		default :
			/* Error */
		break ;
	}

	/* Enable or disable S.W slave mangement */
	switch (copy_config -> uint8SSM){
		case 1  :
			SET_BIT  ((*(SPI[copy_channel] + CR1 )) , SSM);
			SET_BIT  ((*(SPI[copy_channel] + CR1 ))  , SS1);
			break ;
		case 0  :
			CLR_BIT((*(SPI[copy_channel] + CR1 )) , SSM);
			break;
		default :
			/* Error */
		break ;
	}

	/* Full duplex or Receive only  */
	switch (copy_config -> uint8TransmissonMode){
		case 1  :
			SET_BIT  ((*(SPI[copy_channel] + CR1 )) , RXONLY);
			break ;
		case 0  :
			CLR_BIT((*(SPI[copy_channel] + CR1 )) , RXONLY);
			break;
		default :
			/* Error */
		break ;
	}

	/* Prescaller */
	if (copy_config -> uint8Prescaler  <  8 )
	{
		(*(SPI[copy_channel] + CR1 )) |= (copy_config -> uint8Prescaler << BR0);
	}
	else
	{
		/* Error */
	}

	/* Enable or Disable interrupt */
	switch (copy_config -> uint8InterruptEnable){
		case 1  :
			SET_BIT  ((*(SPI[copy_channel] + CR2 )) , RXNEIE);
			break ;
		case 0  :
			CLR_BIT((*(SPI[copy_channel] + CR2 )) , RXNEIE);
			break;
		default :
			/* Error */
		break ;
	}

	/* Configure mode master or slave */
	switch (copy_config -> uint8Mode){
		case 1  :
			SET_BIT  ((*(SPI[copy_channel] + CR1 )) , MSTR);
			break ;
		case 0  :
			CLR_BIT((*(SPI[copy_channel] + CR1 )) , MSTR);
			break;
		default :
			/* Error */
		break ;
	}

	/* Enable SPI */
	SET_BIT  ((*(SPI[copy_channel] + CR1 )) , SPE);
}


uint16 SPI_uint16SendRecSynch (SPI_Ch_t copy_channel , uint16 copy_uint16SendData)
{
	/* Send data */
	(*(SPI[copy_channel] + DR )) = copy_uint16SendData ;
	
	/* Wait till finish transmision */
	while (GET_BIT ( (*(SPI[copy_channel] + SR )) , BSY) == 1) ;
	
	/* Return data data */
	return ( (*(SPI[copy_channel] + DR )) ) ;
}

void SPI_voidSendRecAsynch (SPI_Ch_t copy_channel , uint16 copy_uint16SendData , void (*func)(uint16))
{
	/* Assign call back function */
	callBackFunc[copy_channel] = func ;
	
	/* Send data */
	(*(SPI[copy_channel] + DR )) = copy_uint16SendData ;
}

/***************** ISR handlers ******************/
void SPI1_IRQHandler (void){
	/* clear falg */
	CLR_BIT ((*(SPI[0] + SR )) , RXNE );
	/* Receive data */
	uint16 local_uint16RecData = (*(SPI[0] + DR )) ;
	/* call function*/
	callBackFunc[0](local_uint16RecData);
}

void SPI2_IRQHandler (void){
	/* clear falg */
	CLR_BIT ((*(SPI[1] + SR )) ,RXNE );
	/* Receive data */
	uint16 local_uint16RecData = (*(SPI[1] + DR )) ;
	/* call function*/
	callBackFunc[1](local_uint16RecData);
}


