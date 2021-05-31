/*****************************************************/
 /* Author      : Mosad                              */
 /* Version     : v01                                */
 /* date        : 10/9/2020                          */
/*****************************************************/
#ifndef TMR_PRIVATE_H
#define TMR_PRIVATE_H


/* Array of the base address of each timer  */
volatile uint32 *TIM [TMR_NUMBER] =
{ (uint32*)(0x40012C00) ,
  (uint32*)(0x40000000) ,
  (uint32*)(0x40000400) ,
  (uint32*)(0x40000800)
};

/* Offset of each rigester */
#define    CR1      0
#define    CR2      1
#define    SMCR     2
#define    DIER     3
#define    SR       4
#define    EGR      5
#define    CCMR1    6
#define    CCMR2    7
#define    CCER     8
#define    CNT      9
#define    PSC      10
#define    ARR      11
#define    RCR      12
#define    CCR1     13
#define    CCR2     14
#define    CCR3     15
#define    CCR4     16
#define    BDTR     17
#define    DCR      18
#define    DMAR     19

/* Macros */
#define     MAX_INTERVAL    65536

#endif
