/*******************************************************************************
**  FILENAME     : Buzzer.c                             			                **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2021-05-29                                                 **
**                                                                            **
**  AUTHOR       : osamahijazi	                                              **
**                                                                            **
*******************************************************************************/
/*****************************************************************************************/
/*                                   Include Headers                                     */
/*****************************************************************************************/
#include "Rte_Buzzer.h"
/*****************************************************************************************/
/*                                Include modules Headers                                */
/*****************************************************************************************/

/*****************************************************************************************/
/*                              Main Function Definition                                 */
/*****************************************************************************************/
void Buzzer_MainFunction (void)
{
    Std_ReturnType status = RTE_E_OK ;
    SensorDistanceData Distance = INIT_VALUE ;
			                 /*access piont & sender reciever*/
		                      /* Read Distance from Rte */
	  status = RTE_READ_BUZZER_DISTANCE_DATA(&Distance);
	
	  if( status == RTE_E_OK && Distance <= MAX_RANGE )
	  {
		                 /*Set Buzzer Pulse*/
        status = Alarm_uint8SetPulse();
	   }
   	else
	   {
	           /*Distance is out of configurable Range & No need for Buzzer*/
	   }	
		
}
/***************************************END OF FUNCTION********************************/					




