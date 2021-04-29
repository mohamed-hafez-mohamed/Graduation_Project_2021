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
#deine     RTE_WRITE_CODE_SIZE         Rte_WriteCodeSize
#define    RTE_WEITE_DYCREPTION_KEY    Rte_WriteDecryptionKey
#define    RTE_WRITE_SYSTEM_STATE      Rte_WriteSystemState


/**************************************************************************/
/*                         Received Ports                                 */
/**************************************************************************/
#define    RTE_READ_SYSTEM_STATE      Rte_ReadSystemState




#endif
