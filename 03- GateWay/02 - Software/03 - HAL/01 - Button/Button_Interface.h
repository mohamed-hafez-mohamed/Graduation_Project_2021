/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v01                                */
 /* date        : 15/8/2020                          */
/*****************************************************/
#ifndef BUTTON_INTERFACE_H
#define BUTTON_INTERFACE_H

/* button states  */
typedef enum{
	PRE_PRESSED,
	PRESSED,
	PRE_RELEASED,
	RELEASED
}ButtonStateType;


/* 
  * BUTTON_voidInit - > Initialize the button and add it to the set must be 
						be called for every button 
  * i/p : port id (PORTA - PORTB - PORTC) / pin number ( PIN0 -> PIN15)
  * o/p : the button number in the set used to get state of a button
*/
void Button_voidInit(void);

/* 
  * BUTTON_voidGetState - > check on the button it is a periodic function should be called every 20 ms 
							(the period can change ) and after calling it check on state
*/
void Button_MainFunction(void);

/* 
  * BUTTON_voidGetState - > return the state of a specific button
  * i/p : button number in the set refer to function (BUTTON_voidInit)
  * o/p : state of the button (PRE_PRESSED - PRESSED - PRE_RELEASED - RELEASED)
*/
Std_ReturnType Button_GetState(uint8 copy_uint8ButtonId ,ButtonStateType *Cpy_ButtonState );




#endif