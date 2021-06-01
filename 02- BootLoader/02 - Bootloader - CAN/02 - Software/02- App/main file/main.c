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
#include "BL_interface.h"
#include "CAN_Interface.h"

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
volatile extern CAN_InitTypeDef        CAN_InitStruct ; //can init struct
volatile extern CAN_FilterInitTypeDef  CAN_FilterInitStruct_1 ; //can set filters struct
volatile extern CAN_FilterInitTypeDef  CAN_FilterInitStruct_4 ; //can set filters struct
/******************************************************************************
* Function Definitions
*******************************************************************************/

int main()
{
  // Initialize peripheral used.
  MRCC_voidInitSysClock();
  MRCC_voidEnableClock(RCC_APB2, IOPA_PERIPHERAL);
  MRCC_voidEnableClock(RCC_AHB,  CRCE_PERIPHERAL);
	MRCC_voidEnableClock(RCC_AHB,  FLITF_PERIPHERAL);
	MRCC_voidEnableClock(RCC_APB1,  CAN_PERIPHERAL);
  MGPIO_voidSetPinMode( PINA12, AFIO_OUTPUT_2M_PULL_UP_DN);
  MGPIO_voidSetPinMode(PINA11, GPIO_INPUT_FLOATING);
	CAN_VoidInit(  CAN1 , &CAN_InitStruct ) ;
	//CAN_VoidFilterSet( & CAN_FilterInitStruct_1 ); // ID = OXO3
	CAN_VoidFilterSet( & CAN_FilterInitStruct_4 ); // ID = OXO4
	// Execute Branch Code.
	ABR_voidBranchCode();
}

/*************** END OF FUNCTIONS ***************************************************************************/
