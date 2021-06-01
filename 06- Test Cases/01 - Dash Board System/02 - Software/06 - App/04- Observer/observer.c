/*******************************************************************************
* Title                 :   OBSERVER 
* Filename              :   OBSERVER.c
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
/** @file OBSERVER.c
 *  @brief This is the source file for TODO: WHAT DO I DO? 
 */
/******************************************************************************
* Includes
*******************************************************************************/	

#include "Std_Types.h"
#include "BIT_MATH.h"
#include "Rte_DataTypes.h"
#include "Rte_DataTypes.h"
#include "Rte_ObserverPort.h"
#include "observer_Cfg.h"
#include "observer_Private.h"
#include "observer.h"

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
Std_ReturnType HOBSERVER_u8InitializeModule(void)
{

}

Std_ReturnType HOBSERVER_u8ObserveSystem(void)
{
   // Variable definitions
   FlagType Local_u8SpeedFlagValue = FLAG_NOT_SET;
   FlagType Local_u8TempFlagValue  = FLAG_NOT_SET;
   FlagType Local_u8TimeFlagValue  = FLAG_NOT_SET;
   uint8    Local_u8SpeedData      = INITIALIZED_WITH_ZERO;
   uint8    Local_u8TempData       = INITIALIZED_WITH_ZERO;
   // Read flag values
   RTE_READ_SPEED_FLAG(&Local_u8SpeedFlagValue);
   RTE_READ_TEMP_VAL_FLAG(&Local_u8TempFlagValue);
   RTE_READ_TIME_PTR_FLAG(&Local_u8TimeFlagValue);
   // Check each flag value
   if(FLAG_SET == Local_u8TempFlagValue)
   {
      // Get data
      RTE_READ_TEMP_VAL(&Local_u8TempData);
      // Reset Flag
      RTE_WRITE_TEMP_VAL_FLAG(FLAG_NOT_SET);
      // Check temperature value
      if(Local_u8TempData > MAXIMUM_TEMPERATURE)
      {
         /*!<TODO:Take certain Action*/
      }
   }
   if(FLAG_SET == Local_u8SpeedFlagValue)
   {
      // Get data
      RTE_READ_SPEED(&Local_u8SpeedData);
      // Reset Flag
      RTE_WRITE_SPEED_FLAG(FLAG_NOT_SET);
      // Check speed value
      if(Local_u8SpeedData > MAXIMUM_SPEED)
      {
         /*!<TODO:Take certain Action*/
      }
   }
}
/*************** END OF FUNCTIONS ***************************************************************************/
