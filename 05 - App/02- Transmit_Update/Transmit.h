/****************************************************************************
* Title                 :   Transmit   
* Filename              :   Transmit_interface.h
* Author                :   Mohamed Hafez
* Origin Date           :   30/04/2021
* Version               :   1.0.0
* Compiler              :   ARM V6
* Target                :   STM32F103
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
*  30/04/21   1.0.0   Mohamed Hafez   Interface Created.
*
*****************************************************************************/
/** @file  Transmit_interface.h
 *  @brief This module TODO: WHAT DO I DO?
 * 
 *  This is the header file for the definition TODO: MORE ABOUT ME!
 */
//TODO: UPDATE MACRO BELOW
#ifndef Transmit_INTERFACE_H_
#define Transmit_INTERFACE_H_

/******************************************************************************
* Includes
*******************************************************************************/

/******************************************************************************
* Preprocessor Constants
*******************************************************************************/

/******************************************************************************
* Configuration Constants
*******************************************************************************/
// UDS Information
#define UDS_RECEIVED_PROGRAM_SESSION                1
#define UDS_CONTROL_SEESION                         0X10
#define UDS_PROGRAM_SESSION                         0x03
// Open Program session
#define UDS_CONTROL_PROGRAM_SESSION                 0x0310
#define UDS_MCU_ACCEPT_UPGRADE_REQUEST              0x50
// Header constants
#define UDS_GWY_REQUEST_SENDING_HEADER              0x34
#define UDS_MCU_ACCEPT_RECEIVING_HEADER             0x73
#define UDS_MCU_ACKNOWLEDGE_HEADER_RECEIVED         0x74
// Code Constants
#define UDS_GWY_REQUEST_SENDING_PACKET_OF_CODE      0x36
#define UDS_MCU_ACCEPT_RECEIVING_PACKET_OF_CODE     0x75

#define UDS_MCU_ACKNOWLEDGE_PACKET_OF_CODE_RECEIVED 0x76 
// Finishing communication
#define UDS_GWY_ACKNOWLEDGE_FINISHING_SENDING_CODE  0x37 // 0x04
#define UDS_MCU_ACKNOWLEDGE_RECEIVED_CODE           0x77
// Other constants
#define UDS_MCU_ACKNOWLEDGE_ACTIVE_CODE_CORRECT     0x78
#define UDS_MCU_ACKNOWLEDGE_ACTIVE_CODE_NOT_CORRECT 0x79
#define UDS_MCU_ACKNOWLEDGE_BACKUP_CODE_CORRECT     0x7A
#define UDS_MCU_ACKNOWLEDGE_BACKUP_CODE_NOT_CORRECT 0x7B
/******************************************************************************
* Macros
*******************************************************************************/
	
/******************************************************************************
* Typedefs
*******************************************************************************/

/******************************************************************************
* Variables
*******************************************************************************/

/******************************************************************************
* Function Prototypes
*******************************************************************************/
Std_ReturnType Transmit_InitializeModule(void);
Std_ReturnType Transmit_MainFunction(void);

#endif /*File_H_*/

/*** End of File **************************************************************/
