/*******************************************************************************
* Title                 :   Transmit 
* Filename              :   Transmit_program.c
* Author                :   Mohamed Hafez
* Origin Date           :   30/04/2021
* Version               :   1.0.0
* Compiler              :   ARM V6
* Target                :   STM32F103
* Notes                 :   None 
*
*****************************************************************************/
/*************** SOURCE REVISION LOG *****************************************
*
*    Date    Version   Author          Description 
*  30/04/21   1.0.0   Mohamed Hafez   Initial Release.
*
*******************************************************************************/
/** @file Transmit_program.c
 *  @brief This is the source file for transmit updates to nodes connected on can bus. 
 */
/******************************************************************************
* Includes
*******************************************************************************/	
#include "BIT_MATH.h"
#include "Platform_Types.h"
#include "Std_Types.h"
#include "Rte_DataTypes.h"
#include "Rte_SendUpdatePort.h"
#include "CanIf_Interface.h"
#include "Transmit.h"
#include "Transmit_Cfg.h"
#include "Transmit_private.h"

/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/

/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/

/******************************************************************************
* Module Typedefs
*******************************************************************************/

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/
static uint32               Static_u32CodeSize;
static uint8                Static_u8NodeId;
static uint16               Static_u16TransmittedPacketsCounter;             
static uint16               Static_u16NumberOfPacketsInCode;            
static uint8                Static_u8NumOfBytesInLastPacket;      

static TransmitStates_t     Static_StateVariable;
static State_PtrToFunction  Static_ArrayOfStates[NUBER_OF_STATES];
/******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************
* Function Definitions
*******************************************************************************/

/*****************************Module Function Definitions.*********************/

Std_ReturnType Transmit_InitializeModule(void)
{
   // Initalize static variable in this module
   Static_u32CodeSize                          = INITIALIZE_WITH_ZERO;
   Static_u8NodeId                             = INITIALIZE_WITH_ZERO;
   Static_u16TransmittedPacketsCounter         = INITIALIZE_WITH_ZERO;
   Static_u16NumberOfPacketsInCode             = INITIALIZE_WITH_ZERO;
   Static_u8NumOfBytesInLastPacket             = INITIALIZE_WITH_ZERO;
   // Initialize current state variable
   Static_StateVariable                        = IDLE_STATE;
   // Fill state array with function represent each state
   Static_ArrayOfStates[IDLE_STATE]            = Transmit_IdleState;
   Static_ArrayOfStates[GET_TRANSMIT_HEADER]   = Transmit_GetTransmitHeader;
   Static_ArrayOfStates[CONSUME_TRANSMIT_DATA] = Transmit_ConsumeTransmitData;
   Static_ArrayOfStates[FINISHING_STATE]       = Transmit_FinishingState;
}

Std_ReturnType Transmit_MainFunction(void)
{
   Std_ReturnType       Local_ReturnStatus = STD_IDLE;
   State_PtrToFunction  RunState           = NULL_PTR;
   RunState           = Static_ArrayOfStates[Static_StateVariable];
   Local_ReturnStatus = RunState(NULL_PTR);
   return Local_ReturnStatus;
}

Std_ReturnType Transmit_DeinitializeModule(void)
{
   // Initalize static variable in this module
   Static_u32CodeSize                          = INITIALIZE_WITH_ZERO;
   Static_u8NodeId                             = INITIALIZE_WITH_ZERO;
   Static_u16TransmittedPacketsCounter         = INITIALIZE_WITH_ZERO;
   Static_u16NumberOfPacketsInCode             = INITIALIZE_WITH_ZERO;
   Static_u8NumOfBytesInLastPacket             = INITIALIZE_WITH_ZERO;
   // Initialize current state variable
   Static_StateVariable                        = IDLE_STATE;
}

/*****************************Private Functions' Definitions*******************************/

/*****************************Functions Represent states***********************************/
static Std_ReturnType Transmit_IdleState(void *Cpy_voidPtr)
{
   Std_ReturnType Local_ReturnStatus       = E_OK;
   FlagType       Local_u8HeaderFlagValue  = HEADER_NOT_SET;
   // Get Header Flag Value.
   Local_ReturnStatus = RTE_READ_HEADER_ACK_FLAG(&Local_u8HeaderFlagValue);
   if(E_OK == Local_ReturnStatus)
   {
      // Check The Header Flag Value
      if(HEADER_SET == Local_u8HeaderFlagValue)
      {
         // Go to Get and Transmit Header State.
         Static_StateVariable = GET_TRANSMIT_HEADER;
         // Change Header flag to a not set status
         RTE_WRITE_HEADER_ACK_FLAG(HEADER_NOT_SET);
      }
      else
      {
         Local_ReturnStatus = HEADER_NOT_SET;
      }
   }
   else
   {
      Local_ReturnStatus = E_NOT_OK;
   }
   // Just remove unused parameter warning
   (uint8*)(Cpy_voidPtr);
   return Local_ReturnStatus;
}

