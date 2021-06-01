/*******************************************************************************
**  FILENAME     : ComM.c         			                                        **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2021-04-29                                                  **
**                                                                            **
**  PLATFORM     : stm32f103		                                              **
**                                                                            **
**  AUTHOR       : osamahijazi	                                              **
**                                                                            ***                                                                           **
**  DESCRIPTION  : Canif Driver source file                                     **
**                                                                            **
*******************************************************************************/

/**********************************************include******************************************/
/*Library include*/
#include "BIT_MATH.h"
#include "STD_TYPES.h"
/*header files include*/
#include "CanIf_Interface.h"
#include "CanIf_Private.h"
#include "CanIf_cfg.h"
/*other modules header files include*/
#include "CAN_Interface.h"

Std_ReturnType CanIf_u8TransmitData( const u8 *Copy_u8DataPtr, u8 Copy_u8DataLenght)
{
	
	/*Local variable , Return = ok*/
 	Std_ReturnType Local_ReturnError = E_OK;
	
	/* Check input pionter */
	if (NULL_PTR == Copy_u8DataPtr)
	{
		Local_ReturnError = E_NOT_OK ;// error status = not  ok 
		                              
	  return  Local_ReturnError ;   //return error stats

	}
	
	/*Init transmit struct*/
	 CanTxMsg  TxMessage ;  	
	/*satisfy messages ID according to input Node id*/ 			 
   TxMessage.ID = NODE_ONE_MESS_ID ;
		 
		
	/*static configuration for all sent messages*/
	/*
	DLC = 8 BYTE
	IDE = 0
	RTR = 0
	CANX = CAN1
	*/
  TxMessage.DATA_LENGHT = CONFOIG_DLC ;	
	TxMessage.IDE = CONFOIG_IDE ; 
  TxMessage.RTR = CONFOIG_RTR ;
  u16 Local_u8FramsNumber = (u16)(Copy_u8DataLenght / FRAME_DATA_BYTES ) ;	
	
for (u8 Round_Counter = ZERO; Round_Counter < Local_u8FramsNumber ; Round_Counter++) // send 8 byte in each round  
    {
			/*fetch Data from input buffer byte by byte*/
			for( u8 Data_Counter = ZERO ; Data_Counter < EIGTH_ROUNDS ; Data_Counter++)	
	    {
				
       TxMessage.DATA[Data_Counter] = Copy_u8DataPtr[Data_Counter] ;
				
	    }
			/*send frame*/
		  CAN_VoidTransmit( CAN1 , &TxMessage );
				
		/*increment input pionter by 8 byte to get second frame data inext round*/
			Copy_u8DataPtr += FRAME_DATA_BYTES ;			
   }
		
  return Local_ReturnError ;

}
/************************************************END OF FUNCTION*******************************/
static Std_ReturnType CanIf_u8Receive_Struct(CAN_TypeDef* CANx, u8 Copy_u8FifoNumber, CanRxMsg RxMessage)
{
	/*Local variable , Return = ok*/
 	Std_ReturnType Local_ReturnError = E_OK;
	
	/* Check input pionter */
	if (NULL_PTR == CANx)
	{
		Local_ReturnError = E_NOT_OK ; // error status = not  ok 
		
		return  Local_ReturnError ;    //return error stats

	}
	
/*static configuration for all sent messages*/
	/*
 FIFO NUMBER = FIFO 0
 CANX = CAN1 
*/	
CAN_VoidReceive(CANx, Copy_u8FifoNumber, &RxMessage); //Receive can Frame
	
	return Local_ReturnError ;

}	
/************************************************END OF FUNCTION*******************************/
static Std_ReturnType CanIf_u8Transmit_Struct( CAN_TypeDef* CANx, CanTxMsg TxMessage )
{
	
	/*Local variable , Return = ok*/
 	Std_ReturnType Local_ReturnError = E_OK;
	/* Check input pionter */
	if (NULL_PTR == CANx)
	{
		Local_ReturnError = E_NOT_OK ; // error status = not  ok  
		                               
		return  Local_ReturnError ;    //return error stats
		
	}
	
/*static configuration for all sent messages*/
	/*
 CANX = CAN1 
*/
  CAN_VoidTransmit( CANx , &TxMessage) ;

	return Local_ReturnError ;

}

