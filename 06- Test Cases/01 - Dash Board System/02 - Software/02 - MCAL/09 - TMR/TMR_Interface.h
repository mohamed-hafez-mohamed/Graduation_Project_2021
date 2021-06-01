/*****************************************************/
 /* Author      : Mosad                              */
 /* Version     : v01                                */
 /* date        : 10/9/2020                           */
/*****************************************************/
#ifndef TMR_INTERFACE_H
#define TMR_INTERFACE_H


/**** Timer channels ****/
typedef enum {
	TIM1,
	TIM2,
	TIM3,
	TIM4,
	MAX_TMRS
}TMR_channels_t;

/***********************************************************/
 /* Function Name  : TMR_voidInit 
  * Function Type  : Initialization 
  * Parameters     : void 
  * Return         : void
  * Discription    : 
  * Pre-conditions : RCC must be enabled for used timers
					if interrupt is enabled you must enable 
					the correspending interrupt from NVIC
  */				
/************************************************************/
void TMR_voidInit (void);

/***********************************************************/
 /* Function Name  : TMR_voidSetBusyWait 
  * Function Type  : Delay function  
  * Parameters     : Timer channel   /  Time in us 
  * Return         : void
  * Discription    : 
  * Pre-conditions : Timer's interrupt must be disabled 
  */				
/************************************************************/
void TMR_voidSetBusyWait (TMR_channels_t copy_channel , uint32 copy_u32TimeUS);


/***********************************************************/
 /* Function Name  : TMR_voidSetPeriodic 
  * Function Type  :   
  * Parameters     : Timer channel   /  Time in us  /  void function 
  * Return         : void
  * Discription    : 
  * Pre-conditions :  
  */				
/************************************************************/
void TMR_voidSetPeriodic (TMR_channels_t copy_channel , uint32 copy_u32TimeUS , void (*func)(void));

/***********************************************************/
 /* Function Name  : TMR_voidDisableOverFlowInterrupt 
  * Function Type  :   
  * Parameters     : Timer channel  
  * Return         : void
  * Discription    : 
  * Pre-conditions :  
  */				
/************************************************************/
void TMR_voidDisableOverFlowInterrupt(TMR_channels_t copy_channel );



#endif
