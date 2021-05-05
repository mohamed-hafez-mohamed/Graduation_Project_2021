/*****************************************************/
 /* Author      : Mosad                              */
 /* Version     : v01                                */
 /* date        : 2/5/2020                           */
/*****************************************************/
#ifndef RX_UPDATE_INTERFACE_H
#define RX_UPDATE_INTERFACE_H


/*************************************************************************
 * Name : ReceiveUpdate_voidInit
 * Parameter in : -
 * Parameter out : -
 * Parameter in/out : -
 * Reentrancy: Non reentrant
 * Sync
 * Description: Initialize ReceiveUpdate SWC. 
 ***************************************************************************/
void ReceiveUpdate_voidInit(void);

/*************************************************************************
 * Name : ReceiveUpdate_MainFunction
 * Parameter in : -
 * Parameter out : -
 * Parameter in/out : -
 * Reentrancy: Non reentrant
 * Sync
 * Description: Module MainFunction for Prossessing receiving Update. 
 ***************************************************************************/
void ReceiveUpdate_MainFunction (void);


#endif
