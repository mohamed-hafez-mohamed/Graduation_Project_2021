/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v01                                */
 /* date        : 9/10/2020                          */
/*****************************************************/

		
#ifndef FPEC_INTERFACE_H
#define FPEC_INTERFACE_H

#define    WRITE_DONE    1
#define    WRITE_ERROR   0


/* 
  * FPEC_u8WriteHalfWord - > write half word at specific location
  * I/P : (u32) the address , (u16) data 
  * O/P : u8 (Error state)
*/
uint8 FPEC_u8WriteHalfWord( uint32 copy_u32Address, uint16 copy_u16Data);

/* 
  * FPEC_voidErasePage - > Erase a page 
  * I/P : (u32) the address  
*/
void FPEC_voidErasePage( uint32 copy_u32Address );

/* 
  * FPEC_voidErasePage - > Erase a the whole user pages  
*/
void FPEC_voidMassErase(void);





#endif