static Std_ReturnType Transmit_GetTransmitHeader(void *Cpy_voidPtr)
{
   Std_ReturnType Local_ReturnStatus                          = E_OK;
   Std_ReturnType Local_CanIfReturnStatus                     = E_OK;
   uint8          Local_HeaderBuffer[HEADER_INFORMATION_SIZE] = {INITIALIZE_WITH_ZERO};
   uint8          Local_u8NodeId                              = INITIALIZE_WITH_ZERO;
   uint32         Local_u32CodeSize                           = INITIALIZE_WITH_ZERO;
   uint32         Local_u32CrcValue                           = INITIALIZE_WITH_ZERO;
   uint8          Local_u8ReceivedAck                         = INITIALIZE_WITH_ZERO;
   // Consume Header Information.     
   Transmit_ConsumeHeader(&Local_u8NodeId,&Local_u32CodeSize,&Local_u32CrcValue);
   // Save Size and Node Id.
   Transmit_SaveHeader(&Local_u8NodeId,&Local_u32CodeSize);
   // Handle header information
   Transmit_HandleHeader(Local_u32CodeSize,Local_u32CrcValue,Local_HeaderBuffer);
   /************************Sequance Between Gateway and Bootloader********************/

   // Request Program control.
   CanIf_uint32Transmit_Word(UDS_CONTROL_PROGRAM_SESSION, Local_u8NodeId);
   // Wait Ack from BL
   CanIf_uint8Receive_Byte(&Local_u8ReceivedAck);
   // Check received Ack
   if(UDS_MCU_ACCEPT_UPGRADE_REQUEST == Local_u8ReceivedAck)
   {
      // Request sending Header.
      CanIf_uint8Transmit_Byte(UDS_GWY_REQUEST_SENDING_HEADER, Static_u8NodeId);
      // Wait Ack from BL
      CanIf_uint8Receive_Byte(&Local_u8ReceivedAck);
      if (UDS_MCU_ACCEPT_RECEIVING_HEADER == Local_u8ReceivedAck)
      {
         // sending header.
         CanIf_uint8TransmitData(Local_HeaderBuffer,Static_u8NodeId,HEADER_INFORMATION_SIZE);
      }
      else
      {
         //TODO: Handle the situation that the Bootloader Doesn't reply correctly.
      }
   }
   else
   {
      //TODO: Handle the situation that the Bootloader Doesn't reply correctly.
   }
   // Wait Ack from BL
   CanIf_uint8Receive_Byte(&Local_u8ReceivedAck);
   // Check received Ack
   if(UDS_MCU_ACKNOWLEDGE_HEADER_RECEIVED == Local_u8ReceivedAck)
   {
      // Go to Consume and Transmit data state.
      Static_StateVariable = CONSUME_TRANSMIT_DATA;
   }
   else
   {
      //TODO: Handle the situation that the Bootloader Doesn't reply correctly.
   }
   // Just remove unused parameter warning
   (uint8*)(Cpy_voidPtr);
}

static Std_ReturnType Transmit_ConsumeTransmitData(void *Cpy_voidPtr)
{    
   FlagType       Local_u8BufferFlagValue              = BUFFER_NOT_SET;
   uint8          Local_u8DataBuffer[DATA_BUFFER_SIZE] = {INITIALIZE_WITH_ZERO}; 
   uint8          Local_u8ReceivedAck                  = INITIALIZE_WITH_ZERO;
   // Calculate number of packets and number of bytes in the last packet.
   Static_u16NumberOfPacketsInCode                     = (Static_u32CodeSize) / (DATA_BUFFER_SIZE);
   Static_u8NumOfBytesInLastPacket                     = (Static_u32CodeSize) % (DATA_BUFFER_SIZE);
   // Get Buffer Flag Value.
   RTE_READ_DECRYPTED_DATA_BUFFER_FLAG(&Local_u8BufferFlagValue);
   // Check The Buffer Flag Value
   if(BUFFER_SET == Local_u8BufferFlagValue)
   {
      // Consume Data
      RTE_READ_DECRYPTED_DATA_BUFFER(&Local_u8DataBuffer);
      // Request Sending line of code code.
      CanIf_uint8Transmit_Byte(UDS_GWY_REQUEST_SENDING_PACKET_OF_CODE, Static_u8NodeId);
      // Wait Ack from BL
      CanIf_uint8Receive_Byte(&Local_u8ReceivedAck);
      // Check The node ack
      if(UDS_MCU_ACCEPT_RECEIVING_PACKET_OF_CODE == Local_u8ReceivedAck) 
      {
         // condition to know are we will send the last packet or ordinary packet.
         if(Static_u16TransmittedPacketsCounter < Static_u16NumberOfPacketsInCode)
         {
            // Sending 64 byte of data
            CanIf_uint8TransmitData(Local_u8DataBuffer,Static_u8NodeId,DATA_BUFFER_SIZE);
            // Wait Ack from BL
            CanIf_uint8Receive_Byte(&Local_u8ReceivedAck);
            if(UDS_MCU_ACKNOWLEDGE_PACKET_OF_CODE_RECEIVED == Local_u8ReceivedAck)
            {
               // Increase packet counter by 1
               Static_u16TransmittedPacketsCounter++;
               // Change Buffer flag to a not set status
               RTE_WRITE_DECRYPTED_DATA_BUFFER_FLAG(BUFFER_NOT_SET);
               // Change System State To Decrypt state.
               RTE_WRITE_SYSTEM_STATE(SYS_DECRYPT);
            }
            else
            {
               //TODO: Handle the situation that the Bootloader Doesn't reply correctly.
            }
         }
         else
         {
            // Sending the rest of data
            CanIf_uint8TransmitData(Local_u8DataBuffer,Static_u8NodeId,Static_u8NumOfBytesInLastPacket);
            // Wait Ack from BL
            CanIf_uint8Receive_Byte(&Local_u8ReceivedAck);
            if(UDS_MCU_ACKNOWLEDGE_PACKET_OF_CODE_RECEIVED == Local_u8ReceivedAck)
            {
               // Change Buffer flag to a not set status
               RTE_WRITE_DECRYPTED_DATA_BUFFER_FLAG(BUFFER_NOT_SET);
               // Go to Finial State.
               Static_StateVariable = FINISHING_STATE;
            }
            else
            {
               //TODO: Handle the situation that the Bootloader Doesn't reply correctly.
            }
         }
      } 
      else
      {
         //TODO: Handle the situation that the Bootloader Doesn't reply correctly.
      } 
   }  
   // Just remove unused parameter warning
   (uint8*)(Cpy_voidPtr);
}

