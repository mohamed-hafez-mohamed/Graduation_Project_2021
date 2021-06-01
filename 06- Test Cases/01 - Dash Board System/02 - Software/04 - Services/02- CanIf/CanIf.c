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
#include "Std_Types.h"
/*header files include*/
#include "CanIf_Interface.h"
#include "CanIf_Private.h"
#include "CanIf_cfg.h"
/*other modules header files include*/
#include "CAN_Interface.h"

uint8 counter; 

Std_ReturnType CanIf_uint8TransmitData( const uint8 *Copy_uint8DataPtr, uint8 Copy_uint8NodeID , uint8 Copy_uint8DataLenght)
{
	
	counter = 0 ;
	/*Local variable , Return = ok*/
 	Std_ReturnType Local_ReturnError = E_OK;
	
	/* Check input pionter */
	if (NULL_PTR == Copy_uint8DataPtr)
	{
		Local_ReturnError = E_NOT_OK ;// error status = not  ok 
		                              
	  return  Local_ReturnError ;   //return error stats

	}
	
	/*Init transmit struct*/
	 CanTxMsg  TxMessage ;  	
	/*satisfy messages ID according to input Node id*/
		switch (Copy_uint8NodeID)                                            
    {
  	 case NODE_ONE_ID : 	
			 
            TxMessage.ID = NODE_ONE_MESS_ID ;
		 
		        break;

  	 case NODE_TWO_ID : 
			 
            TxMessage.ID = NODE_TWO_MESS_ID ;
	
	          break;
		 
		default   :		
			
	                  	/*wrong input node id */
		        break;						
                                                 /*END OF SWITCH CASE*/
	}
		
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
  uint16 Local_uint8FramsNumber = (uint16)(Copy_uint8DataLenght / FRAME_DATA_BYTES ) ;	
	
for (uint8 Round_Counter = ZERO; Round_Counter < Local_uint8FramsNumber ; Round_Counter++) // send 8 byte in each round  
    {
			/*fetch Data from input buffer byte by byte*/
			for( uint8 Data_Counter = ZERO ; Data_Counter < EIGTH_ROUNDS ; Data_Counter++)	
	    {
				
       TxMessage.DATA[Data_Counter] = Copy_uint8DataPtr[Data_Counter] ;
				
	    }
			/*send frame*/
		  CAN_VoidTransmit( CAN1 , &TxMessage );
			counter++;
				
		/*increment input pionter by 8 byte to get second frame data inext round*/
			Copy_uint8DataPtr += FRAME_DATA_BYTES ;			
   }
		
  return Local_ReturnError ;

}
/************************************************END OF FUNCTION*******************************/
static Std_ReturnType CanIf_uint8Receive_Struct(CAN_TypeDef* CANx, uint8 Copy_uint8FifoNumber, CanRxMsg RxMessage)
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
CAN_VoidReceive(CANx, Copy_uint8FifoNumber, &RxMessage); //Receive can Frame
	
	return Local_ReturnError ;

}	
/************************************************END OF FUNCTION*******************************/
static Std_ReturnType CanIf_uint8Transmit_Struct( CAN_TypeDef* CANx, CanTxMsg TxMessage )
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
Std_ReturnType CanIf_uint32Receive_Word( uint32 *Copy_uint32Word)
{
	
	/*Local variable , Return = ok*/
 	Std_ReturnType Local_ReturnError = E_OK;
	
	           /* Check input pionter */
	if ( (NULL_PTR == Copy_uint32Word) )
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
uint32 Local_uint32Data ;	
	
Local_uint32Data = Can_uint32SynRecieveWord( CAN1 , CAN_FIFO0 );
	
(*Copy_uint32Word) = Local_uint32Data ; 


return  Local_ReturnError ;	

}
/************************************************END OF FUNCTION*******************************/
Std_ReturnType CanIf_uint8Receive_Byte( uint8 *Copy_uint8Byte )
{
	
	/*Local variable , Return = ok*/
 	Std_ReturnType Local_ReturnError = E_OK;
	
	           /* Check input pionter */
	if ( (NULL_PTR == Copy_uint8Byte) )
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
uint8 Local_uint8Data ;	
	
Local_uint8Data = Can_uint8SynRecieveByte(  CAN1 , CAN_FIFO0  );
	
(*Copy_uint8Byte) = Local_uint8Data ; 
	
return  Local_ReturnError ;	

}
/************************************************END OF FUNCTION*******************************/

