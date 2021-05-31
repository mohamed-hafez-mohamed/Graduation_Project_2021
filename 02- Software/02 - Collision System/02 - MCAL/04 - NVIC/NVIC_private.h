/****************************************************************************
* Title                 :   NVIC   
* Filename              :   NVIC_private.h
* Author                :   Mohamed Hafez
* Origin Date           :   15/08/2020
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
*  15/08/20   1.0.0   Mohamed Hafez   Interface Created.
*
*****************************************************************************/
/** @file  NVIC_private.h
 *  @brief This module TODO: WHAT DO I DO?
 * 
 *  This is the header file for the definition TODO: MORE ABOUT ME!
 */
//TODO: UPDATE MACRO BELOW
#ifndef NVIC_PRIVATE_H_
#define NVIC_PRIVATE_H_

/******************************************************************************
* Includes
*******************************************************************************/


/******************************************************************************
* Preprocessor Constants
*******************************************************************************/

/******************************************************************************
* Configuration Constants
*******************************************************************************/

/*!<*********************************NVIC Base Address************************/
#define NVIC_BASE_ADDRESS   0xE000E100
    
/*!<**************************Offset Definition********************************/
#define ISER0               0X000
#define ISER1               0X004
#define ICER0               0X080
#define ICER1               0X084
#define ISPR0               0X100
#define ISPR1               0X104
#define ICPR0               0X180
#define ICPR1               0X184
#define IABR0               0X200
#define IABR1               0X204
#define IPR                 0X300
#define IPR20               0X320
#define STIR                0XE00
            
/*!<***************************Register Address for PORTA**********************/
#define NVIC_ISER0          *((volatile uint32 * const)(NVIC_BASE_ADDRESS + ISER0))
#define NVIC_ISER1          *((volatile uint32 * const)(NVIC_BASE_ADDRESS + ISER1))
#define NVIC_ICER0          *((volatile uint32 * const)(NVIC_BASE_ADDRESS + ICER0))
#define NVIC_ICER1          *((volatile uint32 * const)(NVIC_BASE_ADDRESS + ICER1))
#define NVIC_ISPR0          *((volatile uint32 * const)(NVIC_BASE_ADDRESS + ISPR0))
#define NVIC_ISPR1          *((volatile uint32 * const)(NVIC_BASE_ADDRESS + ISPR1))
#define NVIC_ICPR0          *((volatile uint32 * const)(NVIC_BASE_ADDRESS + ICPR0))
#define NVIC_ICPR1          *((volatile uint32 * const)(NVIC_BASE_ADDRESS + ICPR1))
#define NVIC_IABR0          *((volatile uint32 * const)(NVIC_BASE_ADDRESS + IABR0))
#define NVIC_IABR1          *((volatile uint32 * const)(NVIC_BASE_ADDRESS + IABR1))
#define NVIC_STIR           *((volatile uint32 * const)(NVIC_BASE_ADDRESS + STIR ))
#define NVIC_IPR             ((volatile uint8  * const)(NVIC_BASE_ADDRESS + IPR  ))


#endif  
/*** End of File **************************************************************/
