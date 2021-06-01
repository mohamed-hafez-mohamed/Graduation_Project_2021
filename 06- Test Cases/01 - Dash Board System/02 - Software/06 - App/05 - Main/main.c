/*******************************************************************************
* Title                 :   main  
* Filename              :   main.c
* Author                :   Mohamed Hafez
* Origin Date           :   04/08/2020
* Version               :   1.0.0
* Compiler              :   TODO: COMPILER GOES HERE
* Target                :   TODO: MCU GOES HERE
* Notes                 :   None 
*
*****************************************************************************/
/*************** SOURCE REVISION LOG *****************************************
*
*    Date    Version   Author          Description 
*  04/08/20   1.0.0   Mohamed Hafez   Initial Release.
*
*******************************************************************************/
/** @file main.c
 *  @brief This is the source file for TODO: WHAT DO I DO? 
 */
/******************************************************************************
* Includes
*******************************************************************************/		
#include "Std_Types.h"
#include "BIT_MATH.h"

/* MCAL */
#include "WDT_interface.h"

/* Services */
#include "SCHEDULER_interface.h"
#include "NVM_interface.h"
#include "CanIf_Interface.h"
#include "EcuM_Interface.h"

/* SWCs */
#include "get.h"
#include "display.h"
#include "Rtc_Interface.h"

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
extern Queue_t ReadyQueue;
/******************************************************************************
* Function Definitions
*******************************************************************************/ 
void WDG_SoftReset(void)
{
  uint32 Data ; 
	
  CanIf_uint32Receive_Word(&Data);//receive header ack

	if (Data == 0X00000310)
	{
       FEE_voidEraseRestoreHeaderPage(BL_BRANCHING_FLAG_ADDRESS_HEX, SET_BRANCHING_FLAG );
       IWDT_voidMakeSoftWareReset();	    		
	}
}

int main()
{
	/*init clock to all mcal peripheral*/
	EcuM_unit8RccPeriphInit(); 
	/*init dio pins for all mcal peripheral*/
	EcuM_unit8DioPeriphInit();	 
	/*init all HW peripherals*/
	EcuM_unit8StartupPeriph();
	
	/* Init SWCs */
  HGET_u8InitializeModule();
  HDISPLAY_u8InitializeModule();
	SCHEDULER_voidInitScheduler(&ReadyQueue);

	/* Create the tasks */
	SCHEDULER_u8CreateTask(0, 0  , 700,  1, &HGET_u8GetData, NULL_PTR);
	SCHEDULER_u8CreateTask(1, 50,  750 , 1, &HDISPLAY_u8DisplayData, NULL_PTR);
	SCHEDULER_u8CreateTask(2, 100,  500 , 1, &Rtc_MainFunction, NULL_PTR);
  SCHEDULER_voidStartScheduler();
  while(1)
	{
		SCHEDULER_voidDispatchTasks(&ReadyQueue);
	}
}

/*************** END OF FUNCTIONS ***************************************************************************/