Std_ReturnType CanIf_uint8Receive_Block( uint8 *Copy_uint8DataPtr ,  uint8 Copy_uint8DataLenght)

{
/*Local variable , Return = ok*/
 	Std_ReturnType Local_ReturnError = E_OK;
	
	           /* Check input pionter */
	if ( (NULL_PTR == Copy_uint8DataPtr) )
	{
		Local_ReturnError = E_NOT_OK ; // error status = not  ok 
		
		return  Local_ReturnError ;    //return error stats
	}
	
/*static configuration for all sent messages*/
	/*
 FIFO NUMBER = FIFO 0
 CANX = CAN1 
*/	
	
Can_voidSynRecieveArray( Copy_uint8DataPtr , Copy_uint8DataLenght);
	
return  Local_ReturnError ;	

}
/************************************************END OF FUNCTION*******************************/
Std_ReturnType CanIf_uint8Transmit_Byte( uint8 Copy_uint8Data , uint8  Copy_uint8NodeID  )
{

	/*Local variable , Return = ok*/
 	Std_ReturnType Local_ReturnError = E_OK;
	
	/*Init transmit struct*/
	 CanTxMsg  TxMessage ;  	
	/*satisfy messages ID according to input Node id*/
		switch (Copy_uint8NodeID)                                            
    {
  	 case NODE_ONE_ID : 	
			 
            TxMessage.ID = NODE_ONE_MESS_ID ;
		 
		        break;

  	 case NODE_TWO_ID : 
			 
            TxMessage.ID = NODE_TWO_MESS_ID ;
	
	          break;	 
		default   :				
	                  	/*wrong input node id */
		        break;						
                                                 /*END OF SWITCH CASE*/
	}
		
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
TxMessage.DATA[BYTE_ZERO] = Copy_uint8Data ; // save byte to first element in array
	
	                        /*send frame*/
Local_ReturnError= CanIf_uint8Transmit_Struct( CAN1, TxMessage );
	
return Local_ReturnError ;

}
/************************************************END OF FUNCTION*******************************/
Std_ReturnType CanIf_uint32Transmit_Word( uint32 Copy_uint32Data , uint8  Copy_uint8NodeID  )
{

	/*Local variable , Return = ok*/
 	Std_ReturnType Local_ReturnError = E_OK;
	
	/*Init transmit struct*/
	 CanTxMsg  TxMessage ; 
/*pionter to save word bytes to struct array*/
	uint8 *Local_uint8DataPtr = &Copy_uint32Data ; 	
	/*satisfy messages ID according to input Node id*/
		switch (Copy_uint8NodeID)                                            
    {
  	 case NODE_ONE_ID : 	
			 
            TxMessage.ID = NODE_ONE_MESS_ID ;
		 
		        break;

  	 case NODE_TWO_ID : 
			 
            TxMessage.ID = NODE_TWO_MESS_ID ;
	
	          break;	 
		default   :				
	                  	/*wrong input node id */
		        break;						
                                                 /*END OF SWITCH CASE*/
	}
		
	/*static configuration for all sent messages*/
/*
	DLC = 1 BYTE
	IDE = 0
	RTR = 0
	CANX = CAN1
	DATA[0] = Copy_uint32Data[0]
	DATA[1] = Copy_uint32Data[1]
	DATA[2] = Copy_uint32Data[2]
	DATA[3] = Copy_uint32Data[3]

*/
TxMessage.DATA_LENGHT = FOUR_BYTES ;	
TxMessage.IDE = CONFOIG_IDE ; 
TxMessage.RTR = CONFOIG_RTR ;
	       /* save word byte by byte to first  4 elements in array*/
	for( uint8 Data_Counter = ZERO ; Data_Counter < FOUR_BYTES ; Data_Counter++)	
	    {		
       TxMessage.DATA[Data_Counter] = Local_uint8DataPtr[Data_Counter] ;			
	    }
	                        /*send frame*/
Local_ReturnError= CanIf_uint8Transmit_Struct( CAN1, TxMessage );
	
return Local_ReturnError ;

}
