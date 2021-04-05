/*******************************************************************************
* Title                 :   main  
* Filename              :   main.c
* Author                :   Mohamed Hafez
* Origin Date           :   14/10/2020
* Version               :   1.0.0
* Compiler              :   TODO: COMPILER GOES HERE
* Target                :   TODO: MCU GOES HERE
* Notes                 :   None 
*
*****************************************************************************/
/*************** SOURCE REVISION LOG *****************************************
*
*    Date    Version   Author          Description 
*  14/10/20   1.0.0   Mohamed Hafez   Initial Release.
*
*******************************************************************************/
/** @file main.c
 *  @brief This is the source file for TODO: WHAT DO I DO? 
 */
/******************************************************************************
* Includes
*******************************************************************************/		
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <stdlib.h>
#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "STK_interface.h"
#include "UART_interface.h"
#include "FPEC_interface.h"
#include "BL_interface.h"
#include "UDS_interface.h"
#include "CRC_interface.h"

/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/

/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/

/******************************************************************************
* Module Typedefs
*******************************************************************************/

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/

/******************************************************************************
* Function Definitions
*******************************************************************************/
	
int main()
{
  // Initialize peripheral used.
  MRCC_voidInitSysClock();
  MRCC_voidEnableClock(RCC_APB2, IOPA_PERIPHERAL);
  MRCC_voidEnableClock(RCC_APB2, USART1_PERIPHERAL);
  MRCC_voidEnableClock(RCC_AHB,  CRCE_PERIPHERAL);
	MRCC_voidEnableClock(RCC_AHB,  FLITF_PERIPHERAL);
  MSTK_voidInit();
  MUART_voidInit();
  MGPIO_voidSetPinMode(UART_1_TX, AFIO_OUTPUT_2M_PULL_UP_DN);
  MGPIO_voidSetPinMode(UART_1_RX, GPIO_INPUT_FLOATING);
	// Execute Branch Code.
	ABR_voidBranchCode();
}

/*************** END OF FUNCTIONS ***************************************************************************/
