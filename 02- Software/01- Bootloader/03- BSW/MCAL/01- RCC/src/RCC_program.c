/*******************************************************************************
* Title                 :   RCC 
* Filename              :   RCC_program.c
* Author                :   Mohamed Hafez
* Origin Date           :   10/8/2020
* Version               :   1.0.0
* Compiler              :   TODO: COMPILER GOES HERE
* Target                :   TODO: MCU GOES HERE
* Notes                 :   None 
*
*****************************************************************************/
/*************** SOURCE REVISION LOG *****************************************
*
*    Date    Version   Author          Description 
*  10/08/20   1.0.0   Mohamed Hafez   Initial Release.
*
*******************************************************************************/
/** @file RCC_program.c
 *  @brief This is the source file for configure clock and reset 
 */
/******************************************************************************
* Includes
*******************************************************************************/
//Include libraries
#include "STD_TYPES.h"
#include "BIT_MATH.h"

//TODO: Include file of lower layers

//Include own driver files(interface, private, config)
#include "RCC_interface.h"
#include "RCC_private.h"
#include "RCC_config.h"

//TODO: UPDATE MY INCLUDE
				/* For TODO: WHY ME? */		

/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/
/**
 * Doxygen tag for documenting variables and constants
 */

/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/

/******************************************************************************
* Module Typedefs
*******************************************************************************/

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/

/******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************
* Function Definitions
*******************************************************************************/

/******************************************************************************
* Function : RCC_u8EnableClock(u8 Copy_u8BusId, u8 Copy_u8BperId)
*//** 
* \b Description:
*
* This function is used to enable the clock for the chosen perpheral.  
*
* PRE-CONDITION:  Peripheral id less than 31(number of bits in the register)
*
* POST-CONDITION: Peripheral clock enabled
*
* @param          Copy_u8BusId  is the Bus type
* 
* @param          Copy_u8BperId is the peripheral type
* 
* @return 		  TODO: Normal return or error code.
*
* \b Example Example:
* @code
* 	TODO: u8 return_code = RCC_u8EnableClock(RCC_AHB, DMA1);
*
* @endcode
*
* @see RCC_u8EnableClock
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <table align="left" style="width:800px">
* <tr><td> Date       </td><td> Software Version </td><td> Initials </td><td> Description </td></tr>
* <tr><td> 10/08/2020 </td><td> 0.5.0            </td><td> JWB      </td><td> Interface Created </td></tr>
* </table><br><br>
* <hr>
*
*******************************************************************************/

void MRCC_voidEnableClock(u8 Copy_u8BusId, u8 Copy_u8BperId) 
{
    if(Copy_u8BperId <= 31)
	{
		switch(Copy_u8BusId)
		{
			case RCC_AHB  : SET_BIT(RCC_AHBENR,  Copy_u8BperId); break;
			case RCC_APB1 : SET_BIT(RCC_APB1ENR, Copy_u8BperId); break;
			case RCC_APB2 : SET_BIT(RCC_APB2ENR, Copy_u8BperId); break;
			//default       : /*TODO: Return Error Code*/          break;

		}
	}
	else
	{
		//TODO: Return Error Code
	}
	
}

/******************************************************************************
* Function : RCC_u8DisableClock(u8 Copy_u8BusId, u8 Copy_u8BperId)
*//** 
* \b Description:
*
* This function is used to disable the clock for the chosen perpheral.  
*
* PRE-CONDITION:  Peripheral id less than 31(number of bits in the register)
*
* POST-CONDITION: Peripheral clock enabled
*
* @param          Copy_u8BusId  is the Bus type
* 
* @param          Copy_u8BperId is the peripheral type
* 
* @return 		  TODO: Normal return or error code.
*
* \b Example Example:
* @code
* 	TODO: u8 return_code = RCC_u8DisableClock(RCC_AHB, DMA1);
*
* @endcode
*
* @see RCC_u8DisableClock
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <table align="left" style="width:800px">
* <tr><td> Date       </td><td> Software Version </td><td> Initials </td><td> Description </td></tr>
* <tr><td> 10/08/2020 </td><td> 0.5.0            </td><td> JWB      </td><td> Interface Created </td></tr>
* </table><br><br>
* <hr>
*
*******************************************************************************/
void MRCC_voidDisableClock(u8 Copy_u8BusId, u8 Copy_u8BperId) 
{
    if(Copy_u8BperId <= 31)
	{
		switch(Copy_u8BusId)
		{
			case RCC_AHB  : CLR_BIT(RCC_AHBENR,  Copy_u8BperId); break;
			case RCC_APB1 : CLR_BIT(RCC_APB1ENR, Copy_u8BperId); break;
			case RCC_APB2 : CLR_BIT(RCC_APB2ENR, Copy_u8BperId); break;
			//default       : /*TODO: Return Error Code*/          break;
		}
	}
	else
	{
		//TODO: Return Error Code
	}
	
}

