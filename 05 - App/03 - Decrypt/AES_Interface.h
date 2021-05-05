/***********************************************************/
/**********Author: osama hegazi*****************************/
/**********Date:27/4/2021***********************************/
/***********version:2***************************************/
/***********************************************************/
#ifndef AES_INTERFACE_H
#define AES_INTERFACE_H

/***********************************************************************************************************************************************************************************************************************************************************
                                              *******Common Macros******
***********************************************************************************************************************************************************************************************************************************************************/																			
#define  ONE          1
#define  ZERO         0
#define  ONE_WORD     4
#define  FOUR_ROUNDS  4
#define  FOUR_WORDS   16

enum ARRAY_INDEX
{
	
BYTE0, 
BYTE1,
BYTE2,
BYTE3,
BYTE4,
BYTE5,
BYTE6,
BYTE7,
BYTE8,
BYTE9,
BYTE10,
BYTE11,
BYTE12,
BYTE13,
BYTE14,
BYTE15
	
};

/***********************************************************************************/
                      /***FUNCTIONS PROTOTYPES***/
/************************************************************************************

*Name       :   Aes_VoidGetRoundkeys

*Description: * Function to Get Rounds keys (key schedule) (176 bytes)              
							
*Pre-Cond   :	None				
							
*pos-Cond   : None

*Input      : Block(16 bytes) represent the key

*Output     : void

*Return     : void

****************************************************************************************/
uint8 AES_uint8KeyExpansion(const uint8 *Copy_u8userkey, uint8 *Copy_roundkeys) ;
/************************************************************************************

*Name       :   Aes_VoidEncrypt_16Bytes

*Description: * Function to encrypt one block(16 bytes) using key Rounds               
							
*Pre-Cond   :	Roundkeys is get				
							
*pos-Cond   : None

*Input      : Block(16 bytes) of plain text and 176 bytes of roundskeys

*Output     : one block(16bytes) of cipher text

*Return     : void

****************************************************************************************/
uint8 AES_uint8Encrypt_16Bytes(const uint8 *Copy_u8roundkeys, const uint8 *Copy_u8plaintext, uint8 *Copy_u8ciphertext) ;
/************************************************************************************

*Name       :   Aes_VoidDecrypt_16Bytes

*Description: * Function to decrypt one block(16 bytes) using key Rounds               
							
*Pre-Cond   :	Roundkeys is get 				
							
*pos-Cond   : None

*Input      : Block(16 bytes) of cipher text and 176 bytes of roundskeys

*Output     : one block(16bytes) of plain text

*Return     : void

****************************************************************************************/
uint8 AES_uint8Decrypt_16Bytes(const uint8 *Copy_u8roundkeys, const uint8 *Copy_u8ciphertext, uint8 *Copy_u8plaintext) ;
/************************************************************************************

*Name       :   AES_VoidEncrypt_64Byte

*Description: * Function to dencrypt 4 blocks(64 bytes) using key Rounds               
							
*Pre-Cond   :	Roundkeys is get 				
							
*pos-Cond   : None

*Input      : array(64 bytes) of cipher text and 176 bytes of roundskeys

*Output     : one array(64bytes) of plain text

*Return     : void

****************************************************************************************/
uint8 AES_uint8Encrypt_Buffer ( const uint8 *Copy_u8roundkeys , const uint8 *Copy_u8PlainText_Buffer , const uint8 *Copy_u8CipherText_Buffer , uint8 Copy_uint8DataLenght);
/************************************************************************************

*Name       :   Aes_VoidDecrypt_4Bytes

*Description: * Function to decrypt 4 blocks(64 bytes) using key Rounds               
							
*Pre-Cond   :	Roundkeys is get 				
							
*pos-Cond   : None

*Input      : array (64 bytes) of cipher text and 176 bytes of roundskeys

*Output     : array(64bytes) of plain text

*Return     : void

****************************************************************************************/
uint8 AES_uint8Decrypt_Buffer ( const uint8 *Copy_u8roundkeys , const uint8 *Copy_u8CipherText_Buffer , const uint8 *Copy_u8PlainText_Buffer , uint8 Copy_uint8DataLenght);



#endif
