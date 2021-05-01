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
#define    RTE_WRITE_CRC_VALUE         Rte_WriteCrc
#define    RTE_WRITE_CODE_SIZE         Rte_WriteCodeSize
#define    RTE_WRITE_SYSTEM_STATE      Rte_WriteSystemState
#define    RT_WRITE_NODE_ID            Rte_WriteNodeId


/**************************************************************************/
/*                         Received Ports                                 */
/**************************************************************************/
#define    RTE_READ_SYSTEM_STATE      Rte_ReadSystemState




#endif
