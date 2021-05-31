/*******************************************************************************
**  FILENAME     : DistanceSensor.c                      			                **
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
#include "Rte_DistanceSensor.h"
/*****************************************************************************************/
/*                                Include modules Headers                                */
/*****************************************************************************************/
/*****************************************************************************************/
/*                              Main Function Definition                                 */
/*****************************************************************************************/
void DistanceSensor_MainFunction (void)
{
    Std_ReturnType status = RTE_E_OK ;
    SensorDistanceData Distance = INIT_VALUE ;
	                          /* Read Distance */
	status = HCSR04_uint8ReadDistance(&Distance);
	           /*check if the status = ok & there are objects in the range of the sensor */
	if( status == RTE_E_OK && Distance != INIT_VALUE )
	{
		                 /*access piont & sender reciever*/
	   status = RTE_WRITE_ULTRASENSOR_DISTANCE_DATA(Distance);	
	}
	else
	{
	           /*No objects exist in the sensor Range*/
	}		
}
/***************************************END OF FUNCTION********************************/					


