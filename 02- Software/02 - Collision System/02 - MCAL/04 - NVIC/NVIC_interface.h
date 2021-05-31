/****************************************************************************
* Title                 :   NVIC   
* Filename              :   NVIC_interface.h
* Author                :   Mohamed Hafez
* Origin Date           :   15/08/2020
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
*  15/8/20   1.0.0   Mohamed Hafez   Interface Created.
*
*****************************************************************************/
/** @file  NVIC_interface.h
 *  @brief This module TODO: WHAT DO I DO?
 * 
 *  This is the header file for the definition TODO: MORE ABOUT ME!
 */
//TODO: UPDATE MACRO BELOW
#ifndef NVIC_INTERFACE_H_
#define NVIC_INTERFACE_H_

/******************************************************************************
* Includes
*******************************************************************************/

/******************************************************************************
* Preprocessor Constants
*******************************************************************************/
#define SET                  1

#define BASE_GROUP_VALUE     0X05FA0300
#define GROUP_STEP           256
#define MS_4Local_u8Counter  4

#define NVIC_GROUP_4_SUB_0   0X05FA0300
#define NVIC_GROUP_3_SUB_1   0X05FA0400
#define NVIC_GROUP_2_SUB_2   0X05FA0500
#define NVIC_GROUP_1_SUB_3   0X05FA0600
#define NVIC_GROUP_0_SUB_4   0X05FA0700
/******************************************************************************
* Configuration Constants
*******************************************************************************/


/******************************************************************************
* Macros
*******************************************************************************/
	
/******************************************************************************
* Typedefs
*******************************************************************************/

typedef enum
{
    WWDG = 0,
    PVD,
    TAMPER,
    RTC,
    FLASH,
    RCC,
    EXTI0,
    EXTI1,
    EXTI2,
    EXTI3,
    EXTI4,
    DMA1_Channel1,
    DMA1_Channel2,
    DMA1_Channel3,
    DMA1_Channel4,
    DMA1_Channel5,
    DMA1_Channel6,
    DMA1_Channel7,
    ADC1_2,
    USB_HP_CAN_TX,
    USB_LP_CAN_RX0,
    CAN_RX1,
    CAN_SCE,
    EXTI9_5,
    TIM1_BRK,
    TIM1_UP,
    TIM1_TRG_COM,
    TIM1_CC,
    TIM2,
    TIM3,
    TIM4,
    I2C1_EV,
    I2C1_ER,
    I2C2_EV,
    I2C2_ER,
    SPI1,
    SPI2,
    USART1,
    USART2,
    USART3,
    EXTI15_10,
    RTCAlarm,
    USBWakeup,
    TIM8_BRK,
    TIM8_UP,
    TIM8_TRG_COM,
    TIM8_CC,
    ADC3,
    FSMC,
    SDIO,
    TIM5,
    SPI3,
    UART4,
    UART5,
    TIM6,
    TIM7,
    DMA2_Channel1,
    DMA2_Channel2,
    DMA2_Channel3,
    DMA2_Channel4_5
}NVIC_HW_PRIORITY;
/******************************************************************************
* Variables
*******************************************************************************/

/******************************************************************************
* Function Prototypes
*******************************************************************************/

uint8 MNVIC_u8EnableInt(NVIC_HW_PRIORITY  copy_IntId);
uint8 MNVIC_u8EnableInts(NVIC_HW_PRIORITY copy_IntId[], uint8 copy_u8ArraySize);
uint8 MNVIC_u8DisableInt(NVIC_HW_PRIORITY  copy_IntId);
uint8 MNVIC_u8DisableInts(NVIC_HW_PRIORITY copy_IntId[], uint8 copy_u8ArraySize);
uint8 MNVIC_u8IsIntActive(NVIC_HW_PRIORITY  copy_IntId);
uint8 MNVIC_u8SetIntpending(NVIC_HW_PRIORITY  copy_IntId);
uint8 MNVIC_u8ClrIntpending(NVIC_HW_PRIORITY  copy_IntId);
uint8 MNVIC_u8SetIntspending(NVIC_HW_PRIORITY copy_IntId[], uint8 copy_u8ArraySize);
uint8 MNVIC_u8ClrIntspending(NVIC_HW_PRIORITY copy_IntId[], uint8 copy_u8ArraySize);
uint8 MNVIC_u8IsIntPending(NVIC_HW_PRIORITY  copy_IntId);
uint8 MNVIC_u8SetPriority(sint8 copy_s8IntId, uint8 copy_u8GroupPriority, uint8 copy_u8SubPriority);

//some additinal functions
uint8 MNVIC_u8EnableInterrupts(uint8 copy_RegId, uint32 copy_RegValue);
uint8 MNVIC_u8DisableInterrupts(uint8 copy_RegId, uint32 copy_RegValue);
uint8 MNVIC_u8SetInterruptspending(uint8 copy_RegId, uint32 copy_RegValue);
uint8 MNVIC_u8ClrInterruptspending(uint8 copy_RegId, uint32 copy_RegValue);






//TODO: UPDATE COMMENT BELOW
#endif /*File_H_*/

/*** End of File **************************************************************/
