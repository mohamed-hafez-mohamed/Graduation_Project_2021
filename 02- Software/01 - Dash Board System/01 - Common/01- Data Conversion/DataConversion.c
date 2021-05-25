/*******************************************************************************
* Title                 :   DataConversion 
* Filename              :   DataConversion_program.c
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
/** @file DataConversion_program.c
 *  @brief This is the source file for TODO: WHAT DO I DO? 
 */
/******************************************************************************
* Includes
*******************************************************************************/	

#include "Std_Types.h"
#include "BIT_MATH.h"
#include "DataConversion.h"

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
void swap(sint16 * Copy_Ps16Num1, sint16 * Copy_Ps16Num2) 
{ 
   sint16 Local_Ps16Temp = *Copy_Ps16Num1; 
   *Copy_Ps16Num1 = *Copy_Ps16Num2; 
   *Copy_Ps16Num2 = Local_Ps16Temp; 
} 
/* A utility function to reverse a string  */
void reverse(uint8 Copy_u8String[], sint16 Copy_s16Length) 
{ 
   sint16 Local_s16Start = 0; 
   sint16 Local_s16End   = Copy_s16Length - 1; 
   while (Local_s16Start < Local_s16End) 
   { 
      swap(*(Copy_u8String + Local_s16Start), *(Copy_u8String + Local_s16End)); 
      Local_s16Start++; 
      Local_s16End--; 
   } 
} 

uint8 * itoa(sint16 Copy_s16Number, uint8 * Copy_u8String, sint16 Copy_s16Base)
{
   sint16  Local_s16Counter = 0;
   boolean Local_boolIsNegative = FALSE; 
  
   /* Handle 0 explicitely, otherwise empty string is printed for 0 */
   if (Copy_s16Number == 0) 
   { 
      Copy_u8String[Local_s16Counter++] = '0'; 
      Copy_u8String[Local_s16Counter] = '\0'; 
      return Copy_u8String; 
   } 
  
   // In standard itoa(), negative numbers are handled only with  
   // base 10. Otherwise numbers are considered unsigned. 
   if (Copy_s16Number < 0 && Copy_s16Base == 10) 
   { 
      Local_boolIsNegative = TRUE; 
      Copy_s16Number = -Copy_s16Number; 
   } 
  
   // Process individual digits 
   while (Copy_s16Number != 0) 
   { 
      sint16 Local_s16Reminder = Copy_s16Number % Copy_s16Base; 
      Copy_u8String[Local_s16Counter++] = (Local_s16Reminder > 9)? (Local_s16Reminder - 10) + 'a' : Local_s16Reminder + '0'; 
      Copy_s16Number = Copy_s16Number / Copy_s16Base; 
   } 
   // If number is negative, append '-' 
   if (Local_boolIsNegative) 
   {
      Copy_u8String[Local_s16Counter++] = '-';
   }
   Copy_u8String[Local_s16Counter] = '\0'; // Append string terminator 
   // Reverse the string 
   reverse(Copy_u8String, Local_s16Counter); 
   return Copy_u8String; 
}


/*************** END OF FUNCTIONS ***************************************************************************/
