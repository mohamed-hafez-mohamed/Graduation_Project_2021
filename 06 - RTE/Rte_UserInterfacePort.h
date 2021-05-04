/*****************************************************/
 /* Author      : Mosad                              */
 /* Version     : v01                                */
 /* date        : 29/4/2020                          */
/*****************************************************/
#ifndef RTE_USERINTERFACE_PORT_H
#define RTE_USERINTERFACE_PORT_H

#include "Rte.h"

/**************************************************************************/
/*                         Provided Ports                                 */
/**************************************************************************/
#define     RTE_WRITE_SYSTEM_STATE             Rte_WriteSystemState
#define     RTE_WRITE_USER_RESPONSE            Rte_WriteUserResponse

/**************************************************************************/
/*                         Received Ports                                 */
/**************************************************************************/
#define    RTE_READ_SYSTEM_STATE        Rte_ReadSystemState
#define    RTE_READ_DOWNLOAD_PROGRESS   Rte_ReadUpdateProgress



#endif
