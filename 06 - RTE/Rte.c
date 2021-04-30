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
static uint32 Global_CrcValue                         = INITIAL_VALUE ;
static uint16 Global_CodeSizeValue                    = INITIAL_VALUE ;
static uint8 *Global_DecryptionKeyPtr                 = NULL_PTR ;
static uint8 *Global_DecryptedDataBufferPtr           = NULL_PTR ;
static BufferFlagType Global_DecryptedDataBufferFlag  = INITIAL_VALUE ;
static SystemStateType Global_SystemStateMachine      = INITIAL_VALUE ;


/* Rte protection flag */
static PortStateType Global_CrcPortState                   = IDLE;
static PortStateType Global_CodeSizePortState              = IDLE;
static PortStateType Global_DecryptionKeyPortState         = IDLE;
static PortStateType Global_DecryptedDataBufferState       = IDLE;
static PortStateType Global_DecryptedDataBufferFlagState   = IDLE;
static PortStateType Global_SystemStateMachineState        = IDLE;


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
Std_ReturnType Rte_WriteCodeSize (uint16 Cpy_CodeSize)
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

Std_ReturnType Rte_ReadCodeSize (uint16 *Cpy_CodeSize)
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
/*                         DecryptionKey Port                             */
/**************************************************************************/
Std_ReturnType Rte_WriteDecryptionKey (uint8 *Cpy_DecryptionKeyPtr)
{
	Std_ReturnType Local_ReturnError = E_OK ;
	
	if ((Global_DecryptionKeyPortState == IDLE) && (Cpy_DecryptionKeyPtr != NULL_PTR))
	{
		/* Lock the port to write */
		Global_DecryptionKeyPortState = BUSY ;
		/* Write the data to the port */
		Global_DecryptionKeyPtr = Cpy_DecryptionKeyPtr ; 
		/* Unlock the port after done writing */
		Global_DecryptionKeyPortState = IDLE ;
	}
	else
	{
		Local_ReturnError = E_NOT_OK ;
	}
	return Local_ReturnError ;
}

Std_ReturnType Rte_ReadDecryptionKey (uint8 **Cpy_DecryptionKeyPtr)
{
	Std_ReturnType Local_ReturnError = E_OK ;
	
	if ( (Global_DecryptionKeyPortState == IDLE) && (Cpy_DecryptionKeyPtr != NULL_PTR) )
	{
		/* Lock the port to write */
		Global_DecryptionKeyPortState = BUSY ;
		/* Write the data to the port */
		 (*Cpy_DecryptionKeyPtr) = Global_DecryptionKeyPtr ; 
		/* Unlock the port after done writing */
		Global_DecryptionKeyPortState = IDLE ;
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