/******************************************************************************
* Function : RCC_voidInitSystem()
*//** 
* \b Description:
*
* This function is used to select clock source for processor.  
*
* PRE-CONDITION:  
*
* POST-CONDITION: system clock determined
*
* @param          No parameter
* 
* @param          No parameter
* 
* @return 		  NO return.
*
* \b Example Example:
* @code
* 	RCC_voidInitSystem();
*
* @endcode
*
* @see RCC_voidInitSystem
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <table align="left" style="width:800px">
* <tr><td> Date       </td><td> Software Version </td><td> Initials </td><td> Description </td></tr>
* <tr><td> 10/08/2020 </td><td> 0.5.0            </td><td> JWB      </td><td> Interface Created </td></tr>
* </table><br><br>
* <hr>
*
*******************************************************************************/
void MRCC_voidInitSysClock(void)
{
	RCC_CR   = 0X00000080;                    /*CLEAR REG + Triming = 0  */
	RCC_CFGR = 0X00000000;                    /*CLEAR REG */
	#if  RCC_CLOCK_TYPE == RCC_HSE_CRYSTAL 
	    SET_BIT(RCC_CR, RCC_CR_CSSON);
		SET_BIT(RCC_CR, RCC_CR_HSEON);
		while(!(GET_BIT(RCC_CR, RCC_CR_HSERDY)));
		RCC_CFGR |= RCC_CFGR_SW_HSE;
	#elif  RCC_CLOCK_TYPE == RCC_HSE_RC 
	    SET_BIT(RCC_CR, RCC_CR_CSSON);
	    SET_BIT(RCC_CR, RCC_CR_HSEBYP);
		SET_BIT(RCC_CR, RCC_CR_HSEON);
		while(!(GET_BIT(RCC_CR, RCC_CR_HSERDY)));
		RCC_CFGR |= RCC_CFGR_SW_HSE;
	#elif  RCC_CLOCK_TYPE == RCC_HSI 
	    SET_BIT(RCC_CR, RCC_CR_HSION);
		while(!(GET_BIT(RCC_CR, RCC_CR_HSIRDY)));
        RCC_CFGR |= RCC_CFGR_SW_HSI;
	#elif  RCC_CLOCK_TYPE == RCC_PLL
        #if   RCC_PLL_INPUT == RCC_PLL_IN_HSI_DIV_2
		    SET_BIT(RCC_CR, RCC_CR_HSION);
		    while(!(GET_BIT(RCC_CR, RCC_CR_HSIRDY)));
            RCC_CFGR |= RCC_CFGR_PLLSRC_HSI_Div2;
	    #elif RCC_PLL_INPUT == RCC_PLL_IN_HSE_DIV_2
		    #if   RCC_PLL_HSE == RCC_PLL_HSE_CRYSTAL
               SET_BIT(RCC_CR, RCC_CR_CSSON);
		       SET_BIT(RCC_CR, RCC_CR_HSEON);
		       while(!(GET_BIT(RCC_CR, RCC_CR_HSERDY)));
			#elif RCC_PLL_HSE == RCC_PLL_HSE_RC
               SET_BIT(RCC_CR, RCC_CR_CSSON);
	           SET_BIT(RCC_CR, RCC_CR_HSEBYP);
		       SET_BIT(RCC_CR, RCC_CR_HSEON);
		       while(!GET_BIT(RCC_CR, RCC_CR_HSERDY));
            #else
			   #warning("Wrong PLL input from HSE...crystal is default")
			   SET_BIT(RCC_CR, RCC_CR_CSSON);
		       SET_BIT(RCC_CR, RCC_CR_HSEON);
		       while(!(GET_BIT(RCC_CR, RCC_CR_HSERDY)));
			#endif
            RCC_CFGR |= RCC_CFGR_PLLXTPRE_HSE_Div2; 
	    #elif RCC_PLL_INPUT == RCC_PLL_IN_HSE
		    #if   RCC_PLL_HSE == RCC_PLL_HSE_CRYSTAL
               SET_BIT(RCC_CR, RCC_CR_CSSON);
		       SET_BIT(RCC_CR, RCC_CR_HSEON);
		       while(!(GET_BIT(RCC_CR, RCC_CR_HSERDY)));
			#elif RCC_PLL_HSE == RCC_PLL_HSE_RC
               SET_BIT(RCC_CR, RCC_CR_CSSON);
	           SET_BIT(RCC_CR, RCC_CR_HSEBYP);
		       SET_BIT(RCC_CR, RCC_CR_HSEON);
		       while(!GET_BIT(RCC_CR, RCC_CR_HSERDY)));
            #else
			   #warning("Wrong PLL input from HSE...crystal is default")
			   SET_BIT(RCC_CR, RCC_CR_CSSON);
		       SET_BIT(RCC_CR, RCC_CR_HSEON);
		       while(!(GET_BIT(RCC_CR, RCC_CR_HSERDY)));
			#endif
            RCC_CFGR |= RCC_CFGR_PLLSRC_HSE;
		#else
            #warning("Wrong PLL Input....HSI is dinput for PLL by default")
			RCC_CFGR |= RCC_CFGR_PLLSRC_HSI_Div2;
		#endif
		#if   RCC_PLL_MUL_VAL == RCC_PLLMULL2
            RCC_CFGR |= RCC_CFGR_PLLMULL2
		#elif RCC_PLL_MUL_VAL == RCC_PLLMULL3
            RCC_CFGR |= RCC_CFGR_PLLMULL3
		#elif RCC_PLL_MUL_VAL == RCC_PLLMULL4
            RCC_CFGR |= RCC_CFGR_PLLMULL4
		#elif RCC_PLL_MUL_VAL == RCC_PLLMULL5
            RCC_CFGR |= RCC_CFGR_PLLMULL5
		#elif RCC_PLL_MUL_VAL == RCC_PLLMULL6
            RCC_CFGR |= RCC_CFGR_PLLMULL6
		#elif RCC_PLL_MUL_VAL == RCC_PLLMULL7
            RCC_CFGR |= RCC_CFGR_PLLMULL7
		#elif RCC_PLL_MUL_VAL == RCC_PLLMULL8
            RCC_CFGR |= RCC_CFGR_PLLMULL8
		#elif RCC_PLL_MUL_VAL == RCC_PLLMULL9
            RCC_CFGR |= RCC_CFGR_PLLMULL9
		#elif RCC_PLL_MUL_VAL == RCC_PLLMULL10
            RCC_CFGR |= RCC_CFGR_PLLMULL10
		#elif RCC_PLL_MUL_VAL == RCC_PLLMULL11
            RCC_CFGR |= RCC_CFGR_PLLMULL11
		#elif RCC_PLL_MUL_VAL == RCC_PLLMULL12
            RCC_CFGR |= RCC_CFGR_PLLMULL12
		#elif RCC_PLL_MUL_VAL == RCC_PLLMULL13
            RCC_CFGR |= RCC_CFGR_PLLMULL13
		#elif RCC_PLL_MUL_VAL == RCC_PLLMULL14
            RCC_CFGR |= RCC_CFGR_PLLMULL14
		#elif RCC_PLL_MUL_VAL == RCC_PLLMULL15
            RCC_CFGR |= RCC_CFGR_PLLMULL15
		#elif RCC_PLL_MUL_VAL == RCC_PLLMULL16
            RCC_CFGR |= RCC_CFGR_PLLMULL16
		#else
            #warning("PLL input clock x 2 by default")
			RCC_CFGR |= RCC_CFGR_PLLMULL2
		#endif
		SET_BIT(RCC_AHBENR, RCC_CR_PLLON);
		while(!(GET_BIT(RCC_CR, RCC_CR_PLLRDY)));
		RCC_CFGR |= RCC_CFGR_SW_PLL;
	#else
	    #warning("Wrong Clock Type/HSI is default")
	    SET_BIT(RCC_CR, RCC_CR_HSION);
		while(!(GET_BIT(RCC_CR, RCC_CR_HSIRDY)));
        RCC_CFGR |= RCC_CFGR_SW_HSI;
	#endif 
	
}

