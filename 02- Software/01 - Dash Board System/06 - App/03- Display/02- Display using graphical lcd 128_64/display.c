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
#include "Rte_DisplayPort.h"
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
static uint8 Static_u8SpeedData;
static uint8 Static_u8TempData;
static uint8 Static_u8TimeBuffer[RTC_YEAR_INDEX + 1];
/******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************
* Function Definitions
*******************************************************************************/
void HDISPLAY_u8InitializeModule(void)
{
   // Initialize variable
   Static_u8SpeedData   = INITIALIZED_WITH_ZERO;
   Static_u8TempData    = INITIALIZED_WITH_ZERO;
   
   HLCD_u8SetCursor(TEMPERATURE_ROW, TEMPERATURE_WORD_COLUMN);
   HLCD_u8WriteString("T:");
   HLCD_u8SetCursor(TEMPERATURE_ROW, TEMPERATURE_DISCRIMINATION_UNIT_COLUMN);
   HLCD_u8WriteString("C");
   HLCD_u8SetCursor(SPEED_ROW, SPEED_WORD_COLUMN);
   HLCD_u8WriteString("S:");
   HLCD_u8SetCursor(SPEED_ROW, SPEED_DISCRIMINATION_UNIT_COLUMN);
   HLCD_u8WriteString("KM");
   HLCD_u8SetCursor(TIME_ROW, TIME_WORD_COLUMN);
   HLCD_u8WriteString("Ti:");
   HLCD_u8SetCursor(TIME_ROW, FIRST_COLON);
   HLCD_u8WriteChar(':');
}

void HDISPLAY_u8DisplayData(void * Cpy_PtroParameter)
{
   // Variable definitions
   FlagType Local_u8SpeedFlagValue = FLAG_NOT_SET;
   FlagType Local_u8TempFlagValue  = FLAG_NOT_SET;
   FlagType Local_u8TimeFlagValue  = FLAG_NOT_SET;
   uint8    Local_u8SpeedData      = INITIALIZED_WITH_ZERO;
   uint8    Local_u8TempData       = INITIALIZED_WITH_ZERO;
   uint8    *Local_u8TimeBuffer    = NULL_PTR;
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
      // Check if new data differ from old data, display it
      if(Local_u8TempData != Static_u8TempData)
      {
         // Store new temperature value
         Static_u8TempData = Local_u8TempData;
         // Clear old value
         HLCD_u8ClearPiexels(TEMPERATURE_ROW, TEMPERATURE_VALUE_COLUMN, TEMPERATURE_END_VALUE_COLUMN);
         // Display temperature value
         HLCD_u8SetCursor(TEMPERATURE_ROW, TEMPERATURE_VALUE_COLUMN);
         HLCD_u8WriteIntNum(Local_u8TempData);
      }
   }
   if(FLAG_SET == Local_u8SpeedFlagValue)
   {
      // Get data
      RTE_READ_SPEED(&Local_u8SpeedData);
      // Reset Flag
      RTE_WRITE_SPEED_FLAG(FLAG_NOT_SET);
      // Check if new data differ from old data, display it
      if(Local_u8SpeedData != Static_u8SpeedData)
      {
         // Store new speed value
         Static_u8SpeedData = Local_u8SpeedData;
         // Clear old value
         HLCD_u8ClearPiexels(SPEED_ROW, SPEED_VALUE_COLUMN, END_OF_SPEED_VALUE_COLUMN);
         // Display speed value
         HLCD_u8SetCursor(SPEED_ROW, SPEED_VALUE_COLUMN);
         HLCD_u8WriteIntNum(Local_u8SpeedData);
      }
   }
   if(FLAG_SET == Local_u8TimeFlagValue)
   {
      // Consume Data
      RTE_READ_TIME_PTR(&Local_u8TimeBuffer);
      // Reset Flag
      RTE_WRITE_TIME_PTR_FLAG(FLAG_NOT_SET);
      // Check if new data differ from old data, display it
      // check minutes
      if(Local_u8TimeBuffer[RTC_MINUTES_INDEX] != Static_u8TimeBuffer[RTC_MINUTES_INDEX])
      {
         // Store new minutes value
         Static_u8TimeBuffer[RTC_MINUTES_INDEX] = Local_u8TimeBuffer[RTC_MINUTES_INDEX];
         // Clear old value
         HLCD_u8ClearPiexels(TIME_ROW, MINUTES_COLUMN, MINUTES_END_COLUMN);
         // Display minutes value
         HLCD_u8SetCursor(TIME_ROW, MINUTES_COLUMN);
         HLCD_u8WriteIntNum(Local_u8TimeBuffer[RTC_MINUTES_INDEX]);
      }
      // check hours
      if(Local_u8TimeBuffer[RTC_HOURS_INDEX] != Static_u8TimeBuffer[RTC_HOURS_INDEX])
      {
         // Store new hours value
         Static_u8TimeBuffer[RTC_HOURS_INDEX] = Local_u8TimeBuffer[RTC_HOURS_INDEX];
         // Clear old value
         HLCD_u8ClearPiexels(TIME_ROW, HOURS_COLUMN, HOURS_END_COLUMN);
         // Display hours value
         HLCD_u8SetCursor(TIME_ROW, HOURS_COLUMN);
         HLCD_u8WriteIntNum(Local_u8TimeBuffer[RTC_HOURS_INDEX]);
      }
   }
   (uint8*)Cpy_PtroParameter;
} 


/*************** END OF FUNCTIONS ***************************************************************************/
