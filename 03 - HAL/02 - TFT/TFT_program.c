/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v01                                */
 /* date        : 21/9/2020                          */
/*****************************************************/

/* Library includes */
#include "BIT_MATH.h"
#include "Std_Types.h"

/* MCAL includes */
#include "GPIO_interface.h"
#include "Spi_Interface.h"
#include "STK_interface.h"

/* module includes */
#include "TFT_interface.h"
#include "TFT_config.h"
#include "TFT_private.h"

void TFT_voidInit (void){
	
	/* Reset pulse */
	GPIO_VoidSetPinValue (TFT_RST_PIN , GPIO_HIGH);
	STK_voidSetBusyWait(100 , TIME_US);
	GPIO_VoidSetPinValue (TFT_RST_PIN , GPIO_LOW);
	STK_voidSetBusyWait(2 , TIME_US);
	GPIO_VoidSetPinValue (TFT_RST_PIN , GPIO_HIGH);
	STK_voidSetBusyWait(100 , TIME_US);
	GPIO_VoidSetPinValue (TFT_RST_PIN , GPIO_LOW);
	STK_voidSetBusyWait(100 , TIME_US);
	GPIO_VoidSetPinValue (TFT_RST_PIN , GPIO_HIGH);
	STK_voidSetBusyWait(120 , TIME_MS);
	
	/* Sleep out */
	voidWriteCommand(0x11);
	
	/* Wait 150 ms */
	STK_voidSetBusyWait(150 , TIME_MS);
	
	/* Colour mode command */
	voidWriteCommand(0x3A);
	voidWriteData(0x05);
	
	/* Display on */
	voidWriteCommand(0x29);

}

void TFT_voidDisplayImage(const uint16* copy_uint16Image){

	/* Set address range for the whole display */
	voidSetAddress(0  , TFT_MAX_X , 0 , TFT_MAX_Y);

	uint16 local_uint16Counter ;
	for (local_uint16Counter = 0 ; local_uint16Counter < (TFT_MAX_X * TFT_MAX_Y); local_uint16Counter++){
		voidSetColour(copy_uint16Image[local_uint16Counter]);
	}
}

void TFT_voidDrawRectangle (uint16 copy_uint16X ,uint16 copy_uint16Y , uint16 copy_uint16Width , uint16 copy_uint16GPIO_HIGHt , uint16 copy_uint16Color ){
	uint16 loacal_uint16EndX = copy_uint16X + copy_uint16Width - 1;
	uint16 loacal_uint16EndY = copy_uint16Y + copy_uint16GPIO_HIGHt - 1;

	/* Set area of addresses */
	voidSetAddress(copy_uint16X ,loacal_uint16EndX,copy_uint16Y ,loacal_uint16EndY );

	/* Draw the Rectangle*/
	for (uint16 i = 0 ; i < (copy_uint16Width *copy_uint16GPIO_HIGHt ) ; i++){
		voidSetColour(copy_uint16Color);
	}
}


void TFT_voidFillDisplay (uint16 copy_uint16Colour){
	TFT_voidDrawRectangle(0 , 0 ,TFT_MAX_X , TFT_MAX_Y , copy_uint16Colour);
}

void TFT_voidPrintChar(sint8 copy_sint8Char , uint16 copy_uint16X , uint16 copy_uint16Y, uint8 copy_uint8Size , uint16 copy_uint16Color , uint16 copy_uint16BackColor)
{
	/* Get array index */
	uint8 local_uint8CharIndex = 0 ;
	if (( copy_sint8Char >= ' ' )){
		local_uint8CharIndex = copy_sint8Char - 32 ;
	}

	/* Background */
	TFT_voidDrawRectangle( copy_uint16X, copy_uint16Y ,copy_uint8Size*TFT_CHARACTER_WIDTH ,copy_uint8Size*TFT_CHARACTER_HIGHT ,copy_uint16BackColor);

	for (uint8 i = 0; i <TFT_CHARACTER_WIDTH ; i++ ){
		for (uint8 j = 0 ; j <TFT_CHARACTER_HIGHT ; j++){
			if (TFT_font[local_uint8CharIndex][i] & (1 << j)){
				if (copy_uint8Size == 1){
					voidDrawPixel(copy_uint16X+i , copy_uint16Y+j , copy_uint16Color);
				}
				else {
					uint16 local_x = copy_uint16X+(i*copy_uint8Size) ;
					uint16 local_y = copy_uint16Y+(j*copy_uint8Size) ;
					TFT_voidDrawRectangle( local_x, local_y ,copy_uint8Size ,copy_uint8Size ,copy_uint16Color);
				}
			}
		}
	}
}

