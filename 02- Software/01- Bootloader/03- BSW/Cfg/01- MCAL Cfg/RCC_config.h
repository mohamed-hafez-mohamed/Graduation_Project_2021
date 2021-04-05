/****************************************************************************
* Title                 :   RCC   
* Filename              :   RCC_config.h
* Author                :   Mohamed Hafez
* Origin Date           :   10/08/2020
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
*  10/8/20   1.0.0   Mohamed Hafez   Interface Created.
*
*****************************************************************************/
/** @file  RCC_config.h
 *  @brief This module TODO: WHAT DO I DO?
 * 
 *  This is the header file for the definition TODO: MORE ABOUT ME!
 */
//TODO: UPDATE MACRO BELOW
#ifndef RCC_CONFIG_H_
#define RCC_CONFIG_H_

/******************************************************************************
* Includes
*******************************************************************************/

/******************************************************************************
* Preprocessor Constants
*******************************************************************************/

/******************************************************************************
* Configuration Constants
*******************************************************************************/

/* 
Clock Source Options:
RCC_HSI           Select High Speed Internal RC  as clock source for processor.
RCC_HSE_CRYSTAL   Select High Speed External Oci as clock source for processor.
RCC_HSE_RC        Select High Speed External RC  as clock source for processor.
RCC_PLL           Select Phase Locked Loop       as clock source for processor.   
*/
#define RCC_CLOCK_TYPE    RCC_HSI


/* 
//PLL Input Options:
RCC_PLL_IN_HSI_DIV_2        Select HSI/2 as input to PLL.
RCC_PLL_IN_HSE_DIV_2        Select HSE/2 as input to PLL.  
RCC_PLL_IN_HSE              Select HSE   as input to PLL.
//HSE from crystal or RC
RCC_PLL_HSE_CRYSTAL       Select Crystal as input to PLL.         
RCC_PLL_HSE_RC            Select RC as input to PLL.  
//  PLL MULL Ortions
RCC_PLLMULL2                PLL input clock x 2  
RCC_PLLMULL3                PLL input clock x 3 
RCC_PLLMULL4                PLL input clock x 4   
RCC_PLLMULL5                PLL input clock x 5   
RCC_PLLMULL6                PLL input clock x 6   
RCC_PLLMULL7                PLL input clock x 7   
RCC_PLLMULL8                PLL input clock x 8  
RCC_PLLMULL9                PLL input clock x 9  
RCC_PLLMULL10               PLL input clock x 10   
RCC_PLLMULL11               PLL input clock x 11  
RCC_PLLMULL12               PLL input clock x 12  
RCC_PLLMULL13               PLL input clock x 13   
RCC_PLLMULL14               PLL input clock x 14  
RCC_PLLMULL15               PLL input clock x 15  
RCC_PLLMULL16               PLL input clock x 16
*/
#if RCC_CLOCK_TYPE == RCC_PLL 
   #define RCC_PLL_INPUT     RCC_PLL_IN_HSI_DIV_2 
   #if RCC_PLL_INPUT == RCC_PLL_IN_HSE
      #define RCC_PLL_HSE       RCC_PLL_HSE_CRYSTAL
   #endif
   #define RCC_PLL_MUL_VAL   RCC_PLLMULL2
#endif

/*
//AHB Prescalar Otions
RCC_HPRE_DIV1
RCC_HPRE_DIV2
RCC_HPRE_DIV4
RCC_HPRE_DIV8
RCC_HPRE_DIV16
RCC_HPRE_DIV64
RCC_HPRE_DIV128
RCC_HPRE_DIV256
RCC_HPRE_DIV512
*/
#define RCC_HPRE_DIV_VAL   RCC_HPRE_DIV1

/*
//APB1 Prescalar Otions
RCC_PPRE1_DIV1
RCC_PPRE1_DIV2
RCC_PPRE1_DIV4
RCC_PPRE1_DIV8
RCC_PPRE1_DIV16
*/
#define RCC_PPRE1_DIV_VAL   RCC_PPRE1_DIV1

/*
//APB2 Prescalar Otions
RCC_PPRE2_DIV1
RCC_PPRE2_DIV2
RCC_PPRE2_DIV4
RCC_PPRE2_DIV8
RCC_PPRE2_DIV16
*/
#define RCC_PPRE2_DIV_VAL   RCC_PPRE2_DIV1

/***************************************************
//ADC Prescalar Otions
RCC_ADCPRE_DIV2
RCC_ADCPRE_DIV4
RCC_ADCPRE_DIV6
RCC_ADCPRE_DIV8
***************************************************/
#define RCC_ADCPRE_DIV_VAL   RCC_ADCPRE_DIV2

/****************************************************
//MCO Options
RCC_MCO_NO_CLK                   
RCC_MCO_SYS_CLK                  
RCC_MCO_HSI_CLK                  
RCC_MCO_HSE_CLK                  
RCC_MCO_PLL_DVID2_CLK            
****************************************************/
#define RCC_MCO_CLK         RCC_MCO_NO_CLK
//TODO: UPDATE COMMENT BELOW
#endif /*File_H_*/

/*** End of File **************************************************************/
