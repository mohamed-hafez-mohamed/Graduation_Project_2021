/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v01                                */
 /* date        : 20/9/2020                          */
/*****************************************************/

#include "Uart_Cfg.h"

UART_config_t UART_configTable [UART_MAX_CH] = {
   // Module 	Date          parity         Rec / trans          Bus       baudrate
   // enable	bits          mode           enable               clk
	{UART_ENABLE   , DATA_8BIT   , NO_PARITY    , ENABLE_BOTH   , APB2_CLK , 9600},
	{UART_DISABLE  , DATA_8BIT   , NO_PARITY    , ENABLE_BOTH   , APB1_CLK , 9600},
	{UART_DISABLE  , DATA_8BIT   , NO_PARITY    , ENABLE_BOTH   , APB1_CLK , 9600}
};