/************************************************END OF FUNCTION*******************************/
Std_ReturnType CanIf_u32Receive_Word( u32 *Copy_u32Word)
{
	
	/*Local variable , Return = ok*/
 	Std_ReturnType Local_ReturnError = E_OK;
	
	           /* Check input pionter */
	if ( (NULL_PTR == Copy_u32Word) )
	{
		Local_ReturnError = E_NOT_OK ; // error status = not  ok 
		
		return  Local_ReturnError ;    //return error stats
	}
/*static configuration for all sent messages*/
	/*
 FIFO NUMBER = FIFO 0
 CANX = CAN1 
	Note : pass the struct name not address
*/	
u32 Local_u32Data ;	
	
Local_u32Data = Can_u32SynRecieveWord( CAN1 , CAN_FIFO0 );
	
(*Copy_u32Word) = Local_u32Data ; 


return  Local_ReturnError ;	

}
/************************************************END OF FUNCTION*******************************/
Std_ReturnType CanIf_u8Receive_Byte( u8 *Copy_u8Byte )
{
	
	/*Local variable , Return = ok*/
 	Std_ReturnType Local_ReturnError = E_OK;
	
	           /* Check input pionter */
	if ( (NULL_PTR == Copy_u8Byte) )
	{
		Local_ReturnError = E_NOT_OK ; // error status = not  ok 
		
		return  Local_ReturnError ;    //return error stats
	}
	
/*static configuration for all sent messages*/
	/*
 FIFO NUMBER = FIFO 0
 CANX = CAN1 
	Note : pass the struct name not address
*/	
u8 Local_u8Data ;	
	
Local_u8Data = Can_u8SynRecieveByte(  CAN1 , CAN_FIFO0  );
	
(*Copy_u8Byte) = Local_u8Data ; 
	
return  Local_ReturnError ;	

}
/************************************************END OF FUNCTION*******************************/

Std_ReturnType CanIf_u8Receive_Block( u8 *Copy_u8DataPtr ,  u8 Copy_u8DataLenght)

{
/*Local variable , Return = ok*/
 	Std_ReturnType Local_ReturnError = E_OK;
	
	           /* Check input pionter */
	if ( (NULL_PTR == Copy_u8DataPtr) )
	{
		Local_ReturnError = E_NOT_OK ; // error status = not  ok 
		
		return  Local_ReturnError ;    //return error stats
	}
	
/*static configuration for all sent messages*/
	/*
 FIFO NUMBER = FIFO 0
 CANX = CAN1 
*/	
	
Can_voidSynRecieveArray( Copy_u8DataPtr , Copy_u8DataLenght);
	
return  Local_ReturnError ;	

}
/************************************************END OF FUNCTION*******************************/
Std_ReturnType CanIf_u8Transmit_Byte( u8 Copy_u8Data  )
{

	/*Local variable , Return = ok*/
 	Std_ReturnType Local_ReturnError = E_OK;
	
	/*Init transmit struct*/
	 CanTxMsg  TxMessage ;  	
	
	/* To be added */
	TxMessage.ID = NODE_ONE_MESS_ID ;
		
	/*static configuration for all sent messages*/
/*
	DLC = 1 BYTE
	IDE = 0
	RTR = 0
	CANX = CAN1
	DATA[0] = Input byte
*/
TxMessage.DATA_LENGHT = ONE_BTYE ;	
TxMessage.IDE = CONFOIG_IDE ; 
TxMessage.RTR = CONFOIG_RTR ;
TxMessage.DATA[BYTE_ZERO] = Copy_u8Data ; // save byte to first element in array
	
	                        /*send frame*/
Local_ReturnError= CanIf_u8Transmit_Struct( CAN1, TxMessage );
	
return Local_ReturnError ;

}
/************************************************END OF FUNCTION*******************************/
Std_ReturnType CanIf_u32Transmit_Word( u32 Copy_u32Data   )
{

	/*Local variable , Return = ok*/
 	Std_ReturnType Local_ReturnError = E_OK;
	
	/*Init transmit struct*/
	 CanTxMsg  TxMessage ; 
/*pionter to save word bytes to struct array*/
	u8 *Local_u8DataPtr = &Copy_u32Data ; 	

	/* To be added */
	TxMessage.ID = NODE_ONE_MESS_ID ;
		
	/*static configuration for all sent messages*/
/*
	DLC = 1 BYTE
	IDE = 0
	RTR = 0
	CANX = CAN1
	DATA[0] = Copy_u32Data[0]
	DATA[1] = Copy_u32Data[1]
	DATA[2] = Copy_u32Data[2]
	DATA[3] = Copy_u32Data[3]

*/
TxMessage.DATA_LENGHT = FOUR_BYTES ;	
TxMessage.IDE = CONFOIG_IDE ; 
TxMessage.RTR = CONFOIG_RTR ;
	       /* save word byte by byte to first  4 elements in array*/
	for( u8 Data_Counter = ZERO ; Data_Counter < FOUR_BYTES ; Data_Counter++)	
	    {		
       TxMessage.DATA[Data_Counter] = Local_u8DataPtr[Data_Counter] ;			
	    }
	                        /*send frame*/
Local_ReturnError= CanIf_u8Transmit_Struct( CAN1, TxMessage );
	
return Local_ReturnError ;

}
