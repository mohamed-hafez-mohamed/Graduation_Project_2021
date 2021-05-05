/*******************************************************************************
**  FILENAME     : Decyrpt.C            			                          **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2021-05-03                                                 **
**                                                                            **
**  AUTHOR       : osamahijazi	                                              **
*******************************************************************************/
/* Library includes */
#include "BIT_MATH.h"
#include "Std_Types.h"
#include "AES_Interface.h"
/* Module includes */
#include "Decrypt_Interface.h"
#include "Decrypt_Cfg.h"
#include "Decrypt_Private.h"
#include "Rte_DecryptPort.h"
/* Other Modules */
#include "Nvm_Interface.h"

/********** Global Variables ************/

  /*Encrypted Data Decrypted Data buffer*/   
static BufferType   Global_CipherDataPtr[BUFFER_LENGTH]  ;
static BufferType   Global_PlainDataPtr [BUFFER_LENGTH]  ;
			 
     /*SWC Global parameters*/
static GlobalFlag Global_SystemState ;
static GlobalFlag Global_BufferFlag  ;

     /*Key expansion falg*/
static GlobalFlag Global_KeyFlag = INIT_VALUE ;

void Decrypt_MainFunction (void)
{

	Std_ReturnType status ;
	
	 /*check system state value "Data receive point "*/
		status = RTE_READ_SYSTEM_STATE(&Global_SystemState);
	
		/* Check if there is an error during read operation */
		if (E_OK == status)
		{			
			/* make sure that system state is Decrypt  */
			if (SYS_DECRYPT == Global_SystemState)
			{
				  /*Read buffer Flag  "Data receive point "*/
			    status = RTE_READ_DECRYPTED_DATA_BUFFER_FLAG(&Global_BufferFlag);
			   	/* Check if there is an error during read operation */
		        if (E_OK == status)
		        {
					   /* make sure that buffer state is not set  */
		            if (BUFFER_NOT_SET == Global_BufferFlag)
			        {
	                              /*access piont to decrypt SWC*/								
			      	          /*Read Decrypted Data from flash rom*/
		                status = Nvm_ReadBlock( Global_CipherDataPtr , BUFFER_LENGTH ) ;
              
						if( E_OK == status )
                        {						                	
			         		      /*Key expansion must accur only once */	
			    		   	if(Global_KeyFlag)	
			     		    {
						
					        	Global_KeyFlag = ZERO ;				
				                 /*Init AES module decrypt input buffer */
   	                            AES_uint8KeyExpansion ( key , roundkeys);

				   		    }
                                status = AES_uint8Decrypt_Buffer (roundkeys , Global_CipherDataPtr , Global_PlainDataPtr , BUFFER_LENGTH);
										
							    if( E_OK == status )
                                {			
			                        /*Write decrypted buffer to decrypt port "Data send point "*/
                                    status = RTE_WRITE_DECRYPTED_DATA_BUFFER (Global_PlainDataPtr) ;	                 
								}
											
				                     /*Change buffer flag value to set "Data send point "*/
			                        RTE_WRITE_DECRYPTED_DATA_BUFFER_FLAG(BUFFER_SET);
				
                                     /*Change system flag to SEND , "Data send point "*/
				                    RTE_WRITE_SYSTEM_STATE(SYS_SEND_UPDATE);
					   }												
				   }  
			       else
				   {
									/*buffer is not set */								
				   }													
			   }			 
	        }
			else
			{
							
							/*system state is not Decrypt*/							
			}						
        }				      
}
/************************************************END OF FUNCTION*******************************/
