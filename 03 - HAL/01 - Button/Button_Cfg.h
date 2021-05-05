/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v01                                */
 /* date        : 15/8/2020                          */
/*****************************************************/
#ifndef BUTTON_CONFIG_H
#define BUTTON_CONFIG_H

/*
	Options : 
		INTERNAL_PULL_UP
		EXTERNAL_PULL_UP
		INTERNAL_PULL_DOWN
		EXTERNAL_PULL_DOWN	
*/

#define    BUTTON_PULL_TYPE     INTERNAL_PULL_UP

/*
	Options : 
		1 : max number of pin in MC	
*/
#define    BUTTON_NUMBER        2


/* check to detrmine the voltage check on pins */
#if   (BUTTON_PULL_TYPE == INTERNAL_PULL_UP ) || (BUTTON_PULL_TYPE == EXTERNAL_PULL_UP )
	#define BUTTON_PRESSED_VOLTAGE   0
	#define BUTTON_RELEASED_VOLTAGE  1
		
#elif (BUTTON_PULL_TYPE == INTERNAL_PULL_DOWN) || (BUTTON_PULL_TYPE == EXTERNAL_PULL_DOWN)
	#define BUTTON_PRESSED_VOLTAGE   1
	#define BUTTON_RELEASED_VOLTAGE  0
	
#else 
		#error("Configuration error")
#endif


#endif
