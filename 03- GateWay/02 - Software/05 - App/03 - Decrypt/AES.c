/***********************************************************/
/**********Author: osama hegazi*****************************/
/**********Date:27/4/2021***********************************/
/***********version:2***************************************/
/***********************************************************/
#include "BIT_MATH.h"
#include "Std_Types.h"
#include "AES_Private.h"
#include "AES_Interface.h"
#include "AES_Cfg.h"

/*************************************************************************************/
                             /*****Functions Definitions********/
/*************************************************************************************/
static uint8 AES_U8GetMul2(uint8 Copy_u8number ) 
{
	
    return (Copy_u8number & RoundConstats[BYTE7] ) ? ((Copy_u8number << ONE) ^ RoundConstats[BYTE8] ) : (Copy_u8number << ONE);
 }
/*****************************************************************END OF FUNCTION**************************************************************************************************************************************************************************************************************************/																                                  
static uint8 AES_uint8MixColoums( uint8 *Copy_u8ciphertext, uint8 *Copy_u8tmptext)
{
	
	/*Local variable , Return = ok*/
 	Std_ReturnType Local_ReturnError = E_OK;
	
	/* Check input pionter */
	if (NULL_PTR == Copy_u8ciphertext  | NULL_PTR == Copy_u8tmptext )
	{
		Local_ReturnError = E_NOT_OK ;
	}
	
uint8 Local_u8elementCounter ;//element counter
uint8 Local_u8tmp1 ;	
	
	for (Local_u8elementCounter = ZERO; Local_u8elementCounter < AES_BLOCK_SIZE; Local_u8elementCounter+=4) 
				{
            Local_u8tmp1 = Copy_u8tmptext[Local_u8elementCounter]  //tmp1 = XOR operation in 4 words of the array
              					 ^ Copy_u8tmptext[Local_u8elementCounter+BYTE1] 
					             ^ Copy_u8tmptext[Local_u8elementCounter+BYTE2] 
					             ^ Copy_u8tmptext[Local_u8elementCounter+BYTE3];
					
            Copy_u8ciphertext[Local_u8elementCounter]   = AES_U8GetMul2(Copy_u8tmptext[Local_u8elementCounter] 
                                               					^ Copy_u8tmptext[Local_u8elementCounter+BYTE1]) 
					                                            ^ Copy_u8tmptext[Local_u8elementCounter]  
                                              					^ Local_u8tmp1;
            Copy_u8ciphertext[Local_u8elementCounter+BYTE1] = AES_U8GetMul2(Copy_u8tmptext[Local_u8elementCounter+BYTE1] 
					                                              ^ Copy_u8tmptext[Local_u8elementCounter+BYTE2])
                                              			          ^ Copy_u8tmptext[Local_u8elementCounter+BYTE1] 
					                                              ^ Local_u8tmp1;
            Copy_u8ciphertext[Local_u8elementCounter+BYTE2] = AES_U8GetMul2(Copy_u8tmptext[Local_u8elementCounter+BYTE2]
                                              					  ^ Copy_u8tmptext[Local_u8elementCounter+BYTE3]) 
					                                              ^ Copy_u8tmptext[Local_u8elementCounter+BYTE2] 
					                                              ^ Local_u8tmp1;
            Copy_u8ciphertext[Local_u8elementCounter+BYTE3] = AES_U8GetMul2(Copy_u8tmptext[Local_u8elementCounter+BYTE3]
                                              					  ^ Copy_u8tmptext[Local_u8elementCounter]  )
                                              					  ^ Copy_u8tmptext[Local_u8elementCounter+BYTE3] 
					                                              ^ Local_u8tmp1;
        }
				
		 return Local_ReturnError ;		
	
 }
