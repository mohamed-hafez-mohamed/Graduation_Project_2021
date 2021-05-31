/*******************************************************************************
**  FILENAME     : EcuM.c         			                                  **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2021-04-30                                                 **
**                                                                            **
**  PLATFORM     : stm32f103		                                          **
**                                                                            **
**  AUTHOR       : osamahijazi	                                              **
**                                                                            **                                                                         **
**  DESCRIPTION  : EcuM Driver source file                                    **
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
#include "Nvic_Interface.h"
#include "I2c_Interface.h"
#include "LCD.h"
#include "ADC.h"
#include "TMR_Interface.h"
#include "LCD.h"
#include "LCD_Cfg.h"
/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/
#if   LCD_MODE == LCD_4_BIT_MODE
   #define LCD_DATA_PINS          4
#elif LCD_MODE == LCD_8_BIT_MODE
   #define LCD_DATA_PINS          8
#endif

#if   LCD_DATA_PINS == 4
   static uint8 Static_u8DataPins[LCD_DATA_PINS] = {LCD_D4,LCD_D5,LCD_D6,LCD_D7};
#elif LCD_DATA_PINS == 4
   static uint8 Static_u8DataPins[LCD_DATA_PINS] = {LCD_D0,LCD_D1,LCD_D2,LCD_D3,LCD_D4,LCD_D5,LCD_D6,LCD_D7};
#endif
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

	/*******************  PORTB ENABLE CLOCK  *******************/
	RCC_VoidEnableClock(RCC_APB2_EN,RCC_GPIOB);
	
	/*******************  AFIO ENABLE CLOCK  *******************/	   
	RCC_VoidEnableClock(RCC_APB2_EN,RCC_AFIO); 
	
	/*******************  CAN1 ENABLE CLOCK  *******************/
	RCC_VoidEnableClock(RCC_APB1_EN,RCC_CAN); 
	
	/*******************  Timer 3 ENABLE CLOCK  *******************/
	RCC_VoidEnableClock(RCC_APB1_EN,RCC_TIM3); 
	/*******************  I2C ENABLE CLOCK  *******************/
	RCC_VoidEnableClock(RCC_APB1_EN, RCC_I2C1);
	RCC_VoidEnableClock(RCC_APB2_EN , RCC_ADC1);
	
	return  Local_ReturnError ;
	
}
/************************************************END OF FUNCTION*******************************/
Std_ReturnType EcuM_unit8DioPeriphInit()
{
	/*Local variable , Return = ok*/
	Std_ReturnType Local_ReturnError = E_OK;
	
	/*******************  CAN ENABLE PINS   *******************/
	MGPIO_u8SetPinMode(PINA11 , GPIO_INPUT_FLOATING);   //RX
	MGPIO_u8SetPinMode(PINA12 , AFIO_OUTPUT_2M_PULL_UP_DN); //TX
	/*******************  I2C ENABLE PINS   *******************/
	MGPIO_u8SetPinMode(PINB6 , AFIO_OUTPUT_10M_OPEN_DRAIN);   //SCL
	MGPIO_u8SetPinMode(PINB7 , AFIO_OUTPUT_10M_OPEN_DRAIN);   //SDA
	
	/*******************  ADC PINS   *************************/
	MGPIO_u8SetPinMode(PINA0, AFIO_INPUT_ANALOG);
	MGPIO_u8SetPinMode(PINA1, AFIO_INPUT_ANALOG);
	/******************** LCD        **************************/	
	MGPIO_u8SetPinMode(LCD_RS, GPIO_OUTPUT_2M_PULL_UP_DN);
   MGPIO_u8SetPinMode(LCD_EN, GPIO_OUTPUT_2M_PULL_UP_DN);
   for(uint8 Local_u8Counter = 0;Local_u8Counter < LCD_DATA_PINS;Local_u8Counter++)
	{
		MGPIO_u8SetPinMode(Static_u8DataPins[Local_u8Counter], GPIO_OUTPUT_2M_PULL_UP_DN);
	}
	
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
	//CAN_VoidFilterSet( & CAN_FilterInitStruct_2 );// ID =0X02
	
	/* Enable Interrupts */
	NVIC_voidEnableIRQ(USB_LP_CAN_IRQ);
	CAN_VoidInterruptSet(CAN1, CAN_FMPIE0 , ENABLE) ; /*message pending interrupt*/

	/* Enabling I2C1 */
	I2C_voidPeripheralControl(I2C1, I2C_ENABLE);
	I2C_voidInit(I2C1);
	
	/* Init Stk */
	MSTK_voidInit();
	
	/* Init Timer */
	TMR_voidInit();
	
	/* Init ADC and LCD */
	HLCD_u8Init();
	
	/* Init ADC */
	MADC_u8InitializeAdc();
   MADC_u8SetSamplingTime(ADC1, CHANNEL0, _1_AND_HALF_CYCLE);
   MADC_u8SetSamplingTime(ADC1, CHANNEL1, _1_AND_HALF_CYCLE);
	MADC_u8SetConversionMode(ADC1, SINGLE_CONVERSION, 0);

  return  Local_ReturnError ;

}
/************************************************END OF FUNCTION*******************************/
