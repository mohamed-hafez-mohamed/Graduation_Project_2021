/*******************************************************************************
**  FILENAME     : Can.c         			                                        **
**                                                                            **
**  VERSION      : 1.2.0                                                      **
**                                                                            **
**  DATE         : 2021-04-28                                                  **
**                                                                            **
**  PLATFORM     : stm32f103		                                              **
**                                                                            **
**  AUTHOR       : osamahijazi	                                              **
**                                                                            ***                                                                           **
**  DESCRIPTION  : CAN Driver source file                                     **
**                                                                            **
*******************************************************************************/

/**********************************************include******************************************/
#include "BIT_MATH.h"
#include "Std_Types.h"

#include "CAN_Interface.h"
#include "CAN_Private.h"
#include "CAN_cfg.h"

/*
Description: CAN Rx message structure for pending interrupt
*/

/************************************************Functions Definition*******************************/
void CAN_VoidInit(CAN_TypeDef* CANx, CAN_InitTypeDef* CANInitStruct)
{
	
 /* Request to exit Sleep mode */
  CAN1->MCR &= ~CAN_MCR_SLEEP;

  /* Request initialisation */
  CANx->MCR |= CAN_MCR_INRQ ;
	
	 /* Wait for initialization mode */
  while((CAN_MSR_SLAK == (CAN_MSR_SLAK & CAN1->MSR))
     || (CAN_MSR_INAK != (CAN_MSR_INAK & CAN1->MSR)))
  {
    /* Do nothing until initialization mode is entered */
  }
	
                           /******************* SET MCR register configuration**************************/	
	
	/* Set the time triggered communication mode */
    if (CANInitStruct->CAN_TTCM == ENABLE)
    {
      CANx->MCR |= CAN_MCR_TTCM;
    }
    else
    {
      CANx->MCR &= ~(uint32)CAN_MCR_TTCM;
    }
		 /* Set the automatic bus-off management */
    if (CANInitStruct->CAN_ABOM == ENABLE)
    {
      CANx->MCR |= CAN_MCR_ABOM;
    }
    else
    {
      CANx->MCR &= ~(uint32)CAN_MCR_ABOM;
    }
	
	   /* Set the automatic wake-up mode */
    if (CANInitStruct->CAN_AWUM == ENABLE)
    {
      CANx->MCR |= CAN_MCR_AWUM;
    }
    else
    {
      CANx->MCR &= ~(uint32)CAN_MCR_AWUM;
    }
	
		/* Set the no automatic retransmission */
    if (CANInitStruct->CAN_NART == ENABLE)
    {
      CANx->MCR |= CAN_MCR_NART;
    }
    else
    {
      CANx->MCR &= ~(uint32)CAN_MCR_NART;
    }
		
		/* Set the transmit FIFO priority */
    if (CANInitStruct->CAN_TXFP == ENABLE)
    {
      CANx->MCR |= CAN_MCR_TXFP;
    }
    else
    {
      CANx->MCR &= ~(uint32)CAN_MCR_TXFP;
    }
		
		                 
    CANx->BTR =(uint32)      ((uint32)CANInitStruct->CAN_MODE << 30   )  
                       |     ((uint32)CANInitStruct->CAN_SJW  << 24   )  
                       |     ((uint32)CANInitStruct->CAN_BS1  << 16   )  
                       |     ((uint32)CANInitStruct->CAN_BS2  << 20   )  
                       |     ((uint32)CANInitStruct->CAN_Prescaler-1  ) ;
		

    /* Request leave initialisation */
    CANx->MCR &= ~(uint32)CAN_MCR_INRQ;
		
}
/************************************************END OF FUNCTION*******************************/
void CAN_VoidFilterSet(CAN_FilterInitTypeDef* CAN_FilterInitStruct)
{

     uint32 Local_u32filterNumberPosition ; // filter posotion number in the register
	   uint8  Local_u8FilterBankExidId ;	   //contain exdended [15 :17] of filter id
	   uint8  Local_u8FilterBankRtrId  ; //contain rtr offilter id
	   uint8  Local_u8FilterBankIdeId  ; //contain ide of filter id
	   uint16 Local_u16FilterBankStdId ;//contain std id of filter id
	
     uint8  Local_u8FilterBankExidMaskId ;	//contain exdended [15 :17] of filter mask id
	   uint8  Local_u8FilterBankRtrMaskId  ;  //contain rtr of filter  mask id
	   uint8  Local_u8FilterBankIdeIdMask  ;  //contain ide of filter  mask id
	   uint16 Local_u16FilterBankStdIdMask ; //contain std id of filter mask id
	
     uint16 Local_u16FilterbankId  ;  // new id to set in 16-scale filter bank                                           
	   uint16 Local_u16FilterbankMaskId  ;  // new maske id to set in 16-scale filter bank 
                               
	
	            /*Get STID[10:3] STID[2:0] RTR IDE EXID[17:15] of filter id */
  	 Local_u8FilterBankExidId   = (uint8)   ((0x00038000 & CAN_FilterInitStruct->CAN_FilterId) >> 15  ) ;
		 Local_u8FilterBankRtrId    = (uint8)   ((0x00000002 & CAN_FilterInitStruct->CAN_FilterId) << 3   ) ;
		 Local_u8FilterBankIdeId    = (uint8)   ((0x00000004 & CAN_FilterInitStruct->CAN_FilterId) << 1   ) ;
		 Local_u16FilterBankStdId   = (uint16)  ((0xFFE00000 & CAN_FilterInitStruct->CAN_FilterId) >> 16  );
	
			            /*Get STID[10:3] STID[2:0] RTR IDE EXID[17:15] of  filter mask id */
	   Local_u8FilterBankExidMaskId = (uint8) ((0x00038000 & CAN_FilterInitStruct->CAN_FilterMaskId) >> 15  ) ;
		 Local_u8FilterBankRtrMaskId  = (uint8) ((0x00000002 & CAN_FilterInitStruct->CAN_FilterMaskId) << 3   ) ;
		 Local_u8FilterBankIdeIdMask  = (uint8) ((0x00000004 & CAN_FilterInitStruct->CAN_FilterMaskId) << 1   ) ;
		 Local_u16FilterBankStdIdMask =(uint16) ((0xFFE00000 & CAN_FilterInitStruct->CAN_FilterMaskId) >> 16  ) ;
		        	
			
	
 Local_u32filterNumberPosition = ( (uint32)(1) ) << CAN_FilterInitStruct->CAN_FilterBankNumber;
	
 /* Initialisation mode for the filter */
 CAN1->FMR |= CAN_FMR_FINIT;
	
 /* Filter Deactivation */
  CAN1->FA1R &= ~(uint32)Local_u32filterNumberPosition;
	
	if (CAN_FilterInitStruct->CAN_FilterBankScale == CAN_FilterScale_16bit)
  {	
		
    /* 16-bit scale for the filter */
  CAN1->FS1R &= ~(uint32)Local_u32filterNumberPosition;
		
		/* Filter mapping
     *   15-8        7-5    4   3     2-0
     * STID[10:3] STID[2:0] RTR IDE EXID[17:15]
     * */
		                           /*Get masked filter id and filter mask id*/
      Local_u16FilterbankId         = (uint16) ( Local_u8FilterBankExidId     | Local_u8FilterBankRtrId   
                                                | Local_u8FilterBankIdeId     | Local_u16FilterBankStdId    );
																							 
     Local_u16FilterbankMaskId      = (uint16)(Local_u8FilterBankExidMaskId   | Local_u8FilterBankRtrMaskId
                                                | Local_u8FilterBankIdeIdMask | Local_u16FilterBankStdIdMask );		
		
	/* Filter Mode */
  if (CAN_FilterInitStruct->CAN_FilterMode == CAN_FilterMode_IdMask)
  {
    /*Id/Mask mode for the filter*/
    CAN1->FM1R &= ~(uint32)Local_u32filterNumberPosition;
		                                     /*FR1 =FR2 = [Local_u16FilterbankMaskId |Local_u16FilterbankId]*/
		CAN1->sFilterRegister[CAN_FilterInitStruct->CAN_FilterBankNumber].FR1 =  ((0x0000FFFF &  (uint32)Local_u16FilterbankMaskId) << 16 )  
		                                                                        | (0x0000FFFF &  (uint32)Local_u16FilterbankId            ) ;	 
		CAN1->sFilterRegister[CAN_FilterInitStruct->CAN_FilterBankNumber].FR2 =  ((0x0000FFFF &  (uint32)Local_u16FilterbankMaskId) << 16 ) 
		                                                                        | (0x0000FFFF &  (uint32)Local_u16FilterbankId            ) ;	 	
		 	
	}
	else /* ( CAN_FilterInitStruct->CAN_FilterMode == CAN_FilterMode_IdList )*/
  {
    /*Identifier list mode for the filter*/
    CAN1->FM1R |= (uint32)Local_u32filterNumberPosition;
		
				       /*FR1 =FR2 = [Local_u16FilterbankId |Local_u16FilterbankId]*/
		CAN1->sFilterRegister[CAN_FilterInitStruct->CAN_FilterBankNumber].FR1 = ((0x0000FFFF &  (uint32)Local_u16FilterbankId) << 16 )  
		                                                                       | (0x0000FFFF &  (uint32)Local_u16FilterbankId        ) ;	 
		CAN1->sFilterRegister[CAN_FilterInitStruct->CAN_FilterBankNumber].FR2 = ((0x0000FFFF &  (uint32)Local_u16FilterbankId) << 16 )                                                                      		
                                                                        	 | (0x0000FFFF &  (uint32)Local_u16FilterbankId        ) ;	 
		 
	}
}
	
	if (CAN_FilterInitStruct->CAN_FilterBankScale == CAN_FilterScale_32bit)
  {
    /* 32-bit scale for the filter */
    CAN1->FS1R |= (uint32)Local_u32filterNumberPosition;
		
		/* Filter Mode */
  if (CAN_FilterInitStruct->CAN_FilterMode == CAN_FilterMode_IdMask)
  {
    /*Id/Mask mode for the filter*/
    CAN1->FM1R &= ~(uint32)Local_u32filterNumberPosition;
		
    /* for scale 32bit FilterbankID = FR1 and FilterbankMASK = FR2 */
    CAN1->sFilterRegister[CAN_FilterInitStruct->CAN_FilterBankNumber].FR1 = (uint32)CAN_FilterInitStruct->CAN_FilterId ;
    CAN1->sFilterRegister[CAN_FilterInitStruct->CAN_FilterBankNumber].FR2 = (uint32)CAN_FilterInitStruct->CAN_FilterMaskId ;
  }
	
	 else /* ( CAN_FilterInitStruct->CAN_FilterMode == CAN_FilterMode_IdList )*/
		 
  {
		    /*Id list mode for the filter*/
    CAN1->FM1R |= (uint32)Local_u32filterNumberPosition;
		
    /* for scale 32bit FilterbankID = FilterbankMASK = FR1 = FR2 */		
    CAN1->sFilterRegister[CAN_FilterInitStruct->CAN_FilterBankNumber].FR1 = (uint32)CAN_FilterInitStruct->CAN_FilterId ;
    CAN1->sFilterRegister[CAN_FilterInitStruct->CAN_FilterBankNumber].FR2 = (uint32)CAN_FilterInitStruct->CAN_FilterId ;
		
  }
	
}	
	
	/* specify Filter FIFO  */
  if (CAN_FilterInitStruct->CAN_FilterFIFONumber == CAN_Filter_FIFO0)
  {
    CAN1->FFA1R &= ~(uint32)Local_u32filterNumberPosition;     // FIFO 0 chosen for the filter 

  }

  if (CAN_FilterInitStruct->CAN_FilterFIFONumber == CAN_Filter_FIFO1)
  {

    CAN1->FFA1R |= (uint32)Local_u32filterNumberPosition;   // FIFO 1 chosen for the filter
  }
	
  if (CAN_FilterInitStruct->CAN_FilterActivation == ENABLE)
  {
    CAN1->FA1R |= Local_u32filterNumberPosition;  	 // Filter activation 

  }

  CAN1->FMR &= ~CAN_FMR_FINIT;     //release init mode for the input filter */

}
/************************************************END OF FUNCTION*******************************/
 uint8 CAN_VoidTransmit(CAN_TypeDef* CANx, CanTxMsg* TxMessage)
{

	uint8 Local_u8TransMailboxNumber = 0; //contain empty mailbox number
  uint8 Local_u8TransDataCounter ; //counter to set data into Transit Data register byte by byte	
/*	
	if ((CANx->TSR&CAN_TSR_TME0) == CAN_TSR_TME0) //check if mailox 0 is empty
  {
    Local_u8TransMailboxNumber = 0;
  }
  else if ((CANx->TSR&CAN_TSR_TME1) == CAN_TSR_TME1) //check if mailox 1 is empty
  {
    Local_u8TransMailboxNumber = 1;
  }
  else if ((CANx->TSR&CAN_TSR_TME2) == CAN_TSR_TME2) //check if mailox 2 is empty
  {
    Local_u8TransMailboxNumber = 2;
  }
  else
  {
    Local_u8TransMailboxNumber = CAN_TxStatus_NoMailBox; // no mail box is empty
  }
	*/
	       /*mail box always is zero so that receiver chould catch all frams properly*/
//  if (Local_u8TransMailboxNumber != CAN_TxStatus_NoMailBox) //
 // {
		
		 while(!(CAN1->TSR & CAN_TSR_TME0));   // Block until mailbox 0 is empty
		 
		CANx->sTxMailBox[Local_u8TransMailboxNumber].TIR = 0;     //reset identifier register
		
		CANx->sTxMailBox[Local_u8TransMailboxNumber].TIR |= (TxMessage->IDE << 2) | (TxMessage->RTR << 1 ) ;//setrtr and ide of input fram
		
		//set CAN identifier		
		if (TxMessage->IDE) //standard
		{	
			CANx->sTxMailBox[Local_u8TransMailboxNumber].TIR |= (TxMessage->ID << 3); //extended
		}
		
		else //extendedD
		{	
			CANx->sTxMailBox[Local_u8TransMailboxNumber].TIR |= (TxMessage->ID << 21); //standard
		}
		
		CANx->sTxMailBox[Local_u8TransMailboxNumber].TDTR = (CANx->sTxMailBox[Local_u8TransMailboxNumber].TDTR & (~0x0f))		//set data length
				                                               | TxMessage->DATA_LENGHT ;
		
		/*reset transmit data registers*/
		CANx->sTxMailBox[Local_u8TransMailboxNumber].TDLR = 0;
		CANx->sTxMailBox[Local_u8TransMailboxNumber].TDHR = 0;
		
		for ( Local_u8TransDataCounter = 0; Local_u8TransDataCounter < TxMessage->DATA_LENGHT; Local_u8TransDataCounter++)
		{
			
			if (Local_u8TransDataCounter < 4)           //set LSB (16 bits) of the Data 
			{
				CANx->sTxMailBox[Local_u8TransMailboxNumber].TDLR |= (TxMessage->DATA[Local_u8TransDataCounter] << (8 * Local_u8TransDataCounter)); // masking word byte by byte to low register
			}
			else /*(Local_u8DataCounter >= 4) */  //set MSB (16 bits) of the Data
			{
				CANx->sTxMailBox[Local_u8TransMailboxNumber].TDHR |= (TxMessage->DATA[Local_u8TransDataCounter] << (8 * (Local_u8TransDataCounter - 4)));// masking word byte by byte to high register
			}
			
		}
		
		CANx->sTxMailBox[Local_u8TransMailboxNumber].TIR |= CAN_TI0R_TXRQ;  //Transmit Mailbox Request
//	} 

		  return Local_u8TransMailboxNumber; // return result state

}
/************************************************END OF FUNCTION*******************************/
void CAN_VoidReceive(CAN_TypeDef* CANx, uint8 Copy_u8FifoNumber, CanRxMsg* RxMessage)
{
	
	
	uint8 Local_u8ReceivDataCounter ; //counter to Get data into Receiv Data register byte by byte	
	
		RxMessage->DATA_LENGHT = (CANx->sFIFOMailBox[Copy_u8FifoNumber].RDTR & (uint8)0x0F); //get data length
			
		RxMessage->IDE = (CANx->sFIFOMailBox[Copy_u8FifoNumber].RIR & (uint8)0x04) ; // get IDE
			
		RxMessage->RTR = (CANx->sFIFOMailBox[Copy_u8FifoNumber].RIR & (uint8)0x02) ; //get RTR
			
    RxMessage->FMI =  ((CANx->sFIFOMailBox[Copy_u8FifoNumber].RDTR >> 8) & (uint8)0xFF) ;	// Get the FMI 
			
		if ( RxMessage->IDE == 0X00 ) //standard
		{
			RxMessage->ID = ( CANx->sFIFOMailBox[Copy_u8FifoNumber].RIR >> 21) & ((uint32)0x000007FF) ; //get 11 bit of standard id
		}			
		else//extended
		{
			RxMessage->ID = ( CANx->sFIFOMailBox[Copy_u8FifoNumber].RIR >> 3 ) & ((uint32)0x1FFFFFFF) ; // get 29 bit of extended message
		}	
		
		for ( Local_u8ReceivDataCounter = 0;  Local_u8ReceivDataCounter< RxMessage->DATA_LENGHT; Local_u8ReceivDataCounter++)
		
		{
			if (Local_u8ReceivDataCounter < 4)  //get LSB (16 bits) of the Data 
			{
				RxMessage->DATA[Local_u8ReceivDataCounter] = (CANx->sFIFOMailBox[Copy_u8FifoNumber].RDLR >> (Local_u8ReceivDataCounter* 8))  & 0xFF; //get Data from low register byte by byte
			}
			else /*(Local_u8ReceivDataCounter >= 4)*/  //Get LSB (16 bits) of the Data 
			{	
				RxMessage->DATA[Local_u8ReceivDataCounter] = (CANx->sFIFOMailBox[Copy_u8FifoNumber].RDHR >> ((Local_u8ReceivDataCounter - 4) * 8)) & 0xFF; //get Data from high register byte by byte
			}	
						
		}
		
		if (Copy_u8FifoNumber == CAN_FIFO0) //check for input FIFO to release
  {
		
    CANx->RF0R |= CAN_RF0R_RFOM0;  //release FIFO 0
		
  }
	
  else if ( Copy_u8FifoNumber == CAN_FIFO1) 
  {
		
    CANx->RF1R |= CAN_RF1R_RFOM1;  //release FIFO 1

  }
	
	else
	{
	
	/*wrong fifo number input*/
	}
		
}
/************************************************END OF FUNCTION*******************************/
uint8 CAN_u8GetLastErrorCodeType(CAN_TypeDef* CANx)
{
  uint8 Local_u8ErrorcodeType=0; //contain Code error Type
  
  Local_u8ErrorcodeType = (((uint8)CANx->ESR) & (uint8)CAN_ESR_LEC); // Get the last error code
  
  return Local_u8ErrorcodeType;//Return the error code
}
/************************************************END OF FUNCTION*******************************/
void CAN_VoidInterruptSet(CAN_TypeDef* CANx, uint32 Copy_u32CanInterruptType, FunctionalState Copy_u8InterruptNewState)
{

  if (Copy_u8InterruptNewState == ENABLE) //check for input new state of input interrupt
  {
    
    CANx->IER |= Copy_u32CanInterruptType; // Enable the selected CANx interrupt 
  }
  else if (Copy_u8InterruptNewState == DISABLE) 
  {
    CANx->IER &= ~Copy_u32CanInterruptType; // Disable the selected CANx interrupt 

  }
	else
	{
	   /*WRONG STATE INPUT*/
	}
}
/************************************************END OF FUNCTION*******************************/
void CAN_VoidTimeTriggerCommMode(CAN_TypeDef* CANx, FunctionalState NewState , uint8 Copy_u8MailBoxNumber)
{
   
	if ( Copy_u8MailBoxNumber > 2) //check to mail box number
	{
	
	/*wrong input mail box*/	
	return   ;
		
	}
	
  if (NewState == ENABLE)
  {
		
		/*This bit is active only when the hardware is in the Time Trigger Communication mode*/
		
    CANx->MCR |= CAN_MCR_TTCM;  //  Enable the TTCM mode 

    CANx->sTxMailBox[Copy_u8MailBoxNumber].TDTR |= (uint32)CAN_TDT0R_TGT; // set the bit
   
  }
  else if (NewState == DISABLE)
  {
		
    CANx->MCR &= ~(uint32)CAN_MCR_TTCM;     // Disable the TTCM mode 

    CANx->sTxMailBox[Copy_u8MailBoxNumber].TDTR &= (uint32)~CAN_TDT0R_TGT; //reset thebit
    
  }
	
	else
  {
	
	/*wrong input state*/
		
	
	}
}

