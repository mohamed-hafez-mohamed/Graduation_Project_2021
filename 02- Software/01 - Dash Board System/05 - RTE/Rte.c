/*****************************************************/
 /* Author      : Mosad                              */
 /* Version     : v01                                */
 /* date        : 25/5/2021                          */
/*****************************************************/

/* Module includes */
#include "Rte.h"

/* Local Data Types */
typedef    uint8   PortStateType  ; 

/* Local Macros */
#define INITIAL_ValUE 0x0u
#define IDLE          0x0u
#define BUSY          0x1u

/* Rte Golable Variables */
static uint8 Global_TempVal                                    = INITIAL_ValUE ;
static FlagType Global_TempValFlag                             = INITIAL_ValUE ;
static uint8 Global_Speed                                      = INITIAL_ValUE ;
static FlagType Global_SpeedFlag                               = INITIAL_ValUE ;
static uint8 *Global_TimePtr                                   = NULL_PTR ;
static FlagType Global_TimePtrFlag                             = INITIAL_ValUE ;

/* Rte protection flag */
static PortStateType Global_TempValPortState                   = IDLE;
static PortStateType Global_TempValFlagPortState               = IDLE ;
static PortStateType Global_SpeedPortState                     = IDLE ;
static PortStateType Global_SpeedFlagPortState                 = IDLE ;
static PortStateType Global_TimePtrPortState                   = IDLE ;
static PortStateType Global_TimePtrFlagPortState               = IDLE ;

/**************************************************************************/
/*                         Temp Val Port                                  */
/**************************************************************************/
Std_ReturnType Rte_WriteTempVal (uint8 Cpy_TempVal)
{
	Std_ReturnType Local_ReturnError = E_OK ;
	
	if (Global_TempValPortState == IDLE)
	{
		/* Lock the port to write */
		Global_TempValPortState = BUSY ;
		/* Write the data to the port */
		Global_TempVal = Cpy_TempVal ; 
		/* Unlock the port after done writing */
		Global_TempValPortState = IDLE ;
	}
	else
	{
		Local_ReturnError = E_NOT_OK ;
	}
	return Local_ReturnError ;
}

Std_ReturnType Rte_ReadTempVal (uint8 *Cpy_TempVal)
{
	Std_ReturnType Local_ReturnError = E_OK ;
	
	if ( (Global_TempValPortState == IDLE) && (Cpy_TempVal != NULL_PTR))
	{
		/* Lock the port to write */
		Global_TempValPortState = BUSY ;
		/* Write the data to the port */
		 (*Cpy_TempVal) = Global_TempVal ; 
		/* Unlock the port after done writing */
		Global_TempValPortState = IDLE ;
	}
	else
	{
		Local_ReturnError = E_NOT_OK ;
	}
	return Local_ReturnError ;
}


/**************************************************************************/
/*                         Temp Val flag Port                             */
/**************************************************************************/
Std_ReturnType Rte_WriteTempvalFlag (uint8 Cpy_TempValFlag)
{
	Std_ReturnType Local_ReturnError = E_OK ;
	
	if (Global_TempValFlagPortState == IDLE)
	{
		/* Lock the port to write */
		Global_TempValFlagPortState = BUSY ;
		/* Write the data to the port */
		Global_TempValFlag = Cpy_TempValFlag ; 
		/* Unlock the port after done writing */
		Global_TempValFlagPortState = IDLE ;
	}
	else
	{
		Local_ReturnError = E_NOT_OK ;
	}
	return Local_ReturnError ;
}

Std_ReturnType Rte_ReadTempvalFlag (uint8 *Cpy_TempValFlag)
{
	Std_ReturnType Local_ReturnError = E_OK ;
	
	if ( (Global_TempValFlagPortState == IDLE) && (Cpy_TempValFlag != NULL_PTR))
	{
		/* Lock the port to write */
		Global_TempValFlagPortState = BUSY ;
		/* Write the data to the port */
		 (*Cpy_TempValFlag) = Global_TempValFlag ; 
		/* Unlock the port after done writing */
		Global_TempValFlagPortState = IDLE ;
	}
	else
	{
		Local_ReturnError = E_NOT_OK ;
	}
	return Local_ReturnError ;
}


/**************************************************************************/
/*                          Speed Port                                    */
/**************************************************************************/
Std_ReturnType Rte_WriteSpeed (uint8 Cpy_Speed)
{
	Std_ReturnType Local_ReturnError = E_OK ;
	
	if (Global_SpeedPortState == IDLE)
	{
		/* Lock the port to write */
		Global_SpeedPortState = BUSY ;
		/* Write the data to the port */
		Global_Speed = Cpy_Speed ; 
		/* Unlock the port after done writing */
		Global_SpeedPortState = IDLE ;
	}
	else
	{
		Local_ReturnError = E_NOT_OK ;
	}
	return Local_ReturnError ;
}

