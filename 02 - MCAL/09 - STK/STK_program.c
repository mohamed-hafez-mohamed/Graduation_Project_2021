/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v02                                */
 /* date        : 25/8/2020                          */
/*****************************************************/
/* Library includes */
#include "BIT_MATH.h"
#include "Std_Types.h"

/* Module includes */
#include "STK_interface.h"
#include "STK_private.h"
#include "STK_config.h"

/*****   Global variable   *****/
uint32 global_uint32Clk       = 0 ;
uint8  Global_uint8SingleFlag = 0 ;
void (* functionCallBack)(void);  

void STK_voidInit(void)
{
	
	/*  choosing clk for the SysTick  */
	#if   STK_CLK_SOURCE  ==  AHP
		SET_BIT   (STK->CTRL , STK_CTRL_CLKSOURCE);
		global_uint32Clk = STK_AHP_CLK ;
		
	#elif STK_CLK_SOURCE  ==  AHP_BY_8
		CLR_BIT (STK->CTRL , STK_CTRL_CLKSOURCE);
		global_uint32Clk = STK_AHP_CLK / 8  ;
	
	#else 
		#error (" configuration error")
	#endif 
}

void STK_voidSetBusyWait( uint32 Copy_uint32Time , STK_time_t copy_unit )
{
	uint32 local_uint32Load = 0 ;
	STK->VAL = 0 ;
	/* Calculate and load the load value */
	switch (copy_unit){
		case TIME_MS : 
			local_uint32Load = Copy_uint32Time * (global_uint32Clk / MS_IN_ONE_SECOND) ;
			STK->LOAD     = local_uint32Load ;
			break;
			
		case TIME_US :
			local_uint32Load = Copy_uint32Time * (global_uint32Clk / US_IN_ONE_SECOND) ;
			STK->LOAD     = local_uint32Load ;
			break ; 
		default :    /* Should not be here */      break;
	}
	
	/* Start timer */
	SET_BIT(STK->CTRL , STK_CTRL_ENABLE);
	
	/* Wait for the flag */
	while ( !(GET_BIT (STK->CTRL , STK_CTRL_COUNTFLAG)));
	
	/* Stop timer */
	CLR_BIT(STK->CTRL , STK_CTRL_ENABLE);
}

void STK_voidSetIntervalPeriodic( uint32 Copy_uint32Time , STK_time_t copy_unit, void (*Copy_func)(void)){
	uint32 local_uint32Load = 0 ;
	STK->VAL = 0 ;
	/* Calculate and load the load value */
	switch (copy_unit){
		case TIME_MS : 
			local_uint32Load = Copy_uint32Time * (global_uint32Clk / MS_IN_ONE_SECOND) ;
			STK->LOAD     = local_uint32Load ;
			break;
			
		case TIME_US :
			local_uint32Load = Copy_uint32Time * (global_uint32Clk / US_IN_ONE_SECOND) ;
			STK->LOAD     = local_uint32Load ;
			break ; 
		default :    /* Should not be here */      break;
	}
	
	/* To pass the function to ISR */
	functionCallBack = Copy_func ;
	
	/* Start timer */
	SET_BIT(STK->CTRL , STK_CTRL_ENABLE);
	
	/* Enable interrupt */
	SET_BIT(STK->CTRL , STK_CTRL_TICKINT);
}

void STK_voidSetIntervalSingle( uint32 Copy_uint32Time , STK_time_t copy_unit, void (*Copy_func)(void)){
	uint32 local_uint32Load = 0 ;
	CLR_BIT(STK->CTRL , STK_CTRL_ENABLE);
	STK->VAL = 0 ;
	/* Calculate and load the load value */
	switch (copy_unit){
		case TIME_MS :
			local_uint32Load = Copy_uint32Time * (global_uint32Clk / 1000) ;
			STK->LOAD     = local_uint32Load ;
			break;

		case TIME_US :
			local_uint32Load = Copy_uint32Time * (global_uint32Clk / 1000000) ;
			STK->LOAD     = local_uint32Load ;
			break ;
		default :    /* Should not be here */      break;
	}

	/* To pass the function to ISR */
	functionCallBack = Copy_func ;

	/* Start timer */
	SET_BIT(STK->CTRL , STK_CTRL_ENABLE);

	/* Enable interrupt */
	SET_BIT(STK->CTRL , STK_CTRL_TICKINT);

	/* Set single flag */
	Global_uint8SingleFlag = 1 ;
}

void STK_voidStop(void)
{
	/* Stop timer */
	CLR_BIT(STK->CTRL , STK_CTRL_ENABLE);
	
	/* Disable interrupt */
	CLR_BIT(STK->CTRL , STK_CTRL_TICKINT);	
}

void STK_voidResume(void)
{
	/* Start timer */
	SET_BIT(STK->CTRL , STK_CTRL_ENABLE);
	
	/* Enable interrupt */
	SET_BIT(STK->CTRL , STK_CTRL_TICKINT);	
}

void STK_voidStart(void)
{
	/* Zero the val rigester */
	STK->VAL = 0 ;
	
	/* Load value with max value */
	STK->LOAD = 0xFFFFFF;
	
	/* Start timer */
	SET_BIT(STK->CTRL , STK_CTRL_ENABLE);
}


uint32 STK_uint32GetElapsedTime(STK_time_t copy_unit)
{
	uint32 local_uint32Value =  STK->LOAD - STK->VAL ;
	uint32 local_uint32ElapsedTime = 0 ;
	/* Calculate the elabsed time in ms or us */
	switch (copy_unit){
		case TIME_MS : 
			local_uint32ElapsedTime = local_uint32Value / (global_uint32Clk / 1000) ;
			break;
			
		case TIME_US :
			local_uint32ElapsedTime = local_uint32Value / (global_uint32Clk / 1000000) ;
			break ; 
		default :    /* Should not be here */      break;
	}
	return local_uint32ElapsedTime ;
}


uint32 STK_uint32GetRemainingTime(STK_time_t copy_unit)
{
	uint32 local_uint32Value = STK->VAL ;
	uint32 local_uint32RemainingTime = 0 ;
	/* Calculate remaining time in ms or us */
	switch (copy_unit){
		case TIME_MS : 
			local_uint32RemainingTime = local_uint32Value / (global_uint32Clk / 1000) ;
			break;
			
		case TIME_US :
			local_uint32RemainingTime = local_uint32Value / (global_uint32Clk / 1000000) ;
			break ; 
		default :    /* Should not be here */      break;
	}
	return local_uint32RemainingTime ;
}

void SysTick_Handler(void)
{
	/* In case of using single interval*/
	if (Global_uint8SingleFlag){
		/* Stop timer */
		CLR_BIT(STK->CTRL , STK_CTRL_ENABLE);
		/* Disable interrupt */	
		CLR_BIT(STK->CTRL , STK_CTRL_TICKINT);
	}
	functionCallBack();
}
