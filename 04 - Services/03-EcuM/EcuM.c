/*******************************************************************************
**  FILENAME     : EcuM.c         			                                        **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2021-04-30                                                  **
**                                                                            **
**  PLATFORM     : stm32f103		                                              **
**                                                                            **
**  AUTHOR       : osamahijazi	                                              **
**                                                                            ***                                                                           **
**  DESCRIPTION  : EcuM Driver source file                                     **
**                                                                            **
*******************************************************************************/

/**********************************************include******************************************/
/*Library include*/
#include "BIT_MATH.h"
#include "Std_Types.h"
/*header files include*/
#include "EcuM_Interface.h"
#include "EcuM_Private.h"
#include "EcuM_Cfg.h"
/*MCAL header files include*/
#include "GPIO_interface.h"
#include "RCC_interface.h"
#include "CAN_Interface.h"
/*******************  Externed Types  *******************/
 //volatile extern  Can_ConfigType Can_Configurations ;

volatile extern CAN_InitTypeDef        CAN_InitStruct ; //can init struct

volatile extern CAN_FilterInitTypeDef  CAN_FilterInitStruct_1 ; //can set filters struct
	
volatile extern  CAN_FilterInitTypeDef  CAN_FilterInitStruct_2 ;//can set filters struct


Std_ReturnType EcuM_unit8RccPeriphInit()
{       
	
	  /*Local variable , Return = ok*/
  	Std_ReturnType Local_ReturnError = E_OK;
	/*******************  RCC SOURCE CLOCK  *******************/
    RCC_VoidInitSysClock(); 

	/*******************  PORTA ENABLE CLOCK  *******************/
    RCC_VoidEnableClock(RCC_APB2_EN,RCC_GPIOA); 
	
	/*******************  AFIO ENABLE CLOCK  *******************/	   
    RCC_VoidEnableClock(RCC_APB2_EN,RCC_AFIO); 
	
	/*******************  CAN1 ENABLE CLOCK  *******************/
    RCC_VoidEnableClock(RCC_APB1_EN,RCC_CAN); 
	
	/*******************  UART1 ENABLE CLOCK  *******************/
	
	
  return  Local_ReturnError ;
	
}
/************************************************END OF FUNCTION*******************************/
Std_ReturnType EcuM_unit8DioPeriphInit()
{
	/*Local variable , Return = ok*/
  	Std_ReturnType Local_ReturnError = E_OK;
	/*******************  CAN1 ENABLE PINS   *******************/
  GPIO_VoidSetPinDirection(GPIOA,PIN11 , INPUT_FLOATING);   //RX
	GPIO_VoidSetPinDirection(GPIOA,PIN12 , OUTPUT_2MHZ_AFPP); //TX
	/*******************  UART1 ENABLE PINS   *******************/

	
	
	
	
	
	
	
  return  Local_ReturnError ;
}
/************************************************END OF FUNCTION*******************************/
Std_ReturnType EcuM_unit8StartupPeriph()
{
	/*Local variable , Return = ok*/
  	Std_ReturnType Local_ReturnError = E_OK;
	
		/*******************  CAN1 INTI HW  *******************/		
   CAN_VoidInit(  CAN1 , &CAN_InitStruct ) ; //Init can					

		/*******************  CAN1 INTIT FILTERS  *******************/	
	  CAN_VoidFilterSet( & CAN_FilterInitStruct_1 ); // ID = OXO3
         CAN_VoidFilterSet( & CAN_FilterInitStruct_2 );// ID =0X02
	
		/*******************  UART1 INTI HW  *******************/		
	
	
	

	

               
  return  Local_ReturnError ;

}
/************************************************END OF FUNCTION*******************************/