void MRCC_voidSetAHBPRE(void)
{
	#if   RCC_HPRE_DIV_VAL == RCC_HPRE_DIV1
        RCC_CFGR |= RCC_CFGR_HPRE_DIV1;
	#elif RCC_HPRE_DIV_VAL == RCC_HPRE_DIV2
        RCC_CFGR |= RCC_CFGR_HPRE_DIV2;
	#elif RCC_HPRE_DIV_VAL == RCC_HPRE_DIV4
        RCC_CFGR |= RCC_CFGR_HPRE_DIV4;
	#elif RCC_HPRE_DIV_VAL == RCC_HPRE_DIV8
        RCC_CFGR |= RCC_CFGR_HPRE_DIV8;
	#elif RCC_HPRE_DIV_VAL == RCC_HPRE_DIV16
        RCC_CFGR |= RCC_CFGR_HPRE_DIV16;
	#elif RCC_HPRE_DIV_VAL == RCC_HPRE_DIV64
        RCC_CFGR |= RCC_CFGR_HPRE_DIV64;
	#elif RCC_HPRE_DIV_VAL == RCC_HPRE_DIV128
        RCC_CFGR |= RCC_CFGR_HPRE_DIV128;
	#elif RCC_HPRE_DIV_VAL == RCC_HPRE_DIV256
        RCC_CFGR |= RCC_CFGR_HPRE_DIV256;
	#elif RCC_HPRE_DIV_VAL == RCC_HPRE_DIV512
	    RCC_CFGR |= RCC_CFGR_HPRE_DIV512;
	#else
	    RCC_CFGR |= RCC_CFGR_HPRE_DIV1;
		#warning(Wrong HPRE....DIV1 is default)
	#endif

}

