/*****************************************************/
 /* Author      : Mosad                              */
 /* Version     : v01                                */
 /* date        : 2/5/2020                           */
/*****************************************************/
/* Library includes */
#include "BIT_MATH.h"
#include "Std_Types.h"
#include "Rte_ReceiveUpatePort.h"

/* Module includes */
#include "ReceiveUpdate_Interface.h"
#include "ReceiveUpdate_Cfg.h"
#include "ReceiveUpdate_Private.h"

/**************************************************************************/
/*                         Global Variables                              */
/**************************************************************************/
static uint32 Global_CrcValue ;
static uint32 Global_SizeValue ;
static uint8 Global_NodeId ;
static SystemStateType Global_SystemState ;
static ReceiveUpdateStateType Global_RxInternalSate ;
static uint8 Global_HeaderBuffer[9];
static uint8 Global_NumberOfPackets ;
static uint16 Global_RemainingBytes ;
static uint8 Global_RxUserResponse;
static uint8 Global_RxBuffer[PACKET_SIZE];
static float32 Global_DownloadPercentage;
static uint8 Global_DownloadUpdateProgeress;
static uint32 Global_ReceivedBytes;

/**************************************************************************/
/*                         Module Functions                               */
/**************************************************************************/

void ReceiveUpdate_voidInit(void)
{
	/* Init Variables */
	Global_CrcValue = INITIAL_VALUE ;
	Global_SizeValue = INITIAL_VALUE ;
	Global_NodeId = INITIAL_VALUE ;
	Global_SystemState = SYS_IDLE ;
	Global_RxInternalSate = RX_IDLE ;
	Global_NumberOfPackets = INITIAL_VALUE ;
	Global_RemainingBytes = INITIAL_VALUE;
	Global_RxUserResponse = INITIAL_VALUE;
	Global_DownloadPercentage = INITIAL_VALUE ;
	Global_DownloadUpdateProgeress = INITIAL_VALUE ;
	Global_ReceivedBytes = INITIAL_VALUE;
	/* Init ESP (uart) interrupt to receive requests */
	ESP_RX_ASYNCH (Esp_NewReq);
}


