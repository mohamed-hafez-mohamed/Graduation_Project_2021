/****************************************************************************
* Title                 :   GPIO   
* Filename              :   GPIO_private.h
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
*  10/08/20   1.0.0   Mohamed Hafez   Interface Created.
*
*****************************************************************************/
/** @file  GPIO_private.h
 *  @brief This module TODO: WHAT DO I DO?
 * 
 *  This is the header file for the definition TODO: MORE ABOUT ME!
 */
//TODO: UPDATE MACRO BELOW
#ifndef GPIO_PRIVATE_H_
#define GPIO_PRIVATE_H_

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

/*!<*********************************PORTS Base Address************************/
#define GPIOA_BASE_ADDRESS  0X40010800
#define GPIOB_BASE_ADDRESS  0X40010C00
#define GPIOC_BASE_ADDRESS  0X40011000

/*!<**************************Offset Definition********************************/
#define CRL                 0X00
#define CRH                 0X04
#define IDR                 0X08
#define ODR                 0X0C
#define BSR                 0X10
#define BRR                 0X14
#define LCK                 0X18
/*!<***************************Register Address for PORTA**********************/
#define GPIOA_CRL           *((volatile uint32 *)(GPIOA_BASE_ADDRESS + CRL))
#define GPIOA_CRH           *((volatile uint32 *)(GPIOA_BASE_ADDRESS + CRH))
#define GPIOA_IDR           *((volatile uint32 *)(GPIOA_BASE_ADDRESS + IDR))
#define GPIOA_ODR           *((volatile uint32 *)(GPIOA_BASE_ADDRESS + ODR))
#define GPIOA_BSR           *((volatile uint32 *)(GPIOA_BASE_ADDRESS + BSR))
#define GPIOA_BRR           *((volatile uint32 *)(GPIOA_BASE_ADDRESS + BRR))
#define GPIOA_LCK           *((volatile uint32 *)(GPIOA_BASE_ADDRESS + LCK))

/*!<***************************Register Address for PORTB**********************/
#define GPIOB_CRL           *((volatile uint32 *)(GPIOB_BASE_ADDRESS + CRL))
#define GPIOB_CRH           *((volatile uint32 *)(GPIOB_BASE_ADDRESS + CRH))
#define GPIOB_IDR           *((volatile uint32 *)(GPIOB_BASE_ADDRESS + IDR))
#define GPIOB_ODR           *((volatile uint32 *)(GPIOB_BASE_ADDRESS + ODR))
#define GPIOB_BSR           *((volatile uint32 *)(GPIOB_BASE_ADDRESS + BSR))
#define GPIOB_BRR           *((volatile uint32 *)(GPIOB_BASE_ADDRESS + BRR))
#define GPIOB_LCK           *((volatile uint32 *)(GPIOB_BASE_ADDRESS + LCK))

/*!<***************************Register Address for PORTC**********************/
#define GPIOC_CRL           *((volatile uint32 *)(GPIOC_BASE_ADDRESS + CRL))
#define GPIOC_CRH           *((volatile uint32 *)(GPIOC_BASE_ADDRESS + CRH))
#define GPIOC_IDR           *((volatile uint32 *)(GPIOC_BASE_ADDRESS + IDR))
#define GPIOC_ODR           *((volatile uint32 *)(GPIOC_BASE_ADDRESS + ODR))
#define GPIOC_BSR           *((volatile uint32 *)(GPIOC_BASE_ADDRESS + BSR))
#define GPIOC_BRR           *((volatile uint32 *)(GPIOC_BASE_ADDRESS + BRR))
#define GPIOC_LCK           *((volatile uint32 *)(GPIOC_BASE_ADDRESS + LCK))

/*!<*********************************Bits Definitions************************/
#define GPIO_LCK_LCKK      16

#endif
/*** End of File **************************************************************/
