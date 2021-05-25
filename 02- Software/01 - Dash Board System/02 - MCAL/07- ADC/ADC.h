/****************************************************************************
* Title                 :   ADC   
* Filename              :   ADC_interface.h
* Author                :   Mohamed Hafez
* Origin Date           :   3/10/2020
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
*  3/10/20   1.0.0   Mohamed Hafez   Interface Created.
*
*****************************************************************************/
/** @file  ADC_interface.h
 *  @brief This module TODO: WHAT DO I DO?
 * 
 *  This is the header file for the definition TODO: MORE ABOUT ME!
 */
//TODO: UPDATE MACRO BELOW
#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

/******************************************************************************
* Includes
*******************************************************************************/
#include "Std_Types.h"
/******************************************************************************
* Preprocessor Constants
*******************************************************************************/
#define CHANNEL_0  PINA0
#define CHANNEL_1  PINA1
#define CHANNEL_2  PINA2
#define CHANNEL_3  PINA3
#define CHANNEL_4  PINA4
#define CHANNEL_5  PINA5
#define CHANNEL_6  PINA6
#define CHANNEL_7  PINA7
#define CHANNEL_8  PINB0
#define CHANNEL_9  PINB1
/******************************************************************************
* Configuration Constants
*******************************************************************************/
// Configure Pin as analog pin
 //  MGPIO_u8SetPinMode(Static_u8Channels[Copy_u8Channel], AFIO_INPUT_ANALOG);
/******************************************************************************
* Macros
*******************************************************************************/
	
/******************************************************************************
* Typedefs
*******************************************************************************/
/**
* Defines two variables which specify the uart.
*/
typedef enum
{
   ADC1,                          /**<Adc 1*/
   ADC2,                          /**<Adc 2*/
   NUMBER_OF_ADC_PERIPHERALS      /**<ADCs on the microcontroller*/
}AdcPeripherals_t;

/**
* Defines how many channels per adc.
*/
typedef enum
{
   CHANNEL0,
   CHANNEL1,
   CHANNEL2,
   CHANNEL3,
   CHANNEL4,
   CHANNEL5,
   CHANNEL6,
   CHANNEL7,
   CHANNEL8,
   CHANNEL9,
   CHANNEL10,
   CHANNEL11,
   CHANNEL12,
   CHANNEL13,
   CHANNEL14,
   CHANNEL15,
   CHANNEL16,
   CHANNEL17
}AdcChannels_t;

/**
* Defines Channel x Sample time selection.
*/
typedef enum
{
	SINGLE_CONVERSION = 0, 
   CONTINUOUS_CONVERSION,      
   SCAN_SINGLE_CONVERSION,   
   SCAN_CONTINUOUS_CONVERSION,  
   DISCONTINUOUS_CONVERSION   
   
}AdcConversionMode_t;

/**
* Defines Channel x Sample time selection.
*/
typedef enum
{
	FIRST_ORDER      = 0, 
   SECOND_ORDER     = 5,
   THIRD_ORDER      = 10,
   FOURTH_ORDER     = 15,
   FIFTH_ORDER      = 20,
   SIXTH_ORDER      = 25,
   SEVENTH_ORDER    = 0, 
   EIGHTH_ORDER     = 5,
   NINTH_ORDER      = 10,
   TENTH_ORDER      = 15,
   ELEVETH_ORDER    = 20,
   TWELVETH_ORDER   = 25,
   THIRTEENTH_ORDER = 0,
   FOURTEENTH_ORDER = 5,
   FIFTEENTH_ORDER  = 10,
   SIXTEEN_ORDER    = 15
}AdcChannelOrder_t;

/**
* Defines Channel x Sample time selection.
*/
typedef enum
{
	_1_AND_HALF_CYCLE = 0, 
   _7_AND_HALF_CYCLE,
   _13_AND_HALF_CYCLE,
   _28_AND_HALF_CYCLE,
   _41_AND_HALF_CYCLE,
   _55_AND_HALF_CYCLE,
   _71_AND_HALF_CYCLE, 
   _239_AND_HALF_CYCLE                             
}AdcSampleTime_t;

typedef void (*PtrToFunction)(uint16 Copy_u16Parameter);
/******************************************************************************
* Variables
*******************************************************************************/

/******************************************************************************
* Function Prototypes
*******************************************************************************/

Std_ReturnType MADC_u8InitializeAdc(void);

Std_ReturnType MADC_u8SetConversionMode(AdcPeripherals_t Cpy_PeripheralNumber, AdcConversionMode_t Cpy_Mode,
                                        uint8 Cpy_u8NumberOfConversions);

Std_ReturnType MADC_u8SetRegularChannelOrder(AdcPeripherals_t Cpy_PeripheralNumber,AdcChannels_t Cpy_u8Channel,
                                      AdcChannelOrder_t Cpy_u8ConvertionOrder);

Std_ReturnType MADC_u8SetSamplingTime(AdcPeripherals_t Cpy_PeripheralNumber,AdcChannels_t Cpy_u8Channel,
                                      AdcSampleTime_t Cpy_u8SamplingTime);

Std_ReturnType MADC_u8ReadResultBlocking(AdcPeripherals_t Cpy_PeripheralNumber, uint16 * Cpy_u16Result);
Std_ReturnType MADC_u8ReadResultNonBlocking(AdcPeripherals_t Cpy_PeripheralNumber, uint16 * Cpy_u16Result);
Std_ReturnType MADC_u8ReadResultAsynch(AdcPeripherals_t Cpy_PeripheralNumber, PtrToFunction CallBack);
#endif /*File_H_*/

/*** End of File **************************************************************/
