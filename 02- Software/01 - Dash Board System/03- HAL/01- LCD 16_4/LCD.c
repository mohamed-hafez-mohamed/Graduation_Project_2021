/*******************************************************************************
* Title                 :   LCD 
* Filename              :   LCD_program.c
* Author                :   Mohamed Hafez
* Origin Date           :   22/09/2020
* Version               :   1.0.0
* Compiler              :   TODO: COMPILER GOES HERE
* Target                :   TODO: MCU GOES HERE
* Notes                 :   None 
*
*****************************************************************************/
/*************** SOURCE REVISION LOG *****************************************
*
*    Date    Version   Author          Description 
*  22/09/20   1.0.0   Mohamed Hafez   Initial Release.
*
*******************************************************************************/
/** @file LCD_program.c
 *  @brief This is the source file for TODO: WHAT DO I DO? 
 */
/******************************************************************************
* Includes
*******************************************************************************/	

#include <stdlib.h>
#include <stdio.h>
#include "Std_Types.h"
#include "BIT_MATH.h"
#include "GPIO_interface.h"
#include "TMR_Interface.h"
#include "LCD.h"
#include "LCD_Cfg.h"
#include "LCD_Private.h"

/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/
#if   LCD_MODE == LCD_4_BIT_MODE
   #define LCD_DATA_PINS          4
#elif LCD_MODE == LCD_8_BIT_MODE
   #define LCD_DATA_PINS          8
#endif

#if   LCD_DATA_PINS == 4
   static uint8 Static_u8DataPins[LCD_DATA_PINS] = {LCD_D4,LCD_D5,LCD_D6,LCD_D7};
#elif LCD_DATA_PINS == 4
   static uint8 Static_u8DataPins[LCD_DATA_PINS] = {LCD_D0,LCD_D1,LCD_D2,LCD_D3,LCD_D4,LCD_D5,LCD_D6,LCD_D7};
#endif

#define LCD_COL_16        16
#define LCD_COL_32        32
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
static void HLCD_voidkick(uint8 Copy_u8Character)
{
   /**
	* Assign Data on the pins of the confg
	* Make pulse to make lcd working
	**/
	for(uint8 Local_u8Counter = 0;Local_u8Counter < LCD_DATA_PINS;Local_u8Counter++)
	{
		if(Copy_u8Character & (SET << Local_u8Counter))
		{
         MGPIO_u8SetPinValue(Static_u8DataPins[Local_u8Counter], HIGH);
		}
		else
		{
         MGPIO_u8SetPinValue(Static_u8DataPins[Local_u8Counter], LOW);
		}
	}
   MGPIO_u8SetPinValue(LCD_EN, HIGH);
   TMR_voidSetBusyWait(TIM3, 20);
   MGPIO_u8SetPinValue(LCD_EN, LOW);
   TMR_voidSetBusyWait(TIM3, 20);
}

Std_ReturnType HLCD_u8Init(void)
{
   /**
	* Config the lcd to start working
	**/
   #if   LCD_MODE == LCD_4_BIT_MODE
   HLCD_u8CMD(LCD_4BIT_MODE_CMD);
   HLCD_u8CMD(LCD_4BIT_MODE_2_LINE_CMD);
   #elif LCD_MODE == LCD_8_BIT_MODE
   HLCD_u8CMD(LCD_8BIT_MODE_2_LINE_CMD);
   #endif 
   HLCD_u8SetCursor(0, 0);
   HLCD_u8CMD(LCD_ENTRY_MODE_CMD);
   HLCD_u8CMD(LCD_CURSOR_OFF_CMD);
   HLCD_u8CMD(LCD_CLEAR_SCREEN_CMD);
}

Std_ReturnType HLCD_u8CMD(uint8 Copy_u8Command)
{
   /**
	* Select the register "command || data " in this case command
	* Sent the command
	**/
   MGPIO_u8SetPinValue(LCD_RS, LOW);
   #if   LCD_MODE == LCD_4_BIT_MODE
   HLCD_voidkick((Copy_u8Command) >> 4);
   HLCD_voidkick(Copy_u8Command);
   #elif LCD_MODE == LCD_8_BIT_MODE
   HLCD_voidkick(Copy_u8Command);
   #endif 
   TMR_voidSetBusyWait(TIM3, 2000);
}

