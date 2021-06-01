/*******************************************************************************
**  FILENAME     : EcuM_Interface.h         			                              **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2021-04-29                                                  **
**                                                                            **                                                                            **
**  PLATFORM     : stm32f103		                                              **
**                                                                            **
**  AUTHOR       : osamahijazi	                                              **
                                                                              **
**  DESCRIPTION  : EcuM Driver interface file                                  **
**                                                                            **
*******************************************************************************/

/* Define to prevent recursive inclusion */

#ifndef EcuM_INTERFACE_H
#define EcuM_INTERFACE_H


/*****************************************************************************************/
/*                                   Include headres                                     */
/*****************************************************************************************/



/***********************************************************************************/
                      /***FUNCTIONS PROTOTYPES***/
/***********************************************************************************
*Name       :   EcuM_unit8RccPeriphInit

*Description: * Enable all Clocks to mcal peripheral and main buses
   
							
*Pre-Cond   :  None				
							
*pos-Cond   :  None

*Input      :   void

*Output     :   void

*Return     :   Error status

****************************************************************************************/                                   	
Std_ReturnType EcuM_unit8RccPeriphInit() ;
/***********************************************************************************
*Name       :   EcuM_unit8DioPeriphInit

*Description: * Init all Dio pins to all Mcal peripheral 
   
							
*Pre-Cond   :  Clock Enable				
							
*pos-Cond   :  None

*Input      :   void

*Output     :   void

*Return     :   Error status

****************************************************************************************/                                   	
Std_ReturnType EcuM_unit8DioPeriphInit();
/***********************************************************************************
*Name       :   EcuM_unit8StartupPeriph

*Description: * Start and init all Mcal Hardware units (CANX , UARTX , ....) 
   
							
*Pre-Cond   :  Clock Enable and pins init				
							
*pos-Cond   :  None

*Input      :   void

*Output     :   void

*Return     :   Error status

****************************************************************************************/                                   	
Std_ReturnType EcuM_unit8StartupPeriph() ;











#endif
/******************************************END OF FILE************************************/
