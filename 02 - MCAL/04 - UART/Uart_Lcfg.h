/*****************************************************/
 /* Author      : Mosad                              */
 /* Version     : v01                                */
 /* date        : 20/9/2020                          */
/*****************************************************/
#ifndef UART_LCFG_H
#define UART_LCFG_H

/* Configration data types */
typedef enum {
	UART_ENABLE ,
	UART_DISABLE
}State_t;

typedef enum {
	DATA_8BIT ,
	DATA_9BIT
}WordLeng_t;

typedef enum {
	EVEN_PARITY ,
	ODD_PARITY ,
	NO_PARITY
}ParityMode_t;

typedef enum {
	ENABLE_RECEIVER ,
	ENABLE_TRANSMITTER,
	ENABLE_BOTH
}RTControl_t;

/*  Configuration table data type */
typedef struct {
	State_t moduleEnable ;
	WordLeng_t wordLenght;
	ParityMode_t parityMode ;
	RTControl_t RTControl ;
	uint32 u32BusFreq ;
	uint32 u32Baudrate ;
}UART_config_t;


#endif