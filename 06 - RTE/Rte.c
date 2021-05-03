/*****************************************************/
 /* Author      : Mosad                              */
 /* Version     : v01                                */
 /* date        : 29/4/2020                          */
/*****************************************************/

/* Module includes */
#include "Rte.h"

/* Local Data Types */
typedef    uint8   PortStateType  ; 

/* Local Macros */
#define INITIAL_VALUE 0x0u
#define IDLE          0x0u
#define BUSY          0x1u

/* Rte Golable Variables */
static uint32          Global_HeaderFlagValue            = INITIAL_VALUE ;
static uint32          Global_CrcValue                   = INITIAL_VALUE ;
static uint32          Global_CodeSizeValue              = INITIAL_VALUE ;
static uint8           Global_NodeId                     = INITIAL_VALUE ;
static uint8         * Global_DecryptedDataBufferPtr     = NULL_PTR ;
static BufferFlagType  Global_DecryptedDataBufferFlag    = INITIAL_VALUE ;
static SystemStateType Global_SystemStateMachine         = INITIAL_VALUE ;


/* Rte protection flag */
static PortStateType Global_HeaderFlagState              = IDLE;
static PortStateType Global_CrcPortState                 = IDLE;
static PortStateType Global_CodeSizePortState            = IDLE;
static PortStateType Global_NodeIdPortState              = IDLE;
static PortStateType Global_DecryptedDataBufferState     = IDLE;
static PortStateType Global_DecryptedDataBufferFlagState = IDLE;
static PortStateType Global_SystemStateMachineState      = IDLE;


/**************************************************************************/
/*                         Header Flag Port                               */
/**************************************************************************/
Std_ReturnType Rte_WriteHeaderFlag(uint32  Cpy_HeaderFlag)
{
	Std_ReturnType Local_ReturnError = E_OK ;
	if (Global_HeaderFlagState == IDLE)
	{
		/* Lock the port to write */
		Global_HeaderFlagState = BUSY ;
		/* Write the data to the port */
		Global_HeaderFlagValue = Cpy_HeaderFlag; 
		/* Unlock the port after done writing */
		Global_HeaderFlagState = IDLE ;
	}
	else
	{
		Local_ReturnError = E_NOT_OK ;
	}
	return Local_ReturnError ;
}

Std_ReturnType Rte_ReadHeaderFlag(uint32 *Cpy_HeaderFlag)
{
	Std_ReturnType Local_ReturnError = E_OK ;
	if ( (Global_HeaderFlagState == IDLE) && (Cpy_HeaderFlag != NULL_PTR) )
	{
		/* Lock the port to write */
		Global_HeaderFlagState = BUSY ;
		/* Write the data to the port */
		(*Global_HeaderFlagValue) = Global_DecryptedDataBufferFlag ; 
		/* Unlock the port after done writing */
		Global_HeaderFlagState = IDLE ;
	}
	else
	{
		Local_ReturnError = E_NOT_OK ;
	}
	return Local_ReturnError ;
}
/**************************************************************************/
/*                         Crc Port                                       */
/**************************************************************************/
Std_ReturnType Rte_WriteCrc (uint32 Cpy_Crc)
{
	Std_ReturnType Local_ReturnError = E_OK ;
	
	if (Global_CrcPortState == IDLE)
	{
		/* Lock the port to write */
		Global_CrcPortState = BUSY ;
		/* Write the data to the port */
		Global_CrcValue = Cpy_Crc ; 
		/* Unlock the port after done writing */
		Global_CrcPortState = IDLE ;
	}
	else
	{
		Local_ReturnError = E_NOT_OK ;
	}
	return Local_ReturnError ;
}

