/*******************************************************************************
**  FILENAME     : Can_Interface.h         			                              **
**                                                                            **
**  VERSION      : 1.2.0                                                      **
**                                                                            **
**  DATE         : 2021-04-02                                                  **
**                                                                            **                                                                            **
**  PLATFORM     : stm32f103		                                              **
**                                                                            **
**  AUTHOR       : osamahijazi	                                              **
                                                                              **
**  DESCRIPTION  : CAN Driver interface file                                  **
**                                                                            **
*******************************************************************************/

/* Define to prevent recursive inclusion */

#ifndef CAN_INTERFACE_H
#define CAN_INTERFACE_H



/*****************************************************************************************/
/*                                   Include headres                                     */
/*****************************************************************************************/
#include "Std_Types.h"
#include "CAN_Private.h"
#include "CAN_cfg.h"

/******************************************************************************************/
/*                                    Macro Definition                                    */
/*******************************************************************************************/

/************************************************can status**********************************/

#define CAN_InitStatus_Failed             ((uint8)0x00) /* CAN initialization failed */
#define CAN_InitStatus_Success            ((uint8)0x01) /* CAN initialization OK */

/**************************************************can mode *********************************/	

#define CAN_Mode_Normal                   ((uint8)0x00)  /* normal mode */
#define CAN_Mode_LoopBack                 ((uint8)0x01)  /* loopback mode */
#define CAN_Mode_Silent                   ((uint8)0x02)  /* silent mode */
#define CAN_Mode_Silent_LoopBack          ((uint8)0x03)  /* loopback combined with silent mode */

/*********************************************can operating mode******************************/

#define CAN_OperatingMode_Init            ((uint8)0x00) /* Initialization mode */
#define CAN_OperatingMode_Normal          ((uint8)0x01) /* Normal mode */
#define CAN_OperatingMode_Sleep           ((uint8)0x02) /* sleep mode */

/*************************************************can mode input status************************/

#define CAN_ModeStatus_Failed             ((uint8)0x00)                     /* CAN entering the specific mode failed */
#define CAN_ModeStatus_Success            ((uint8)!CAN_ModeStatus_Failed)   /* CAN entering the specific mode Succeed */

/******************************************CAN_synchronisation_jump_width*********************/

#define CAN_SJW_1tq                       ((uint8)0x00)  /* 1 time quantum */
#define CAN_SJW_2tq                       ((uint8)0x01)  /* 2 time quantum */
#define CAN_SJW_3tq                       ((uint8)0x02)  /* 3 time quantum */
#define CAN_SJW_4tq                       ((uint8)0x03)  /* 4 time quantum */
													 
/*****************************************CAN_filter bank scale types**************************/

#define CAN_FilterScale_16bit             ((uint8)0x00) /* Two 16-bit filters */
#define CAN_FilterScale_32bit             ((uint8)0x01) /* One 32-bit filter */

/****************************************************can filer mode****************************/

#define CAN_FilterMode_IdMask            ((uint8)0x00)  /* identifier/mask mode */
#define CAN_FilterMode_IdList            ((uint8)0x01)  /* identifier list mode */

/****************************************************CAN_filter_FIFO**************************/	

#define CAN_Filter_FIFO0             ((uint8)0x00)  /* Filter FIFO 0 assignment for filter x */
#define CAN_Filter_FIFO1             ((uint8)0x01)  /* Filter FIFO 1 assignment for filter x */

/*************************************************CAN transmit_constants***********************/

#define CAN_TxStatus_Failed          ((uint8)0x00) /*  CAN transmission failed */
#define CAN_TxStatus_Ok              ((uint8)0x01) /* CAN transmission succeeded */
#define CAN_TxStatus_Pending         ((uint8)0x02) /* CAN transmission pending */
#define CAN_TxStatus_NoMailBox       ((uint8)0x04) /* CAN cell did not provide an empty mailbox */

/*********************************************CAN receive FIFO numbers***********************/

#define CAN_FIFO0                   ((uint8)0x00) /* CAN FIFO 0 used to receive */
#define CAN_FIFO1                   ((uint8)0x01) /* CAN FIFO 1 used to receive */		

/**********************************************CAN jump width constants *********************/