void MRCC_voidSetAPB1Pre(void)
{
	#if   RCC_PPRE1_DIV_VAL == RCC_PPRE1_DIV1
        RCC_CFGR |= RCC_CFGR_PPRE1_DIV1;
	#elif RCC_PPRE1_DIV_VAL == RCC_PPRE1_DIV2
        RCC_CFGR |= RCC_CFGR_PPRE1_DIV2;
	#elif RCC_PPRE1_DIV_VAL == RCC_PPRE1_DIV4
        RCC_CFGR |= RCC_CFGR_PPRE1_DIV4;
	#elif RCC_PPRE1_DIV_VAL == RCC_PPRE1_DIV8
        RCC_CFGR |= RCC_CFGR_PPRE1_DIV8;
	#elif RCC_PPRE1_DIV_VAL == RCC_PPRE1_DIV16
        RCC_CFGR |= RCC_CFGR_PPRE1_DIV16;
	#else
	    RCC_CFGR |= RCC_CFGR_PPRE1_DIV1;
		#warning(Wrong PPRE1....DIV1 is default)
	#endif
}

void MRCC_voidSetAPB2Pre(void)
{
	#if   RCC_PPRE2_DIV_VAL == RCC_PPRE2_DIV1
        RCC_CFGR |= RCC_CFGR_PPRE2_DIV1;
	#elif RCC_PPRE2_DIV_VAL == RCC_PPRE2_DIV2
        RCC_CFGR |= RCC_CFGR_PPRE2_DIV2;
	#elif RCC_PPRE2_DIV_VAL == RCC_PPRE2_DIV4
        RCC_CFGR |= RCC_CFGR_PPRE2_DIV4;
	#elif RCC_PPRE2_DIV_VAL == RCC_PPRE2_DIV8
        RCC_CFGR |= RCC_CFGR_PPRE2_DIV8;
	#elif RCC_PPRE2_DIV_VAL == RCC_PPRE2_DIV16
        RCC_CFGR |= RCC_CFGR_PPRE2_DIV16;
	#else
	    RCC_CFGR |= RCC_CFGR_PPRE2_DIV1;
		#warning(Wrong PRE2....DIV1 is default)
	#endif
}

void MRCC_voidSetADCPre(void)
{
	#if   RCC_ADCPRE_DIV_VAL == RCC_ADCPRE_DIV2
        RCC_CFGR |= RCC_CFGR_ADCPRE_DIV2;
	#elif RCC_ADCPRE_DIV_VAL == RCC_ADCPRE_DIV4
        RCC_CFGR |= RCC_CFGR_ADCPRE_DIV4;
	#elif RCC_ADCPRE_DIV_VAL == RCC_ADCPRE_DIV6
        RCC_CFGR |= RCC_CFGR_ADCPRE_DIV6;
	#elif RCC_ADCPRE_DIV_VAL == RCC_ADCPRE_DIV8
        RCC_CFGR |= RCC_CFGR_ADCPRE_DIV8;
	#else
	    RCC_CFGR_ADCPRE_DIV2;
		#warning(Wrong ADCPRE....DIV2 is default)
	#endif
}

void MRCC_voidMcoClk(void)
{
	#if   RCC_MCO_CLK == RCC_MCO_NO_CLK
	   RCC_CFGR |= RCC_CFGR_MCO_NOCLOCK;
	#elif RCC_MCO_CLK == RCC_MCO_SYS_CLK
	   RCC_CFGR |= RCC_CFGR_MCO_SYSCLK;
	#elif RCC_MCO_CLK == RCC_MCO_HSI_CLK
       RCC_CFGR |= RCC_CFGR_MCO_HSI;
	#elif RCC_MCO_CLK == RCC_MCO_HSE_CLK
       RCC_CFGR |= RCC_CFGR_MCO_HSE;
	#elif RCC_MCO_CLK == RCC_MCO_PLL_DVID2_CLK
	   RCC_CFGR |= RCC_CFGR_MCO_PLL;
	#endif // 
	
}

/*************** END OF FUNCTIONS ***************************************************************************/
