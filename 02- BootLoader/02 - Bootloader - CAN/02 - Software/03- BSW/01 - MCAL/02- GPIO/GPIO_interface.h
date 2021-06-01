/****************************************************************************
* Title                 :   GPIO   
* Filename              :   GPIO_interface.h
* Author                :   Mohamed Hafez
* Origin Date           :   10/08/2020
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
*  10/8/20   1.0.0   Mohamed Hafez   Interface Created.
*
*****************************************************************************/
/** @file  GPIO_interface.h
 *  @brief This module TODO: WHAT DO I DO?
 * 
 *  This is the header file for the definition TODO: MORE ABOUT ME!
 */
//TODO: UPDATE MACRO BELOW
#ifndef GPIO_INTERFACE_H_
#define GPIO_INTERFACE_H_

/******************************************************************************
* Includes
*******************************************************************************/

/******************************************************************************
* Preprocessor Constants
*******************************************************************************/
#define	LOW			0
#define	HIGH		   1
#define  SET         1
/******************************************************************************
* Configuration Constants
*******************************************************************************/
/*!<***************************Auxiliary Configuratio**********************************/
#define GPIO_CLR_MODE           0b1111         /*!<Clear Mode Bits*/
#define GPIO_PORT_ENTRY         0 
#define GPIO_PORT_MIDDLE        7              /*!<The Middle Of Port*/
#define GPIO_PORT_END           15             /*!<The End Of Port*/
#define GPIO_SHIFT_BIT          4              /*!<Multiply Pin By 4 to Shift 4 Bits As Each Pin Has 4 Bits*/
#define GPIO_ADJUST_BIT         8              /*!<Subtract Pin That > 7 By 8 to Start With 0 As Each Reg Start With Zero*/
#define GPIO_PORTA_ENTRY        0
#define GPIO_PORTA_END          15
#define GPIO_PORTB_ENTRY        16
#define GPIO_PORTB_END          31
#define GPIO_PORTC_ENTRY        32
#define GPIO_PORTC_END          47
#define GPIO_ADJUST_PORTB_PIN   16
#define GPIO_ADJUST_PORTC_PIN   32
/******************************************************************************
* Typedefs
*******************************************************************************/

/*!<*************************Ports Definitions**********************************/
typedef enum
{
   PORTA = 0X40010800,
   PORTB = 0X40010C00,
   PORTC = 0X40011000
}GPIO_PortId_t;

/*!<*************************Pins Definitions**********************************/
typedef enum
{
   //PORTA PINS
   PINA0 = 0 ,
   PINA1,
   PINA2,
   PINA3,
   PINA4,
   PINA5,
   PINA6,
   PINA7,
   PINA8,
   PINA9,
   PINA10,
   PINA11,
   PINA12,
   PINA13,
   PINA14,
   PINA15,
   //PORTB PINS
   PINB0,
   PINB1,
   PINB2,
   PINB3,
   PINB4,
   PINB5,
   PINB6,
   PINB7,
   PINB8,
   PINB9,
   PINB10,
   PINB11,
   PINB12,
   PINB13,
   PINB14,
   PINB15,
   //PORTB PINS
   PINC0,
   PINC1,
   PINC2,
   PINC3,
   PINC4,
   PINC5,
   PINC6,
   PINC7,
   PINC8,
   PINC9,
   PINC10,
   PINC11,
   PINC12,
   PINC13,
   PINC14,
   PINC15
}GPIO_PinId_t;

/*******************************************************************************/
/*!<***************************Modes Definitions*******************************/
typedef enum
{
   /*!<GPIO Input */
AFIO_INPUT_ANALOG           =   0b0000,
GPIO_INPUT_FLOATING         =   0b0100,
GPIO_INPUT_PULL_UP_DN       =   0b1000,
	/*!<10M modes*******************************************/
GPIO_OUTPUT_10M_PULL_UP_DN  =   0b0001,
GPIO_OUTPUT_10M_OPEN_DRAIN  =   0b0101,
AFIO_OUTPUT_10M_PULL_UP_DN  =   0b1001,
AFIO_OUTPUT_10M_OPEN_DRAIN  =   0b1101,
/*!<2M modes*******************************************/
GPIO_OUTPUT_2M_PULL_UP_DN   =   0b0010,
GPIO_OUTPUT_2M_OPEN_DRAIN   =   0b0110,
AFIO_OUTPUT_2M_PULL_UP_DN   =   0b1010,
AFIO_OUTPUT_2M_OPEN_DRAIN   =   0b1110,
/*!<50M modes*******************************************/
GPIO_OUTPUT_50M_PULL_UP_DN  =   0b0011,
GPIO_OUTPUT_50M_OPEN_DRAIN  =   0b0111,
AFIO_OUTPUT_50M_PULL_UP_DN  =   0b1011,
AFIO_OUTPUT_50M_OPEN_DRAIN  =   0b1111,
}GPIO_PIN_MODE;

typedef enum
{
   GPIO_PULL_DOWN = 0,
   GPIO_PULL_UP = 1
}GPIO_PULL_MODE_t;
/******************************************************************************
* Variables
*******************************************************************************/


/******************************************************************************
* Function Prototypes
*******************************************************************************/

void MGPIO_voidSetPinMode( GPIO_PinId_t copy_u8PinId , GPIO_PIN_MODE copy_u8Mode);
void MGPIO_voidSetPinValue(GPIO_PinId_t copy_u8PinId , u8 copy_u8Value);
u8   MGPIO_u8GetPinValue(GPIO_PinId_t copy_u8PinId);




#endif /*File_H_*/

/*** End of File **************************************************************/