/************************************************END OF FUNCTION*******************************/
void USB_HP_CAN1_TX0_IRQHandler (void)
	{
                                  /*Check For Request completed mailbox */
		
		CanRxMsg   RxMessage;               // CAN messge   struct  for  receiving

				
  if (CAN1->TSR & CAN_TSR_RQCP0)   // request completed mbx 0
		{                
  
    CAN1->TSR |= CAN_TSR_RQCP0;                    // reset request complete mbx 0
	
    CAN1->IER &= ~CAN_IER_TMEIE;                   // disable  TME interrupt
	
  }
	else if(CAN1->TSR & CAN_TSR_RQCP1)          // request completed mbx 1
{

	  CAN1->TSR |= CAN_TSR_RQCP1;                    // reset request complete mbx 0
	
    CAN1->IER &= ~CAN_IER_TMEIE;                   // disable  TME interrupt

}
else if(CAN1->TSR & CAN_TSR_RQCP2)          // request completed mbx 1
{

	  CAN1->TSR |= CAN_TSR_RQCP2;                    // reset request complete mbx 0
	
    CAN1->IER &= ~CAN_IER_TMEIE;                   // disable  TME interrupt
}

else
{
     /*no data t capture*/
}
	
}
/************************************************END OF FUNCTION*******************************/
void USB_LP_CAN1_RX0_IRQHandler (void) 
	{
		
		 /*check if it is software reset interrupt or normal message*/
		WDG_VoidSoftReset();
	  CanRxMsg   RxMessage;               // CAN messge   struct  for  receiving

  if (CAN1->RF0R & CAN_RF0R_FMP0)  // CHECK IF fifo 0 is not empty
		
{			      
  
	CAN_VoidReceive ( CAN1 , CAN_FIFO0 ,&RxMessage);                       // read the message of FIFO 0
	
  }
	
	else if (CAN1->RF1R & CAN_RF1R_FMP1)       // CHECK IF fifo 1 is not empty
	{
	
	CAN_VoidReceive ( CAN1 , CAN_FIFO1,&RxMessage);                  // read the message	of FIFO 1
	
	}	
else
{

      /*no data t capture*/
}	
}
/************************************************END OF FUNCTION*******************************/
void Can_voidSynRecieveArray( uint8 *Copy_uint8DataPtr ,  uint8 Copy_uint8DataLenght)
{
	
  uint8 counter1 = ZERO ;	
	uint8 Frame_Number = (Copy_uint8DataLenght / FRAME_DATA) ;
	
	for(uint8 Data_Counter1 = ZERO ; Data_Counter1 < Frame_Number ; Data_Counter1++)
{	
	
CanRxMsg   RxMessage;               // CAN messge   struct  for  receiving

 while (!(CAN1->RF0R & CAN_RF0R_FMP0));  // wait until fifo 0 become pending	
  
	CAN_VoidReceive ( CAN1 , CAN_FIFO0 ,&RxMessage);                       // read the message of FIFO 0		
	
	for( uint8 Data_Counter = ZERO ; Data_Counter < FRAME_DATA ; Data_Counter++)	
	 {
				
      Copy_uint8DataPtr[counter1]= RxMessage.DATA[Data_Counter]   ;
				
					counter1++ ;							
   }
	

}	
}

