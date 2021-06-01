/************************************************/
/******Author: osama salah hijazi****************/
/******Date: 20 / 8 /2020*************************/
/****** Ver: Version 2***************************/
#ifndef RCC_PRIVATE_H
#define RCC_PRIVATE_H

/***********************************************************************************************************************************************************************************************************************************************************
                                                   *******RCC Registers Definition**********
***********************************************************************************************************************************************************************************************************************************************************/																																										 

#define RCC_CR         *((uint32*)0x40021000)
#define RCC_CFGR       *((uint32*)0x40021004)
#define RCC_CIR        *((uint32*)0x40021008)
#define RCC_APB2RSTR   *((uint32*)0x4002100C)
#define RCC_APB1RSTR   *((uint32*)0x40021010)
#define RCC_AHBENR     *((uint32*)0x40021014)
#define RCC_APB2ENR    *((uint32*)0x40021018)
#define RCC_APB1ENR    *((uint32*)0x4002101C)
#define RCC_BDCR       *((uint32*)0x40021020)
#define RCC_CSR        *((uint32*)0x40021024)
/***********************************************************************************************************************************************************************************************************************************************************
                                                           *******CONFIGURATION PRIVATE MACROS**********
***********************************************************************************************************************************************************************************************************************************************************/																																										 
                                                               /*CLOCK INPUT TYPES*/								
#define  RCC_HSE_CRYSTAL         0
#define  RCC_HSE_RC              1
#define  RCC_HSI                 2
#define  RCC_PLL                 3	 
#define  TURN_ON                 4
#define  TURN_OFF                5
#define  PLL_BITS_SHIFT          15
		                                                             /*PLL CLOCK SOURCE*/
								 
#define RCC_PLL_IN_HSI_DIV_2     0
#define RCC_PLL_IN_HSE_DIV_2     1 
#define RCC_PLL_IN_HSE           2		 
                                                                
		                                                       /*CLOCK INPUT TYPES , MCO OUTPUT PIN*/								
#define NO_CLOCK                 0
#define SYSTEM_CLOCK             1
#define HSI_CLOCK                2
#define HSE_CLOCK                3
#define PLL_CLOCK                4
                                                          /*PRESCALLER OF INPUT CLOCK OF BUSES AND OTHER PERIPHERALS*/
#define RCC_PRESCALLER_BY_0 	   0  
#define RCC_PRESCALLER_BY_2      1
#define RCC_PRESCALLER_BY_4      2
#define RCC_PRESCALLER_BY_8      3
#define RCC_PRESCALLER_BY_16     4
#define RCC_PRESCALLER_BY_64     5
#define RCC_PRESCALLER_BY_128    6 
#define RCC_PRESCALLER_BY_256    7
#define RCC_PRESCALLER_BY_512    8
                                                                /*PRESCALLER OF INPUT CLOCK OF USB*/
#define PLL_CLOCK_DEVIDED_BY_2   0                                                             
#define PLL_CLOCK_DEVIDED_BY_0 	 1
/***********************************************************************************************************************************************************************************************************************************************************
                                                           *******REGISTERS BITS PRIVATE MACROS**********
***********************************************************************************************************************************************************************************************************************************************************/																																										 
                                                                  /*RCC_CR PRIVATE BITS*/

#define RCC_HSI_ON               0           /*INTERNAL CLOCK ENABLE*/
#define RCC_HSI_IS_READY         1           /*INTERNAL CLOCK READY FLAG*/
#define RCC_HSI_TRIM0                        /*INTERNAL CLOCK TERMINGN*/
#define RCC_HSI_TRIM1            4            
#define RCC_HSI_TRIM2            5            
#define RCC_HSI_TRIM3            6
#define RCC_HSI_TRIM4            7            
#define RCC_HSE_ON               16          /*EXTERNAL CLOCK ENABLE*/
#define RCC_HSE_IS_READY         17          /*EXTERNAL CLOCK READY FLAG*/
#define RCC_HSE_BYP              18          /*EXTERNAL CLOCK BYPASS*/
#define RCC_CSS_ON               19          /*CLOCK SECURITY SYSTEM ENABLE*/
#define RCC_PLL_ON               24          /*PLL ENABLE*/
#define RCC_PLL_IS_READY         25          /*PLL CLOCK READY FLAG*/

                                                                  /*RCC_CFGR PRIVATE BITS*/
																																	
#define RCC_SW0                  0           /*SYSTEM CLOCK SWITCH SOURCE*/
#define RCC_SW1                  1
#define RCC_SWS0                 2           /*SYSTEM CLOCK SRTATUS*/
#define RCC_SWS1                 3
#define RCC_HPRE0                4           /*AHB PRESCALLER BITS*/
#define RCC_HPRE1                5
#define RCC_HPRE2                6
#define RCC_HPRE3                7
#define RCC_PPRE1_0              8           /*APB1 PRESCALLER BITS*/
#define RCC_PPRE1_1              9
#define RCC_PPRE1_2              10 
#define RCC_PPRE2_0              11          /*APB2 PRESCALLER BITS*/
#define RCC_PPRE2_1              12 
#define RCC_PPRE2_2              13
#define RCC_ADCPRE0              14          /*ADCC PRESCALLER BITS*/
#define RCC_ADCPRE2              15
#define RCC_PLL_SRC              16          /*PLL ENTRY SOURCE CLOCK*/
#define RCC_PLL_XT_PRE           17          /*HSE DRIVER FOR PLL ENTRY,IT EFFECTED BY BIT 0 IN RCC_CFGR2 REGISTER,*/
#define RCC_PLL_MUL0             18          /*PLL CLOCK INPUT MUL*/
#define RCC_PLL_MUL1             19
#define RCC_PLL_MUL2             20
#define RCC_PLL_MUL3             21
#define RCC_USB_PRE              22          /*USB PRESCLALLER , NOTE THAT USM IS NOT EXIST IN THIS VERSION*/
#define RCC_MCO_0                24          /*CLOCK OUTPUT BITS*/
#define RCC_MCO_1                25
#define RCC_MCO_2                26
#define WAIT_HSE_GET_READY        IS_BIT_CLEAR(RCC_CR,RCC_HSE_IS_READY)       /*HSE FLAG IS READY*/
#define WAIT_HSI_GET_READY        IS_BIT_CLEAR(RCC_CR,RCC_HSI_IS_READY)       /*HSI FLAG IS READY*/
																																					
#endif
/**************************************************************END OF FILE*********************************************************************************************************************************************************************/

