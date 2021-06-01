/****************************************************************************
* Title                 :   FPEC   
* Filename              :   FPEC_private.h
* Author                :   Mohamed Hafez
* Origin Date           :   13/10/2020
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
*  13/10/20   1.0.0   Mohamed Hafez   Interface Created.
*
*****************************************************************************/
/** @file  FPEC_private.h
 *  @brief This module TODO: WHAT DO I DO?
 * 
 *  This is the header file for the definition TODO: MORE ABOUT ME!
 */
//TODO: UPDATE MACRO BELOW
#ifndef FPEC_PRIVATE_H_
#define FPEC_PRIVATE_H_

/******************************************************************************
* Includes
*******************************************************************************/

/******************************************************************************
* Typedefs
*******************************************************************************/
/**
* Defines eight variables which specify the FPEC registers.
*/
typedef struct 
{
    volatile u32 ACR;
    volatile u32 KEYR;       /**<Key register */
    volatile u32 OPTKEYR;
    volatile u32 SR;         /**<Status register */
    volatile u32 CR;         /**<Control register */
    volatile u32 AR;         /**<Page address regiter */
    volatile u32 OBR;
    volatile u32 WRPR;
}FPEC_t;
/******************************************************************************
* Preprocessor Constants
*******************************************************************************/
#define FPEC_BASE_ADDRESS     0x40022000
// Some auxilary constants.
// Some auxilary constants.
#define SET                        1
#define CLEAR                      0
#define FPEC_CATCH_LEAST_HALF_WORD 0x0000FFFF
#define FPEC_CATCH_MOST_HALF_WORD  0xFFFF0000
#define CLR_REGISTER               0x00000080
#define FLASH_START_ADDRESS        0x08000000
#define FPEC_RDPRT                 0x00A5
#define FPEC_KEY_1                 0x45670123
#define FPEC_KEY_2                 0xCDEF89AB
#define PAGE_SIZE                  1024
#define TWO_BYTE                   2
#define ONE_WORD_SIZE              4
#define TWO_BYTES_IN_BITS          16
/******************************************************************************
* Configuration Constants
*******************************************************************************/
#define FPEC                  ((volatile FPEC_t * const)(FPEC_BASE_ADDRESS))
// Register bits definition.

// ACR register bits defniton.
#define LATENCY         0
#define HLFCYA          3
#define PRFTBE          4
#define PRFTBS          5
//SR register bits defniton.
#define BSY             0 
#define PGERR           2
#define WRPRTERR        4
#define EOP             5
//CR register bits defniton.
#define PG              0
#define PER             1
#define MER             2
#define OPTPG           4
#define OPTER           5
#define STRT            6
#define LOCK            7
#define OPTWRE          9
#define ERRIE           10
#define EOPIE           12
/******************************************************************************
* Module Variable Definitions
*******************************************************************************/

/******************************************************************************
* Function Prototypes
*******************************************************************************/

#endif
/*** End of File **************************************************************/
