/*****************************************************/
 /* Author      : Mosad                              */
 /* Version     : v01                                */
 /* date        : 25/5/2021                          */
/*****************************************************/
#ifndef RTE_H
#define RTE_H

/* Includes */
#include "Std_Types.h"
#include "Rte_DataTypes.h"

/* Proto types */

/**************************************************************************/
/*                         Temp val  Port                                 */
/**************************************************************************/
Std_ReturnType Rte_WriteTempVal(uint8 Cpy_CodeSize);
Std_ReturnType Rte_ReadTempVal (uint8 *Cpy_CodeSize);

/**************************************************************************/
/*                         Temp val flag Port                             */
/**************************************************************************/
Std_ReturnType Rte_WriteTempvalFlag(uint8 Cpy_TempvalFlag);
Std_ReturnType Rte_ReadTempvalFlag (uint8 *Cpy_TempvalFlag);

/**************************************************************************/
/*                          Speed Port                                    */
/**************************************************************************/
Std_ReturnType Rte_WriteSpeed (uint8 Cpy_Speed);
Std_ReturnType Rte_ReadSpeed (uint8 *Cpy_Speed);

/**************************************************************************/
/*                         Speed flag Port                                */
/**************************************************************************/
Std_ReturnType Rte_WriteSpeedFlag (uint8 Cpy_SpeedFlag);
Std_ReturnType Rte_ReadSpeedFlag (uint8 *Cpy_SpeedFlag);

/**************************************************************************/
/*                          TimePtr Port                                  */
/**************************************************************************/
Std_ReturnType Rte_WriteTimePtr (uint8 *Cpy_TimePtr);
Std_ReturnType Rte_ReadTimePtr (uint8 **Cpy_TimePtr);

/**************************************************************************/
/*                         TimePtr flag Port                              */
/**************************************************************************/
Std_ReturnType Rte_WriteTimePtrFlag (uint8 Cpy_TimePtrFlag);
Std_ReturnType Rte_ReadTimePtrFlag (uint8 *Cpy_TimePtrFlag);



#endif
