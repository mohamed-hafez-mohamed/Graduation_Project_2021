/****************************************************************************
* Title                 :   UART   
* Filename              :   UART_private.h
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
/** @file  UART_private.h
 *  @brief This module TODO: WHAT DO I DO?
 * 
 *  This is the header file for the definition TODO: MORE ABOUT ME!
 */
//TODO: UPDATE MACRO BELOW
#ifndef UART_PRIVATE_H_
#define UART_PRIVATE_H_

/******************************************************************************
* Includes
*******************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
/******************************************************************************
* Typedefs
*******************************************************************************/

/**
* Defines seven variables which specify the UART registers.
*/
typedef struct 
{
    volatile u32 SR;    /**<Status register */
    volatile u32 DR;    /**<Data register */
    volatile u32 BRR;   /**<BaudRate register */
    volatile u32 CR1;   /**<Control register number 1 */
    volatile u32 CR2;   /**<Control register number 2 */
    volatile u32 CR3;   /**<Control register number 3 */
    volatile u32 GTPR;  
}UART_t;

/******************************************************************************
* Preprocessor Constants
*******************************************************************************/
// Some auxilary constants.
// UARTS base address.
#define UART_1_BASE_ADDRESS     0x40013800
#define UART_2_BASE_ADDRESS     0x40004400
#define UART_3_BASE_ADDRESS     0x40004800
// Other constants.
#define CLR_REGISTER            0X00000000
#define NUMBER_OF_UART_CHANNELS 3 
#define ONE_BYTE                0xFF
// Baudrate Configuration
// Clock: 1 MHz 
#define UART_BAUDRATE_1200_CLK_1M       0X0341
#define UART_BAUDRATE_2400_CLK_1M       0X01A0
#define UART_BAUDRATE_4800_CLK_1M       0X00D0
#define UART_BAUDRATE_9600_CLK_1M       0X0068
#define UART_BAUDRATE_19200_CLK_1M      0X0034
// Clock: 8 MHz 
#define UART_BAUDRATE_1200_CLK_8M       0X1A0B
#define UART_BAUDRATE_2400_CLK_8M       0X0D05
#define UART_BAUDRATE_4800_CLK_8M       0X0683
#define UART_BAUDRATE_9600_CLK_8M       0X0341
#define UART_BAUDRATE_19200_CLK_8M      0X01A1
/******************************************************************************
* Configuration Constants
*******************************************************************************/
// Register bits definition.

// SR bits register definition.
#define PE                    0
#define FE                    1
#define OREE                  2
#define NE                    3
#define IDLE                  4
#define RXNE                  5
#define TC                    6
#define TXE                   7
#define LDB                   8
#define CTS                   9
// CR1 bits register definition.
#define SPK                   0
#define RWU                   1  
#define RE                    2
#define TE                    3
#define IDLEIE                4
#define RXNEIE                5
#define TCIE                  6
#define TXEIE                 7
#define PEIE                  8
#define PS                    9
#define PCE                   10
#define WAKE                  11
#define M                     12
#define UE                    13
// CR2 bits register definition.
#define ADD                   0
#define LBDL                  5
#define LBDIE                 6
#define LBCL                  8
#define CPHA                  9
#define CPOL                  10
#define CLKEN                 11
#define STOP                  12
#define LINEN                 14
// CR3 bits register definition.
#define EIE                   0
#define IREN                  1
#define IRLP                  2
#define HDSEL                 3
#define NACK                  4
#define SCEN                  5
#define DMAR                  6
#define DMAT                  7
#define RTSE                  8
#define CTSE                  9
#define CTSIE                 10
// GTPR bits register definition.
#define PSC                   0
#define GT                    1
/******************************************************************************
* Module Variable Definitions
*******************************************************************************/
// Array of UART channels that exist on MC.
static volatile UART_t * const UARTChannel[NUMBER_OF_UART_CHANNELS] = 
{
    ((volatile UART_t * const)(UART_1_BASE_ADDRESS)),
    ((volatile UART_t * const)(UART_2_BASE_ADDRESS)),
    ((volatile UART_t * const)(UART_3_BASE_ADDRESS))
};
/******************************************************************************
* Function Prototypes
*******************************************************************************/

#endif
/*** End of File **************************************************************/
