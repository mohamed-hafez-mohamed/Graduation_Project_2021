/*******************************************************************************
**  FILENAME     : Can_cfg.h              			                              **
**                                                                            **
**  VERSION      : 1.2.0                                                      **
**                                                                            **
**  DATE         : 2021-02-2                                                  **
**                                                                            **                                                                            **
**  PLATFORM     : stm32f103		                                              **
**                                                                            **
**  AUTHOR       : osamahijazi	                                              **
                                                                              **
**  DESCRIPTION  : CAN Driver configuration file                              **
**                                                                            **
*******************************************************************************/
#ifndef CAN_CFG_H
#define CAN_CFG_H

#include "Std_Types.h"
#include "CAN_Private.h"


/*
Description: CAN Init structure configuration
*/
typedef struct
{
  uint16 CAN_Prescaler;  //describe time quantum length                             
  
  uint8 CAN_MODE;     // describe the operation mode of can driver                                                          

  uint8 CAN_SJW;  // describe max number of time quantum                                    
                                                                           
  uint8 CAN_BS1;   // describe time quantum in segment 1                                   
                         
  uint8 CAN_BS2;   // describe time quantum in seqment 2                                  
                                                       
  FunctionalState CAN_TTCM; //enable  or disable time trigger communication mode                            
                             
  FunctionalState CAN_ABOM; //Enable or disable the automatic bus-off  management                                                      

  FunctionalState CAN_AWUM;  //Enable or disable the automatic wake-up mode                                                      

  FunctionalState CAN_NART; //Enable or disable the no-automatic retransmission mode                                                      

  FunctionalState CAN_RFLM;  // Enable or disable the Receive FIFO Locked mode                                                    

  FunctionalState CAN_TXFP;  // Enable or disable the transmit FIFO priority                           
														
} CAN_InitTypeDef;

/*
Description: CAN filter init structure definition
*/
typedef struct
{
  uint32 CAN_FilterId;         // contain ID of filter bank
                                                        
  uint32 CAN_FilterMaskId;     //contain Mask of filter bank
	
	uint8 CAN_FilterMode;        // specifiy the mode of filter "ID OR MASK" 

  uint8 CAN_FilterBankNumber;  //contain the filter bank numer to specifiy
	
	uint8 CAN_FilterBankScale;   // Specify the bank scale type " 16 or 32"                      
                                                                                
  uint8 CAN_FilterFIFONumber; //contain the FIFO number to add bank to it
                             
  FunctionalState CAN_FilterActivation; // specify the state of the filter "ENABLE OR DISABLE"
	
} CAN_FilterInitTypeDef;


#endif
/**************************************************************END OF FILE*********************************************************************************************************************************************************************/
