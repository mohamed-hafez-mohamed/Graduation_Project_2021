/*******************************************************************************
* Title                 :   SENSORS 
* Filename              :   SENSORS.c
* Author                :   Mohamed Hafez
* Origin Date           :   22/05/2021
* Version               :   1.0.0
* Compiler              :   TODO: COMPILER GOES HERE
* Target                :   TODO: MCU GOES HERE
* Notes                 :   None 
*
*****************************************************************************/
/*************** SOURCE REVISION LOG *****************************************
*
*    Date    Version   Author          Description 
*  22/05/21   1.0.0   Mohamed Hafez   Initial Release.
*
*******************************************************************************/
/** @file SENSORS_program.c
 *  @brief This is the source file for TODO: WHAT DO I DO? 
 */
/******************************************************************************
* Includes
*******************************************************************************/	
#include "Std_Types.h"
#include "BIT_MATH.h"
#include "Rte_DataTypes.h"
#include "Rte_SpeedPort.h"
#include "Rte_TempPort.h"
#include "ADC.h"
#include "sensors.h"
#include "sensors_Cfg.h"
#include "sensors_Private.h"

/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/

/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/

/******************************************************************************
* Module Typedefs
*******************************************************************************/

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/

/******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************
* Function Definitions
*******************************************************************************/
Std_ReturnType HSENSORS_u8InitializeModule(void)
{
   /*!<TODO: Initialize Variables*/
}

Std_ReturnType HSENSORS_u8ScanSensors(uint8 * Cpy_TemperatureData, uint8 * Cpy_SpeedData)
{
   // Define Local variables
   uint16  Local_u16ADCResultSpeed       = INITIALIZED_WITH_ZERO;
   uint16  Local_u16ADCResultTemperature = INITIALIZED_WITH_ZERO;
   float32 Local_Speed                   = INITIALIZED_WITH_ZERO_FLOAT;
   float32 Local_Temperature             = INITIALIZED_WITH_ZERO_FLOAT;
   // Get converted data
   MADC_u8ReadResultBlocking(ADC1, TEMPERATURE_CHANNEL, _2_CONVERSION, &Local_u16ADCResultTemperature);
   MADC_u8ReadResultBlocking(ADC1, SPEED_CHANNEL      , _2_CONVERSION, &Local_u16ADCResultSpeed);
   // Adjust temperature
   Local_Temperature    = Local_u16ADCResultTemperature * REFERENCE_VOLTAGE_FLOAT * MAPPING_FROM_MV_TO_TEMPERATURE;
   Local_Temperature    = Local_Temperature / MAXIMUM_LEVEL_INTEGER;
   // Adjust speed
   Local_Speed          = Local_u16ADCResultSpeed * REFERENCE_VOLTAGE_FLOAT;
   Local_Speed          = Local_Speed / MAXIMUM_LEVEL_INTEGER;
   Local_Speed          = Local_Speed * SPEED_ADJUST_FACTOR;
   // Out data
   *Cpy_TemperatureData = (uint8)(Local_Temperature);
   *Cpy_SpeedData       = (uint8)(Local_Speed);
}


/*************** END OF FUNCTIONS ***************************************************************************/
