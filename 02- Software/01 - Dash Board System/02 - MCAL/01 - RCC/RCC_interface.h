/************************************************/
/******Author: osama salah hijazi****************/
/******Date: 20 / 8 /2020*************************/
/****** Ver: Version 2***************************/

#ifndef RCC_INTERFACE_H
#define RCC_INTERFACE_H

/***********************************************************************************************************************************************************************************************************************************************************
                                                    *******CLOCK BUSES MACROS******
***********************************************************************************************************************************************************************************************************************************************************/																			

#define RCC_AHB_EN        0
#define RCC_APB1_EN       1
#define RCC_APB2_EN       2
#define RCC_APB1_RES      3
#define RCC_APB2_RES      4

/***********************************************************************************************************************************************************************************************************************************************************
                                                  *******PERIPHERAL ENABLE AND RESET CLOCK MACROS******
***********************************************************************************************************************************************************************************************************************************************************/																			
/*
 RCC_AHBENR  -->ENABLE PERIPHERAL CLOCK
*/
#define RCC_DMA1       0
#define RCC_DMA2       1
#define RCC_SRAM       2
#define RCC_FLITF      4
#define RCC_CRC        6
#define RCC_FSMC       8
#define RCC_SDIO       10




/*
 ARCC_APB2ENR-->ENABLE PERIPHERAL CLOCK
 RCC_APB2RSTR-->RESET  PERIPHERAL
*/                                                              
#define RCC_AFIO       0 
#define RCC_GPIOA      2
#define RCC_GPIOB      3 
#define RCC_GPIOC      4  
#define RCC_GPIOD      5  
#define RCC_GPIOE      6  
#define RCC_GPIOF      7  
#define RCC_GPIOG      8  
#define RCC_ADC1       9  
#define RCC_ADC2       10  
#define RCC_TIM1       11 
#define RCC_SPI1       12 
#define RCC_TIM8       13 
#define RCC_USART1     14  
#define RCC_ADC3       15 
#define RCC_TIM9       19 
#define RCC_TIM10      20 
#define RCC_TIM11      21 
/*
 RCC_APB1ENR-->ENABLE PERIPHERAL CLOCK
 RCC_APB1RSTR-->RESET  PERIPHERAL
*/                                                                
#define RCC_TIM2       0 
#define RCC_TIM3       1 
#define RCC_TIM4       2 
#define RCC_TIM5       3 
#define RCC_TIM6       4 
#define RCC_TIM7       5 
#define RCC_TIM12      6 
#define RCC_TIM13      7 
#define RCC_TIM14      8 
#define RCC_WWD        11
#define RCC_SPI2       14 
#define RCC_SPI3       15 
#define RCC_USART2     17 
#define RCC_USART3     18 
#define RCC_USART4     19 
#define RCC_USART5     20 
#define RCC_I2C1       21 
#define RCC_I2C2       22 
#define RCC_USB        23 
#define RCC_CAN        25 
#define RCC_BKP        27 
#define RCC_PWR        26 
#define RCC_DAC        29 
/***********************************************************************************************************************************************************************************************************************************************************
                                                   *******ERROR Macros**********
													  EACH VALUE REPRESENT ERROR TYPE WHICH INDICATE REASON AND LOCATION OF ITS ERROR
***********************************************************************************************************************************************************************************************************************************************************/																																										 
#define  WRONG_BUS_EN_CLK         1  
#define  WRONG_PER_EN_CLK         2
#define  WRONG_BUS_DIS_CLK        3
#define  WRONG_PER_DIS_CLK        4
#define  WRONG_BUS_RES_PER        5
#define  WRONG_PER_RES_PER        6
/***********************************************************************************************************************************************************************************************************************************************************
                                                *******ERROR CHECK VARIABLE******
***********************************************************************************************************************************************************************************************************************************************************/																			
/*
 VALUE *****   VARIABLE_NAME  **** EUNCTION_NAME** 
  1    *****    Copy_u8BusId   **** ENABLE CLOCK 
  2    *****    Copy_u8PerId   **** ENABLE CLOCK
  3    *****    Copy_u8BusId   **** DISABLE CLOCK
  4    *****    Copy_u8PerId   **** DISABLE CLOCK
  5    *****    Copy_u8BusId   **** RESET CLCOK
	6    *****    Copy_u8PerId   **** RESET CLOCK
*/
/***********************************************************************************************************************************************************************************************************************************************************
                                                  *******FUNCTIONS PROTOTYPES******
***********************************************************************************************************************************************************************************************************************************************************/																			
/*
 * Description:adjust all configurations of system clock   
 * Input:void
 * Output:void
 */                                                 
void RCC_VoidInitSysClock(void);
/*
 * Description:Enable Clock of A certain peropheral 
   Input: Bus number and clock enable bit number of prepiral
	 Output:void
 */	
void RCC_VoidEnableClock(uint8 Copy_u8BusId ,  
                         uint8 Copy_u8PerId   );
/*												 
 * Description:Disable Clock of A certain peropheral 
   Input: Bus number and clock enable bit number of prepiral
	 Output:void
 */	
void RCC_VoidDisableClock(uint8 Copy_u8BusId ,  
                          uint8 Copy_u8PerId   );
/*
 * Description:Set Abit of A certain peropheral To Reset it. 
   Input: Reset Register number and Reset bit number of prepiral
	 Output:void
 */	
void RCC_VoidResetPeriph(uint8 Copy_u8BusId ,  
                         uint8 Copy_u8PerId   );

#endif
/**************************************************************END OF FILE*********************************************************************************************************************************************************************/