#define CAN_SJW_1tq                 ((uint8)0x00)  /* 1 time quantum */
#define CAN_SJW_2tq                 ((uint8)0x01)  /* 2 time quantum */
#define CAN_SJW_3tq                 ((uint8)0x02)  /* 3 time quantum */
#define CAN_SJW_4tq                 ((uint8)0x03)  /* 4 time quantum */

/********************************************CAN time quantum in bit segment_1* *****************/
#define CAN_BS1_1tq                 ((uint8)0x00)  /* 1 time quantum */
#define CAN_BS1_2tq                 ((uint8)0x01)  /* 2 time quantum */
#define CAN_BS1_3tq                 ((uint8)0x02)  /* 3 time quantum */
#define CAN_BS1_4tq                 ((uint8)0x03)  /* 4 time quantum */
#define CAN_BS1_5tq                 ((uint8)0x04)  /* 5 time quantum */
#define CAN_BS1_6tq                 ((uint8)0x05)  /* 6 time quantum */
#define CAN_BS1_7tq                 ((uint8)0x06)  /* 7 time quantum */
#define CAN_BS1_8tq                 ((uint8)0x07)  /* 8 time quantum */
#define CAN_BS1_9tq                 ((uint8)0x08)  /* 9 time quantum */
#define CAN_BS1_10tq                ((uint8)0x09)  /* 10 time quantum */
#define CAN_BS1_11tq                ((uint8)0x0A)  /* 11 time quantum */
#define CAN_BS1_12tq                ((uint8)0x0B)  /* 12 time quantum */
#define CAN_BS1_13tq                ((uint8)0x0C)  /* 13 time quantum */
#define CAN_BS1_14tq                ((uint8)0x0D)  /* 14 time quantum */
#define CAN_BS1_15tq                ((uint8)0x0E)  /* 15 time quantum */
#define CAN_BS1_16tq                ((uint8)0x0F)  /* 16 time quantum */

/*******************************************CAN time quantum In bit segment_2*******************/	

#define CAN_BS2_1tq                 ((uint8)0x00)  /* 1 time quantum */									
#define CAN_BS2_2tq                 ((uint8)0x01)  /* 2 time quantum */									
#define CAN_BS2_3tq                 ((uint8)0x02)  /* 3 time quantum */									
#define CAN_BS2_4tq                 ((uint8)0x03)  /* 4 time quantum */									
#define CAN_BS2_5tq                 ((uint8)0x04)  /* 5 time quantum */									
#define CAN_BS2_6tq                 ((uint8)0x05)  /* 6 time quantum */
#define CAN_BS2_7tq                 ((uint8)0x06)  /* 7 time quantum */
#define CAN_BS2_8tq                 ((uint8)0x07)  /* 8 time quantum */

/*****************************************************CAN Error Types*****************************/       

#define CAN_NoError                 ((uint8)0x00) /* No Error */ 
#define	CAN_StuffError              ((uint8)0x10) /* Stuff Error */ 
#define	CAN_FormError               ((uint8)0x20) /* Form Error */ 
#define	CAN_ACKError                ((uint8)0x30) /* Acknowledgment Error */ 
#define	CAN_BitRecessiveError       ((uint8)0x40) /* Bit Recessive Error */ 
#define	CAN_BitDominantError        ((uint8)0x50) /* Bit Dominant Error */ 
#define	CAN_CRCError                ((uint8)0x60) /* CRC Error  */ 
#define	CAN_SoftwareSetError        ((uint8)0x70) /* Software Set Error */

