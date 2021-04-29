/*****************************************************/
 /* Author      : Mosad                              */
 /* Version     : v01                                */
 /* date        : 29/4/2020                          */
/*****************************************************/
#ifndef RTE_DATA_TYPES_H
#define RTE_DATA_TYPES_H

#include "Rte.h"

typedef     uint8    SystemStateType ;

/* SystemStateType  values */
#define    SYS_IDLE                    0x0u
#define    SYS_NEW_UPDATE_REQ          0x1u
#define    SYS_REC_UPDATE              0x2u
#define    SYS_DECRYPT                 0x3u
#define    SYS_SEND_UPDATE             0x4u
#define    SYS_DONE_UPDATE             0x5u





#endif