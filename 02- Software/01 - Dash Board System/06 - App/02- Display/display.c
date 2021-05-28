/*******************************************************************************
* Title                 :   DISPLAY 
* Filename              :   DISPLAY.c
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
/** @file DISPLAY_program.c
 *  @brief This is the source file for TODO: WHAT DO I DO? 
 */
/******************************************************************************
* Includes
*******************************************************************************/	
#include "Std_Types.h"
#include "BIT_MATH.h"
#include "Rte_DataTypes.h"
#include "Rte_DispalyPort.h"
#include "LCD.h"
#include "display.h"
#include "display_Cfg.h"
#include "display_Private.h"

/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/
#define INITIALIZED_WITH_ZERO  0
/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/

/******************************************************************************
* Module Typedefs
*******************************************************************************/

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/
uint8 Static_u8SpeedData = INITIALIZED_WITH_ZERO;
uint8 Static_u8TempData  = INITIALIZED_WITH_ZERO;
/******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************
* Function Definitions
*******************************************************************************/
Std_ReturnType HDISPLAY_u8InitializeModule(void)
{
   HLCD_u8SetCursor(0,0);
   HLCD_u8WriteString("Speed:");
   HLCD_u8SetCursor(0,9);
   HLCD_u8WriteString("KM");
   HLCD_u8SetCursor(1,0);
   HLCD_u8WriteString("Temperature:");
   HLCD_u8SetCursor(1,14);
   HLCD_u8WriteString("C");
   HLCD_u8SetCursor(2,0);
   HLCD_u8WriteString("Time:");
   HLCD_u8SetCursor(2,7);
   HLCD_u8WriteChar(':');
}

Std_ReturnType HDISPLAY_u8DisplayData(void)
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
   if(FLAG_SET == Local_u8SpeedFlagValue)
   {
      // Get data
      RTE_READ_SPEED(&Local_u8SpeedData);
      // Reset Flag
      RTE_WRITE_SPEED_FLAG(FLAG_NOT_SET);
      // Check if new data differ from old data, display it
      if(Local_u8SpeedData != Static_u8SpeedData)
      {
         HLCD_u8SetCursor(0,6);
         HLCD_u8WriteIntNum(Local_u8SpeedData);
      }
   }
   if(FLAG_SET == Local_u8TempFlagValue)
   {
      // Get data
      RTE_READ_TEMP_VAL(&Local_u8TempData);
      // Reset Flag
      RTE_WRITE_TEMP_VAL_FLAG(FLAG_NOT_SET);
      // Check if new data differ from old data, display it
      if(Local_u8TempData != Static_u8TempData)
      {
         HLCD_u8SetCursor(0,12);
         HLCD_u8WriteIntNum(Local_u8TempData);
      }
   }
   /*!<TODO: Time*/
} 


/*************** END OF FUNCTIONS ***************************************************************************/
