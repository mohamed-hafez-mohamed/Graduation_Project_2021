/****************************************************************************
* Title                 :   RCC   
* Filename              :   RCC_interface.h
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
/** @file  RCC_interface.h
 *  @brief This module TODO: WHAT DO I DO?
 * 
 *  This is the header file for the definition TODO: MORE ABOUT ME!
 */
//TODO: UPDATE MACRO BELOW
#ifndef RCC_INTERFACE_H_
#define RCC_INTERFACE_H_

/******************************************************************************
* Includes
*******************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
/******************************************************************************
* Preprocessor Constants
*******************************************************************************/
/*!<Bus Type*/
#define   RCC_AHB   0         //Select Advanced High Performance Bus
#define   RCC_APB1  1         //Select Advanced Performance Bus number 1
#define   RCC_APB2  2         //Select Advanced Performance Bus number 2

/*!<Peripheral Type*/
//periphera id bits for AHP
#define DMA1_PERIPHERAL     0
#define DMA2_PERIPHERAL     1
#define SRAM_PERIPHERAL     2
#define FLITF_PERIPHERAL    4
#define CRCE_PERIPHERAL     6
#define FSMC_PERIPHERAL     8
#define SDIO_PERIPHERAL     10

//periphera id bits for APB2
#define AFIO_PERIPHERAL     0
#define IOPA_PERIPHERAL     2
#define IOPB_PERIPHERAL     3
#define IOPC_PERIPHERAL     4
#define IOPD_PERIPHERAL     5
#define IOPE_PERIPHERAL     6
#define IOPF_PERIPHERAL     7  
#define IOPG_PERIPHERAL     8
#define ADC1_PERIPHERAL     9
#define ADC2_PERIPHERAL     10
#define TIM1_PERIPHERAL     11
#define SPI1_PERIPHERAL     12
#define TIM8_PERIPHERAL     13
#define USART1_PERIPHERAL   14
#define ADC3_PERIPHERAL     15
#define TIM9_PERIPHERAL     19
#define TIM10_PERIPHERAL    20
#define TIM11_PERIPHERAL    21

//periphera id bits for APB1
#define TIM2_PERIPHERAL     0
#define TIM3_PERIPHERAL     1
#define TIM4_PERIPHERAL     2
#define TIM5_PERIPHERAL     3
#define TIM6_PERIPHERAL     4
#define TIM7_PERIPHERAL     5
#define TIM12_PERIPHERAL    6
#define TIM13_PERIPHERAL    7
#define TIM14_PERIPHERAL    8
#define WWD_PERIPHERAL      11 
#define SPI2_PERIPHERAL     14
#define SPI3_PERIPHERAL     15
#define USART2_PERIPHERAL   17
#define USART3_PERIPHERAL   18
#define USART4_PERIPHERAL   19
#define USART5_PERIPHERAL   20
#define I2C1_PERIPHERAL     21
#define I2C2_PERIPHERAL     22
#define USB_PERIPHERAL      23
#define CAN_PERIPHERAL      25
#define BKP_PERIPHERAL      27
#define PWR_PERIPHERAL      28
#define DAC_PERIPHERAL      29

/******************************************************************************
* Configuration Constants
*******************************************************************************/
/*!< Clock Source Type */
#define RCC_HSI                          1
#define RCC_HSE_CRYSTAL                  2
#define RCC_HSE_RC                       3
#define RCC_PLL                          4

/*!< PLL INPUT Options */
#define RCC_PLL_IN_HSI_DIV_2             1
#define RCC_PLL_IN_HSE_DIV_2             2
#define RCC_PLL_IN_HSE                   3
/*!<HSE is crystal or RC*/
#define RCC_PLL_HSE_CRYSTAL              1
#define RCC_PLL_HSE_RC                   2        
/*!< PLL MULL */
#define RCC_PLLMULL2                     2                       
#define RCC_PLLMULL3                     3
#define RCC_PLLMULL4                     4
#define RCC_PLLMULL5                     5
#define RCC_PLLMULL6                     6
#define RCC_PLLMULL7                     7
#define RCC_PLLMULL8                     8
#define RCC_PLLMULL9                     9
#define RCC_PLLMULL10                    10
#define RCC_PLLMULL11                    11
#define RCC_PLLMULL12                    12
#define RCC_PLLMULL13                    13
#define RCC_PLLMULL14                    14
#define RCC_PLLMULL15                    15
#define RCC_PLLMULL16                    16
/*!< AHP Prescalar */
#define RCC_HPRE_DIV1                    1
#define RCC_HPRE_DIV2                    2
#define RCC_HPRE_DIV4                    4
#define RCC_HPRE_DIV8                    8
#define RCC_HPRE_DIV16                   16
#define RCC_HPRE_DIV64                   64
#define RCC_HPRE_DIV128                  128
#define RCC_HPRE_DIV256                  256
#define RCC_HPRE_DIV512                  512
/*!<APB1 Prescalar Otions */
#define RCC_PPRE1_DIV1                   1
#define RCC_PPRE1_DIV2                   2
#define RCC_PPRE1_DIV4                   4
#define RCC_PPRE1_DIV8                   8
#define RCC_PPRE1_DIV16                  16
/*!<APB2 Prescalar Otions */
#define RCC_PPRE2_DIV1                   1
#define RCC_PPRE2_DIV2                   2
#define RCC_PPRE2_DIV4                   4
#define RCC_PPRE2_DIV8                   8
#define RCC_PPRE2_DIV16                  16
/*!<ADC Prescalar Otions */
#define RCC_ADCPRE_DIV2                  2
#define RCC_ADCPRE_DIV4                  4
#define RCC_ADCPRE_DIV6                  6
#define RCC_ADCPRE_DIV8                  8
/*!<MCO Otions */
#define RCC_MCO_NO_CLK                   1
#define RCC_MCO_SYS_CLK                  2
#define RCC_MCO_HSI_CLK                  3
#define RCC_MCO_HSE_CLK                  4
#define RCC_MCO_PLL_DVID2_CLK            5
/******************************************************************************/

/******************************************************************************
* Macros
*******************************************************************************/

/******************************************************************************
* Function Prototypes
*******************************************************************************/

extern void MRCC_voidEnableClock(u8 Copy_u8BusId,  u8 Copy_u8BperId);

extern void MRCC_voidDisableClock(u8 Copy_u8BusId, u8 Copy_u8BperId);

extern void MRCC_voidInitSysClock(void);

extern void MRCC_voidSetAHBPRE(void);

extern void MRCC_voidSetAPB1Pre(void);

extern void MRCC_voidSetAPB2Pre(void);

extern void MRCC_voidSetADCPre(void);

extern void MRCC_voidMcoClk(void);

//TODO: UPDATE COMMENT BELOW
#endif /*File_H_*/

/*** End of File **************************************************************/