Std_ReturnType HLCD_u8SetCursor(uint8 Copy_u8Row, uint8 Copy_u8Col)
{
   switch(Copy_u8Row)
   {
      case 0 :
         HLCD_u8CMD((unsigned)(LCD_BEGIN_AT_FIRST_RAW_CMD  | Copy_u8Col));
      break;
      case 1 :
         HLCD_u8CMD((unsigned)(LCD_BEGIN_AT_SECOND_RAW_CMD | Copy_u8Col));
      break;
      #if LCD_TYPE == LCD_16_4
      case 2 :
         HLCD_u8CMD((unsigned)(LCD_BEGIN_AT_THIRD_RAW_CMD  | Copy_u8Col));
      break;
      case 3 :
         HLCD_u8CMD((unsigned)(LCD_BEGIN_AT_FOURTH_RAW_CMD | Copy_u8Col));
      break;
      #endif
   }
}

Std_ReturnType HLCD_u8ClearSreen(void)
{
   HLCD_u8CMD(LCD_CLEAR_SCREEN_CMD);
}

Std_ReturnType HLCD_u8ClearPiexels(uint8 Cpy_ROW, uint8 Cpy_Initial, uint8 Cpy_End)
{
   for(uint8 Local_PixelCounter = Cpy_Initial;Local_PixelCounter <= Cpy_End;Local_PixelCounter++)
   {
      HLCD_u8SetCursor(Cpy_ROW, Local_PixelCounter);
      HLCD_u8WriteChar(' ');
   }
}

Std_ReturnType HLCD_u8TurnOffDisplay(void)
{
   HLCD_u8CMD(LCD_DISPLAY_OFF_CMD);
}

Std_ReturnType HLCD_u8WriteChar(uint8 Copy_u8Character)
{
   MGPIO_u8SetPinValue(LCD_RS, HIGH);
   #if   LCD_MODE == LCD_4_BIT_MODE
   HLCD_voidkick((Copy_u8Character) >> 4);
   HLCD_voidkick(Copy_u8Character);
   #elif LCD_MODE == LCD_8_BIT_MODE
   HLCD_voidkick(Copy_u8Character);
   #endif 
   TMR_voidSetBusyWait(TIM3, 2000);
}

Std_ReturnType HLCD_u8WriteString(uint8 * Copy_u8String)
{
   uint8 Local_u8Counter = 0;
   while(Copy_u8String[Local_u8Counter] != '\0')
   {
      HLCD_u8WriteChar(Copy_u8String[Local_u8Counter]);
      Local_u8Counter++;
      if(Local_u8Counter == LCD_COL_16)
      {
         HLCD_u8SetCursor(1, 0);
      }
      else if(Local_u8Counter == LCD_COL_32)
      {
         HLCD_u8ClearSreen();
         HLCD_u8SetCursor(1, 0);
         Local_u8Counter = 0;
      }
   }
}

Std_ReturnType HLCD_u8WriteIntNum(uint8 Copy_u8Number)
{
   uint8 * Local_u8Buffer[16];
   sprintf(Local_u8Buffer, "%d", Copy_u8Number);
   HLCD_u8WriteString(Local_u8Buffer);
}

Std_ReturnType HLCD_u8WriteFloatNum(float32 Copy_floatNumber)
{
   uint8 *  Local_u8Buffer[16];
   uint8 *  Local_u8Sign     = (Copy_floatNumber < 0)? '-' : '+';                              //Get sign
   float32  Local_floatNum   = (Copy_floatNumber < 0)? -Copy_floatNumber : Copy_floatNumber;   //store the sent number
   uint16   Local_u8IntPart  = Local_floatNum;                                                 //Get the first integer part before the point
   float32  Local_floatPart  = Local_floatNum - Local_u8IntPart;                               //Get fraction
   uint8    Local_u8FracPart = Local_floatPart * LCD_NUMBER_TYPE_AFTER_POINT;                  //Turn into fraction into integer value
   // Print as parts
	sprintf(Local_u8Buffer, "%s%d.%2d", Local_u8Sign, Local_u8IntPart, Local_u8FracPart);
   HLCD_u8WriteString(Local_u8Buffer);
}

/*************** END OF FUNCTIONS ***************************************************************************/
