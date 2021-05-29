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

Std_ReturnType HSENSORS_u8GetData(AdcPeripherals_t Cpy_PeripheralNumber)
{
   // Define Local variables
   uint16 Local_u16ADCResultSpeed       = INITIALIZED_WITH_ZERO;
   uint16 Local_u16ADCResultTemperature = INITIALIZED_WITH_ZERO;
   uint8  Local_u8Speed                 = INITIALIZED_WITH_ZERO;
   uint8  Local_u8Temperature           = INITIALIZED_WITH_ZERO;
   // Get converted data
   MADC_u8ReadResultBlocking(ADC1, SPEED_CHANNEL      , _2_CONVERSION, &Local_u16ADCResultSpeed);
   MADC_u8ReadResultBlocking(ADC1, TEMPERATURE_CHANNEL, _2_CONVERSION, &Local_u16ADCResultTemperature);
   // Adjust speed
   float32 Local_Speed = (Local_u16ADCResultSpeed * REFERENCE_VOLTAGE_FLOAT) / (MAXIMUM_LEVEL_FLOAT);
   Local_u8Speed       = (uint8)(Local_Speed * ADJUST_FACTOR);
   // Adjust temperature
   Local_u8Temperature = (Local_u16ADCResultTemperature * REFERENCE_VOLTAGE_INTEGER * MAPPING_FROM_MV_TO_TEMPERATURE) / (MAXIMUM_LEVEL_INTEGER);
   // Write speed value into RTE
   RTE_WRITE_SPEED(Local_u8Speed);
   RTE_WRITE_SPEED_FLAG(FLAG_SET);
   // Write temperature value into RTE
   RTE_WRITE_TEMP_VAL(Local_u8Temperature);
   RTE_WRITE_TEMP_VAL_FLAG(FLAG_SET);
}


/*************** END OF FUNCTIONS ***************************************************************************/
