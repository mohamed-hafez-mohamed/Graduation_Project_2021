/*******************************************************************************
**  FILENAME     : ComM_Interface.h         			                              **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2021-04-29                                                  **
**                                                                            **                                                                            **
**  PLATFORM     : stm32f103		                                              **
**                                                                            **
**  AUTHOR       : osamahijazi	                                              **
                                                                              **
**  DESCRIPTION  : Canif Driver interface file                                  **
**                                                                            **
*******************************************************************************/

/* Define to prevent recursive inclusion */

#ifndef CanIf_INTERFACE_H
#define CanIf_INTERFACE_H


/*****************************************************************************************/
/*                                   Include headres                                     */
/*****************************************************************************************/
#include "CAN_Interface.h"
#include "CanIf_Private.h"
#include "CanIf_cfg.h"

/***********************************************************************************/
                      /***FUNCTIONS PROTOTYPES***/
/***********************************************************************************
*Name       :   CanIf_uint8TransmitData

*Description: *Send an array of Data according to static configuration
								
*Pre-Cond   :	can is init
							
*pos-Cond   : None

*Input      : - pionter to array address
              - target ID 
              - array lenght which must ne manltiplied of 8						 

*Output     : void

*Return     : error status

*************************************************************************************/
uint8 CanIf_uint8TransmitData( const uint8 *Copy_uint8DataPtr, uint8 Copy_uint8NodeID , uint16 Copy_uint8DataLenght);
/************************************************************************************

*Name       :   CanIf_uint8Receive_Struct

*Description: * recive a completet frame  
								
*Pre-Cond   :	can-init
							
*pos-Cond   : None

*Input      : -canx struct "x=1,2,..."  always = CAN1
             - message fram struct address that will contain received message		
             - FIFO Number	always 0 					 

*Output     : void

*Return     : error status

*************************************************************************************/
uint8 CanIf_uint8Receive_Struct(CAN_TypeDef* CANx, uint8 Copy_u8FifoNumber, CanRxMsg RxMessage);
/************************************************************************************

*Name       :   CanIf_uint8Transmit_Struct

*Description: * init transmit can frame to send it throught 
                specific mail box
								
*Pre-Cond   :	None				
							
*pos-Cond   : None

*Input      : -canx struct "x=1,2,..."  always = CAN1
              CAN InitStruct to specifiy the configuration
             - message fram struct address that will contain transmit message						 

*Output     : void

*Return     : error status

*************************************************************************************/
uint8 CanIf_uint8Transmit_Struct( CAN_TypeDef* CANx, CanTxMsg TxMessage ); 
/************************************************************************************

*Name       :   CanIf_uint32Receive_Word

*Description: *block FIFO until recive only one word  
								
*Pre-Cond   :	can is init
							
*pos-Cond   : None

*Input      : void

*Output     : void

*Return     : Received word
*************************************************************************************/
uint32 CanIf_uint32Receive_Word(void);
/************************************************************************************

*Name       :   CanIf_uint8Receive_Byte

*Description: *block FIFO until recive only one byte  
								
*Pre-Cond   :	can is init
							
*pos-Cond   : None

*Input      : void

*Output     : void

*Return     : Received byte
*************************************************************************************/
uint8 CanIf_uint8Receive_Byte( void );
/************************************************************************************

*Name       :   CanIf_uint8Receive_Byte

*Description: *block FIFO until All Bytes is received    
								
*Pre-Cond   :	can is init
							
*pos-Cond   : None

*Input      : array address and excepted Data length

*Output     : void

*Return     : local error
*************************************************************************************/

uint8 CanIf_uint8Receive_Block( uint8 *Copy_uint8DataPtr ,  uint8 Copy_uint8DataLenght);






#endif
/******************************************END OF FILE************************************/
