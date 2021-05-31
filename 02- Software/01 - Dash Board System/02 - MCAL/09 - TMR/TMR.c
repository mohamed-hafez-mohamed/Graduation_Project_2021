/*****************************************************/
 /* Author      : Mosad                              */
 /* Version     : v01                                */
 /* date        : 10/9/2020                          */
/*****************************************************/

/* Library includes */
#include "BIT_MATH.h"
#include "Std_Types.h"

/* module includes */
#include "TMR_Interface.h"
#include "TMR_Cfg.h"
#include "TMR_Private.h"

/*  Global variables  */
extern const TMR_config_t configTable[TMR_NUMBER];
void (* callBackFunc[TMR_NUMBER])(void);

void TMR_voidInit (void)
{
	for (TMR_channels_t i = 0 ; i < MAX_TMRS ; i++){
		/* Will only configure the time if enabled otherwise the rigseters 
		   will remain at the reset value */
		if (configTable[i].u8Enable){
			/* Disable timer */
			CLR_BIT ( *(TIM[i]+CR1)  , 0 );
			
			/* choose mode */
			switch (configTable[i].u8Mode) {
				case UP_COUNTER     :
					CLR_BIT ( *(TIM[i]+CR1)  , 4 );
					break ;
				case DOWN_COUNTER   :
					SET_BIT   ( *(TIM[i]+CR1)  , 4 );
					break ;
				default : 
					break;
			}
			
			/* Enable / disable interrupt for update  */
			/* Rest of interrups will be implemented later */
			if (configTable[i].u8InterruptEnable){
				SET_BIT   ( (*(TIM[i]+DIER))  , 0 );

			}
			else {
				CLR_BIT ( (*(TIM[i]+DIER))  , 0 );
			}
			
			/* Configure prescaller */
			(*(TIM[i]+PSC)) =  (configTable[i].u16Prescaler - 1 ) ;
			
			/* Configure interval  */
			uint32 loacl_u32Hold =  (configTable[i].u32ClkSource / 1000000 ) * configTable[i].u32Interval ;
			loacl_u32Hold =  loacl_u32Hold / configTable[i].u16Prescaler;
			if (loacl_u32Hold < 65536 ){
				(*(TIM[i]+ARR)) = loacl_u32Hold ;
			}
			else {
				/* Error code */
			}

			/* Start timer */
			SET_BIT ( (*(TIM[i] +CR1)) , 0 );
		}
	}
} 

/****************** Timer basic functions **********************/

void TMR_voidSetBusyWait (TMR_channels_t copy_channel , uint32 copy_u32TimeUS)
{
	/* Stop timer */
	CLR_BIT ( (*(TIM[copy_channel]+CR1))  , 0 ); 
	
	/* Clear flag */
	CLR_BIT ((*(TIM[copy_channel] +SR)) , 0);
	
	/* Configure interval */
	uint32 loacl_u32Hold =  (configTable[copy_channel].u32ClkSource / 1000000 ) * copy_u32TimeUS ;
	loacl_u32Hold =  loacl_u32Hold / configTable[copy_channel].u16Prescaler;
	if (loacl_u32Hold < MAX_INTERVAL ){
		(*(TIM[copy_channel]+ARR)) = loacl_u32Hold ;
		(*(TIM[copy_channel]+CNT)) = 0 ;
	}
	else {
		/* Error code */
	}
	
	/* Start timer */
	SET_BIT ( (*(TIM[copy_channel] +CR1)) , 0 ); 
	
	/* Wait for flag */
	while (!(GET_BIT ((*(TIM[copy_channel] +SR)) , 0)));
	
	/* Stop timer */
	CLR_BIT ( (*(TIM[copy_channel]+CR1))  , 0 ); 
} 


void TMR_voidSetPeriodic (TMR_channels_t copy_channel , uint32 copy_u32TimeUS , void (*func)(void))
{

	/* Stop timer */
	CLR_BIT ( (*(TIM[copy_channel]+CR1))  , 0 ); 
	
	/* Configure interval */
	uint32 loacl_u32Hold =  (configTable[copy_channel].u32ClkSource / 1000000 ) * copy_u32TimeUS  ;
	loacl_u32Hold =  loacl_u32Hold / configTable[copy_channel].u16Prescaler;
	if (loacl_u32Hold < MAX_INTERVAL ){
		(*(TIM[copy_channel]+ARR)) = loacl_u32Hold ;
	}
	else {
		/* Error code */
	}
	
	/* Set call back function */
	callBackFunc[copy_channel] = func ;
	
	/* Start timer */
	SET_BIT ( (*(TIM[copy_channel] +CR1)) , 0 ); 
	
	/* Enable interrupt */
	SET_BIT   ( (*(TIM[copy_channel]+DIER))  , 0 );
}


void TMR_voidDisableOverFlowInterrupt(TMR_channels_t copy_channel )
{
	/* Disable interrupt */
	CLR_BIT( (*(TIM[copy_channel]+DIER))  , 0 );
}



/************** ISR handlers ******************/

void TIM2_IRQHandler (void){
	/* Clear flag */
	CLR_BIT ((*(TIM[1] +SR)) , 0);
	callBackFunc[1]();
}
void TIM3_IRQHandler (void){
	/* Clear flag */
	CLR_BIT ((*(TIM[2] +SR)) , 0);
	callBackFunc[2]();
}
void TIM4_IRQHandler (void){
	/* Clear flag */
	CLR_BIT ((*(TIM[3] +SR)) , 0);
	callBackFunc[3]();
}
