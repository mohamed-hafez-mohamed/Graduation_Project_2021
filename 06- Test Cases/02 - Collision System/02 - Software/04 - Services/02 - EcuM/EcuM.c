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
/*****************************************************************************************/
/*                                 Include Libraries                                     */
/*****************************************************************************************/
#include "BIT_MATH.h"
#include "Std_Types.h"
/*****************************************************************************************/
/*                                   Include Headers                                     */
/*****************************************************************************************/
#include "EcuM_Interface.h"
#include "EcuM_Private.h"
#include "EcuM_Cfg.h"
/*****************************************************************************************/
/*                                Include modules Headers                                */
/*****************************************************************************************/
#include "GPIO_interface.h"
#include "RCC_interface.h"
#include "STK_Interface.h"
#include "CAN_Interface.h"
#include "NVIC_interface.h"
#include "FPEC_interface.h"
#include "WDT_interface.h"
#include "CanIf_Interface.h"
#include "UltraSensor_Interface.h"
#include "Alarm_Interface.h"
/*****************************************************************************************/
/*                                Local Data Types                                       */                              
/*****************************************************************************************/                         

/*****************************************************************************************/
/*                               Extern Data Types                                       */                              
/*****************************************************************************************/                         
volatile extern CAN_InitTypeDef         CAN_InitStruct ; //can init struct
volatile extern CAN_FilterInitTypeDef   CAN_FilterInitStruct_4 ; //can set filters struct	
/*****************************************************************************************/
/*                              Local Varaible Definition                                */
/*****************************************************************************************/
Std_ReturnType EcuM_unit8RccPeriphInit()
{       
	
	 /*Local variable , Return = ok*/
  	Std_ReturnType Local_ReturnError = E_OK;
	
	/*******************  RCC SOURCE CLOCK  *******************/
    RCC_VoidInitSysClock(); 

	/*******************  PORTA ENABLE CLOCK  *******************/
    RCC_VoidEnableClock(RCC_APB2_EN,RCC_GPIOA); 
	
	/*******************  FPEC ENABLE CLOCK  *******************/
    RCC_VoidEnableClock(RCC_AHB_EN,RCC_FLITF); 
	
	/*******************  AFIO ENABLE CLOCK  *******************/	   
    RCC_VoidEnableClock(RCC_APB2_EN,RCC_AFIO); 
	
	/*******************  CAN1 ENABLE CLOCK  *******************/
    RCC_VoidEnableClock(RCC_APB1_EN,RCC_CAN); 
 		
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
	 /******************* Enable UltraSensor Pins  **********/	
	  HCSR04_VoidInit();	
    /*******************  Enable Buzzer Pins  *******************/ 
	 ALarm_VoidInit(); 
	
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
   CAN_VoidFilterSet( &CAN_FilterInitStruct_4 ); // ID = 0X04	
	  /********************** STK init **************************/	
   STK_voidInit(); 
	/**************CAN Reception Interrupt Enable******************/
   MNVIC_u8EnableInt(USB_LP_CAN_RX0);
	/*message pending interrupt*/
	 CAN_VoidInterruptSet(CAN1, CAN_FMPIE0 , ENABLE) ; 
               
  return  Local_ReturnError ;

}
/************************************************END OF FUNCTION*******************************/
