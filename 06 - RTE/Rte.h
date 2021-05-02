/*****************************************************/
 /* Author      : Mosad                              */
 /* Version     : v01                                */
 /* date        : 29/4/2020                          */
/*****************************************************/
#ifndef RTE_H
#define RTE_H

/* Includes */
#include "Std_Types.h"
#include "Rte_DataTypes.h"

/* Proto types */

/**************************************************************************/
/*                         Crc Port                                       */
/**************************************************************************/
Std_ReturnType Rte_WriteCrc (uint32 Cpy_Crc);
Std_ReturnType Rte_ReadCrc (uint32 *Cpy_Crc);


/**************************************************************************/
/*                         CodeSize Port                                  */
/**************************************************************************/
Std_ReturnType Rte_WriteCodeSize (uint32 Cpy_CodeSize);
Std_ReturnType Rte_ReadCodeSize (uint32 *Cpy_CodeSize);

/**************************************************************************/
/*                         NodeId Port                                  */
/**************************************************************************/
Std_ReturnType Rte_WriteNodeId (uint8 Cpy_NodeId);
Std_ReturnType Rte_ReadNodeId (uint8 *Cpy_NodeId);

/**************************************************************************/
/*                         DecryptedDataBuffer Port                       */
/**************************************************************************/
Std_ReturnType Rte_WriteDecryptedDataBuffer (uint8 *Cpy_DecryptedDataBufferPtr);
Std_ReturnType Rte_ReadDecryptedDataBuffer (uint8 **Cpy_DecryptedDataBufferPtr);

/**************************************************************************/
/*                         DecryptedDataBufferFlag Port                   */
/**************************************************************************/
Std_ReturnType Rte_WriteDecryptedDataBufferFlag (BufferFlagType Cpy_DecryptedDataBufferFlag);
Std_ReturnType Rte_ReadDecryptedDataBufferFlag (BufferFlagType *Cpy_DecryptedDataBufferFlag);

/**************************************************************************/
/*                         SystemState Port                               */
/**************************************************************************/
Std_ReturnType Rte_WriteSystemState (SystemStateType Cpy_SystemState);
Std_ReturnType Rte_ReadSystemState (SystemStateType *Cpy_SystemState);





#endif
