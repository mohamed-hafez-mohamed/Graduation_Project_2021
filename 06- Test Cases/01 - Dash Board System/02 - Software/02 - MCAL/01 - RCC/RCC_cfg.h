/*******************************************************/
/*************Author: osama salah hijazi****************/
/***************Date: 20 / 8 /2020*************************/
/*************** Ver: Version 2***************************/

#ifndef RCC_CFG_H
#define RCC_CFG_H
/***********************************************************************************************************************************************************************************************************************************************************
                                                   *******RCC CLOCK SOURCES**********
***********************************************************************************************************************************************************************************************************************************************************/																																										 

/* OPTIONS:   
           RCC_HSE_CRYSTAL
           RCC_HSE_RC
	  			 RCC_HSI
  				 RCC_PLL									 
									                  */

# define RCC_CLOCK_TYPE     RCC_HSE_CRYSTAL        /*CHOOSE HERE RCC CLOCK MAIN SOURCE*/
/***********************************************************************************************************************************************************************************************************************************************************/
/*  OPTIONS:   
            RCC_PLL_IN_HSI_DIV_2
            RCC_PLL_IN_HSE_DIV_2 
						RCC_PLL_IN_HSE
                                      */		
																			
#if    RCC_CLOCK_TYPE == RCC_PLL   /*select value incase of PPL input*/

   #define RCC_PLL_INPUT  RCC_PLL_IN_HSI_DIV_2    /*CHOOSE HERE PLL CLOCK MAIN SOURCE*/
	 
#endif


/* NOTE: dONT USE HIS PAR WITHOUT USING PLL TYPE*/
                    /*OPTIONS 2 TO 16*/
										
#if   (  RCC_CLOCK_TYPE == RCC_PLL ) 
#define RCC_PLL_MAL_VAL    4                      /*CHOOSE HERE PLL CLOCK PRESCALLER*/
#endif
/***********************************************************************************************************************************************************************************************************************************************************
                                                   *******Buses and Peripheral prescallers**********
***********************************************************************************************************************************************************************************************************************************************************/																																										 
/*
  Options :  		  
			     RCC_PRESCALLER_BY_2   
			     RCC_PRESCALLER_BY_4 
		      	RCC_PRESCALLER_BY_6
	         RCC_PRESCALLER_BY_8
*/ 
#define RCC_ADC_PRESCALLER    RCC_PRESCALLER_BY_2            /*CHOOSE HERE ADC CLOCK PRESCALLER*/
/*
  Options : 
		      	RCC_PRESCALLER_BY_0 		  
			      RCC_PRESCALLER_BY_2   
			      RCC_PRESCALLER_BY_4 
			      RCC_PRESCALLER_BY_8
			      RCC_PRESCALLER_BY_16
*/ 
#define RCC_APB2_PRESCALLER   RCC_PRESCALLER_BY_0            /*CHOOSE HERE APB2 BUS CLOCK PRESCALLER*/
/*
  Options : 
			     RCC_PRESCALLER_BY_0 		  
			     RCC_PRESCALLER_BY_2   
			     RCC_PRESCALLER_BY_4 
			     RCC_PRESCALLER_BY_8
			     RCC_PRESCALLER_BY_16
*/
#define RCC_APB1_PRESCALLER   RCC_PRESCALLER_BY_0           /*CHOOSE HERE APB1 BUS CLOCK PRESCALLER*/
/*
  Options : 
     			RCC_PRESCALLER_BY_0 		  
			    RCC_PRESCALLER_BY_2   
		    	RCC_PRESCALLER_BY_4 
		    	RCC_PRESCALLER_BY_8
    			RCC_PRESCALLER_BY_16
		    	RCC_PRESCALLER_BY_64
    			RCC_PRESCALLER_BY_128
		    	RCC_PRESCALLER_BY_256
			    RCC_PRESCALLER_BY_512			
*/
#define RCC_AHP_PRESCALLER    RCC_PRESCALLER_BY_0         /*CHOOSE HERE AHB BUS CLOCK PRESCALLER*/
/*
  Options :  		  
			     PLL_CLOCK_DEVIDED_BY_1.5   
			     PLL_CLOCK_DEVIDED_BY_0 		      	
*/ 
#define RCC_USB_PRESCALLER    PLL_CLOCK_DEVIDED_BY_0            /*CHOOSE HERE USB CLOCK PRESCALLER*/
/* 
 SECURITY OF CLOCK INPUT SYSTEM ENABLE :
                                      TURN_ON 
 																			TURN_OFF
 */
#define CSS_ON                TURN_OFF
/***********************************************************************************************************************************************************************************************************************************************************
                                                    *******MICRO CLOCK OUTPUT**********
***********************************************************************************************************************************************************************************************************************************************************/																																										 
/*
  Options : 
    			NO_CLOCK  
			    SYSTEM_CLOCK					
		    	HSI_CLOCK     
			    HSE_CLOCK     
			    PLL_CLOCK     
*/ 
#define RCC_MCO_PIN          NO_CLOCK                     /*CHOOSE HERE OUTPUT CLOCK PIN SOURCE*/
/***********************************************************************************************************************************************************************************************************************************************************/


#endif
/**************************************************************END OF FILE*********************************************************************************************************************************************************************/
