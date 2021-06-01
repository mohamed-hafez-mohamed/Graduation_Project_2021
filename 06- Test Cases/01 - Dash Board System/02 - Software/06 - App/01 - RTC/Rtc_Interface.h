/*****************************************************/
 /* Author      : Mosad                              */
 /* Version     : v01                                */
 /* date        : 28/5/2021                          */
/*****************************************************/
#ifndef RTC_INTERFACE_H
#define RTC_INTERFACE_H

/*************************************************************************
 * Name : Rtc_Init
 * Parameter in : -
 * Parameter out : -
 * Parameter in/out : -
 * Reentrancy: Non reentrant
 * Sync
 * Description: Init function for RTC module  
 ***************************************************************************/
void Rtc_Init (void);

/*************************************************************************
 * Name : Rtc_MainFunction
 * Parameter in : -
 * Parameter out : -
 * Parameter in/out : -
 * Reentrancy: Non reentrant
 * Sync
 * Description: Module MainFunction, Task will be called periodic every 500 ms 
 ***************************************************************************/
void Rtc_MainFunction(void);

#endif