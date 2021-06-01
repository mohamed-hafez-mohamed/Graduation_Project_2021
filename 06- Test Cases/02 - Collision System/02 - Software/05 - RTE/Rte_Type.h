/***********************************************************/
/**********Author: osama hegazi*****************************/
/**********Date:25/5/2021***********************************/
/***********version:1***************************************/
/***********************************************************/
#ifndef RTE_TYPE_H
#define RTE_TYPE_H
/*****************************************************************************************/
/*                                   Include Headers                                     */
/*****************************************************************************************/
#include "Std_Types.h"
#include "BIT_MATH.h"
/*****************************************************************************************/
/*                             Rte Local Data Types                                      */                              
/*****************************************************************************************/                         
typedef    uint8   Rte_SenderRecieverDistanceDataType  ; 
typedef    uint8   Rte_SenderRecieverDataFlagType  ;
typedef    uint8   Rte_PortStateType ;
typedef    uint8   FlagUpdate ;
typedef    uint8   SensorDistanceData ;
/*****************************************************************************************/
/*                             Rte Local Macro Definition                                */
/*****************************************************************************************/
#define INIT_VALUE            0U
#define RTE_E_OK	            0U
#define RTE_E_NOK	            1U
#define NOT_UPDATED           0U         				 
#define UPDATED               1U  



#endif