/*****************************************************************END OF FUNCTION**************************************************************************************************************************************************************************************************************************/																                                  
static uint8 AES_uint8InvMixColoums( uint8 *Copy_u8plaintext, uint8 *Copy_u8tmptext)
{

	/*Local variable , Return = ok*/
 	Std_ReturnType Local_ReturnError = E_OK;
	
	/* Check input pionter */
	if (NULL_PTR == Copy_u8plaintext  | NULL_PTR == Copy_u8tmptext )
	{
		Local_ReturnError = E_NOT_OK ;
	}
	
uint8  Local_u8elementCounter ; //element counter in the array
uint8	Local_u8tmp1 ;
uint8	Local_u8tmp2 ;
uint8  Local_u8tmp3 ;		
	
 for (Local_u8elementCounter = ZERO; Local_u8elementCounter < AES_BLOCK_SIZE; Local_u8elementCounter+=4) 
	{
            Local_u8tmp1 = Copy_u8tmptext[Local_u8elementCounter]  //tmp1 = XOR operation in 4 words of the array
					               ^ Copy_u8tmptext[Local_u8elementCounter+BYTE1] 
					               ^ Copy_u8tmptext[Local_u8elementCounter+BYTE2] 
					               ^ Copy_u8tmptext[Local_u8elementCounter+BYTE3];
					
            Copy_u8plaintext[Local_u8elementCounter]   = Local_u8tmp1 ^ Copy_u8tmptext[Local_u8elementCounter]
                                              	       ^ AES_U8GetMul2(Copy_u8tmptext[Local_u8elementCounter] 
                                              	       ^ Copy_u8tmptext[Local_u8elementCounter+BYTE1]);
					
            Copy_u8plaintext[Local_u8elementCounter+BYTE1] = Local_u8tmp1 ^ Copy_u8tmptext[Local_u8elementCounter+BYTE1]
                                               	           ^ AES_U8GetMul2(Copy_u8tmptext[Local_u8elementCounter+BYTE1] 
					                                       ^ Copy_u8tmptext[Local_u8elementCounter+BYTE2]);
					
            Copy_u8plaintext[Local_u8elementCounter+BYTE2] = Local_u8tmp1 ^ Copy_u8tmptext[Local_u8elementCounter+BYTE2] 
					                                       ^ AES_U8GetMul2(Copy_u8tmptext[Local_u8elementCounter+BYTE2] 
					                                       ^ Copy_u8tmptext[Local_u8elementCounter+BYTE3]);
					
            Copy_u8plaintext[Local_u8elementCounter+BYTE3] = Local_u8tmp1 ^ Copy_u8tmptext[Local_u8elementCounter+BYTE3] 
					                                       ^ AES_U8GetMul2(Copy_u8tmptext[Local_u8elementCounter+BYTE3]  
					                                       ^ Copy_u8tmptext[Local_u8elementCounter]);
					
            Local_u8tmp2 = AES_U8GetMul2(AES_U8GetMul2(Copy_u8tmptext[Local_u8elementCounter]
              		     ^ Copy_u8tmptext[Local_u8elementCounter+BYTE2]));
					
            Local_u8tmp3 = AES_U8GetMul2(AES_U8GetMul2(Copy_u8tmptext[Local_u8elementCounter+BYTE1] 
						 ^ Copy_u8tmptext[Local_u8elementCounter+BYTE3]));
					
            Local_u8tmp1 = AES_U8GetMul2(Local_u8tmp2 ^ Local_u8tmp3);
					
            Copy_u8plaintext[Local_u8elementCounter] ^= Local_u8tmp1 ^ Local_u8tmp2;
            Copy_u8plaintext[Local_u8elementCounter+BYTE1] ^= Local_u8tmp1 ^ Local_u8tmp3;
            Copy_u8plaintext[Local_u8elementCounter+BYTE2] ^= Local_u8tmp1 ^ Local_u8tmp2;
            Copy_u8plaintext[Local_u8elementCounter+BYTE3] ^= Local_u8tmp1 ^ Local_u8tmp3;
    }
				
		 return Local_ReturnError ;		
		
 } 
