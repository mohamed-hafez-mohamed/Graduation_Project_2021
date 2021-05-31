/***********************************************************/
/**********Author: osama hegazi*****************************/
/**********Date:26/5/2021***********************************/
/***********version:1***************************************/
/***********************************************************/

/*****************************************************************************************/
/*                                   Include Headers                                     */
/*****************************************************************************************/
#include "Rte_Type.h"
#include "Rte_Buzzer.h"
#include "Rte_DistanceSensor.h"
/*****************************************************************************************/
/*                             Rte Local Data Types                                      */                              
/*****************************************************************************************/                         

/*****************************************************************************************/
/*                             Rte Local Macro Definition                                */
/*****************************************************************************************/

/*****************************************************************************************/
/*        Sender Receiver Variables Definition & Rte protection flag                     */
/*****************************************************************************************/
                                       /*Distance Data*/
static  Rte_SenderRecieverDistanceDataType  Rte_SenderRecieverDistance = INIT_VALUE ;
                                    /* data update flag */
static  Rte_SenderRecieverDataFlagType  Rte_SenderRecieverFlag = INIT_VALUE ;
/*****************************************************************************************/
/*                      Rte Sender Receiver Protections Flags                            */
/*****************************************************************************************/
                                       /*Distance Falg*/
static  Rte_PortStateType   Rte_DistanceDataPortState    = RTE_E_OK;
                                    /* data update flag */
static  Rte_PortStateType   Rte_DataFlagPortState    = RTE_E_OK;									   
/*****************************************************************************************/
/*                          Rte Sender Receiver APIs Definition                          */
/*****************************************************************************************/
/*****************************************************************************************/
/*                             Distance Data Port APIs                                   */
/*****************************************************************************************/
Std_ReturnType Rte_Read_Buzzer_DistanceData (SensorDistanceData *Distance)
{
	Std_ReturnType Local_ReturnError = E_OK ;
	
	if ( (Rte_DistanceDataPortState == RTE_E_OK) && (Distance != NULL_PTR))
	{
		/* Lock the port to write */
		Rte_DistanceDataPortState = RTE_E_NOK ;
		/* Write the data to the port */
		 (*Distance) = Rte_SenderRecieverDistance ; 
		/* Unlock the port after done writing */
		Rte_DistanceDataPortState = RTE_E_OK ;
	}
	else
	{
		Local_ReturnError = E_NOT_OK ;
	}
	return Local_ReturnError ;
}

Std_ReturnType Rte_Write_DistanceSensor_DistanceData(SensorDistanceData Distance)
{
	Std_ReturnType Local_ReturnError = E_OK ;
	
            	 /*protection process*/
	if (Rte_DistanceDataPortState == RTE_E_OK)
	{
		   /* Lock the port to write */
		Rte_DistanceDataPortState = RTE_E_NOK ;
		/* Write the data to the port */
		Rte_SenderRecieverDistance = Distance ; 
		/* Unlock the port after done writing */
		Rte_DistanceDataPortState = RTE_E_OK ;
	}
	else
	{
		Local_ReturnError = E_NOT_OK ;
	}
	return Local_ReturnError ;	
}
/*****************************************************************************************/
/*                               Data Falg Port APIs                                     */
/*****************************************************************************************/
Std_ReturnType Rte_Read_DataFlag (FlagUpdate *Flag)
{
	Std_ReturnType Local_ReturnError = E_OK ;
	
	if ( (Rte_DataFlagPortState == RTE_E_OK) && (Flag != NULL_PTR))
	{
		/* Lock the port to write */
		Rte_DataFlagPortState = RTE_E_NOK ;
		/* Write the data to the port */
		 (*Flag) = Rte_SenderRecieverFlag ; 
		/* Unlock the port after done writing */
		Rte_DataFlagPortState = RTE_E_OK ;
	}
	else
	{
		Local_ReturnError = E_NOT_OK ;
	}
	return Local_ReturnError ;
}

Std_ReturnType Rte_Write_DataFlag(FlagUpdate Flag)
{
	Std_ReturnType Local_ReturnError = E_OK ;
	
            	 /*protection process*/
	if (Rte_DataFlagPortState == RTE_E_OK)
	{
		   /* Lock the port to write */
		Rte_DataFlagPortState = RTE_E_NOK ;
		/* Write the data to the port */
		Rte_SenderRecieverFlag = Flag ; 
		/* Unlock the port after done writing */
		Rte_DataFlagPortState = RTE_E_OK ;
	}
	else
	{
		Local_ReturnError = E_NOT_OK ;
	}
	return Local_ReturnError ;	
}
/***************************************END OF FUNCTION********************************/					