/*************************************can interrupts for " Transmit , Receive , Error and Modes Ack "*****/																			
#define  CAN_TMEIE                       ((uint32)0x00000001) /*transmit mail box empt*/
#define  CAN_FMPIE0                      ((uint32)0x00000002) /*FIFO 0 pending interrupt*/
#define  CAN_FFIE0                       ((uint32)0x00000004) /*FIFO 0 full interrupt*/
#define  CAN_FOVIE0                      ((uint32)0x00000008) /*FIFO 0 oveeun interrupt*/
#define  CAN_FMPIE1                      ((uint32)0x00000010) /*FIFO 1 pending interrupt*/
#define  CAN_FFIE1                       ((uint32)0x00000020) /*FIFO 1 full interrupt*/
#define  CAN_FOVIE1                      ((uint32)0x00000040) /*FIFO 1 overun interrupt*/
#define  CAN_EWGIE                       ((uint32)0x00000100) /*Error Warning interrupt*/
#define  CAN_EPVIE                       ((uint32)0x00000200) /*error passive interrupt*/
#define  CAN_BOFIE                       ((uint32)0x00000400) /*bus off interupt*/
#define  CAN_LECIE                       ((uint32)0x00000800) /*code type error interrupt*/
#define  CAN_ERRIE                       ((uint32)0x00008000) /*error interrupt*/
#define  CAN_WKUIE                       ((uint32)0x00010000) /*Wake up mode interrupt*/
#define  CAN_SLKIE                       ((uint32)0x00020000) /*Sleep   mode interrupt*/
/*
Description: CAN Tx message structure definition
*/
typedef struct {
	
	uint8 IDE;  //1 -> extended identifier,0 -> standard identifier
	
	uint8 RTR;  //1 -> Remote frame, 0 -> Data frame
	
	uint32 ID;  // message identifier
	
	uint8 DATA_LENGHT;  //number of data bytes "0 - 8"
	
	uint8 DATA[8];  // pointer to the data 
	
}CanTxMsg ;

/*
Description: CAN Rx message structure definition
*/
typedef struct {
	
	uint8 IDE;  //1 -> extended identifier,0 -> standard identifier
	
	uint8 RTR;  //1 -> Remote frame, 0 -> Data frame
	
	uint32 ID;  // message identifier
	
	uint8 DATA_LENGHT;  //number of data bytes "0 - 8"
	
	uint8 DATA[8];  // pointer to the data 
	
	uint8 FMI;      // contain the index of the filter the message was stored in 
                       
}CanRxMsg ;


/*
This container contains the configuration parameters 
and sub containers of the  Can HW.
/*Not used in this version*/
volatile typedef struct 
{
    /*Reference to CAN Controller */
    CAN_TypeDef*  CanControllerBaseAddress;
    /*This container contains the configuration  */
    CAN_InitTypeDef*  CanHwdefRef;
	
} Can_ConfigType;


/***********************************************************************************/
                      /***FUNCTIONS PROTOTYPES***/
