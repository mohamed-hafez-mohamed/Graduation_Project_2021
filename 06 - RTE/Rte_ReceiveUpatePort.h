/*****************************************************/
 /* Author      : Mosad                              */
 /* Version     : v01                                */
 /* date        : 29/4/2020                          */
/*****************************************************/
#ifndef RTE_RECEIVE_UPDATE_PORT_H
#define RTE_RECEIVE_UPDATE_PORT_H

#include "Rte.h"

/**************************************************************************/
/*                         Provided Ports                                 */
/**************************************************************************/
#define    RTE_WRITE_CRC_VALUE           Rte_WriteCrc
#define    RTE_WRITE_CODE_SIZE           Rte_WriteCodeSize
#define    RTE_WRITE_SYSTEM_STATE        Rte_WriteSystemState
#define    RTE_WRITE_NODE_ID             Rte_WriteNodeId
#define    RTE_WRITE_HEADER_ACK_FLAG   	 Rte_WriteHeaderAckFlag
#define    RTE_WRITE_DOWNLOAD_PROGRESS   Rte_WriteUpdateProgress


/**************************************************************************/
/*                         Received Ports                                 */
/**************************************************************************/
#define    RTE_READ_SYSTEM_STATE      Rte_ReadSystemState
#define    RTE_READ_USER_RESPONSE     Rte_ReadUserResponse



#endif
