/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v01                                */
 /* date        : 9/10/2020                          */
/*****************************************************/
#ifndef FPEC_PRIVATE_H
#define FPEC_PRIVATE_H

/** Register defintions **/
typedef struct {
	volatile uint32 FLASH_ACR ;
	volatile uint32 FLASH_KEYR ;
	volatile uint32 FLASH_OPTKEYR ;
	volatile uint32 FLASH_SR ;
	volatile uint32 FLASH_CR ;
	volatile uint32 FLASH_AR ;
	volatile uint32 RESERVED ;
	volatile uint32 FLASH_OBR ;
	volatile uint32 FLASH_WRPR ;
}FPEC_t ;

#define   FPEC    ((volatile FPEC_t *)0x40022000)

/** Register bits **/

// FLASH_SR 
#define    BSY       0
#define    PGERR     2
#define    WRPRTERR  4
#define    EOP       5

// FLASH_CR
#define    PG        0 
#define    PER       1
#define    MER       2
#define    OPTPG     4
#define    OPTER     5
#define    STRT      6
#define    LOCK      7
#define    OPTWRE    9
#define    ERRIE     10
#define    EOPIE     12

// Lock keys 
#define    FPEC_KEY1    0x45670123
#define    FPEC_KEY2    0xCDEF89AB
#define    RDPRT_key    0x00A5




#endif
