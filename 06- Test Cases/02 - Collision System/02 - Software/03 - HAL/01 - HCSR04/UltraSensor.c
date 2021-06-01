/*******************************************************************************
**  FILENAME     : UltraSensor.c                         			                **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2021-05-24                                                 **
**                                                                            **
**  AUTHOR       : osamahijazi	                                              **
**                                                                            **
*******************************************************************************/
/*****************************************************************************************/
/*                                   Include Headers                                     */
/*****************************************************************************************/
#include "BIT_MATH.h"
#include "Std_Types.h"
/*****************************************************************************************/
/*                                Include modules Headers                                */
/*****************************************************************************************/
#include "UltraSensor_Interface.h"
#include "UltraSensor_Private.h"
#include "UltraSensor_Cfg.h"
#include "GPIO_interface.h"
#include "STK_interface.h"
/*****************************************************************************************/
/*                                Local Data Types                                       */                              
/*****************************************************************************************/                         

/*****************************************************************************************/
/*                              Local Varaible Definition                                */
/*****************************************************************************************/
 volatile static uint8   Global_uint8TimerFlag = INIT_VALUE ;
/*****************************************************************************************/
/*                               Function Definition                                     */
/*****************************************************************************************/
void HCSR04_VoidInit(void)
{
	             /********** Enable UltraSensor PINS***********/
    GPIO_VoidSetPinDirection(TRIGGER_PORT,TRIGGER_PIN , OUTPUT_MODE); 
    GPIO_VoidSetPinDirection(ECHO_PORT,ECHO_PIN , INPUT_MODE); 
    GPIO_VoidSetPinValue(ECHO_PORT , ECHO_PIN , ECHO_PULLDOWN); 
  
} 
/***********************END OF FUNCTION************************/																                                  																 																
Std_ReturnType HCSR04_uint8ReadDistance(uint8 *Copy_uint8Distance)
{
	       /*Local Error = ok*/
     Std_ReturnType Local_ReturnError = E_OK ;
       /*Local variables to get Duration of echo pulse */ 
     static uint32  Local_uint32Duration = INIT_VALUE ; 
    (*Copy_uint8Distance)  = INIT_VALUE ;
	  /*
	  Step 1 :*Send Trigger Pulse 
    */  
               /*Reset Trigger Pin before send pulse*/
    GPIO_VoidSetPinValue(TRIGGER_PORT , TRIGGER_PIN , LOW );
    STK_voidSetBusyWait ( TRIGGER_RESET , TIME_US );	
                     /*Send Trigger pulse*/
    GPIO_VoidSetPinValue(TRIGGER_PORT , TRIGGER_PIN , HIGH );
    STK_voidSetBusyWait ( TRIGGER_PULSE_WIDTH , TIME_US );	
    GPIO_VoidSetPinValue(TRIGGER_PORT , TRIGGER_PIN , LOW  );
    /*
	  Step 2 :*wait until high echo pulse .
            *wait until low  echo pulse .
            *calculate the time interval .
            *dont wait more than configrable time interval.			  
    */
                       	/*Set time interval and start timer */ 
    STK_voidSetIntervalSingle( TIMEOUT_INTERVAL , TIME_US , HCSR04_VoidCallBack) ; 
                 /*wait echo pin to be High with limited time out*/
    while( GPIO_VoidGetPinValue( ECHO_PORT,ECHO_PIN) == LOW )
    {		     	  /* incase of interrupt happened*/
	  if(Global_uint8TimerFlag == HIGH) 
            {	   
         		 /*Distance = zero indicate that signal was not returned & return = not ok*/
            (*Copy_uint8Distance) = OUT_OF_RANGE ;
              Local_ReturnError = E_NOT_OK ;	
              return Local_ReturnError ;					
           }			
    }
                       	/*Set time interval again and start timer */ 
    STK_voidSetIntervalSingle( TIMEOUT_INTERVAL , TIME_US , HCSR04_VoidCallBack) ; 
                    /*wait echo pin to be Low with limited time out*/
    while( GPIO_VoidGetPinValue( ECHO_PORT,ECHO_PIN) == HIGH )
	{			          /* incase of interrupt happened*/
	    if(Global_uint8TimerFlag == HIGH)
	     {	
         		 /*Distance = zero indicate that signal was not returned & return = not ok*/
	       (*Copy_uint8Distance) = OUT_OF_RANGE ;
               Local_ReturnError = E_NOT_OK ;	
               return Local_ReturnError ;	
             }			
       }
	                  /*Get time between two Edges in us*/
    Local_uint32Duration = STK_uint32GetElapsedTime(TIME_US ) ; 	
    STK_voidStop();
	               /*Calculate the distance in cm by devide pulse duration by 58*/
    (*Copy_uint8Distance) = (uint8)(Local_uint32Duration / TIME_CONS ) ;
		
    return Local_ReturnError ;
	                   
}
/***********************END OF FUNCTION************************/																                                  																 																
void HCSR04_VoidCallBack(void)
{
          /*Indicate that time is out and no echo signal has returned*/
    Global_uint8TimerFlag = HIGH ; 

}
/***********************END OF FUNCTION************************/																                                  																 																