/************************************************END OF FUNCTION*******************************/
uint32 Can_uint32SynRecieveWord(CAN_TypeDef* CANx, uint8 Copy_u8FifoNumber  )
{
	
  uint32 Copy_uint32Data = ZERO ;
	
  CanRxMsg   RxMessage;               // CAN messge   struct  for  receiving
	
  while (!(CAN1->RF0R & CAN_RF0R_FMP0));  // wait until fifo 0 become pending	
  
	CAN_VoidReceive ( CANx , Copy_u8FifoNumber ,&RxMessage);   // read the message of FIFO 0		
	
	Copy_uint32Data = (uint32)((RxMessage.DATA[BYTE_THREE]<<24) | (RxMessage.DATA[BYTE_TWO]<<16) | (RxMessage.DATA[BYTE_ONE]<<8) | (RxMessage.DATA[BYTE_ZERO]) ) ;
	
	return  Copy_uint32Data ;
}

/************************************************END OF FUNCTION*******************************/
uint8 Can_uint8SynRecieveByte( CAN_TypeDef* CANx, uint8 Copy_u8FifoNumber  )
{

 uint8 Copy_uint8Data = ZERO ;		
	
  CanRxMsg   RxMessage;               // CAN messge   struct  for  receiving

  while (!(CAN1->RF0R & CAN_RF0R_FMP0));  // wait until fifo 0 become pending	
  
	CAN_VoidReceive ( CANx , Copy_u8FifoNumber ,&RxMessage);   // read the message of FIFO 0		
	
	Copy_uint8Data = (uint8)((RxMessage.DATA[BYTE_ZERO]) ) ;
	
	return  Copy_uint8Data ;


}
	
