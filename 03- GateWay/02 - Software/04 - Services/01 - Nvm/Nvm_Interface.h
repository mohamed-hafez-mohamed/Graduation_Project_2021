/*****************************************************/
 /* Author      : Mosad                              */
 /* Version     : v01                                */
 /* date        : 29/4/2020                          */
/*****************************************************/
#ifndef NVM_INTERFACE_H
#define NVM_INTERFACE_H


/*************************************************************************
 * Name : Nvm_voidInitVariables
 * Parameter in : -
 * Parameter out : -
 * Parameter in/out : -
 * Reentrancy: Non reentrant
 * Sync
 * Description: Initial the start address for reading and writing
 ***************************************************************************/
void Nvm_voidInitVariables (void);

/*************************************************************************
 * Name : Nvm_voidInit
 * Parameter in : -
 * Parameter out : -
 * Parameter in/out : -
 * Reentrancy: Non reentrant
 * Sync
 * Description: Initial the Module
 ***************************************************************************/
void Nvm_voidInit( void);

/*************************************************************************
 * Name : Nvm_WriteBlock
 * Parameter in : Legnth of data to be written (uint16)
 * Parameter out : -
 * Parameter in/out : Pointer to the buffer to be written (pointer to uint8)
 * Reentrancy: Non reentrant
 * Sync
 * Description: Write a block to the flash (Non volatile memory)
 ***************************************************************************/
Std_ReturnType Nvm_WriteBlock(const uint8 *Cpy_DataPtr , uint16 Cpy_DataLength );

/*************************************************************************
 * Name : Nvm_ReadBlock
 * Parameter in : Legnth of data to be Read (uint16)
 * Parameter out : Pointer to the buffer to be Read (pointer to uint8)
 * Parameter in/out : 
 * Reentrancy: Non reentrant
 * Sync
 * Description: Read a block to the flash (Non volatile memory)
 ***************************************************************************/
Std_ReturnType Nvm_ReadBlock(uint8 *Cpy_DataPtr , uint16 Cpy_DataLength);




#endif
