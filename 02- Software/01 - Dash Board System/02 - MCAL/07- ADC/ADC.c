/*******************************************************************************
* Title                 :   ADC 
* Filename              :   ADC_program.c
* Author                :   Mohamed Hafez
* Origin Date           :   3/10/2020
* Version               :   1.0.0
* Compiler              :   TODO: COMPILER GOES HERE
* Target                :   TODO: MCU GOES HERE
* Notes                 :   None 
*
*****************************************************************************/
/*************** SOURCE REVISION LOG *****************************************
*
*    Date    Version   Author          Description 
*  04/08/20   1.0.0   Mohamed Hafez   Initial Release.
*
*******************************************************************************/
/** @file ADC_program.c
 *  @brief This is the source file for TODO: WHAT DO I DO? 
 */
/******************************************************************************
* Includes
*******************************************************************************/	

#include "Std_Types.h"
#include "BIT_MATH.h"

#include "ADC.h"
#include "ADC_Cfg.h"
#include "ADC_Private.h"

/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/
#define WAIT_FOR_CONVERSION (GET_BIT(AdcChannel[Cpy_PeripheralNumber]->SR, EOC) == FLAG_NOT_SET)
/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/

/******************************************************************************
* Module Typedefs
*******************************************************************************/

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/
PtrToFunction CallBackFunction;
/******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************
* Function Definitions
*******************************************************************************/

Std_ReturnType MADC_u8InitializeAdc(void)
{
   // Configure adc that enabled by user.
	// Loop on adcs to find which enabled.
	for(uint8 Local_u8AdcNumber = ADC1;Local_u8AdcNumber < NUMBER_OF_ADC_PERIPHERALS;Local_u8AdcNumber++)
	{
		if(Static_AdcConfig[Local_u8AdcNumber].ModuleState == ENABLE_ADC)
		{
			// Clear registers
         AdcChannel[Local_u8AdcNumber]->CR1   = CLR_REGISTER;
         AdcChannel[Local_u8AdcNumber]->CR2   = CLR_REGISTER;
         AdcChannel[Local_u8AdcNumber]->SMPR1 = CLR_REGISTER;
         AdcChannel[Local_u8AdcNumber]->SMPR2 = CLR_REGISTER;
         AdcChannel[Local_u8AdcNumber]->SQR1  = CLR_REGISTER;
         AdcChannel[Local_u8AdcNumber]->SQR2  = CLR_REGISTER;
         AdcChannel[Local_u8AdcNumber]->SQR3  = CLR_REGISTER;
         // Configurations
         // Specify Regular channel sequence length
         AdcChannel[Local_u8AdcNumber]->SQR1 |= ((Static_AdcConfig[Local_u8AdcNumber].NumberOfChannels) << L0);
         // Specify Data Alignment
         AdcChannel[Local_u8AdcNumber]->CR2  |= ((Static_AdcConfig[Local_u8AdcNumber].DataAlignment) << ALIGN);
         // Specify Calibration
         AdcChannel[Local_u8AdcNumber]->CR2  |= ((Static_AdcConfig[Local_u8AdcNumber].CalibrationState) << CAL);
         // Turn on Adc
         SET_BIT(AdcChannel[Local_u8AdcNumber]->CR2, ADON);
		}
	} 
}

Std_ReturnType MADC_u8SetConversionMode(AdcPeripherals_t Cpy_PeripheralNumber, AdcConversionMode_t Cpy_Mode,
                                        uint8 Cpy_u8NumberOfConversions)
{
   switch(Cpy_Mode)
   {
      case SINGLE_CONVERSION          :
         // Apply Single conversion Mode
         CLR_BIT(AdcChannel[Cpy_PeripheralNumber]->CR2, CONT);
         // Just for removing warning.
         (uint8)Cpy_u8NumberOfConversions;
      break;
      case CONTINUOUS_CONVERSION      :
         // Apply continuous conversion Mode
         SET_BIT(AdcChannel[Cpy_PeripheralNumber]->CR2, CONT);
         (uint8)Cpy_u8NumberOfConversions;
      break;
      case SCAN_SINGLE_CONVERSION     :
         // Apply scan single conversion Mode
         CLR_BIT(AdcChannel[Cpy_PeripheralNumber]->CR2, CONT);
         SET_BIT(AdcChannel[Cpy_PeripheralNumber]->CR1, SCAN);
         SET_BIT(AdcChannel[Cpy_PeripheralNumber]->CR2, DMA); 
         (uint8)Cpy_u8NumberOfConversions;
      break;
      case SCAN_CONTINUOUS_CONVERSION :
         // Apply scan continuous conversion Mode
         SET_BIT(AdcChannel[Cpy_PeripheralNumber]->CR2, CONT);
         SET_BIT(AdcChannel[Cpy_PeripheralNumber]->CR1, SCAN);
         SET_BIT(AdcChannel[Cpy_PeripheralNumber]->CR2, DMA);
         (uint8)Cpy_u8NumberOfConversions;
      break;
      case DISCONTINUOUS_CONVERSION   :
      // Apply scan discontinuous conversion Mode
         SET_BIT(AdcChannel[Cpy_PeripheralNumber]->CR1, DISCEN);
         AdcChannel[Cpy_PeripheralNumber]->CR1 |= (Cpy_u8NumberOfConversions << DISCNUM0);
      break;
   }
}

