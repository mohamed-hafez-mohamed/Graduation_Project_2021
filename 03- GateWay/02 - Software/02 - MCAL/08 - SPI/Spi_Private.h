/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v01                                */
 /* date        : 16/9/2020                          */
/*****************************************************/
#ifndef SPI_PRIVATE_H
#define SPI_PRIVATE_H

/*************** Regsiters defintions **************/
volatile uint32 *SPI[SPI_MAX_CH] = {
	(volatile uint32 *) (0x40013000) ,
	(volatile uint32 *) (0x40003800)
};

/** Offsets **/
#define      CR1          0
#define      CR2          1
#define      SR           2
#define      DR           3
#define      CRCPR        4
#define      RXCRCR       5
#define      TXCRCR       6
#define      I2SCFGR      7
#define      I2SPR        8

/************* Bits difention **************/

/*** CR1 ****/
#define    CPHA       0
#define    CPOL       1
#define    MSTR       2
#define    BR0        3
#define    SPE        6
#define    LSBFIRST   7
#define    SS1        8
#define    SSM        9
#define    RXONLY     10
#define    DFF        11

/*** CR2 ***/
#define    TXEIE      7
#define    RXNEIE     6
#define    ERRIE      5
#define    SSOE       2

/*** SR ***/
#define    RXNE       0
#define    TXE        1
#define    CHSIDE     2
#define    UDR        3
#define    CRCERR     4
#define    MODF       5
#define    OVR        6
#define    BSY        7




#endif