/*****************************************************************END OF FUNCTION**************************************************************************************************************************************************************************************************************************/																                                   
static uint8 AES_uint8ShiftRows(uint8 *Copy_u8state)	
{
	
	/*Local variable , Return = ok*/
 	Std_ReturnType Local_ReturnError = E_OK;
	
	/* Check input pionter */
	if (NULL_PTR == Copy_u8state )
	{
		Local_ReturnError = E_NOT_OK ;
	}
/*
    * row 0 is not shifted
	* row 1 is shifted by 1
	* row 2 is shifted by 2
	* row 3 is shifted by 3
*/	
    uint8 Local_u8temp;
    // row1
    Local_u8temp       = *(Copy_u8state+BYTE1);
    *(Copy_u8state+BYTE1)  = *(Copy_u8state+BYTE5);
    *(Copy_u8state+BYTE5)  = *(Copy_u8state+BYTE9);
    *(Copy_u8state+BYTE9)  = *(Copy_u8state+BYTE13);
    *(Copy_u8state+BYTE13) = Local_u8temp;
    // row2
    Local_u8temp       = *(Copy_u8state+BYTE2);
    *(Copy_u8state+BYTE2)  = *(Copy_u8state+BYTE10);
    *(Copy_u8state+BYTE10) = Local_u8temp;
    Local_u8temp       = *(Copy_u8state+BYTE6);
    *(Copy_u8state+BYTE6)  = *(Copy_u8state+BYTE14);
    *(Copy_u8state+BYTE14) = Local_u8temp;
    // row3
    Local_u8temp       = *(Copy_u8state+BYTE15);
    *(Copy_u8state+BYTE15) = *(Copy_u8state+BYTE11);
    *(Copy_u8state+BYTE11) = *(Copy_u8state+BYTE7);
    *(Copy_u8state+BYTE7)  = *(Copy_u8state+BYTE3);
    *(Copy_u8state+BYTE3)  = Local_u8temp;
		
			 return Local_ReturnError ;			
}
/*****************************************************************END OF FUNCTION**************************************************************************************************************************************************************************************************************************/																                                  	
static uint8 AES_uint8InvShiftRows(uint8 *Copy_u8state)
{
	/*Local variable , Return = ok*/
 	Std_ReturnType Local_ReturnError = E_OK;
	
	/* Check input pionter */
	if (NULL_PTR == Copy_u8state )
	{
		Local_ReturnError = E_NOT_OK ;
	}
		
    uint8 Local_u8temp;
    // row1
    Local_u8temp        = *(Copy_u8state+BYTE13);
    *(Copy_u8state+BYTE13) = *(Copy_u8state+BYTE9);
    *(Copy_u8state+BYTE9)  = *(Copy_u8state+BYTE5);
    *(Copy_u8state+BYTE5)  = *(Copy_u8state+BYTE1);
    *(Copy_u8state+BYTE1)  = Local_u8temp;
    // row2
    Local_u8temp        = *(Copy_u8state+BYTE14);
    *(Copy_u8state+BYTE14) = *(Copy_u8state+BYTE6);
    *(Copy_u8state+BYTE6)  = Local_u8temp;
    Local_u8temp        = *(Copy_u8state+BYTE10);
    *(Copy_u8state+BYTE10) = *(Copy_u8state+BYTE2);
    *(Copy_u8state+BYTE2)  = Local_u8temp;
    // row3
    Local_u8temp        = *(Copy_u8state+BYTE3);
    *(Copy_u8state+BYTE3)  = *(Copy_u8state+BYTE7);
    *(Copy_u8state+BYTE7)  = *(Copy_u8state+BYTE11);
    *(Copy_u8state+BYTE11) = *(Copy_u8state+BYTE15);
    *(Copy_u8state+BYTE15) = Local_u8temp;
		
	return Local_ReturnError ;
	
}
/*****************************************************************END OF FUNCTION**************************************************************************************************************************************************************************************************************************/																                                  
uint8 AES_uint8KeyExpansion(const uint8 *Copy_u8Initkey, uint8 *Copy_u8roundkeys) //each round has its unique key 
{	
	
	/*Local variable , Return = ok*/
 	Std_ReturnType Local_ReturnError = E_OK;
	
	/* Check input pionter */
	if (NULL_PTR == Copy_u8Initkey  | NULL_PTR == Copy_u8roundkeys )
	{
		Local_ReturnError = E_NOT_OK ;
	}
    uint8  Local_u8temptext[ONE_WORD]; //The key expansion routine creates round keys word by word
                             // word is an array of four bytes 
    uint8 *Local_u8last4bytesptr;  // pointer to the last 4 bytes of one round
    uint8 *Local_u8lastroundptr;  //pionter to the last round
    uint8  Local_u8roundCounter; //counter of the rounds
    uint8  Local_u8elementCounter; //counter of the rounds

	
    for (Local_u8elementCounter = ZERO; Local_u8elementCounter < AES_BLOCK_SIZE; ++Local_u8elementCounter) 
	{                    //save first round of keys
			
        *Copy_u8roundkeys++ = *Copy_u8Initkey++;
    }

    Local_u8last4bytesptr = Copy_u8roundkeys - ONE_WORD;//piont to last round
		
    for (Local_u8roundCounter = ZERO; Local_u8roundCounter < AES_ROUNDS; ++Local_u8roundCounter) //set other 10 rounds of keys
    {
			
        // k0-k3 for next round
        Local_u8temptext[BYTE3] = SBOX[*Local_u8last4bytesptr++];
        Local_u8temptext[BYTE0] = SBOX[*Local_u8last4bytesptr++];
        Local_u8temptext[BYTE1] = SBOX[*Local_u8last4bytesptr++];
        Local_u8temptext[BYTE2] = SBOX[*Local_u8last4bytesptr++];
        Local_u8temptext[BYTE0] ^= RoundConstats[Local_u8roundCounter]; //XOR operation to add round key
        Local_u8lastroundptr = Copy_u8roundkeys-AES_BLOCK_SIZE;//piont to last round
        *Copy_u8roundkeys++ = Local_u8temptext[BYTE0] ^ *Local_u8lastroundptr++;
        *Copy_u8roundkeys++ = Local_u8temptext[BYTE1] ^ *Local_u8lastroundptr++;
        *Copy_u8roundkeys++ = Local_u8temptext[BYTE2] ^ *Local_u8lastroundptr++;
        *Copy_u8roundkeys++ = Local_u8temptext[BYTE3] ^ *Local_u8lastroundptr++;
        // k4-k7 for next round        
        *Copy_u8roundkeys++ = *Local_u8last4bytesptr++ ^ *Local_u8lastroundptr++;
        *Copy_u8roundkeys++ = *Local_u8last4bytesptr++ ^ *Local_u8lastroundptr++;
        *Copy_u8roundkeys++ = *Local_u8last4bytesptr++ ^ *Local_u8lastroundptr++;
        *Copy_u8roundkeys++ = *Local_u8last4bytesptr++ ^ *Local_u8lastroundptr++;
        // k8-k11 for next round
        *Copy_u8roundkeys++ = *Local_u8last4bytesptr++ ^ *Local_u8lastroundptr++;
        *Copy_u8roundkeys++ = *Local_u8last4bytesptr++ ^ *Local_u8lastroundptr++;
        *Copy_u8roundkeys++ = *Local_u8last4bytesptr++ ^ *Local_u8lastroundptr++;
        *Copy_u8roundkeys++ = *Local_u8last4bytesptr++ ^ *Local_u8lastroundptr++;
        // k12-k15 for next round
        *Copy_u8roundkeys++ = *Local_u8last4bytesptr++ ^ *Local_u8lastroundptr++;
        *Copy_u8roundkeys++ = *Local_u8last4bytesptr++ ^ *Local_u8lastroundptr++;
        *Copy_u8roundkeys++ = *Local_u8last4bytesptr++ ^ *Local_u8lastroundptr++;
        *Copy_u8roundkeys++ = *Local_u8last4bytesptr++ ^ *Local_u8lastroundptr++;
    }
		
		return Local_ReturnError ;	
}
/*****************************************************************END OF FUNCTION**************************************************************************************************************************************************************************************************************************/																                                  
uint8 AES_uint8Encrypt_16Bytes(const uint8 *Copy_u8roundkeys, const uint8 *Copy_u8plaintext, uint8 *Copy_u8ciphertext) 
{
	
	/*Local variable , Return = ok*/
 	Std_ReturnType Local_ReturnError = E_OK;
	
	/* Check input pionter */
	if (NULL_PTR == Copy_u8plaintext  | NULL_PTR == Copy_u8roundkeys | NULL_PTR == Copy_u8ciphertext  )
	{
		Local_ReturnError = E_NOT_OK ;
	}
    uint8 Local_u8tmptext[16] ;
    uint8 Local_u8elementcounter;
    uint8 Local_u8roundcounter	 ;

    // first round we add Roundkeys
    for ( Local_u8elementcounter = ZERO; Local_u8elementcounter < AES_BLOCK_SIZE; ++Local_u8elementcounter )
    {
			
        *(Copy_u8ciphertext+Local_u8elementcounter) = *(Copy_u8plaintext+Local_u8elementcounter)
                                               			^ *(Copy_u8roundkeys++); // XOR operation to add roundkey to each element
    }

    // 9 rounds
    for (Local_u8roundcounter = ONE; Local_u8roundcounter< AES_ROUNDS; ++Local_u8roundcounter)
	{

        // SubBytes step
      for (Local_u8elementcounter = ZERO; Local_u8elementcounter < AES_BLOCK_SIZE; ++Local_u8elementcounter)
	   {
            *(Local_u8tmptext+Local_u8elementcounter) = SBOX[*(Copy_u8ciphertext+Local_u8elementcounter)];//replace each byte of cipher with  depend on the keyround
        }
		     //shift rows step	
       AES_uint8ShiftRows(Local_u8tmptext);
				
	     	//mix coloums step		
	    	AES_uint8MixColoums( Copy_u8ciphertext , Local_u8tmptext );
        
        // AddRoundKey step
        for ( Local_u8elementcounter= ZERO; Local_u8elementcounter < AES_BLOCK_SIZE; ++Local_u8elementcounter )
		{
            *(Copy_u8ciphertext+Local_u8elementcounter) ^= *(Copy_u8roundkeys++);
        }
    }    
		
         // final round this one not contain mix coloums
		
	    	// SubBytes step
        for (Local_u8elementcounter = ZERO; Local_u8elementcounter < AES_BLOCK_SIZE; ++Local_u8elementcounter) 
	    {
           *(Copy_u8ciphertext+Local_u8elementcounter) = SBOX[*(Copy_u8ciphertext+Local_u8elementcounter)]; //replace each byte of cipher with  depend on the keyround
        }
		
	      //shift rows step	
        AES_uint8ShiftRows(Copy_u8ciphertext);
		
		    //add Round key
        for ( Local_u8elementcounter = ZERO; Local_u8elementcounter < AES_BLOCK_SIZE; ++Local_u8elementcounter )
		{
           *(Copy_u8ciphertext+Local_u8elementcounter) ^= *(Copy_u8roundkeys++); // XOR operation to add roundkey to each element
        }

		return Local_ReturnError ;	
		
}
/*****************************************************************END OF FUNCTION**************************************************************************************************************************************************************************************************************************/																                                  
uint8 AES_uint8Decrypt_16Bytes(const uint8 *Copy_u8roundkeys, const uint8 *Copy_u8ciphertext, uint8 *Copy_u8plaintext) 
{

	/*Local variable , Return = ok*/
 	Std_ReturnType Local_ReturnError = E_OK;
	
	/* Check input pionter */
	if (NULL_PTR == Copy_u8plaintext  | NULL_PTR == Copy_u8roundkeys | NULL_PTR == Copy_u8ciphertext  )
	{
		Local_ReturnError = E_NOT_OK ;
	}
    uint8 Local_u8tmptext[AES_BLOCK_SIZE] ;
    uint8 Local_u8elementcounter;
    uint8 Local_u8roundcounter	 ;

    Copy_u8roundkeys += AES_TEN_BLOCK_SIZE;

    // first round
    for ( Local_u8elementcounter = ZERO; Local_u8elementcounter < AES_BLOCK_SIZE; ++Local_u8elementcounter )
  	{
        *(Copy_u8plaintext+Local_u8elementcounter) = *(Copy_u8ciphertext+Local_u8elementcounter)  
			                                       ^ *(Copy_u8roundkeys+Local_u8elementcounter);
    }
    Copy_u8roundkeys -= AES_BLOCK_SIZE;
		
    AES_uint8InvShiftRows(Copy_u8plaintext);
		
    for (Local_u8elementcounter = ZERO; Local_u8elementcounter < AES_BLOCK_SIZE; ++Local_u8elementcounter)
	{
			
        *(Copy_u8plaintext+Local_u8elementcounter) = INV_SBOX[*(Copy_u8plaintext+Local_u8elementcounter)];
    }

    for (Local_u8roundcounter = ONE; Local_u8roundcounter < AES_ROUNDS; ++Local_u8roundcounter)
	{
        
        // Inverse AddRoundKey
        for ( Local_u8elementcounter= ZERO; Local_u8elementcounter < AES_BLOCK_SIZE; ++Local_u8elementcounter)
		{
				
            *(Local_u8tmptext+Local_u8elementcounter) = *(Copy_u8plaintext+Local_u8elementcounter) 
				                                      ^ *(Copy_u8roundkeys+Local_u8elementcounter);
        }

         // inv Mix couloms
       AES_uint8InvMixColoums( Copy_u8plaintext , Local_u8tmptext );
        
        // Inverse ShiftRows
        AES_uint8InvShiftRows(Copy_u8plaintext);
        
        // Inverse SubBytes
        for (Local_u8elementcounter = ZERO; Local_u8elementcounter < AES_BLOCK_SIZE; ++Local_u8elementcounter)
		{
            *(Copy_u8plaintext+Local_u8elementcounter) = INV_SBOX[*(Copy_u8plaintext+Local_u8elementcounter)];
        }

        Copy_u8roundkeys -= AES_BLOCK_SIZE;

    }

    // last AddRoundKey
    for ( Local_u8elementcounter = ZERO; Local_u8elementcounter < AES_BLOCK_SIZE; ++Local_u8elementcounter ) 
    {
        *(Copy_u8plaintext+Local_u8elementcounter) ^= *(Copy_u8roundkeys+Local_u8elementcounter);
    }
		
		return Local_ReturnError ;	
		
}
/*****************************************************************END OF FUNCTION**************************************************************************************************************************************************************************************************************************/																                                  
Std_ReturnType AES_uint8Decrypt_Buffer ( const uint8 *Copy_u8roundkeys , const uint8 *Copy_u8CipherText_Buffer , const uint8 *Copy_u8PlainText_Buffer , uint8 Copy_uint8DataLenght)
{
	
	/*Local variable , Return = ok*/
 	Std_ReturnType Local_ReturnError = E_OK;
	
	/* Check input pionter */
	if (NULL_PTR == Copy_u8PlainText_Buffer  | NULL_PTR == Copy_u8roundkeys | NULL_PTR == Copy_u8CipherText_Buffer  )
	{
		Local_ReturnError = E_NOT_OK ;
		return Local_ReturnError ;
	}
	uint8 *Local_uint8CipherTextPtr =  Copy_u8CipherText_Buffer   ;
	uint8 *Local_uint8PlainTextPtr  =  Copy_u8PlainText_Buffer    ;
	uint8  Local_uint8RoundsNumber  = (Copy_uint8DataLenght / 16) ;

	 for (uint8 Round_Counter = 0; Round_Counter < Local_uint8RoundsNumber ; Round_Counter++) // fetch 16 byte == one record and fill message1 array
    {
	 
 	          AES_uint8Decrypt_16Bytes ( Copy_u8roundkeys  , Local_uint8CipherTextPtr  , Local_uint8PlainTextPtr) ; //get 16 byte of plain text
	          Local_uint8CipherTextPtr += FOUR_WORDS ;
	          Local_uint8PlainTextPtr  += FOUR_WORDS ;	
    }
		
			return Local_ReturnError ;	

 }
