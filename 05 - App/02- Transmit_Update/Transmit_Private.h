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

/******************************************************************************
* Configuration Constants
*******************************************************************************/
#define HEADER_INFORMATION_SIZE                     9
#define INITIALIZE_WITH_ZERO                        0
#define INITIALIZE_WITH_ONE                         1
#define RESET_FLAG                                  0
#define ONE_BYTE                                    1
#define GET_FIRST_BYTE                              0X000000FF
#define GET_SECOND_BYTE                             0X0000FF00
#define GET_THIRD_BYTE                              0X00FF0000
#define GET_FOURTH_BYTE                             0XFF000000
#define FIRST_BYTE                                  0
#define SECOND_BYTE                                 1
#define THIRD_BYTE                                  2
#define FOURTH_BYTE                                 3
#define FIFTH_BYTE                                  4
#define SIXTH_BYTE                                  5
#define SEVENTH_BYTE                                6
#define EIGHTH_BYTE                                 7
#define NINETH_BYTE                                 8
/******************************************************************************
* Module Variable Definitions
*******************************************************************************/

/******************************************************************************
* Function Prototypes
*******************************************************************************/
static Std_ReturnType Transmit_ConsumeHeader(uint8 *Cpy_NodeId,uint32 *Cpy_Size,uint32 *Cpy_Crc);
static Std_ReturnType Transmit_HandleHeader(uint32 Cpy_Size,uint32 Cpy_Crc,uint8 *Cpy_PtrToBytes);
static Std_ReturnType Transmit_SaveHeader(uint8 *Cpy_NodeId,uint32 *Cpy_Size);
static Std_ReturnType Transmit_FinishHeaderTansmission(void);
// Functions that handle states.
static Std_ReturnType Transmit_IdleState(void*);
static Std_ReturnType Transmit_GetTransmitHeader(void*);
static Std_ReturnType Transmit_ConsumeTransmitData(void*);
static Std_ReturnType Transmit_FinishingState(void*);
#endif
/*** End of File **************************************************************/
