/*****************************************************/
 /* Author      : Mosad                              */
 /* Version     : v01                                */
 /* date        : 29/4/2020                          */
/*****************************************************/
#ifndef RTE_SEND_UPDATE_PORT_H
#define RTE_SEND_UPDATE_PORT_H

#include "Rte.h"

/**************************************************************************/
/*                         Provided  Ports                                */
/**************************************************************************/
#define    RTE_WRITE_SYSTEM_STATE               Rte_WriteSystemState
#define    RTE_WRITE_HEADER_FLAG                Rte_WriteHeaderFlag
#define    RTE_WRITE_DECRYPTED_DATA_BUFFER_FLAG Rte_WriteDecryptedDataBufferFlag
/**************************************************************************/
/*                         Requested Ports                                */
/**************************************************************************/
#define    RTE_READ_HEADER_FLAG                 Rte_ReadHeaderFlag
#define    RTE_READ_CRC_VALUE                   Rte_ReadCrc
#define    RTE_READ_CODE_SIZE                   Rte_ReadCodeSize
#define    RTE_READ_NODE_ID                     Rte_ReadNodeId
#define    RTE_READ_DECRYPTED_DATA_BUFFER       Rte_ReadDecryptedDataBuffer
#define    RTE_READ_DECRYPTED_DATA_BUFFER_FLAG  Rte_ReadDecryptedDataBufferFlag

#endif
