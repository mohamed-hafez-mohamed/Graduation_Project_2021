/*******************************************************************************
**  FILENAME     : main.c                               			                **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2021-05-29                                                **
**                                                                            **
**  AUTHOR       : osamahijazi	                                              **
**                                                                            **
*******************************************************************************/
/*****************************************************************************************/
/*                                   Include Headers                                     */
/*****************************************************************************************/
#include "BIT_MATH.h"
#include "Std_Types.h"
/*****************************************************************************************/
/*                                Include modules Headers                                */
/*****************************************************************************************/
#include "EcuM_Interface.h"
#include "CanIf_Interface.h"
#include "FPEC_interface.h"
#include "WDT_interface.h"
#include "UDS_interface.h"
#include "Rte_DistanceSensor.h"
#include "Rte_Buzzer.h"
/*****************************************************************************************/
/*                                Local Data Types                                       */                              
/*****************************************************************************************/                         

/*****************************************************************************************/
/*                              Local Varaible Definition                                */
/*****************************************************************************************/

/*****************************************************************************************/
/*                         Local Functions Decleration                                   */
/*****************************************************************************************/
void WDG_VoidSoftReset(void);
/*****************************************************************************************/
/*                         Local Functions Definition                                     */
/*****************************************************************************************/
                                /*CallBack Fun used to respond to Soft Reset Request*/
void WDG_VoidSoftReset(void)
{
  uint8 Local_status ;
  uint32 Local_uint32Data; 
  Local_status  =  CanIf_uint32Receive_Word(&Local_uint32Data);//receive header ack
  if (Local_uint32Data == 0X00000310)
   {	
      FEE_voidEraseRestoreHeaderPage(BL_BRANCHING_FLAG_ADDRESS_HEX, SET_BRANCHING_FLAG );
      IWDT_voidMakeSoftWareReset();		    		
   }
}
 /*****************************************************************************************/
/*                         Main Function Definition                                     */
/*****************************************************************************************/
 
 int main (void)
 {  
	  /*Enable Clock*/
   EcuM_unit8RccPeriphInit();
	  /* Enable mcal & hal pins */
   EcuM_unit8DioPeriphInit(); 
	  /*Init  mcal & hal  */
   EcuM_unit8StartupPeriph(); 
	 
  while(1)  
  { 
	/*Get Distance From Sensor SWC*/
   DistanceSensor_MainFunction();
	/*Set action by Actuator SWC*/
   Buzzer_MainFunction();
  }  
	
}
 
