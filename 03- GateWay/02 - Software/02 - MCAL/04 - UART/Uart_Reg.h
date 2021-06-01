/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v01                                */
 /* date        : 20/9/2020                          */
/*****************************************************/
#ifndef UART_PRIVATE_H
#define UART_PRIVATE_H

/*************** Regsiters defintions **************/
volatile uint32 *UART[UART_MAX_CH] = {
	(volatile uint32 *) (0x40013800) ,    //APB2
	(volatile uint32 *) (0x40004400) ,    //APB1
	(volatile uint32 *) (0x40004800)      //APB1
};

/*** Registers offsets ***/
#define      SR       0
#define      DR       1
#define      BBR      2
#define      CR1      3
#define      CR2      4
#define      CR3      5
#define      GTPR     6


/************ Registers bits defintion ***************/

/** CR1 **/
#define    SBK      0
#define    RWU      1
#define    RE       2
#define    TE       3
#define    IDLEIE   4
#define    RXNEIE   5
#define    TCIE     6
#define    TXEIE    7
#define    PEIE     8
#define    PS       9
#define    PCE      10
#define    WAKE     11
#define    M        12
#define    UE       13

/** CR2 **/
#define    ADD0     0
#define    LBDL     5
#define    LBCL     8
#define    CPHA     9
#define    CPOL     10
#define    CLKEN    11
#define    STOP     12
#define    LINEN    13

/** CR3 **/
          
#define    EIE     0
#define    IREN    1
#define    IRLP    2
#define    HDSEL   3
#define    NACK    4
#define    SCEN    5
#define    DMAR    6
#define    DMAT    7
#define    RTSE    8
#define    CTSE    9
#define    CTSIE   10


/** SR **/ 
#define   PE       0
#define   FE       1
#define   OREE     2
#define   NE       3
#define   IDLE     4
#define   RXNE     5
#define   TC       6
#define   TXE      7
#define   LDB      8
#define   CTS      9


/****/






#endif