/*****************************************************************END OF FUNCTION**************************************************************************************************************************************************************************************************************************/																                                  
Std_ReturnType AES_uint8Encrypt_Buffer ( const uint8 *Copy_u8roundkeys , const uint8 *Copy_u8PlainText_Buffer , const uint8 *Copy_u8CipherText_Buffer , uint8 Copy_uint8DataLenght)
{

	/*Local variable , Return = ok*/
 	Std_ReturnType Local_ReturnError = E_OK;
	
	/* Check input pionter */
	if (NULL_PTR == Copy_u8PlainText_Buffer  | NULL_PTR == Copy_u8roundkeys | NULL_PTR == Copy_u8CipherText_Buffer  )
	{
		Local_ReturnError = E_NOT_OK ;
				return Local_ReturnError ;
	}
	
	uint8 *Local_uint8PlainTextPtr  =  Copy_u8PlainText_Buffer       ;
	uint8 *Local_uint8CipherTextPtr =  Copy_u8CipherText_Buffer      ;
	uint8  Local_uint8RoundsNumber  = (Copy_uint8DataLenght / 16) ;

	 for (uint8 Round_Counter = 0; Round_Counter < Local_uint8RoundsNumber ; Round_Counter++) // fetch 16 byte == one record and fill message1 array
        {
	 
 	          AES_uint8Encrypt_16Bytes ( Copy_u8roundkeys  , Local_uint8PlainTextPtr  , Local_uint8CipherTextPtr) ; //get 16 byte of plain text
	          Local_uint8CipherTextPtr += FOUR_WORDS ;
	          Local_uint8PlainTextPtr  += FOUR_WORDS ;
	
        }
		
	 	return Local_ReturnError ;	
}

/*****************************************************************END OF FUNCTION**************************************************************************************************************************************************************************************************************************/																                                  