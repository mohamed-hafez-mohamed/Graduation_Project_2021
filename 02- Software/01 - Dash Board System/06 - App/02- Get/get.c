/*******************************************************************************
* Title                 :   GET 
* Filename              :   GET.c
* Author                :   Mohamed Hafez
* Origin Date           :   30/05/2021
* Version               :   1.0.0
* Compiler              :   TODO: COMPILER GOES HERE
* Target                :   TODO: MCU GOES HERE
* Notes                 :   None 
*
*****************************************************************************/
/*************** SOURCE REVISION LOG *****************************************
*
*    Date    Version   Author          Description 
*  30/05/21   1.0.0   Mohamed Hafez   Initial Release.
*
*******************************************************************************/
/** @file GET.c
 *  @brief This is the source file for TODO: WHAT DO I DO? 
 */
/******************************************************************************
* Includes
*******************************************************************************/	

#include "BIT_MATH.h"
#include "Std_Types.h"
#include "Rte_DataTypes.h"
#include "Rte_SpeedPort.h"
#include "Rte_TempPort.h"
#include "sensors.h"
#include "get.h"
#include "get_Cfg.h"
#include "get_Private.h"
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
uint8  Static_u8SWTimer;
uint16 Static_u16TemperatureReads;
uint16 Static_u16SpeedReads;
/******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************
* Function Definitions
*******************************************************************************/
void HGET_u8InitializeModule(void)
{
   // Initialization Variables
   Static_u8SWTimer           = INITIALIZED_WITH_ZERO;
   Static_u16TemperatureReads = INITIALIZED_WITH_ZERO;
   Static_u16SpeedReads       = INITIALIZED_WITH_ZERO;
}

void HGET_u8GetData(void  * Cpy_PtroParameter)
{
   uint8 Local_u8Temperature  = INITIALIZED_WITH_ZERO;
   uint8 Local_u8Speed        = INITIALIZED_WITH_ZERO;
   uint8 Local_u8TempAverage  = INITIALIZED_WITH_ZERO;
   uint8 Local_u8SpeedAverage = INITIALIZED_WITH_ZERO;
   if(NUMBER_OF_READS == Static_u8SWTimer)
   {
      // Get average value
      Local_u8TempAverage  = (Static_u16TemperatureReads) / (NUMBER_OF_READS);
      Local_u8SpeedAverage = (Static_u16SpeedReads)       / (NUMBER_OF_READS);
      // Write data into RTE
      // Write temperature value into RTE
      RTE_WRITE_TEMP_VAL(Local_u8TempAverage);
      RTE_WRITE_TEMP_VAL_FLAG(FLAG_SET);
      // Write speed value into RTE
      RTE_WRITE_SPEED(Local_u8SpeedAverage);
      RTE_WRITE_SPEED_FLAG(FLAG_SET);
      // Rests variables
      Static_u8SWTimer           = INITIALIZED_WITH_ZERO;
      Static_u16TemperatureReads = INITIALIZED_WITH_ZERO;
      Static_u16SpeedReads       = INITIALIZED_WITH_ZERO;
   }
   else
   {
      // Get data
      HSENSORS_u8ScanSensors(&Local_u8Temperature, &Local_u8Speed);
      Static_u16TemperatureReads += Local_u8Temperature;
      Static_u16SpeedReads       += Local_u8Speed;
      Static_u8SWTimer++;
   }
   (uint8*)Cpy_PtroParameter;
}
/*************** END OF FUNCTIONS ***************************************************************************/