Std_ReturnType MADC_u8SetRegularChannelOrder(AdcPeripherals_t Cpy_PeripheralNumber,AdcChannels_t Cpy_u8Channel,
                                      AdcChannelOrder_t Cpy_u8ConvertionOrder)
{
   
   if(Cpy_u8Channel <= END_OF_SQR3)
   {
      AdcChannel[Cpy_PeripheralNumber]->SQR3 |= (Cpy_u8Channel) << (Cpy_u8ConvertionOrder);
   }
   else if(Cpy_u8Channel <= END_OF_SQR2)
   {
      AdcChannel[Cpy_PeripheralNumber]->SQR2 |= (Cpy_u8Channel) << (Cpy_u8ConvertionOrder);
   }
   else if(Cpy_u8Channel <= END_OF_SQR1)
   {
      AdcChannel[Cpy_PeripheralNumber]->SQR1 |= (Cpy_u8Channel) << (Cpy_u8ConvertionOrder);
   }
   else
   {
      /*!<TODO: Handle error*/
   }
}

Std_ReturnType MADC_u8SetSamplingTime(AdcPeripherals_t Cpy_PeripheralNumber,AdcChannels_t Cpy_u8Channel,
                                      AdcSampleTime_t Cpy_u8SamplingTime)
{
   if(Cpy_u8Channel <= END_OF_SMPR2)
   {
      AdcChannel[Cpy_PeripheralNumber]->SMPR2 |= (Cpy_u8Channel * OFFSET) << (Cpy_u8SamplingTime);
   }
   else if(Cpy_u8Channel <= END_OF_SMPR1)
   {
      Cpy_u8Channel -= ADJUST_CHANNEL;
      AdcChannel[Cpy_PeripheralNumber]->SMPR1 |= (Cpy_u8Channel * OFFSET) << (Cpy_u8SamplingTime);
   }
   else
   {
      /*!<TODO: Handle error*/
   }
}

Std_ReturnType MADC_u8ReadResultBlocking(AdcPeripherals_t Cpy_PeripheralNumber, uint16 * Cpy_u16Result)
{
   // Start Conversion
   SET_BIT(AdcChannel[Cpy_PeripheralNumber]->CR2, ADON);
   SET_BIT(AdcChannel[Cpy_PeripheralNumber]->CR2, SWSTART);
   // Wait conversion
   while(WAIT_FOR_CONVERSION);
   // Get Data
   *Cpy_u16Result = ((AdcChannel[Cpy_PeripheralNumber]->DR) & GET_RIGHT_ALIGNED_DATA);
   // Clear flag
   CLR_BIT(AdcChannel[Cpy_PeripheralNumber]->SR, EOC);
}

Std_ReturnType MADC_u8ReadResultNonBlocking(AdcPeripherals_t Cpy_PeripheralNumber, uint16 * Cpy_u16Result)
{
   // Start Conversion
   SET_BIT(AdcChannel[Cpy_PeripheralNumber]->CR2, ADON);
   SET_BIT(AdcChannel[Cpy_PeripheralNumber]->CR2, SWSTART);
   if(GET_BIT(AdcChannel[Cpy_PeripheralNumber]->SR, EOC) == FLAG_SET)
   {
      // Get Data
      *Cpy_u16Result = ((AdcChannel[Cpy_PeripheralNumber]->DR) & GET_RIGHT_ALIGNED_DATA);
      // Clear flag
      CLR_BIT(AdcChannel[Cpy_PeripheralNumber]->SR, EOC);
   }
}
Std_ReturnType MADC_u8ReadDigitalAsynch(AdcPeripherals_t Cpy_PeripheralNumber, PtrToFunction CallBack)
{
   CallBackFunction = CallBack;
   SET_BIT(AdcChannel[Cpy_PeripheralNumber]->CR1, EOCIE);
   SET_BIT(AdcChannel[Cpy_PeripheralNumber]->CR2, ADON);
   SET_BIT(AdcChannel[Cpy_PeripheralNumber]->CR2, SWSTART);
}

void ADC1_2_IRQHandler(void)
{
   CallBackFunction((AdcChannel[0]->DR) & GET_RIGHT_ALIGNED_DATA);
   CLR_BIT(AdcChannel[0]->SR, EOC);
}


/*************** END OF FUNCTIONS ***************************************************************************/
