/*******************************************************************************
**  FILENAME     : Decyrpt_Interface.h         			                          **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2021-05-03                                                 **
**                                                                            **                                                                            **
**  AUTHOR       : osamahijazi	                                              **
**
**                                                                            **
*******************************************************************************/

/* Define to prevent recursive inclusion */

#ifndef DECRYPT_INTERFACE_H
#define DECRYPT_INTERFACE_H

/*****************************************************************************************/
/*                                   Include headres                                     */
/*****************************************************************************************/

/************************************************************************************

*Name       :   Decrypt_MainFunction

*Description: * read decryoted data from rom 64 byte in each round
              * deecrypt this buffer by AES module to plain Data
              * privide Decrypt bufffer to sender receiver API in Rte 
                 
							
*Pre-Cond   :  buffer flag is not set & sys flag is assign to decrypt 				
							
*pos-Cond   :  buffer flag is set & sys flag is assign to send 

*Input      :   void

*Output     :   void

*Return     :   void

****************************************************************************************/                                   	

void Decrypt_MainFunction (void) ;



#endif
/******************************************END OF FILE************************************/
