/*******************************************************************************
**  FILENAME     : UltraSensor_Interface.h              			                **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2021-05-24                                                 **
**                                                                            **
**  AUTHOR       : osamahijazi	                                              **
**                                                                            **
*******************************************************************************/
#ifndef ULTRASENSOR_INTERFACE_H
#define ULTRASENSOR_INTERFACE_H
/*****************************************************************************************/
/*                                   Include Headers                                     */
/*****************************************************************************************/


/*****************************************************************************************/
/*                                   Local Macro Definition                              */
/*****************************************************************************************/


/*****************************************************************************************/
/*                                    Functions Declaration                              */
/*****************************************************************************************/
/************************************************************************************

*Name       :   HCSR04_VoidInit

*Description: * Function to init ultra sensor pins
              				
*Pre-Cond   :	PORTA is activated 				
							
*pos-Cond   : None

*Input      : void

*Output     : void

*Return     : void

****************************************************************************************/
void  HCSR04_VoidInit(void);
/************************************************************************************

*Name       :   HCSR04_uint8ReadDistance

*Description: *Function to sent trigger pulse and Read distance in cm
              				
*Pre-Cond   : *module is Init.
              *Stk is init.  		  
*pos-Cond   : 

*Input      : void

*Output     : void

*Return     : Distance value " if Distance = 0 that is mean there is no objects in Sensor Range"

****************************************************************************************/
Std_ReturnType HCSR04_uint8ReadDistance(uint8 *Copy_uint8Distance);
/************************************************************************************

*Name       :   HCSR04_VoidCallBack

*Description: * STK timer Callback to set timer Falg
              				
*Pre-Cond   :	Stk is activated and set interval time  				
							
*pos-Cond   : None

*Input      : void

*Output     : void

*Return     : void

****************************************************************************************/
void HCSR04_VoidCallBack(void);

#endif
/****************************************END OF FILE*************************************/
