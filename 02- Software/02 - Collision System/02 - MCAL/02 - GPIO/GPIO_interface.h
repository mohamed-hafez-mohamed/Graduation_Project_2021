/***********************************************************/
/**********Author: osama hegazi*****************************/
/**********Date:14/8/2020***********************************/
/***********version:1***************************************/
/*********Description:GPIOS REGISTERS***********************/
/***********************************************************/

#ifndef GPIO_INTERFACE_H
#define GPIO_INTERFACE_H

/***********************************************************************************************************************************************************************************************************************************************************
                                                  *******Ports Macros******
***********************************************************************************************************************************************************************************************************************************************************/																			
#define GPIOA        0
#define GPIOB        1
#define GPIOC        2
#define GPIO_HIGH    1          /*HIGH*/
#define GPIO_LOW     0          /*LOW*/
#define GPIOA_HIGH  0XFFFF      /*ALL PINS ARE HIGH*/
#define GPIOB_HIGH  0XFFFF      /*ALL PINS ARE HIGH*/
#define GPIOC_HIGH  0XE000      /*ALL PINS ARE HIGH*/

/***********************************************************************************************************************************************************************************************************************************************************
                                                   *******Pins Macros**********
***********************************************************************************************************************************************************************************************************************************************************/																																										 
#define PIN0        0
#define PIN1        1
#define PIN2        2
#define PIN3        3
#define PIN4        4
#define PIN5        5
#define PIN6        6
#define PIN7        7
#define PIN8        8
#define PIN9        9
#define PIN10       10
#define PIN11       11
#define PIN12       12
#define PIN13       13 
#define PIN14       14
#define PIN15       15
/***********************************************************************************************************************************************************************************************************************************************************
                                                   *******Mode Configuration**********
***********************************************************************************************************************************************************************************************************************************************************/																																										 
/*                                                         
               INPUT MODE               REG_VLAUE
*/							 
#define        INPUT_ANALOG              0b0000
#define        INPUT_FLOATING            0b0100
#define        INPUT_PULL_UP_DOWN        0b1000
/*                                                         
               OUTPUT MODE              REG_VLAUE
*/
#define       OUTPUT_10MHZ_PP             0b0001
#define       OUTPUT_10MHZ_OD             0b0101
#define       OUTPUT_10MHZ_AFPP           0b1001
#define       OUTPUT_10MHZ_AFOD           0b0101
 
#define       OUTPUT_2MHZ_PP              0b0010
#define       OUTPUT_2MHZ_OD              0b0110
#define       OUTPUT_2MHZ_AFPP            0b1010
#define       OUTPUT_2MHZ_AFOD            0b0110

#define       OUTPUT_50MHZ_PP             0b0011
#define       OUTPUT_50MHZ_OD             0b0111
#define       OUTPUT_50MHZ_AFPP           0b1011
#define       OUTPUT_50MHZ_AFOD           0b0111
/***********************************************************************************************************************************************************************************************************************************************************
                                                *******FUNCTIONS PROTOTYPE******
***********************************************************************************************************************************************************************************************************************************************************/																			
/*
  * Description:Set The mode of Certain pin
  * Input:Port and pin number and The needed mode
	* Output:void
*/
 void  GPIO_VoidSetPinDirection  (uint8  Copy_u8Port ,
	                                uint8  Copy_u8Pin  ,
                                  uint8  Copy_u8Mode );                                                
/*
  * Description:Set The Value of Certain pin
  * Input:Port and pin number and The needed mode
	* Output:void
*/ 
 void  GPIO_VoidSetPinValue      (uint8  Copy_u8Port ,
	                                uint8  Copy_u8Pin  ,
                                  uint8  Copy_u8Value );
/*
  * Description:Get The Value of Certain pin
  * Input:Port and pin number 
	* Output:void
*/
 uint8 GPIO_VoidGetPinValue      (uint8  Copy_u8Port ,
                                  uint8  Copy_u8Pin   );
/*
  * Description:Toggle A certain pin
  * Input:Port and pin number 
	* Output:void
*/ 
 void  GPIO_voidTogglePinValue   (uint8  Copy_u8Port ,
	                                uint8  Copy_u8Pin   );
/*
  * Description:SET Acertain Port Direction
  * Input:Port number 
	* Output:void
*/ 
 void  GPIO_voidSetPortDirection (uint8  Copy_u8Port  ,
	                                uint8  Copy_u8Mode  );
/*
  * Description:SET Port value
  * Input:Port and pin number 
	* Output:void
*/ 
 void  GPIO_voidSetPortValue     (uint8  Copy_u8Port ,
	                                uint16 Copy_uint16Value);
/*
  * Description:Get The Value of Certain Port
  * Input:Port number 
	* Output:Port value
*/
 uint16 GPIO_VoidGetPortValue      (uint8  Copy_u8Port  );                                  
/*
  * Description:Toggle A certain Port
  * Input:Port number 
	* Output:void
*/ 
 void  GPIO_voidTogglePortValue   (uint8  Copy_u8Port  );	                              
/*
  * Description:lock the configuration of the port bits
  * Input:Port and pin number 
	* Output:void
*/ 
 void  GPIO_voidLockPinConfig    (uint8 Copy_u8Port  ,
	                                uint8 Copy_u8Pin    );
 /*
  * Description:lock the configuration of the all port 
  * Input:Port number 
	* Output:void
*/ 
 void  GPIO_voidLockPortConfig    (uint8 Copy_u8Port  );
	                                 
#endif
 /**************************************************************END OF FILE*********************************************************************************************************************************************************************/