Std_ReturnType Rte_ReadCrc (uint32 *Cpy_Crc)
{
	Std_ReturnType Local_ReturnError = E_OK ;
	
	if ( (Global_CrcPortState == IDLE) && (Cpy_Crc != NULL_PTR) )
	{
		/* Lock the port to write */
		Global_CrcPortState = BUSY ;
		/* Write the data to the port */
		 (*Cpy_Crc) = Global_CrcValue ; 
		/* Unlock the port after done writing */
		Global_CrcPortState = IDLE ;
	}
	else
	{
		Local_ReturnError = E_NOT_OK ;
	}
	return Local_ReturnError ;
}

/**************************************************************************/
/*                         CodeSize Port                                  */
/**************************************************************************/
Std_ReturnType Rte_WriteCodeSize (uint32 Cpy_CodeSize)
{
	Std_ReturnType Local_ReturnError = E_OK ;
	
	if (Global_CodeSizePortState == IDLE)
	{
		/* Lock the port to write */
		Global_CodeSizePortState = BUSY ;
		/* Write the data to the port */
		Global_CodeSizeValue = Cpy_CodeSize ; 
		/* Unlock the port after done writing */
		Global_CodeSizePortState = IDLE ;
	}
	else
	{
		Local_ReturnError = E_NOT_OK ;
	}
	return Local_ReturnError ;
}

Std_ReturnType Rte_ReadCodeSize (uint32 *Cpy_CodeSize)
{
	Std_ReturnType Local_ReturnError = E_OK ;
	
	if ( (Global_CodeSizePortState == IDLE) && (Cpy_CodeSize != NULL_PTR))
	{
		/* Lock the port to write */
		Global_CodeSizePortState = BUSY ;
		/* Write the data to the port */
		 (*Cpy_CodeSize) = Global_CodeSizeValue ; 
		/* Unlock the port after done writing */
		Global_CodeSizePortState = IDLE ;
	}
	else
	{
		Local_ReturnError = E_NOT_OK ;
	}
	return Local_ReturnError ;
}

/**************************************************************************/
/*                         NodeId Port                                  */
/**************************************************************************/
Std_ReturnType Rte_WriteNodeId (uint8 Cpy_NodeId)
{
	Std_ReturnType Local_ReturnError = E_OK ;
	
	if (Global_NodeIdPortState == IDLE)
	{
		/* Lock the port to write */
		Global_NodeIdPortState = BUSY ;
		/* Write the data to the port */
		Global_NodeId = Cpy_NodeId ; 
		/* Unlock the port after done writing */
		Global_NodeIdPortState = IDLE ;
	}
	else
	{
		Local_ReturnError = E_NOT_OK ;
	}
	return Local_ReturnError ;
}

Std_ReturnType Rte_ReadNodeId (uint8 *Cpy_NodeId)
{
	Std_ReturnType Local_ReturnError = E_OK ;
	
	if ( (Global_NodeIdPortState == IDLE) && (Cpy_NodeId != NULL_PTR))
	{
		/* Lock the port to write */
		Global_NodeIdPortState = BUSY ;
		/* Write the data to the port */
		 (*Cpy_NodeId) = Global_NodeId ; 
		/* Unlock the port after done writing */
		Global_NodeIdPortState = IDLE ;
	}
	else
	{
		Local_ReturnError = E_NOT_OK ;
	}
	return Local_ReturnError ;
}



/**************************************************************************/
/*                         DecryptedDataBuffer Port                       */
/**************************************************************************/
Std_ReturnType Rte_WriteDecryptedDataBuffer (uint8 *Cpy_DecryptedDataBufferPtr)
{
	Std_ReturnType Local_ReturnError = E_OK ;
	
	if ((Global_DecryptedDataBufferState == IDLE)&& (Cpy_DecryptedDataBufferPtr != NULL_PTR))
	{
		/* Lock the port to write */
		Global_DecryptedDataBufferState = BUSY ;
		/* Write the data to the port */
		Global_DecryptedDataBufferPtr = Cpy_DecryptedDataBufferPtr ; 
		/* Unlock the port after done writing */
		Global_DecryptedDataBufferState = IDLE ;
	}
	else
	{
		Local_ReturnError = E_NOT_OK ;
	}
	return Local_ReturnError ;
}

