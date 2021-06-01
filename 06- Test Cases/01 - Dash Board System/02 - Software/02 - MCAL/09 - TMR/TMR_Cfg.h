/*****************************************************/
 /* Author      : Mosad                              */
 /* Version     : v01                                */
 /* date        : 10/9/2020                          */
/*****************************************************/
#ifndef TMR_CONFIG_H
#define TMR_CONFIG_H


/*
	Enter the APB2 and APB1 bus clock 
*/
#define    APB2_CLK     8000000
#define    APB1_CLK     8000000

/*
	Number of timer in the MCU 
*/

#define   TMR_NUMBER   4


/******************* Private data for the config.c ******************/

/***  Timer configurations struct  ***/
typedef struct {
	uint8 u8Channel ;
	uint8  u8Enable ;
	uint8  u8Mode ;
	uint8  u8InterruptEnable;
	uint32 u32ClkSource ;
	uint16 u16Prescaler;
	uint32 u32Interval ;
}TMR_config_t;

/* Macros */
#define     ENABLE    1
#define     DISABLE   0

/* Timer Modes */
#define      UP_COUNTER    0
#define      DOWN_COUNTER  1




#endif
