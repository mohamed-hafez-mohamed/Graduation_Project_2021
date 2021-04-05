/****************************************************************************
* Title                 :   WDT   
* Filename              :   WDT_private.h
* Author                :   Mohamed Hafez
* Origin Date           :   22/12/2020
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
*  22/12/20   1.0.0   Mohamed Hafez   Interface Created.
*
*****************************************************************************/
/** @file  WDT_private.h
 *  @brief This module TODO: WHAT DO I DO?
 * 
 *  This is the header file for the definition TODO: MORE ABOUT ME!
 */
//TODO: UPDATE MACRO BELOW
#ifndef WDT_PRIVATE_H_
#define WDT_PRIVATE_H_

/******************************************************************************
* Includes
*******************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
/******************************************************************************
* Typedefs
*******************************************************************************/

/******************************************************************************
* Preprocessor Constants
*******************************************************************************/
// Important Constant
#define IWDT_ACCESS_PR_RLR_KEY  0x5555
#define IWDT_ENABLE_IWDT        0xCCCC
#define IWDT_REFRESH_IWDT       0xAAAA
#define WWDT_REQUEST_SW_RESET   0xBF
/*!<**************************PORTS Base Address*******************************/
#define IWDT_BASE_ADDRESS       0x40003000
#define WWDT_BASE_ADDRESS       0x40002C00
/*!<**************************Offset Definition********************************/
// IWDT 
#define KR                      0X00
#define PR                      0X04
#define RLR                     0X08
#define SR                      0X0C
// WWDT
#define CR                      0X00
#define CFR                     0X04
#define WSR                     0X08
/*!<***************************Bite Definitions*********************************/
// IWDT
#define PUV                     0
#define RUV                     1
// WWDT
#define WDGA                    7
#define WDGTB0                  7
#define WDGTB1                  8
#define EVI                     9
#define EVIF                    0
#define T6                      6
/******************************************************************************
* Configuration Constants
*******************************************************************************/
/*!<***************************Register Address********************************/
// IWDT
#define IWDT_KR                 *((volatile u32 *)(IWDT_BASE_ADDRESS + KR))
#define IWDT_PR                 *((volatile u32 *)(IWDT_BASE_ADDRESS + PR))
#define IWDT_RLR                *((volatile u32 *)(IWDT_BASE_ADDRESS + RLR))
#define IWDT_SR                 *((volatile u32 *)(IWDT_BASE_ADDRESS + SR))
// WWDT
#define WWDT_CR            *((volatile u32 *)(WWDT_BASE_ADDRESS + CR))
#define WWDT_CFR           *((volatile u32 *)(WWDT_BASE_ADDRESS + CFR))
#define WWDT_SR            *((volatile u32 *)(WWDT_BASE_ADDRESS + WSR))

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/

/******************************************************************************
* Function Prototypes
*******************************************************************************/

#endif
/*** End of File **************************************************************/