Std_ReturnType Rte_ReadDecryptedDataBuffer (uint8 **Cpy_DecryptedDataBufferPtr)
{
	Std_ReturnType Local_ReturnError = E_OK ;
	
	if ( (Global_DecryptedDataBufferState == IDLE) && (Cpy_DecryptedDataBufferPtr != NULL_PTR))
	{
		/* Lock the port to write */
		Global_DecryptedDataBufferState = BUSY ;
		/* Write the data to the port */
		 (*Cpy_DecryptedDataBufferPtr) = Global_DecryptedDataBufferPtr ; 
		/* Unlock the port after done writing */
		Global_DecryptedDataBufferState = IDLE ;
	}
	else
	{
		Local_ReturnError = E_NOT_OK ;
	}
	return Local_ReturnError ;
}

/**************************************************************************/
/*                         DecryptedDataBufferFlag Port                   */
/**************************************************************************/
Std_ReturnType Rte_WriteDecryptedDataBufferFlag (BufferFlagType Cpy_DecryptedDataBufferFlag)
{
	Std_ReturnType Local_ReturnError = E_OK ;
	
	if (Global_DecryptedDataBufferFlagState == IDLE)
	{
		/* Lock the port to write */
		Global_DecryptedDataBufferFlagState = BUSY ;
		/* Write the data to the port */
		Global_DecryptedDataBufferFlag = Cpy_DecryptedDataBufferFlag ; 
		/* Unlock the port after done writing */
		Global_DecryptedDataBufferFlagState = IDLE ;
	}
	else
	{
		Local_ReturnError = E_NOT_OK ;
	}
	return Local_ReturnError ;
}

Std_ReturnType Rte_ReadDecryptedDataBufferFlag (BufferFlagType *Cpy_DecryptedDataBufferFlag)
{
	Std_ReturnType Local_ReturnError = E_OK ;
	
	if ( (Global_DecryptedDataBufferFlagState == IDLE) && (Cpy_DecryptedDataBufferFlag != NULL_PTR) )
	{
		/* Lock the port to write */
		Global_DecryptedDataBufferFlagState = BUSY ;
		/* Write the data to the port */
		 (*Cpy_DecryptedDataBufferFlag) = Global_DecryptedDataBufferFlag ; 
		/* Unlock the port after done writing */
		Global_DecryptedDataBufferFlagState = IDLE ;
	}
	else
	{
		Local_ReturnError = E_NOT_OK ;
	}
	return Local_ReturnError ;
}



/**************************************************************************/
/*                         SystemState Port                               */
/**************************************************************************/
Std_ReturnType Rte_WriteSystemState (SystemStateType Cpy_SystemState)
{
	Std_ReturnType Local_ReturnError = E_OK ;
	
	if (Global_SystemStateMachineState == IDLE)
	{
		/* Lock the port to write */
		Global_SystemStateMachineState = BUSY ;
		/* Write the data to the port */
		Global_SystemStateMachine = Cpy_SystemState ; 
		/* Unlock the port after done writing */
		Global_SystemStateMachineState = IDLE ;
	}
	else
	{
		Local_ReturnError = E_NOT_OK ;
	}
	return Local_ReturnError ;
}

Std_ReturnType Rte_ReadSystemState (SystemStateType *Cpy_SystemState)
{
	Std_ReturnType Local_ReturnError = E_OK ;
	
	if ( (Global_SystemStateMachineState == IDLE) && (Cpy_SystemState != NULL_PTR))
	{
		/* Lock the port to write */
		Global_SystemStateMachineState = BUSY ;
		/* Write the data to the port */
		 (*Cpy_SystemState) = Global_SystemStateMachine ; 
		/* Unlock the port after done writing */
		Global_SystemStateMachineState = IDLE ;
	}
	else
	{
		Local_ReturnError = E_NOT_OK ;
	}
	return Local_ReturnError ;
}