void TFT_voidPrintText(sint8 *copy_sint8Text , uint16 copy_uint16X , uint16 copy_uint16Y, uint8 copy_uint8Size , uint16 copy_uint16Color, uint16 copy_uint16BackColor)
{
	while (*copy_sint8Text){
		TFT_voidPrintChar(*copy_sint8Text , copy_uint16X ,copy_uint16Y ,copy_uint8Size ,copy_uint16Color,copy_uint16BackColor );
		copy_uint16X += (copy_uint8Size *TFT_CHARACTER_WIDTH)  ;
		copy_sint8Text++;
	}
}

static void voidWriteCommand (uint8 copy_uint8Command){
	/* Set A0 GPIO_LOW */
	GPIO_VoidSetPinValue (TFT_A0_PIN , GPIO_LOW);
	/* Activate TFT slave */
	GPIO_VoidSetPinValue (TFT_SLAVE_PIN , GPIO_LOW);
	/* Send command */
	SPI_uint16SendRecSynch(SPI1 , copy_uint8Command );
	/* Deactivate TFT slave */
	GPIO_VoidSetPinValue (TFT_SLAVE_PIN , GPIO_HIGH);
}

static void voidWriteData (uint8 copy_uint8Data){
	/* Set A0 GPIO_HIGH */
	GPIO_VoidSetPinValue (TFT_A0_PIN , GPIO_HIGH);
	/* Activate TFT slave */
	GPIO_VoidSetPinValue (TFT_SLAVE_PIN , GPIO_LOW);
	/* Send Data */
	SPI_uint16SendRecSynch(SPI1 ,copy_uint8Data );
	/* Deactivate TFT slave */
	GPIO_VoidSetPinValue (TFT_SLAVE_PIN , GPIO_HIGH);
}

static void voidDrawPixel (uint16 copy_uint16X , uint16 copy_uint16Y , uint16 copy_uint16Colour)
{
	if ( (copy_uint16X < TFT_MAX_X ) && (copy_uint16Y < TFT_MAX_Y )){

		/* Set address of the pixel */
		voidSetAddress(copy_uint16X  , copy_uint16X+1 , copy_uint16Y , copy_uint16Y+1);

		/* Write pixel colour */
		voidSetColour(copy_uint16Colour);
	}
}

static void voidSetAddress (uint16 copy_uint16StartX ,uint16 copy_uint16EndX , uint16 copy_uint16StartY , uint16 copy_uint16EndY)
{
	if ( (copy_uint16StartX < TFT_MAX_X ) && (copy_uint16StartY < TFT_MAX_Y )){
		/* Set x Address */
		voidWriteCommand(0x2A);
		/* Start byte */
		voidWriteData((copy_uint16StartX >> SHIFT_BY_8));  // MS byte
		voidWriteData(copy_uint16StartX);

		/* Stop byte */
		voidWriteData((copy_uint16EndX >> SHIFT_BY_8));
		voidWriteData(copy_uint16EndX);

		/* Set x Address */
		voidWriteCommand(0x2B);
		/* Start byte */
		voidWriteData((copy_uint16StartY >> SHIFT_BY_8));  // MS byte
		voidWriteData(copy_uint16StartY);
		/* Stop byte */
		voidWriteData((copy_uint16EndY >> SHIFT_BY_8));
		voidWriteData(copy_uint16EndY);

		/* RAM write */
		voidWriteCommand(0x2C);
	}
}

static void voidSetColour(uint16 copy_uint16Colour)
{

	/* Write pixel */
	uint8 GPIO_HIGH_byte = (copy_uint16Colour >> 8);
	uint8 GPIO_LOW_byte = (copy_uint16Colour & 0xff);
	voidWriteData(GPIO_HIGH_byte);
	voidWriteData(GPIO_LOW_byte);
}


