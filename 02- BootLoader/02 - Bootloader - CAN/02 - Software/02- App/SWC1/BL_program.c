/*******************************************************************************
* Title                 :   BL 
* Filename              :   BL_program.c
* Author                :   Mohamed Hafez
* Origin Date           :   14/10/2020
* Version               :   1.0.0
* Compiler              :   TODO: COMPILER GOES HERE
* Target                :   TODO: MCU GOES HERE
* Notes                 :   None 
*
*****************************************************************************/
/*************** SOURCE REVISION LOG *****************************************
*
*    Date    Version   Author          Description 
*  14/10/20   1.0.0   Mohamed Hafez   Initial Release.
*
*******************************************************************************/
/** @file BL_program.c
 *  @brief This is the source file for TODO: WHAT DO I DO? 
 */
/******************************************************************************
* Includes
*******************************************************************************/	

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "BL_interface.h"
#include "CRC_interface.h"
#include "GPIO_interface.h"
#include "FPEC_interface.h"
#include "NVM_interface.h"
#include "WDT_interface.h"
#include "BL_config.h"
#include "BL_private.h"
#include "CanIf_Interface.h"

u32 Local_u32SizeOfCode ;
/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/

/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/

/******************************************************************************
* Module Typedefs
*******************************************************************************/

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/
extern Global_u8FirstFlashingFlag;
u8 Local_u32RxBuffer[PACKET_SIZE] ;
/******************************************************************************
* Function Definitions
*******************************************************************************/
void ABL_voidHandleActiveImageVectorTable(void)
{
	// Setting the offset of the vector table.
   SCB_VTOR = ADRESS_OF_ACTIVE_IMAGE_STARTUP;
}

void ABL_voidReceiveCode(void)
{
   u8  Local_u8RecordBuffer[BL_NUMBER_OF_DIGITS_IN_RECORD]  = {BL_INITIALIZE_WITH_ZERO};
   u8  Local_u8RecordCounter                                = BL_RESET_COUNTER_TO_START_NEW_REC ;
   u8  Local_u8UartReceivedStatus                           = BLNOT_RECEIVED;
	u8  Local_u8GatewayRequest                               = BL_INITIALIZE_WITH_FALSE;
	u32 Local_u32InactiveImageAddressCounter                 = ADRESS_OF_ACTIVE_IMAGE_STARTUP;
	Local_u32SizeOfCode = MFPEC_voidReadWord(ACTIVE_IMAGE_SIZE_ADDRESS);
	// Erasing flash only one time to be written.
   MFPEC_voidEraseAppArea(FIRST_PAGE_NUMBER_IN_ACTIVE_IMAGE_REGION, LAST_PAGE_NUMBER_IN_ACTIVE_IMAGE_REGION);
	// Acknowledge Gateway that Header Received.
	CanIf_u8Transmit_Byte(UDS_MCU_ACKNOWLEDGE_HEADER_RECEIVED);
	
	while (Local_u32SizeOfCode)
	{
		CanIf_u8Receive_Byte(&Local_u8GatewayRequest);
		if(Local_u8GatewayRequest == UDS_GWY_REQUEST_SENDING_LINE_OF_CODE)
		{
			CanIf_u8Transmit_Byte(UDS_MCU_ACCEPT_RECEIVING_PACKET_OF_CODE);
			if (Local_u32SizeOfCode > PACKET_SIZE)
			{
				CanIf_u8Receive_Block (Local_u32RxBuffer ,PACKET_SIZE);
				Local_u32SizeOfCode -= PACKET_SIZE ;
				MFPEC_u8ProgramFlashBuffer(Local_u32InactiveImageAddressCounter , (Local_u32RxBuffer) ,PACKET_SIZE);
				Local_u32InactiveImageAddressCounter+=PACKET_SIZE ;
				CanIf_u8Transmit_Byte(UDS_MCU_ACKNOWLEDGE_LINE_OF_CODE_RECEIVED);
			}
			else 
			{
				CanIf_u8Receive_Block (Local_u32RxBuffer, Local_u32SizeOfCode);
				MFPEC_u8ProgramFlashBuffer(Local_u32InactiveImageAddressCounter, Local_u32RxBuffer, Local_u32SizeOfCode);
				Local_u32SizeOfCode -= Local_u32SizeOfCode ;	
				CanIf_u8Transmit_Byte(UDS_MCU_ACKNOWLEDGE_LINE_OF_CODE_RECEIVED);
			}				
	}
	CanIf_u8Receive_Byte(&Local_u8GatewayRequest);
	if (UDS_GWY_ACKNOWLEDGE_FINISHING_SENDING_CODE == Local_u8GatewayRequest)
	{
		ABL_voidFinishBootLoader();
	}
}

void ABL_voidFinishBootLoader(void)
{
	// Acknowledge Gateway that the New Cod Received.
	CanIf_u8Transmit_Byte(UDS_MCU_ACKNOWLEDGE_FINISHING);
	// Update Headers
   FEE_voidEraseRestoreHeaderPage(ACTIVE_IMAGE_STATUS_ADDRESS, BR_SET_IMAGE_ACTIVE);
	FEE_voidEraseRestoreHeaderPage(BACKUP_IMAGE_STATUS_ADDRESS, BR_SET_IMAGE_BACKUP);
	// Move the active image to the backup region when the backup region erased.
	if(Global_u8FirstFlashingFlag == BL_FIRST_FLASHING)
	{
		Global_u8FirstFlashingFlag = BL_NOT_FIRST_FLASHING;
		ABR_voidCopyImageToBackupRegion();
	}
	// Reset Branching Flag.
	FEE_voidEraseRestoreHeaderPage(BL_BRANCHING_FLAG_ADDRESS, BL_RESET_BRANCHING_FLAG);
	// Make Software Reset.
	IWDT_voidMakeSoftWareReset();
}

/*************** END OF FUNCTIONS ***************************************************************************/