Std_ReturnType Rte_ReadSpeed (uint8 *Cpy_Speed)
{
	Std_ReturnType Local_ReturnError = E_OK ;
	
	if ( (Global_SpeedPortState == IDLE) && (Cpy_Speed != NULL_PTR))
	{
		/* Lock the port to write */
		Global_SpeedPortState = BUSY ;
		/* Write the data to the port */
		 (*Cpy_Speed) = Global_Speed ; 
		/* Unlock the port after done writing */
		Global_SpeedPortState = IDLE ;
	}
	else
	{
		Local_ReturnError = E_NOT_OK ;
	}
	return Local_ReturnError ;
}


/**************************************************************************/
/*                         Speed flag Port                                */
/**************************************************************************/
Std_ReturnType Rte_WriteSpeedFlag (uint8 Cpy_SpeedFlag)
{
	Std_ReturnType Local_ReturnError = E_OK ;
	
	if (Global_SpeedFlagPortState == IDLE)
	{
		/* Lock the port to write */
		Global_SpeedFlagPortState = BUSY ;
		/* Write the data to the port */
		Global_SpeedFlag = Cpy_SpeedFlag ; 
		/* Unlock the port after done writing */
		Global_SpeedFlagPortState = IDLE ;
	}
	else
	{
		Local_ReturnError = E_NOT_OK ;
	}
	return Local_ReturnError ;
}

Std_ReturnType Rte_ReadSpeedFlag (uint8 *Cpy_SpeedFlag)
{
	Std_ReturnType Local_ReturnError = E_OK ;
	
	if ( (Global_SpeedFlagPortState == IDLE) && (Cpy_SpeedFlag != NULL_PTR))
	{
		/* Lock the port to write */
		Global_SpeedFlagPortState = BUSY ;
		/* Write the data to the port */
		 (*Cpy_SpeedFlag) = Global_SpeedFlag ; 
		/* Unlock the port after done writing */
		Global_SpeedFlagPortState = IDLE ;
	}
	else
	{
		Local_ReturnError = E_NOT_OK ;
	}
	return Local_ReturnError ;
}

/**************************************************************************/
/*                          TimePtr Port                                  */
/**************************************************************************/
Std_ReturnType Rte_WriteTimePtr (uint8 *Cpy_TimePtr)
{
	Std_ReturnType Local_ReturnError = E_OK ;
	
	if ((Global_TimePtrPortState == IDLE)  && (Cpy_TimePtr != NULL_PTR) )
	{
		/* Lock the port to write */
		Global_TimePtrPortState = BUSY ;
		/* Write the data to the port */
		Global_TimePtr = Cpy_TimePtr ; 
		/* Unlock the port after done writing */
		Global_TimePtrPortState = IDLE ;
	}
	else
	{
		Local_ReturnError = E_NOT_OK ;
	}
	return Local_ReturnError ;
}

Std_ReturnType Rte_ReadTimePtr (uint8 **Cpy_TimePtr)
{
	Std_ReturnType Local_ReturnError = E_OK ;
	
	if ( (Global_TimePtrPortState == IDLE) && (Cpy_TimePtr != NULL_PTR))
	{
		/* Lock the port to write */
		Global_TimePtrPortState = BUSY ;
		/* Write the data to the port */
		 (*Cpy_TimePtr) = Global_TimePtr ; 
		/* Unlock the port after done writing */
		Global_TimePtrPortState = IDLE ;
	}
	else
	{
		Local_ReturnError = E_NOT_OK ;
	}
	return Local_ReturnError ;
}


/**************************************************************************/
/*                         TimePtr flag Port                              */
/**************************************************************************/
Std_ReturnType Rte_WriteTimePtrFlag (uint8 Cpy_TimePtrFlag)
{
	Std_ReturnType Local_ReturnError = E_OK ;
	
	if (Global_TimePtrFlagPortState == IDLE)
	{
		/* Lock the port to write */
		Global_TimePtrFlagPortState = BUSY ;
		/* Write the data to the port */
		Global_TimePtrFlag = Cpy_TimePtrFlag ; 
		/* Unlock the port after done writing */
		Global_TimePtrFlagPortState = IDLE ;
	}
	else
	{
		Local_ReturnError = E_NOT_OK ;
	}
	return Local_ReturnError ;
}

Std_ReturnType Rte_ReadTimePtrFlag (uint8 *Cpy_TimePtrFlag)
{
	Std_ReturnType Local_ReturnError = E_OK ;
	
	if ( (Global_TimePtrFlagPortState == IDLE) && (Cpy_TimePtrFlag != NULL_PTR))
	{
		/* Lock the port to write */
		Global_TimePtrFlagPortState = BUSY ;
		/* Write the data to the port */
		 (*Cpy_TimePtrFlag) = Global_TimePtrFlag ; 
		/* Unlock the port after done writing */
		Global_TimePtrFlagPortState = IDLE ;
	}
	else
	{
		Local_ReturnError = E_NOT_OK ;
	}
	return Local_ReturnError ;
}