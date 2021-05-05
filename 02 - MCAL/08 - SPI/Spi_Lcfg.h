/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v01                                */
 /* date        : 14/9/2020                          */
/*****************************************************/
#ifndef SPI_LCFG_H
#define SPI_LCFG_H

/********************************** Data Types ***********************/
/************************************* 
* Name  : SpiModeType
* Type  : uint8
* Range : SPI_MASTER_MODE 
		  SPI_SLAVE_MODE
************************************/
typedef uint8 SpiModeType ; 

/* Values */
#define  SPI_MASTER_MODE  0x01u
#define  SPI_SLAVE_MODE   0x00u

/****** CPOL data type ******/
typedef uint8 SpiCpolType ; 
/* Values */
#define  SPI_IDLE_HIGH  0x01u
#define  SPI_IDLE_LOW   0x00u

/****** CPHA data type ******/
typedef uint8 SpiCphaType ; 
/* Values */
#define  SPI_READ_FIRST    0x01u
#define  SPI_WRITE_FIRST   0x00u

/****** Frame format data type ******/
typedef uint8 SpiFrameFormatType ; 
/* Values */
#define  SPI_LSB_FIRST    0x01u
#define  SPI_MSB_FIRST    0x00u

/****** Frame size data type ******/
typedef uint8 SpiFrameSizeType ; 
/* Values */
#define  SPI_16BIT_FRAME    0x01u
#define  SPI_8BIT_FRAME     0x00u

/****** slave mangement data type ******/
typedef uint8 SpiSlaveMangType ; 
/* Values */
#define  SPI_SW_MANG_SLAVE    0x01u
#define  SPI_HW_MANG_SLAVE     0x00u

/****** Transmision mode data type ******/
typedef uint8 SpiTxModeType ; 
/* Values */
#define  SPI_RECEIVE_ONLY    0x01u
#define  SPI_FULL_DUPLEX     0x00u

/****** Pre scaller data type ******/
typedef uint8 SpiPreScallerType ; 
/* Values */
#define  PRESCALLER_2    0x00u
#define  PRESCALLER_4    0x01u
#define  PRESCALLER_8    0x02u
#define  PRESCALLER_16   0x03u
#define  PRESCALLER_32   0x04u
#define  PRESCALLER_64   0x05u
#define  PRESCALLER_128  0x06u
#define  PRESCALLER_256  0x07u

/****** Interrupt state data type ******/
typedef uint8 SpiInterruptStateType ; 
/* Values */
#define  SPI_INTERRUPT_ENABLE      0x01u
#define  SPI_INTERRUPT_DISABLE     0x00u

/*** Configuration parameters ***/
typedef struct {
	SpiModeType  uint8Mode;
	SpiCpolType  uint8CPOL ;
	SpiCphaType  uint8CPHA ;
	SpiFrameFormatType  uint8FrameFormat ;
	SpiFrameSizeType  uint8FrameSize   ;
	SpiSlaveMangType  uint8SSM ;
	SpiTxModeType  uint8TransmissonMode ;
	SpiPreScallerType  uint8Prescaler;
	SpiInterruptStateType uint8InterruptEnable ;
}SpiCfgType;

/* Global Variables */
extern SpiCfgType Spi1_config ;
extern SpiCfgType Spi2_config ;



#endif