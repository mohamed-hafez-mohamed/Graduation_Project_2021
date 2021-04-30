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
#include "BIT_MATH.h"
#include "Std_Types.h"

#include "CanIf_Interface.h"
#include "CanIf_Private.h"
#include "CanIf_cfg.h"

#include "CAN_Interface.h"

uint8 CanIf_uint8TransmitData( const uint8 *Copy_uint8DataPtr, uint8 Copy_uint8NodeID , uint8 Copy_uint8DataLenght)
{
	
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
  uint8 Local_uint8FramsNumber = (uint8)(Copy_uint8DataLenght / FRAME_DATA_BYTES ) ;	
	
for (uint8 Round_Counter = 0; Round_Counter < Local_uint8FramsNumber ; Round_Counter++) // send 8 byte in each round  
    {
			/*fetch Data from input buffer byte by byte*/
			for( uint8 Data_Counter = 0 ; Data_Counter < EIGTH_ROUNDS ; Data_Counter++)	
	    {
				
       TxMessage.DATA[Data_Counter] = Copy_uint8DataPtr[Data_Counter] ;
				
	    }
			/*send frame*/
		  CAN_VoidTransmit( CAN1 , &TxMessage );
		/*increment input pionter by 8 byte to get second frame data inext round*/
			Copy_uint8DataPtr += FRAME_DATA_BYTES ;			
   }
		
  return Local_ReturnError ;

}
/************************************************END OF FUNCTION*******************************/
uint8 CanIf_uint8Transmit_1Byte( uint8 Copy_uint8Data, uint8 Copy_uint8NodeID)
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
			
			   Local_ReturnError = E_NOT_OK;	                  	/*wrong input node id */
			   
			   return Local_ReturnError ;

		        break;						
                                                 /*END OF SWITCH CASE*/
	}
		
	/*static configuration for all sent messages*/
	/*
	DLC = 8 BYTE
	IDE = 0
	RTR = 0
	CANX = CAN1
	DaATA[0] = Copy_uint8Data
	*/
  TxMessage.DATA_LENGHT = ONE_BTYE ;	
	TxMessage.IDE = CONFOIG_IDE ; 
  TxMessage.RTR = CONFOIG_RTR ;	
  TxMessage.DATA[BYTE_ZERO] = Copy_uint8Data ;
	/*send frame that iclude only one byte*/
  CAN_VoidTransmit( CAN1 , &TxMessage );
	
	return Local_ReturnError ;
	
}
/************************************************END OF FUNCTION*******************************/
uint8 CanIf_uint8Receive_1Byte(void)
{
/* CAN messge   struct  for  receiving*/
CanRxMsg  RxMessage;
	/*init received byte as zero*/
RxMessage.DATA[0] = 0 ; 	

/*static configuration for all sent messages*/
	/*
 FIFO NUMBER = FIFO 0
 CANX = CAN1 
*/
	CAN_VoidReceive ( CAN1 , CAN_FIFO0 , &RxMessage );	// check if there is a received message

	return (RxMessage.DATA[BYTE_ZERO]) ;
		
}
/************************************************END OF FUNCTION*******************************/
uint8 CanIf_uint8Receive_Struct(CAN_TypeDef* CANx, uint8 Copy_u8FifoNumber, CanRxMsg RxMessage)
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
uint8 CanIf_uint8Transmit_Struct( CAN_TypeDef* CANx, CanTxMsg TxMessage )
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

