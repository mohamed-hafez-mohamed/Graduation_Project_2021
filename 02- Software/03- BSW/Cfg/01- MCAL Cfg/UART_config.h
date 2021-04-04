/****************************************************************************
* Title                 :   UART   
* Filename              :   UART_config.h
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
/** @file  UART_UART_config.h
 *  @brief This module TODO: WHAT DO I DO?
 * 
 *  This is the header file for the definition TODO: MORE ABOUT ME!
 */
//TODO: UPDATE MACRO BELOW
#ifndef UART_CONFIG_H_
#define UART_CONFIG_H_

/******************************************************************************
* Includes
*******************************************************************************/

/******************************************************************************
* Preprocessor Constants
*******************************************************************************/
//Different Modes
#define UART_CLOCK_PHASE_CAP_SECOND     1
#define UART_CLOCK_POLARITY_LOW         0
/**
 * Choose your BaudRate
 * Clock: 1 MHz 
 * UART_BAUDRATE_1200_CLK_1M      
 * UART_BAUDRATE_2400_CLK_1M      
 * UART_BAUDRATE_4800_CLK_1M      
 * UART_BAUDRATE_9600_CLK_1M       
 * UART_BAUDRATE_19200_CLK_1M      
 * Clock: 8 MHz 
 * UART_BAUDRATE_1200_CLK_8M       
 * UART_BAUDRATE_2400_CLK_8M      
 * UART_BAUDRATE_4800_CLK_8M       
 * UART_BAUDRATE_9600_CLK_8M       
 * UART_BAUDRATE_19200_CLK_8M 
 * 
 */
     

#define UART_BAUDRATE                   UART_BAUDRATE_9600_CLK_8M
/******************************************************************************
* Configuration Constants
*******************************************************************************/ 
// Turn on uart in transmitter and receiver mode.                         
#define UART_Enable_TX_RX               3
#define ENABLE_UART                     1
// Applying Clock Phase and Clock Ploarity Mode.
#define UART_CLOCK_PHASE                UART_CLOCK_PHASE_CAP_SECOND
#define UART_CLOCK_POLARITY             UART_CLOCK_POLARITY_LOW 

#endif /*File_H_*/

/*** End of File **************************************************************/
