/****************************************************************************
* Title                 :   OBSERVER   
* Filename              :   OBSERVER.h
* Author                :   Mohamed Hafez
* Origin Date           :   30/05/2021
* Version               :   1.0.0
* Compiler              :   TODO: COMPILER GOES HERE
* Target                :   TODO: MCU GOES HERE
* Notes                 :   None
*
*****************************************************************************/
/****************************************************************************
* Doxygen C Template 
*
*****************************************************************************/
/*************** INTERFACE CHANGE LIST **************************************
*
*    Date    Version   Author          Description 
*  30/05/21   1.0.0   Mohamed Hafez   Interface Created.
*
*****************************************************************************/
/** @file  OBSERVER.h
 *  @brief This module TODO: WHAT DO I DO?
 * 
 *  This is the header file for the definition TODO: MORE ABOUT ME!
 */
//TODO: UPDATE MACRO BELOW
#ifndef OBSERVER_INTERFACE_H_
#define OBSERVER_INTERFACE_H_

/******************************************************************************
* Includes
*******************************************************************************/

/******************************************************************************
* Preprocessor Constants
*******************************************************************************/

/******************************************************************************
* Configuration Constants
*******************************************************************************/
#define MAXIMUM_TEMPERATURE      30
#define MAXIMUM_SPEED            64
#define MAXIMUM_DISTANCE         30
/******************************************************************************
* Macros
*******************************************************************************/
	
/******************************************************************************
* Typedefs
*******************************************************************************/

/******************************************************************************
* Variables
*******************************************************************************/

/******************************************************************************
* Function Prototypes
*******************************************************************************/
Std_ReturnType HOBSERVER_u8InitializeModule(void);
Std_ReturnType HOBSERVER_u8ObserveSystem(void);

#endif /*File_H_*/

/*** End of File **************************************************************/