/***********************************************************************************

*Name       :   CAN_VoidInit

*Description: * Initializes the CAN peripheral according 
                 to the specified parameters in the init struct  
							
*Pre-Cond   :	None				
							
*pos-Cond   : None

*Input      : -canx struct "x=1,2,..."  according to how many can in controller
              CAN InitStruct to specifiy the configuration
             fifo number we want to receive the message located on itvoid
               message fram struct address that will contain reveived message	
*Output     :


*Return     : void

************************************************************************************/
void CAN_VoidInit(CAN_TypeDef* CANx, CAN_InitTypeDef* CANInitStruct) ;
/************************************************************************************

*Name       :   CAN_VoidFilterSet

*Description: * Initializes specific filtr bank with   
							  configuration in filter init struct
								
*Pre-Cond   :	None				
							
*pos-Cond   : None

*Input      : None 

*Output     : void

*Return     : void

*************************************************************************************/
void CAN_VoidFilterSet(CAN_FilterInitTypeDef* CAN_FilterInitStruct);
/************************************************************************************

*Name       :   CAN_VoidReceive

*Description: * init receive message struct to receive can frame 
                in specific fifo 
								
*Pre-Cond   :	None				
							
*pos-Cond   : None

*Input      : -canx struct "x=1,2,..."  according to how many can in controller
              CAN InitStruct to specifiy the configuration
						 - fifo number we want to receive the message located on it
             - message fram struct address that will contain reveived message						 

*Output     : void

*Return     : void

*************************************************************************************/
void CAN_VoidReceive(CAN_TypeDef* CANx, uint8 Copy_u8FifoNumber, CanRxMsg* RxMessage);
/************************************************************************************

*Name       :   CAN_VoidTransmit

*Description: * init transmit can frame to send it throught 
                specific mail box
								
*Pre-Cond   :	None				
							
*pos-Cond   : None

*Input      : -canx struct "x=1,2,..."  according to how many can in controller
              CAN InitStruct to specifiy the configuration
             - message fram struct address that will contain transmit message						 

*Output     : void

*Return     : void

*************************************************************************************/
uint8 CAN_VoidTransmit(CAN_TypeDef* CANx, CanTxMsg*  TxMessage);
/************************************************************************************

*Name       :   CAN_u8GetLastErrorCodeType

*Description: * get the last accured error in "CANx->ESR"register
                 get the value of t2 bits specific for can error
								
*Pre-Cond   :	None				
							
*pos-Cond   : None

*Input      : -canx struct "x=1,2,..."  according to how many can in controller
              CAN InitStruct to specifiy the configuration
             - 						 

*Output     : error code Type , the Error should be one of the following
              No Error  
							Stuff Error
							Form Error
							Acknowledgment Error
							Bit Recessive Error
							Bit Dominant Error
							CRC Error
							Software Set Error  

*Return     : void
*************************************************************************************/
uint8 CAN_u8GetLastErrorCodeType(CAN_TypeDef* CANx);
/************************************************************************************

*Name       :   CAN_VoidInterruptSet

*Description: * Enables or disables the specified CANx interrupts.   
							
*Pre-Cond   :	None				
							
*pos-Cond   : None

*Input      : -canx struct "x=1,2,..."  according to how many can in controller
              CAN InitStruct to specifiy the configuration
							- type of interrupt you want to enable or disable,it should be on of the following :
							CAN_IER_TMEIE 
							CAN_FMPIE0
							CAN_FFIE0 
							CAN_FOVIE0
							CAN_FMPIE1
							CAN_FFIE1 
							CAN_FOVIE1
							CAN_EWGIE 
							CAN_EPVIE 
							CAN_BOFIE 
							CAN_LECIE 
							CAN_ERRIE 
							CAN_WKUIE 
							CAN_SLKIE 
*Output     : void

*Return     : last Error code type
****************************************************************************************/
void CAN_VoidInterruptSet(CAN_TypeDef* CANx, uint32 Copy_u32CanInterruptType, FunctionalState Copy_u8InterruptNewState);
/************************************************************************************

*Name       :   CAN_VoidTransmit

*Description: * activate or deactivate time trigger communication mode of a specific mailbox 

*Notes      :  DLC must be 8 bytes in order these two bytes to be sent over the CAN bus.
								
*Pre-Cond   :	None				
							
*pos-Cond   : None

*Input      : -canx struct "x=1,2,..."  according to how many can in controller
              CAN InitStruct to specifiy the configuration
             -new state of the mode
             -number of the mail box to activate						 

*Output     : void

*Return     : void

*************************************************************************************/
void CAN_VoidTimeTriggerCommMode(CAN_TypeDef* CANx, FunctionalState NewState , uint8 Copy_u8MailBoxNumber);
/************************************************************************************

*Name       :   Can_voidSynRecieveArray

*Description: * Recive Array of Data 
								
*Pre-Cond   :	None				
							
*pos-Cond   : None

*Input      : beside static configurations , input can unit and fifo number						 

*Output     : void

*Return     : void

*************************************************************************************/
void Can_voidSynRecieveArray( uint8 *Copy_uint8DataPtr ,  uint8 Copy_uint8DataLenght);
/************************************************************************************

*Name       :   Can_voidSynRecieveWord

*Description: * Recive only one word in FIFO O
								
*Pre-Cond   :	None				
							
*pos-Cond   : None

*Input      : beside static configurations , input can unit and fifo number						 

*Output     : void

*Return     : void

*************************************************************************************/
uint32 Can_uint32SynRecieveWord(CAN_TypeDef* CANx, uint8 Copy_u8FifoNumber  );
/************************************************************************************

*Name       :   Can_voidSynRecieveByte

*Description: * Recive only one byte in FIFO O
								
*Pre-Cond   :	None				
							
*pos-Cond   : None

*Input      : beside static configurations , input can unit and fifo number						 

*Output     : void

*Return     : void

*************************************************************************************/
uint8 Can_uint8SynRecieveByte(CAN_TypeDef* CANx, uint8 Copy_u8FifoNumber  );



#endif
/******************************************END OF FILE************************************/
