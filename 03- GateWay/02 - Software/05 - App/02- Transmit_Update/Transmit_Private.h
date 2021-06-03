/****************************************************************************
* Title                 :   Transmit   
* Filename              :   Transmit_private.h
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
/** @file  Transmit_private.h
 *  @brief This module TODO: WHAT DO I DO?
 * 
 *  This is the header file for the definition TODO: MORE ABOUT ME!
 */
//TODO: UPDATE MACRO BELOW
#ifndef Transmit_PRIVATE_H_
#define Transmit_PRIVATE_H_

/******************************************************************************
* Includes
*******************************************************************************/

/******************************************************************************
* Typedefs
*******************************************************************************/
typedef Std_ReturnType (*State_PtrToFunction)(void * );
typedef enum
{
   IDLE_STATE = 0,
   GET_TRANSMIT_HEADER,
   CONSUME_TRANSMIT_DATA,
   FINISHING_STATE,
   NUBER_OF_STATES
}TransmitStates_t;
/******************************************************************************
* Preprocessor Constants
*******************************************************************************/
#define INITIALIZE_WITH_ZERO                        0
#define INITIALIZE_WITH_ONE                         1
#define ZERO_BYTE                                   0
#define COMPLETE_PACKET                             64
#define RESET_FLAG                                  0
#define ONE_BYTE                                    1
/******************************************************************************
* Configuration Constants
*******************************************************************************/
#define HEADER_INFORMATION_SIZE                     8

#define GET_BYTE                                    0XFF
#define SHIFT_TO_GET_SECOND_BYTE                    8
#define SHIFT_TO_GET_THIRD_BYTE                     16
#define SHIFT_TO_GET_FOURTH_BYTE                    24

#define FIRST_BYTE                                  0
#define SECOND_BYTE                                 1
#define THIRD_BYTE                                  2
#define FOURTH_BYTE                                 3
#define FIFTH_BYTE                                  4
#define SIXTH_BYTE                                  5
#define SEVENTH_BYTE                                6
#define EIGHTH_BYTE                                 7
/******************************************************************************
* Module Variable Definitions
*******************************************************************************/

/******************************************************************************
* Function Prototypes
*******************************************************************************/
static Std_ReturnType Transmit_ConsumeHeader(uint8 *Cpy_NodeId,uint32 *Cpy_Size,uint32 *Cpy_Crc);
static Std_ReturnType Transmit_HandleHeader(uint32 Cpy_Size,uint32 Cpy_Crc,uint8 *Cpy_PtrToBytes);
static Std_ReturnType Transmit_SaveHeader(uint8 *Cpy_NodeId,uint32 *Cpy_Size);
// Functions that handle states.
static Std_ReturnType Transmit_IdleState(void *Cpy_voidPtr);
static Std_ReturnType Transmit_GetTransmitHeader(void *Cpy_voidPtr);
static Std_ReturnType Transmit_ConsumeTransmitData(void *Cpy_voidPtr);
static Std_ReturnType Transmit_FinishingState(void *Cpy_voidPtr);
static Std_ReturnType Transmit_FinishHeaderTansmission(void);
#endif
/*** End of File **************************************************************/
