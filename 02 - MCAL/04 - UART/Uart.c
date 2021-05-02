/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v01                                */
 /* date        : 20/9/2020                          */
/*****************************************************/
/* Library includes */
#include "BIT_MATH.h"
#include "Std_Types.h"

/* Module includes */
#include "Uart_Interface.h"
#include "Uart_Cfg.h"
#include "Uart_Reg.h"

extern UART_config_t UART_configTable [UART_MAX_CH];

Uart_pFunc_t Uart_CallBack[3] ; 

void Uart_voidInit(void)
{
	UART_Ch_t local_u8Counter = 0;
	// To initiaize all the channels 
	for (local_u8Counter = 0 ; local_u8Counter < MAX_TIMERS ; local_u8Counter++){
		// To only configure the enabled uart modules 
		if (UART_configTable [local_u8Counter].moduleEnable == UART_ENABLE){
			
			/* Configure word length */
			switch (UART_configTable [local_u8Counter].wordLenght){
				case DATA_8BIT :
					CLR_BIT ((*(UART[local_u8Counter]+CR1)) , M);
					break ;
				case DATA_9BIT :
					SET_BIT ((*(UART[local_u8Counter]+CR1)) , M);
					break ;
				default : /* Should not be here */ break;
			}
			
			/* Configure parity mode */
			switch (UART_configTable [local_u8Counter].parityMode){
				case EVEN_PARITY :
					SET_BIT ((*(UART[local_u8Counter]+CR1)) , PCE);    // enable parity control
					CLR_BIT ((*(UART[local_u8Counter]+CR1)) , PS);   // choose even parity
					break ;
				case ODD_PARITY :
					SET_BIT ((*(UART[local_u8Counter]+CR1)) , PCE);    // enable parity control
					SET_BIT ((*(UART[local_u8Counter]+CR1)) , PS);     // choose odd parity
					break ;
				case NO_PARITY :
					CLR_BIT ((*(UART[local_u8Counter]+CR1)) , PCE);  // disable parity control
					break ;
				default : /* Should not be here */ break;
			}
			
			/* Configure R / T enable and disable */
			switch (UART_configTable [local_u8Counter].RTControl){
				case ENABLE_RECEIVER :
					SET_BIT ((*(UART[local_u8Counter]+CR1)) , RE);
					break ;
				case ENABLE_TRANSMITTER :
					SET_BIT ((*(UART[local_u8Counter]+CR1)) , TE);   
					break ;
				case ENABLE_BOTH :
					SET_BIT ((*(UART[local_u8Counter]+CR1)) , RE);
					SET_BIT ((*(UART[local_u8Counter]+CR1)) , TE);
					break ;
				default : /* Should not be here */ break;
			}
			
			/* Configure baud rate */
			uint32 local_u32BRRValue = UART_configTable [local_u8Counter].u32BusFreq / (16 * UART_configTable [local_u8Counter].u32Baudrate);
			*(UART[local_u8Counter]+BBR)  = (local_u32BRRValue << 4) ;   
			
			/* Enable module */
			SET_BIT((*(UART[local_u8Counter]+CR1)) , UE);
			
			/* Intialize status rigeter */
			*(UART[local_u8Counter]+SR)  = 0 ;
		}
	}
}


void Uart_voidTxSynch(UART_Ch_t copy_ch , uint8 *copy_u8data)
{
	while (*copy_u8data){
		*(UART[copy_ch]+DR)  = *copy_u8data ;
		while (GET_BIT ((*(UART[copy_ch]+SR)) , TC) == 0);
		copy_u8data++;
	}
}

void Uart_voidTxByteSynch(UART_Ch_t copy_ch , uint8 copy_u8data)
{
	*(UART[copy_ch]+DR)  = copy_u8data ;
	while (GET_BIT ((*(UART[copy_ch]+SR)) , TC) == 0);
}

void Uart_voidRxSynch (UART_Ch_t copy_ch , uint8 *copy_u8data , uint8 copy_u8DataLength)
{
	while (copy_u8DataLength--){
		while (GET_BIT ((*(UART[copy_ch]+SR)) , RXNE) == 0);
		*copy_u8data = (uint8) (*(UART[copy_ch]+DR));
		copy_u8data++;
	}
}

void Uart_voidRxAsynch(UART_Ch_t copy_ch , Uart_pFunc_t func )
{
	if (func == NULL_PTR){
		// error
	}
	else 
	{
		
	}
	/* Enable transmit interrupt */
	SET_BIT((*(UART[copy_ch]+CR1)) , RXNEIE);
	/* Set call back function */
	Uart_CallBack[copy_ch] = func ; 
}

void Uart_voidRxDisableInterrupt (UART_Ch_t copy_ch)
{
	CLR_BIT((*(UART[copy_ch]+CR1)) , RXNEIE);
}

void USART1_IRQHandler(void)
{
	// Determine what cause interrupt.
   if(GET_BIT( (*(UART[UART1]+SR)), RXNE))
	{
		// Clear Flag.
		CLR_BIT( (*(UART[UART1]+SR)), RXNE);
		Uart_CallBack[UART1]( (uint8)(*(UART[UART1]+DR)));
	}
}

void USART2_IRQHandler(void)
{
	// Determine what cause interrupt.
   if(GET_BIT( (*(UART[UART2]+SR)), RXNE))
	{
		// Clear Flag.
		CLR_BIT( (*(UART[UART2]+SR)), RXNE);
		Uart_CallBack[UART2]((uint8) (*(UART[UART2]+DR)));
	}
}

void USART3_IRQHandler(void)
{
	// Determine what cause interrupt.
   if(GET_BIT( (*(UART[UART3]+SR)), RXNE))
	{
		// Clear Flag.
		CLR_BIT( (*(UART[UART3]+SR)), RXNE);
		Uart_CallBack[UART3]( (uint8)(*(UART[UART3]+DR)));
	}
}