static Std_ReturnType Transmit_FinishingState(void *Cpy_voidPtr)
{
   uint8 Local_u8ReceivedAck = INITIALIZE_WITH_ZERO;
   // Ack node of the end of code transmission
   CanIf_uint8Transmit_Byte(UDS_GWY_ACKNOWLEDGE_FINISHING_SENDING_CODE, Static_u8NodeId);
   // Wait Ack from BL
   CanIf_uint8Receive_Byte(&Local_u8ReceivedAck);
   if(UDS_MCU_ACKNOWLEDGE_RECEIVED_CODE == Local_u8ReceivedAck)
   {
      // Deinitialze the module
      Transmit_DeinitializeModule();
      // Change System State To System Done Update.
      RTE_WRITE_SYSTEM_STATE(SYS_DONE_UPDATE);
   }
   // Just remove unused parameter warning
   (uint8*)(Cpy_voidPtr);
}

/*******************************Auxalriy Private Function***************************/

static Std_ReturnType Transmit_ConsumeHeader(uint8 *Cpy_NodeId,uint32 *Cpy_Size,uint32 *Cpy_Crc)
{
   Std_ReturnType Local_ReturnStatus = E_OK;
   // Consume Header Information.     
   Local_ReturnStatus                = RTE_READ_NODE_ID  (Cpy_NodeId);
   Local_ReturnStatus                = RTE_READ_CODE_SIZE(Cpy_Size);
   Local_ReturnStatus                = RTE_READ_CRC_VALUE(Cpy_Crc);
   return Local_ReturnStatus;
}

static Std_ReturnType Transmit_HandleHeader(uint32 Cpy_Size,uint32 Cpy_Crc,uint8 *Cpy_PtrToBytes)
{
   // Convert code size into bytes and store it in buffer.
   Cpy_PtrToBytes[FIRST_BYTE]   = (Cpy_Size  &  GET_BYTE);
   Cpy_PtrToBytes[SECOND_BYTE]  = ((Cpy_Size >> SHIFT_TO_GET_SECOND_BYTE) & GET_BYTE);
   Cpy_PtrToBytes[THIRD_BYTE]   = ((Cpy_Size >> SHIFT_TO_GET_THIRD_BYTE)  & GET_BYTE);
   Cpy_PtrToBytes[FOURTH_BYTE]  = ((Cpy_Size >> SHIFT_TO_GET_FOURTH_BYTE) & GET_BYTE);
   // Convert CRC Value into bytes and store it in buffer.
   Cpy_PtrToBytes[FIFTH_BYTE]   = (Cpy_Crc   &  GET_BYTE);
   Cpy_PtrToBytes[SIXTH_BYTE]   = ((Cpy_Crc  >> SHIFT_TO_GET_SECOND_BYTE) & GET_BYTE);
   Cpy_PtrToBytes[SEVENTH_BYTE] = ((Cpy_Crc  >> SHIFT_TO_GET_THIRD_BYTE)  & GET_BYTE);
   Cpy_PtrToBytes[EIGHTH_BYTE]  = ((Cpy_Crc  >> SHIFT_TO_GET_FOURTH_BYTE) & GET_BYTE);
}

static Std_ReturnType Transmit_SaveHeader(uint8 *Cpy_NodeId,uint32 *Cpy_Size)
{
   // Store Node Id To Use It to determinr the node.
   Static_u8NodeId    = *Cpy_NodeId;
   // Store Size To Use It to calculate number of packts.
   Static_u32CodeSize = *Cpy_Size;
}

/*************** END OF FUNCTIONS ***************************************************************************/
