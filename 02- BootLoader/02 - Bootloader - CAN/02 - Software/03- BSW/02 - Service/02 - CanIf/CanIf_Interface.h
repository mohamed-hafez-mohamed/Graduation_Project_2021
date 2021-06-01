/*******************************************************************************
**  FILENAME     : CanIf_Interface.h         			                              **
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
*Name       :   CanIf_u8TransmitData

*Description: *Send an array of Data according to static configuration
								
*Pre-Cond   :	can is init
							
*pos-Cond   : None

*Input      : - pionter to array address
              - target ID 
              - array lenght which must ne manltiplied of 8						 

*Output     : void

*Return     : error status

*************************************************************************************/
Std_ReturnType CanIf_u8TransmitData( const u8 *Copy_u8DataPtr , u8 Copy_u8DataLenght);
/************************************************************************************

*Name       :   CanIf_u8Receive_Struct

*Description: * recive a completet frame  
								
*Pre-Cond   :	can-init
							
*pos-Cond   : None

*Input      : -canx struct "x=1,2,..."  always = CAN1
             - message fram struct address that will contain received message		
             - FIFO Number	always 0 					 

*Output     : void

*Return     : error status

*************************************************************************************/
static Std_ReturnType CanIf_u8Receive_Struct(CAN_TypeDef* CANx, u8 Copy_u8FifoNumber, CanRxMsg RxMessage);
/************************************************************************************

*Name       :   CanIf_u8Transmit_Struct

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
static Std_ReturnType CanIf_u8Transmit_Struct( CAN_TypeDef* CANx, CanTxMsg TxMessage ); 
/************************************************************************************

*Name       :   CanIf_u32Receive_Word

*Description: *block FIFO until recive only one word  
								
*Pre-Cond   :	can is init
							
*pos-Cond   : None

*Input      : addres of u32 variable

*Output     : reciverd word

*Return     : local errror
*************************************************************************************/
Std_ReturnType CanIf_u32Receive_Word( u32 *Copy_u32Word);
/************************************************************************************

*Name       :   CanIf_u8Receive_Byte

*Description: *block FIFO until recive only one byte  
								
*Pre-Cond   :	can is init
							
*pos-Cond   : None

*Input      : address of unit8  variable

*Output     : Received byte

*Return     : local errror
*************************************************************************************/
Std_ReturnType CanIf_u8Receive_Byte( u8*Copy_u8Byte ) ;
/************************************************************************************

*Name       :   CanIf_u8Receive_Block

*Description: *block FIFO until All Bytes is received    
								
*Pre-Cond   :	can is init
							
*pos-Cond   : None

*Input      : array address and excepted Data length

*Output     : void

*Return     : local error
*************************************************************************************/
Std_ReturnType CanIf_u8Receive_Block( u8 *Copy_u8DataPtr ,  u8 Copy_u8DataLenght);
/************************************************************************************

*Name       :   CanIf_u8Transmit_Byte

*Description: *transmit only one byte to corresponding node    
								
*Pre-Cond   :	can is init
							
*pos-Cond   : mailbox 0 is empty 

*Input      : Byte to be sent and node id

*Output     : void

*Return     : local error
*************************************************************************************/
Std_ReturnType CanIf_u8Transmit_Byte( u8 Copy_u8Data );
/************************************************************************************

*Name       :   CanIf_u32Transmit_Word

*Description: *transmit only one word to corresponding node    
								
*Pre-Cond   :	can is init
							
*pos-Cond   : mailbox 0 is empty

*Input      : word to be sent and node id

*Output     : void

*Return     : local error
*************************************************************************************/
Std_ReturnType CanIf_u32Transmit_Word( u32 Copy_u32Data );





#endif
/******************************************END OF FILE************************************/
