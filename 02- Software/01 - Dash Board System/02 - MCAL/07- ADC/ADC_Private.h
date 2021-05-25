/****************************************************************************
* Title                 :   ADC   
* Filename              :   ADC_private.h
* Author                :   Mohamed Hafez
* Origin Date           :   3/10/2020
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
*  03/10/20   1.0.0   Mohamed Hafez   Interface Created.
*
*****************************************************************************/
/** @file  ADC_private.h
 *  @brief This module TODO: WHAT DO I DO?
 * 
 *  This is the header file for the definition TODO: MORE ABOUT ME!
 */
//TODO: UPDATE MACRO BELOW
#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_

/******************************************************************************
* Includes
*******************************************************************************/
#include "Std_Types.h"
/******************************************************************************
* Typedefs
*******************************************************************************/
typedef struct 
{
    volatile uint32 SR;
    volatile uint32 CR1;
    volatile uint32 CR2;
    volatile uint32 SMPR1;
    volatile uint32 SMPR2;
    volatile uint32 JOFR1;
    volatile uint32 JOFR2;
    volatile uint32 JOFR3;
    volatile uint32 JOFR4;
    volatile uint32 HTR;
    volatile uint32 LTR;
    volatile uint32 SQR1;
    volatile uint32 SQR2;
    volatile uint32 SQR3;
    volatile uint32 JSQR;
    volatile uint32 JDR1;
    volatile uint32 JDR2;
    volatile uint32 JDR3;
    volatile uint32 JDR4;
    volatile uint32 DR;
}ADC_t;

/******************************************************************************
* Preprocessor Constants
*******************************************************************************/
//ADC Base Address
#define ADC_1_BASE_ADDRESS         0x40012400
#define ADC_2_BASE_ADDRESS         0x40012800
//////////////////////
#define FLAG_NOT_SET               0
#define FLAG_SET                   1
#define SET                        1
#define CLR_REGISTER               0X00000000
#define GET_RIGHT_ALIGNED_DATA     0x0FFF
#define ADC_NUMBER_OF_CHANNELS     2
#define START_OF_SMPR1             10
#define END_OF_SMPR1               17
#define START_OF_SMPR2             0
#define END_OF_SMPR2               9
#define ADJUST_CHANNEL             10
#define OFFSET                     3
#define START_OF_SQR1              13
#define END_OF_SQR1                16
#define START_OF_SQR2              7
#define END_OF_SQR2                12
#define START_OF_SQR3              1
#define END_OF_SQR3                6
#define ADJUST_CHANNEL_BITS_SQR    5
#define ADJUST_CHANNEL_BITS_SMPR   3
/******************************************************************************
* Configuration Constants
*******************************************************************************/
//SR Register
#define EOC       1
#define STRT      4
//CR1 Register
#define EOCIE     5
#define SCAN      8
#define DISCEN    11
#define DISCNUM0  13
//CR2 Register 
#define ADON     0
#define CONT     1
#define CAL      2
#define RSTCAL   3
#define DMA      8
#define ALIGN    11
#define EXTSEL   17
#define EXTTRIG  20
#define SWSTART  22

// SMPR2 Register
#define SMP0     0
#define SMP1     3
#define SMP2     6
#define SMP3     9
#define SMP4     12
#define SMP5     15
#define SMP6     18
#define SMP7     21
#define SMP8     24
#define SMP9     27
// SMPR1 Register
#define SMP10    0
#define SMP11    3
#define SMP12    6
#define SMP13    9
#define SMP14    12
#define SMP15    15
#define SMP16    18
#define SMP17    21

// SQR3 Register
#define SQ1      0
#define SQ2      5
#define SQ3      10
#define SQ4      15
#define SQ5      20
#define SQ6      25
// SQR2 Register
#define SQ7      0
#define SQ8      5
#define SQ9      10
#define SQ10     15
#define SQ11     20
#define SQ12     25
// SQR1 Register 
#define SQ13     0
#define SQ14     5
#define SQ15     10
#define SQ16     15
#define L0       20
/******************************************************************************
* Module Variable Definitions
*******************************************************************************/
static volatile ADC_t * const AdcChannel[ADC_NUMBER_OF_CHANNELS] = 
{
    ((volatile  ADC_t * const)(ADC_1_BASE_ADDRESS)),
    ((volatile  ADC_t * const)(ADC_2_BASE_ADDRESS))
};
/******************************************************************************
* Function Prototypes
*******************************************************************************/

#endif
/*** End of File **************************************************************/
