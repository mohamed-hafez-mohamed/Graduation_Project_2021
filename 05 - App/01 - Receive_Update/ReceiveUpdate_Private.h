/*****************************************************/
 /* Author      : Mosad                              */
 /* Version     : v01                                */
 /* date        : 2/5/2020                           */
/*****************************************************/
#ifndef RX_UPDATE_PRIVATE_H
#define RX_UPDATE_PRIVATE_H

/* Other Modules */
#include "Uart_Interface.h"
#include "Nvm_Interface.h"

/**************************************************************************/
/*                         Uart Wrappers                                 */
/**************************************************************************/
#define   ESP_TX_BYTE(BYTE)                     Uart_voidTxByteSynch(UART1,BYTE)
#define   ESP_RX_SYNCH(BUFFER_ADDRESS,LENGTH)   Uart_voidRxSynch(UART1,BUFFER_ADDRESS,LENGTH)
#define   ESP_RX_ASYNCH(FUNC)                   Uart_voidRxAsynch(UART1,FUNC)
#define   ESP_DISABLE_INTTERUPT                 Uart_voidRxDisableInterrupt(UART1)

/**************************************************************************/
/*                         Private DataTypes                              */
/**************************************************************************/
typedef   uint8     ReceiveUpdateStateType ;
/* Range of values */
#define      RX_IDLE                  0x00u
#define      RX_ACCEPT_UPDATE         0x01u
#define      RX_RECEIVE_HEADER        0x02u
#define      RX_RECEIVE_PACKET        0x03u
#define      RX_END_STATE             0x04u
#define      RX_REFUSE_UPDATE         0x05u

/**************************************************************************/
/*                         Private Macros                                */
/**************************************************************************/
/* NodeMcu To Gateway messages */
#define   NEW_UPDATE_REQUEST     0x01u

/* Gateway To NodeMCU errors */
#define   SYSTEM_STATE_UNDIFINED     0x02u
#define   GATEWAY_BUSY               0x03u
#define   INVALID_REQUEST            0X04u
#define   REQUEST_ACCEPTED           0x05u
#define   REQUEST_REFUSED            0x06u
#define   ESP_SEND_HEADER            0x07u
#define   HEADR_RECEIVED             0x08u
#define   HEADR_ERROR                0x09u
#define   PACKET_RECEIVED            0x0Au
#define   LAST_PACKET_RECEIVED       0x0Bu
#define   SEND_NEXT_PACKET           0x0Cu
#define   ESP_DOWNLOAD_DONE          0x0Du


/**/
#define   INITIAL_VALUE    0
#define   SHIFT_BY_8       8
#define   SHIFT_BY_16      16
#define   SHIFT_BY_24      24
#define   PACKET_SIZE      1024


/**************************************************************************/
/*                         Private Functions                              */
/**************************************************************************/
static void Esp_NewReq ( uint8 Cpy_Data);

#endif
