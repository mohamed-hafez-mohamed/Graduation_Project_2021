/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v01                                */
 /* date        : 15/8/2020                          */
/*****************************************************/
/* Library includes */
#include "Std_Types.h"
#include "BIT_MATH.h"

/* MCAL includes */
#include "GPIO_interface.h"


/* Specific module includes  */
#include "Button_Interface.h"
#include "Button_Private.h"
#include "Button_Cfg.h"


/***** Data Types ******/
typedef struct {
	ButtonStateType state ;
	uint8 samples[2];
}ButtonData_t;

typedef struct {
	uint8 ButtonPort ;
	uint8 ButtonPin  ;
}ButtonType;

static ButtonData_t Global_ButtonInfoArr [BUTTON_NUMBER] ; 

static ButtonType ButtonGpio[BUTTON_NUMBER] = {
	{ GPIOB,PIN1 } ,
	{ GPIOB,PIN3 }
};
 

void Button_voidInit(void)
{
	static uint8 Local_counter = 0 ;
	
	for (Local_counter = 0 ; Local_counter <BUTTON_NUMBER; Local_counter++)
	{
		Global_ButtonInfoArr[Local_counter].state = RELEASED;
	}
}

void Button_MainFunction(void)
{
	for ( uint8 i = 0 ; i < BUTTON_NUMBER ; i++){
		Global_ButtonInfoArr[i].samples[0] = Global_ButtonInfoArr[i].samples[1] ;
		
		Global_ButtonInfoArr[i].samples[1] = GPIO_VoidGetPinValue(ButtonGpio[i].ButtonPort , ButtonGpio[i].ButtonPin);
		
		switch(Global_ButtonInfoArr[i].state){
			case RELEASED:
				if((Global_ButtonInfoArr[i].samples[0] == BUTTON_PRESSED_VOLTAGE) &&
				   (Global_ButtonInfoArr[i].samples[1] == BUTTON_PRESSED_VOLTAGE))
				{
					Global_ButtonInfoArr[i].state = PRE_PRESSED;
				}
				break;
				
			case PRE_PRESSED:
				if(Global_ButtonInfoArr[i].samples[1] == BUTTON_PRESSED_VOLTAGE)
				{
					Global_ButtonInfoArr[i].state = PRESSED;
				}
				break;
				
			case PRESSED:
				if((Global_ButtonInfoArr[i].samples[0] == BUTTON_RELEASED_VOLTAGE) &&
				   (Global_ButtonInfoArr[i].samples[1] == BUTTON_RELEASED_VOLTAGE))
				{
					Global_ButtonInfoArr[i].state = PRE_RELEASED;
				}
				break;
			case PRE_RELEASED:
				if(Global_ButtonInfoArr[i].samples[1] == BUTTON_RELEASED_VOLTAGE)
				{
					Global_ButtonInfoArr[i].state = RELEASED;
				}
				break;
			default:
				/* Should not be here */
			break;
		}
	}
}

Std_ReturnType Button_GetState(uint8 copy_uint8ButtonId ,ButtonStateType *Cpy_ButtonState )
{
	Std_ReturnType Local_Error = E_OK;
	if (Cpy_ButtonState != NULL_PTR)
	{
		*Cpy_ButtonState = Global_ButtonInfoArr[copy_uint8ButtonId].state ;
	}
	else 
	{
		Local_Error = E_NOT_OK;
	}
	return Local_Error ;
	
}