/****************************************************************************
* Title                 :   SENSORS   
* Filename              :   SENSORS.h
* Author                :   Mohamed Hafez
* Origin Date           :   22/05/2021
* Version               :   1.0.0
* Compiler              :   TODO: COMPILER GOES HERE
* Target                :   TODO: MCU GOES HERE
* Notes                 :   None
*
*****************************************************************************/
/****************************************************************************
* Doxygen C Template 
*
*****************************************************************************/
/*************** INTERFACE CHANGE LIST **************************************
*
*    Date    Version   Author          Description 
*  22/05/21   1.0.0   Mohamed Hafez   Interface Created.
*
*****************************************************************************/
/** @file  SENSORS_interface.h
 *  @brief This module TODO: WHAT DO I DO?
 * 
 *  This is the header file for the definition TODO: MORE ABOUT ME!
 */
//TODO: UPDATE MACRO BELOW
#ifndef SENSORS_INTERFACE_H_
#define SENSORS_INTERFACE_H_

/******************************************************************************
* Includes
*******************************************************************************/
#include "Std_Types.h"

/******************************************************************************
* Preprocessor Constants
*******************************************************************************/
#define INITIALIZED_WITH_ZERO          0
#define INITIALIZED_WITH_ZERO_FLOAT    0.0
/******************************************************************************
* Configuration Constants
*******************************************************************************/
#define SPEED_ADJUST_FACTOR            10
#define MAPPING_FROM_MV_TO_TEMPERATURE 100
#define TEMPERATURE_CHANNEL            CHANNEL0
#define SPEED_CHANNEL                  CHANNEL1

/******************************************************************************
* Macros
*******************************************************************************/
	
/******************************************************************************
* Typedefs
*******************************************************************************/

/******************************************************************************
* Variables
*******************************************************************************/

/******************************************************************************
* Function Prototypes
*******************************************************************************/
Std_ReturnType HSENSORS_u8InitializeModule(void);
Std_ReturnType HSENSORS_u8ScanSensors(uint8 * Cpy_TemperatureData, uint8 * Cpy_SpeedData);

#endif /*File_H_*/

/*** End of File **************************************************************/