void ReceiveUpdate_MainFunction (void)
{
	switch (Global_RxInternalSate)
	{
		
		/*****************************RX_IDLE***********************************/
		case RX_IDLE :
		{
			/* read system response */
			uint8 Local_Error = RTE_READ_USER_RESPONSE(&Global_RxUserResponse);
			if (E_OK == Local_Error)
			{
				if (ACCEPT_UPDATE == Global_RxUserResponse)
				{
					Global_RxInternalSate = RX_ACCEPT_UPDATE ;
				}
				else if (REFUSE_UPDATE == Global_RxUserResponse)
				{
					Global_RxInternalSate = RX_REFUSE_UPDATE ;
				}
				else
				{
					
				}
			}
			else if (E_NOT_OK == Local_Error)
			{
				/* Report Error */
			}
			else 
			{
				
			}
			break;
		}
		
		/*****************************RX_ACCEPT_UPDATE ***********************************/
		case RX_ACCEPT_UPDATE :
		{
			/* Inform ESP to accept request */
			ESP_TX_BYTE(REQUEST_ACCEPTED);
			/* Change Internal State */
			Global_RxInternalSate = RX_RECEIVE_HEADER ;
			break;
		}
		
		/*****************************RX_REFUSE_UPDATE***********************************/
		case RX_REFUSE_UPDATE :
		{
			/* Inform ESP to Reject request */
			ESP_TX_BYTE(REQUEST_REFUSED);
			/* Initialize */
			Global_RxUserResponse = INITIAL_VALUE;
			/* Change System state */
			RTE_WRITE_SYSTEM_STATE(SYS_IDLE);
			/* Enable Uart interrupt */
			ESP_RX_ASYNCH (Esp_NewReq);
			/* Change Internal State */
			Global_RxInternalSate = RX_IDLE ;
			break;
		}
		
		/*****************************RX_RECEIVE_HEADER***********************************/
		case RX_RECEIVE_HEADER : 
		{
			/* Inform ESP to send Header */
			ESP_TX_BYTE(ESP_SEND_HEADER);
			
			/* Receive Header */
			ESP_RX_SYNCH(Global_HeaderBuffer , 9);
			
			/* Process header */
			Global_SizeValue = Global_HeaderBuffer[0] | (Global_HeaderBuffer[1] << SHIFT_BY_8) |(Global_HeaderBuffer[2] << SHIFT_BY_16) | (Global_HeaderBuffer[3] << SHIFT_BY_24);
			Global_CrcValue = Global_HeaderBuffer[4] | (Global_HeaderBuffer[5] << SHIFT_BY_8) |(Global_HeaderBuffer[6] << SHIFT_BY_16) | (Global_HeaderBuffer[7] << SHIFT_BY_24);
			Global_NodeId = Global_HeaderBuffer[8] ;
			
			/* Write Datat To Rte */
			RTE_WRITE_CRC_VALUE(Global_CrcValue);
			RTE_WRITE_CODE_SIZE(Global_SizeValue);
			RTE_WRITE_NODE_ID(Global_NodeId);
			RTE_WRITE_HEADER_ACK_FLAG(HEADER_SET);
			
			/* Get info from header */
			Global_NumberOfPackets  = (uint8)(Global_SizeValue / PACKET_SIZE) ;
			Global_RemainingBytes = (Global_SizeValue % PACKET_SIZE);
			
			/* Ack Header */
			ESP_TX_BYTE(HEADR_RECEIVED);
			
			/* Change State */
			Global_RxInternalSate = RX_RECEIVE_PACKET ;
			
			break;
		}
		
		/*****************************RX_RECEIVE_PACKET***********************************/
		case RX_RECEIVE_PACKET : 
		{
			ESP_TX_BYTE(SEND_NEXT_PACKET);
			if (Global_NumberOfPackets > 0)
			{
				/* Receive packet */
				ESP_RX_SYNCH(Global_RxBuffer,PACKET_SIZE);
				Global_NumberOfPackets--;
				/* Store Packet */
				Nvm_WriteBlock (Global_RxBuffer , PACKET_SIZE);
				/* Ack Packet */
				ESP_TX_BYTE(PACKET_RECEIVED);
				/* Update Received byte to calculate progress */
				Global_ReceivedBytes += PACKET_SIZE ;
			}
			
			else if ((Global_NumberOfPackets == 0) && (Global_RemainingBytes > 0) ) 
			{
				/* Receive packet */
				ESP_RX_SYNCH(Global_RxBuffer,Global_RemainingBytes);
				/* Store Packet */
				Nvm_WriteBlock (Global_RxBuffer , Global_RemainingBytes);
				/* Ack last packet */
				ESP_TX_BYTE(LAST_PACKET_RECEIVED);
				/* Change Internal state */
				Global_RxInternalSate = RX_END_STATE ;
				/* Update Received byte to calculate progress */
				Global_ReceivedBytes += Global_RemainingBytes ;
			}
			
			else 
			{
				/* Error */
			}
			/*Calculate progress */
			Global_DownloadPercentage = ((float32)Global_ReceivedBytes /(float32) Global_SizeValue) ;
			Global_DownloadUpdateProgeress = Global_DownloadPercentage * 100 ;
			/* Write to RTE to Signal UserIntrface Module */
			RTE_WRITE_DOWNLOAD_PROGRESS (Global_DownloadUpdateProgeress);
			break;
		}
		
		/*****************************RX_END_STATE***********************************/
		case RX_END_STATE : 
		{
			/* Inform the Esp Code has been received */
			ESP_TX_BYTE(ESP_DOWNLOAD_DONE);
			
			/* Change System state */
			RTE_WRITE_SYSTEM_STATE(SYS_DECRYPT);
			
			/* Reset Variables */
			Global_CrcValue = INITIAL_VALUE ;
			Global_SizeValue = INITIAL_VALUE ;
			Global_NodeId = INITIAL_VALUE ;
			Global_NumberOfPackets = INITIAL_VALUE ;
			Global_RemainingBytes = INITIAL_VALUE;
			Global_RxUserResponse = INITIAL_VALUE;
			Global_DownloadPercentage = INITIAL_VALUE ;
			Global_DownloadUpdateProgeress = INITIAL_VALUE ;
			Global_ReceivedBytes = INITIAL_VALUE;
			
			RTE_WRITE_DOWNLOAD_PROGRESS(INITIAL_VALUE);
			
			/* Reset Nvm Variables */
			Nvm_voidInitVariables();
			
			/* Change system state */
			Global_RxInternalSate = RX_IDLE ;
			
			/* Enable Uart interrupt */
			ESP_RX_ASYNCH (Esp_NewReq);
			break;
		}
		
		/*****************************DEFUALT (ERROR)***********************************/
		default :
			/* Error */
			break ;
	}
}


/**************************************************************************/
/*                         Esp Uart Handler                               */
/**************************************************************************/
static void Esp_NewReq ( uint8 Cpy_Data) 
{
	Std_ReturnType Local_Error ;
	/* Check of the ESP request */
	if (NEW_UPDATE_REQUEST == Cpy_Data)
	{
		Local_Error = RTE_READ_SYSTEM_STATE(&Global_SystemState);
		/* Check whether a read operation of the system state done successfully or not */
		if (E_OK == Local_Error)
		{
			/* Before accepting update request will check the system state */
			if (SYS_IDLE == Global_SystemState)
			{
				/* Accept the request and change system state */
				RTE_WRITE_SYSTEM_STATE(SYS_NEW_UPDATE_REQ);
				/* Disble the interrupt till receive the code by synch function */
				ESP_DISABLE_INTTERUPT ;
			}
			else 
			{
				/* Refuse the update request as the system is not ready to receive updates */
				ESP_TX_BYTE (GATEWAY_BUSY);
			}
		}
		else if (E_NOT_OK == Local_Error)
		{
			/* to Hold the ESP from sending new requests for a while as system state can't be read */
			ESP_TX_BYTE (SYSTEM_STATE_UNDIFINED);
		}
		else 
		{
			
		}
	}
	else 
	{
		/* Response for unvalid requests */
		ESP_TX_BYTE (INVALID_REQUEST);
	}
	
}






