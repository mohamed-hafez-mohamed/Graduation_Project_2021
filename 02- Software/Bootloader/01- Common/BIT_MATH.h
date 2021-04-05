/****************************************************************************
* Title                 :   BIT_MATH   
* Filename              :   BIT_MATH .h
* Author                :   Mohamed Hafez
* Origin Date           :   29/7/2020
* Version               :   1.0.0
* Compiler              :   TODO: COMPILER GOES HERE
* Target                :   TODO: MCU GOES HERE
* Notes                 :   None
*
*****************************************************************************/

#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#include "STD_TYPES.h"
#define ACCESS_REG_8BIT(REG)         (*(volatile u8  * )REG)

#define ACCESS_REG_16BIT(REG)        (*(volatile u16 * )REG)

#define ACCESS_REG_32BIT(REG)        (*(volatile u32 * )REG)

#define SET_BIT(REG,BIT_NUM)		 ((REG)  |=  (1   << BIT_NUM))
 
#define CLR_BIT(REG,BIT_NUM)         ((REG)  &= ~(1   << BIT_NUM))

#define GET_BIT(REG,BIT_NUM)         ((REG >> BIT_NUM) & (1))

#define TOG_BIT(REG,BIT_NUM)  	     ((REG)   ^= (1 << BIT_NUM))

#define IS_BIT_SET(REG,BIT_NUM)      ((REG)   &  (1 << BIT_NUM))

#define IS_BIT_CLEAR(REG,BIT_NUM)    (!(IS_BIT_SET(REG,BIT_NUM)))

#endif
