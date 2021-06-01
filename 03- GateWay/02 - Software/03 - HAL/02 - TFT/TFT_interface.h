/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v01                                */
 /* date        : 21/9/2020                          */
/*****************************************************/
#ifndef TFT_INTERFACE_H
#define TFT_INTERFACE_H


/* Colours */
#define     TFT_BLACK        0x0000
#define     TFT_WHITE        0xffff
#define     TFT_RED          0xf800
#define     TFT_BLUE         0x39df
#define     TFT_YELLOW       0xffc0
#define     TFT_ORANGE       0xfd20
#define     TFT_PURPLE       0xf1df
#define     TFT_GREEN        0x1427


void TFT_voidInit (void);

void TFT_voidDisplayImage(const uint16* copy_uint16Image);

void TFT_voidDrawRectangle (uint16 copy_uint16X ,uint16 copy_uint16Y , uint16 copy_uint16Width , uint16 copy_uint16Hight , uint16 copy_uint16Color );

void TFT_voidFillDisplay (uint16 copy_uint16Colour);

void TFT_voidPrintChar(sint8 copy_sint8Char , uint16 copy_uint16X , uint16 copy_uint16Y, uint8 copy_uint8Size , uint16 copy_uint16Color, uint16 copy_uint16BackColor);

void TFT_voidPrintText(sint8 *copy_sint8Text , uint16 copy_uint16X , uint16 copy_uint16Y, uint8 copy_uint8Size , uint16 copy_uint16Color, uint16 copy_uint16BackColor);

#endif
