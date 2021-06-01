/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v01                                */
 /* date        : 14/9/2020                          */
/*****************************************************/
#include "Std_Types.h"
#include "Spi_Lcfg.h"

/* Spi channel 1 */
SpiCfgType Spi1_config =
		{ SPI_MASTER_MODE   ,
   		  SPI_IDLE_HIGH     , 
		  SPI_READ_FIRST    ,
		  SPI_MSB_FIRST     ,
		  SPI_8BIT_FRAME    , 
		  SPI_SW_MANG_SLAVE ,
		  SPI_FULL_DUPLEX   ,
		  PRESCALLER_2      ,
		  SPI_INTERRUPT_DISABLE };
		  
/* Spi channel 2 */
SpiCfgType Spi2_config =
		{ SPI_MASTER_MODE   ,
   		  SPI_IDLE_HIGH     , 
		  SPI_READ_FIRST    ,
		  SPI_MSB_FIRST     ,
		  SPI_8BIT_FRAME    , 
		  SPI_SW_MANG_SLAVE ,
		  SPI_FULL_DUPLEX   ,
		  PRESCALLER_2      ,
		  SPI_INTERRUPT_DISABLE };