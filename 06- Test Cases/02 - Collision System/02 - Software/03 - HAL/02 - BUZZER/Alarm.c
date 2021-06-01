/*******************************************************************************
**  FILENAME     : Alarm.c                               			                **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2021-05-27                                                 **
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
#include "Alarm_Interface.h"
#include "Alarm_Private.h"
#include "Alarm_cfg.h"
#include "GPIO_interface.h"
#include "STK_Interface.h"
#include "Alarm_Interface.h"
/*****************************************************************************************/
/*                                Local Data Types                                       */                              
/*****************************************************************************************/                         


/*****************************************************************************************/
/*                              Local Varaible Definition                                */
/*****************************************************************************************/

/*****************************************************************************************/
/*                               Function Definition                                     */
/*****************************************************************************************/
void ALarm_VoidInit(void)
{
	             /********** Enable Buzzer PINS***********/
    GPIO_VoidSetPinDirection(ALARM_PORT , ALARM_PIN , OUTPUT_MODE ); 
} 
/***********************END OF FUNCTION************************/																                                  																 																
Std_ReturnType Alarm_uint8SetPulse(void)
{
                  /*Local Error = ok*/
    Std_ReturnType Local_ReturnError = E_OK ;
    GPIO_VoidSetPinValue(ALARM_PORT  , ALARM_PIN , HIGH );   
    STK_voidSetBusyWait (PULSE_WIDTH  , TIME_US );	
    GPIO_VoidSetPinValue(ALARM_PORT  , ALARM_PIN , LOW ) ;
    return Local_ReturnError ; 
}
/***********************END OF FUNCTION************************/																                                  																 																



