/****************************************************************************
* Title                 :   ADC   
* Filename              :   ADC_config.h
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
/** @file  ADC_ADC_config.h
 *  @brief This module TODO: WHAT DO I DO?
 * 
 *  This is the header file for the definition TODO: MORE ABOUT ME!
 */
//TODO: UPDATE MACRO BELOW
#ifndef ADC_CONFIG_H_
#define ADC_CONFIG_H_

/******************************************************************************
* Includes
*******************************************************************************/
#include "Std_Types.h"
/******************************************************************************
* Preprocessor Constants
*******************************************************************************/

/******************************************************************************
* Configuration Constants
*******************************************************************************/

/******************************************************************************
* Typedefs
*******************************************************************************/

/**
* Defines two variables which specify the state of ADC.
*/
typedef enum 
{
   DISABLE_ADC = 0,                          /**<Disable ADC */
	ENABLE_ADC                                /**<Enable ADC */
}AdcState_t;

/**
* Defines two variables which specify the data alignment.
*/
typedef enum 
{
   RIGHT_ALIGNEMENT = 0,                          
	LEFT_ALIGNEMENT                           
}AdcDataAlignment_t;

/**
* Defines two variables which specify the calibration state.
*/
typedef enum 
{
   ENABLE_CALIBRATION = 1                                                   
}AdcCalibrationState_t;
typedef struct
{
	AdcState_t                        ModuleState;           /**<ADC State */
   AdcDataAlignment_t                DataAlignment;
   AdcCalibrationState_t             CalibrationState;
}AdcConfig_t;

/******************************************************************************
* Variables
*******************************************************************************/

// Configure ADC by choosing above variables.
static const AdcConfig_t Static_AdcConfig[NUMBER_OF_ADC_PERIPHERALS] =
{
//    ADC        Channel Squance     Sampling
//    State         Length             Time
//
   {ENABLE_ADC,  RIGHT_ALIGNEMENT, ENABLE_CALIBRATION},
   {DISABLE_ADC, RIGHT_ALIGNEMENT, ENABLE_CALIBRATION}
};

#endif /*File_H_*/

/*** End of File **************************************************************/
