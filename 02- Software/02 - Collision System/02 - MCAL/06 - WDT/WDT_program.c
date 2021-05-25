/*******************************************************************************
* Title                 :   WDT 
* Filename              :   WDT_program.c
* Author                :   Mohamed Hafez
* Origin Date           :   22/12/2020
* Version               :   1.0.0
* Compiler              :   TODO: COMPILER GOES HERE
* Target                :   TODO: MCU GOES HERE
* Notes                 :   None 
*
*****************************************************************************/
/*************** SOURCE REVISION LOG *****************************************
*
*    Date    Version   Author          Description 
*  22/12/20   1.0.0   Mohamed Hafez   Initial Release.
*
*******************************************************************************/
/** @file WDT_program.c
 *  @brief This is the source file for TODO: WHAT DO I DO? 
 */
/******************************************************************************
* Includes
*******************************************************************************/	

#include "Std_Types.h"
#include "BIT_MATH.h"
#include "WDT_interface.h"
#include "WDT_config.h"
#include "WDT_private.h"

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
* Function Prototypes
*******************************************************************************/

/******************************************************************************
* Function Definitions
*******************************************************************************/
void IWDT_voidChangePrescaler(uint8 Copy_uint8Divisor)
{
   CLR_BIT(IWDT_SR, PUV);
   IWDT_KR = IWDT_ACCESS_PR_RLR_KEY;
   IWDT_PR = Copy_uint8Divisor;
}

void IWDT_voidEnableIwdtWithMaxValue(void)
{
   IWDT_KR = IWDT_ENABLE_IWDT;
}

void IWDT_voidEnableIwdtWithGivenValue(uint16 Copy_uint16ReloadValue)
{
   CLR_BIT(IWDT_SR, RUV);
   IWDT_KR = IWDT_ACCESS_PR_RLR_KEY;
   IWDT_PR = Copy_uint16ReloadValue;
   IWDT_KR = IWDT_ENABLE_IWDT;
}

void IWDT_voidRefreshIwdtWithValue(void)
{
   IWDT_KR = IWDT_REFRESH_IWDT;
}

void IWDT_voidMakeSoftWareReset(void)
{
   CLR_BIT(IWDT_SR, RUV);
   IWDT_KR = IWDT_ACCESS_PR_RLR_KEY;
   IWDT_PR = 1;
   IWDT_KR = IWDT_ENABLE_IWDT;
}

void WWDT_voidMakeSoftWareReset(void)
{
   WWDT_CR = WWDT_REQUEST_SW_RESET;
}


/*************** END OF FUNCTIONS ***************************************************************************/
