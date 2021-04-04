/*******************************************************************************
* Title                 :   BL2_program 
* Filename              :   BL2_program.c
* Author                :   Mohamed Hafez
* Origin Date           :   31/12/2020
* Version               :   1.0.0
* Compiler              :   TODO: COMPILER GOES HERE
* Target                :   TODO: MCU GOES HERE
* Notes                 :   None 
*
*****************************************************************************/
/*************** SOURCE REVISION LOG *****************************************
*
*    Date    Version   Author          Description 
*  31/12/20   1.0.0   Mohamed Hafez   Initial Release.
*
*******************************************************************************/
/** @file BL2_program_program.c
 *  @brief This is the source file for TODO: WHAT DO I DO? 
 */
/******************************************************************************
* Includes
*******************************************************************************/	

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "BL_interface.h"
#include "BL_config.h"
#include "BL_private.h"
#include "FPEC_interface.h"
#include "UART_interface.h"
#include "UDS_interface.h"
#include "CRC_interface.h"
#include "WDT_interface.h"
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
u8 Global_u8FirstFlashingFlag = BL_NOT_FIRST_FLASHING;
/******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************
* Function Definitions
*******************************************************************************/

void ABR_voidBranchCode(void)
{
	// Read Branching Request Update Flag to determine behaviour.
	u32 Local_u32BranchingFlag = MFPEC_voidReadWord(BL_BRANCHING_FLAG_ADDRESS);
	if(Local_u32BranchingFlag      == BL_BRANCHING_FLAG_RESET)
	{
		// Check images existence, status and CRC.
		ABR_voidCheckActiveRegion();
	}
	else if(Local_u32BranchingFlag == BL_BRANCHING_FLAG_SET)
	{
		// Goto Bootloader to Receive code in the inactive image.
	  ABR_voidJumpToBootloader();
	}
}

void ABR_voidCheckActiveRegion(void)
{
	// Read Images Satus To Determine Which Case Will Be Excuted.
	u32 Local_u32ActiveImageStatus = MFPEC_voidReadWord(ACTIVE_IMAGE_STATUS_ADDRESS);
	u32 Local_u32ReceivedCRC       = MFPEC_voidReadWord(ACTIVE_IMAGE_CRC_ADDRESS);
	u32 Local_u32BackupStatus      = BL_INITIALIZE_EITH_CORRUPTED;  
	// Check Active region Image Status. 
	if(Local_u32ActiveImageStatus == BR_IMAGE_IS_ACTIVE)
	{
		// Active Case.
		u32 Local_u32CalculateActiveImageCRC = ABR_u32CalculateActiveImageCRC();
		if(Local_u32CalculateActiveImageCRC == Local_u32ReceivedCRC)
		{
			// Acknowledge Gateway that the Active Code Is Correct.
	      MUART_voidTransmitByteSynch(UDS_MCU_ACKNOWLEDGE_ACTIVE_CODE_CORRECT);
			// Excute Image in the active region If it's CRC is Correct.
			ABR_voidJumpToAactiveRegion();
		}
		else
		{
			// Acknowledge Gateway that the Active Code Is not Correct.
	      MUART_voidTransmitByteSynch(UDS_MCU_ACKNOWLEDGE_ACTIVE_CODE_NOT_CORRECT);
			// Make Image in the active region Corrupted As it's CRC is Wrong.
			FEE_voidEraseRestoreHeaderPage(ACTIVE_IMAGE_STATUS_ADDRESS, BR_SET_IMAGE_CORRUPTED);
			// Make Software Reset to return to branch code.
	      IWDT_voidMakeSoftWareReset();
		}
	}
	else if(Local_u32ActiveImageStatus == BR_IMAGE_IS_CORRUPTED || Local_u32ActiveImageStatus == BR_IMAGE_IS_NOT_EXISTING)
	{
		// Check the status of the backup image if the image in he active region is corrupted or not exisit.
      Local_u32BackupStatus    = ABR_32CheckBackupRegion();
		if(Local_u32BackupStatus == BR_IMAGE_IS_CORRECT)
		{
			// Move the backup image to the active region to be eexecuted.
			ABR_voidCopyImageToActiveRegion();
			// Excute Image in the active region If it's CRC is Correct.
			ABR_voidJumpToAactiveRegion();
		}
		else if(Local_u32BackupStatus == BR_IMAGE_IS_CORRUPTED || Local_u32BackupStatus == BR_IMAGE_IS_NOT_EXISTING)
		{
			// Set branching flag to go to bootloader to receive a new code as all codes in the flash corrupted.
			ABR_voidSetBranchingFlagAndMakeSWR();
		}  
	}
}

u32 ABR_32CheckBackupRegion(void)
{
	// Read Backup Images Satus To Determine Which Case Will Be Excuted.
	u32 Local_u32BackupStatus = MFPEC_voidReadWord(BACKUP_IMAGE_STATUS_ADDRESS);
	u32 Local_u32RceivedCRC   = MFPEC_voidReadWord(BACKUP_IMAGE_CRC_ADDRESS);
	if(Local_u32BackupStatus == BR_IMAGE_IS_BACKUP)
	{
		u32 Local_u32CalculatedBackupImageCRC = ABR_u32CalculateBackupImageCRC();
		if(Local_u32CalculatedBackupImageCRC == Local_u32RceivedCRC)
		{
			// Acknowledge Gateway that the Backup Code Is Correct.
         MUART_voidTransmitByteSynch(UDS_MCU_ACKNOWLEDGE_BACKUP_CODE_CORRECT);
			return BR_IMAGE_IS_CORRECT;
		}
		else
		{
			// Acknowledge Gateway that the Backup Code Is Not Correct.
         MUART_voidTransmitByteSynch(UDS_MCU_ACKNOWLEDGE_BACKUP_CODE_NOT_CORRECT);
			// Make Image in the active region Corrupted As it's CRC is Wrong.
         FEE_voidEraseRestoreHeaderPage(BACKUP_IMAGE_STATUS_ADDRESS, BR_SET_IMAGE_CORRUPTED);
			return BR_IMAGE_IS_CORRUPTED;
		}
	}
}

u8  ABR_u8CheckImageExistingOrCorruptted(void)
{
	u8  Local_u8Result              = BR_IMAGES_EXISTING;
	// Chec Images status.
	u32 Local_u32ActiveImageStatus  = BR_IMAGE_IS_ACTIVE;
	u32 Local_u32BackupImageStatus  = BR_IMAGE_IS_BACKUP;
	Local_u32ActiveImageStatus      = MFPEC_voidReadWord(ACTIVE_IMAGE_STATUS_ADDRESS);
	Local_u32BackupImageStatus      = MFPEC_voidReadWord(BACKUP_IMAGE_STATUS_ADDRESS);
	if(  (Local_u32ActiveImageStatus == BR_IMAGE_IS_NOT_EXISTING) || (Local_u32ActiveImageStatus == BR_IMAGE_IS_CORRUPTED))
	{
		if((Local_u32BackupImageStatus == BR_IMAGE_IS_NOT_EXISTING) || (Local_u32BackupImageStatus == BR_IMAGE_IS_CORRUPTED))
		{
			Local_u8Result =  BR_IMAGES_NOT_EXISTING_OR_CORRUPTTED;
		}
		else
		{
			Local_u8Result =  BR_IMAGES_EXISTING;
		}
	}
	else
	{
		Local_u8Result =  BR_IMAGES_EXISTING;
	}
	return Local_u8Result;
}

u8 ABR_u8BollingUntillAck(void)
{
	u8 Local_u8ReceivedValue    = 0;
	u8 Local_u8ControlParameter = 0;
	// Check Received Value from Gateway.
	Local_u8ReceivedValue = MUART_u8ReceiveByteSynch();
	if(Local_u8ReceivedValue == UDS_CONTROL_SEESION)
  { 
	  Local_u8ControlParameter = MUART_u8ReceiveByteSynch();
	  if(Local_u8ControlParameter == UDS_PROGRAM_CONTROL_SESSION)
	  {
	    return UDS_RECEIVED_PROGRAM_SESSION;
	  }
	}
}

void ABR_voidUpdateHeaders(void)
{
	u8  Local_u8FlashState                = BL_INITIALIZE_WITH_ZERO;
	u8  local_u8DataArray[9]              = {BL_INITIALIZE_WITH_ZERO};
	u32 Local_u32ActiveRegionStatus       = BL_INITIALIZE_WITH_ZERO;
	u32 Local_u32ImageSizeInWord          = BL_INITIALIZE_WITH_ZERO;
	u32 Local_u32CRCValue                 = BL_INITIALIZE_WITH_ZERO; 
	Local_u8FlashState                    = ABR_u8CheckImageExistingOrCorruptted();
	Local_u32ActiveRegionStatus           = MFPEC_voidReadWord(ACTIVE_IMAGE_STATUS_ADDRESS); 
	if(Local_u8FlashState == BR_IMAGES_NOT_EXISTING_OR_CORRUPTTED)
	{
		// Waiting if the flash is erased.
		ABR_u8BollingUntillAck();
		Global_u8FirstFlashingFlag = BL_FIRST_FLASHING;
	}
   // Acknowledge Gateway that the Update Request is accepted.
	MUART_voidTransmitByteSynch(UDS_MCU_ACKNOWLEDGE_UPGRADE_REQUEST);
	for(u8 Local_u8Counter = 0;Local_u8Counter < 9;Local_u8Counter++)
	{
		// Rceiving Hrader From Gateway.
		local_u8DataArray[Local_u8Counter] = MUART_u8ReceiveByteSynch();
	}
	// Extracting Info from the Received Value.
	Local_u32ImageSizeInWord =((local_u8DataArray[4])<< BR_SHIFT_LEFT_24_BIT) | ((local_u8DataArray[3]) << BR_SHIFT_LEFT_16_BIT)|
	                          ((local_u8DataArray[2])<< BR_SHIFT_LEFT_8_BIT)  | ((local_u8DataArray[1]));
	Local_u32CRCValue        =((local_u8DataArray[8]) << BR_SHIFT_LEFT_24_BIT)| ((local_u8DataArray[7]) << BR_SHIFT_LEFT_16_BIT)|
	                          ((local_u8DataArray[6])<< BR_SHIFT_LEFT_8_BIT)  | ((local_u8DataArray[5]));
	// Move the Active image to the backup region to be backup.
	if(Local_u32ActiveRegionStatus == BR_SET_IMAGE_ACTIVE)
	{
		ABR_voidCopyImageToBackupRegion();
	}
	
	if(local_u8DataArray[0] == UDS_GWY_PROVIDE_HEADER)
	{
		// Update Image Header with New Values.
     FEE_voidEraseRestoreHeaderPage(ACTIVE_IMAGE_SIZE_ADDRESS, Local_u32ImageSizeInWord);
	  FEE_voidEraseRestoreHeaderPage(ACTIVE_IMAGE_CRC_ADDRESS,  Local_u32CRCValue);
	}
}

void ABR_voidJumpToBootloader(void)
{
	// Execute Bootloader.
	ABR_voidUpdateHeaders();
	ABL_voidReceiveCode();
}

void ABR_voidJumpToAactiveRegion(void)
{
	Function_t AddressToCall = 0;
	AddressToCall = *(Function_t*)(ADRESS_OF_ACTIVE_IMAGE);
   // Jump to application based on the address
   AddressToCall();
}

u32  ABR_u32CalculateActiveImageCRC(void)
{
	u32 Local_u32CalculatedActiveImageCRC    = 0;
	u32 Local_u32Image1SizeInWord = MFPEC_voidReadWord(ACTIVE_IMAGE_SIZE_ADDRESS);
	// Calcaulate The CRC using MCU Peripheral.
	MCRC_voidCalculateCrcDirect(ADRESS_OF_ACTIVE_IMAGE_DECIMAL, Local_u32Image1SizeInWord, &Local_u32CalculatedActiveImageCRC);
	return Local_u32CalculatedActiveImageCRC;
}

u32  ABR_u32CalculateBackupImageCRC(void)
{
	u32 Local_u32CalculatedCRC2    = 0;
	u32 Local_u32Image2SizeInWord = MFPEC_voidReadWord(BACKUP_IMAGE_SIZE_ADDRESS);
	// Calcaulate The CRC using MCU Peripheral.
	MCRC_voidCalculateCrcDirect(ADRESS_OF_BACKUP_IMAGE_DECIMAL, Local_u32Image2SizeInWord, &Local_u32CalculatedCRC2);
	return Local_u32CalculatedCRC2;
}

void ABR_voidSetBranchingFlagAndMakeSWR(void)
{
	// Set Branching Flag To Receive New Code.
	FEE_voidEraseRestoreHeaderPage(BL_BRANCHING_FLAG_ADDRESS, BL_SET_BRANCHING_FLAG);
	// Make Software Reset.
	IWDT_voidMakeSoftWareReset();
}

void ABR_voidCopyImageToActiveRegion(void)
{
	u32 Local_u32BackupDataWord       = BL_INITIALIZE_WITH_ZERO;
	u32 Local_u32BackupDataAddress    = BL_INITIALIZE_WITH_ZERO;
	u32 Local_u32ActiveDataAddress    = BL_INITIALIZE_WITH_ZERO;
	u32 Local_u32BackupSizeInWord     = MFPEC_voidReadWord(BACKUP_IMAGE_SIZE_ADDRESS);
	u32 Local_u32BackupCRCValue       = MFPEC_voidReadWord(BACKUP_IMAGE_CRC_ADDRESS);
	// Erase the Active region.
	MFPEC_voidEraseAppArea(FIRST_PAGE_NUMBER_IN_ACTIVE_IMAGE_REGION, LAST_PAGE_NUMBER_IN_ACTIVE_IMAGE_REGION);
	//Copy data from backup to active region.
	for(u32 Local_u32WordCounter      = 0;Local_u32WordCounter < Local_u32BackupSizeInWord;Local_u32WordCounter++)
  {
	  Local_u32ActiveDataAddress      = (ADRESS_OF_ACTIVE_IMAGE_STARTUP + (WORD_SIZE_IN_BYTE * Local_u32WordCounter));
	  Local_u32BackupDataAddress      = (ADRESS_OF_BACKUP_IMAGE_STARTUP + (WORD_SIZE_IN_BYTE * Local_u32WordCounter));
	  Local_u32BackupDataWord         = *((volatile u32*)(Local_u32BackupDataAddress));
	  MFPEC_u8ProgramOneWordFlash(Local_u32ActiveDataAddress, Local_u32BackupDataWord);
  }
  // Update headers.
  FEE_voidEraseRestoreHeaderPage(ACTIVE_IMAGE_SIZE_ADDRESS,   Local_u32BackupSizeInWord);
  FEE_voidEraseRestoreHeaderPage(ACTIVE_IMAGE_CRC_ADDRESS,    Local_u32BackupCRCValue);
  FEE_voidEraseRestoreHeaderPage(ACTIVE_IMAGE_STATUS_ADDRESS, BR_SET_IMAGE_ACTIVE);
  FEE_voidEraseRestoreHeaderPage(BACKUP_IMAGE_STATUS_ADDRESS, BR_SET_IMAGE_BACKUP);
}

void ABR_voidCopyImageToBackupRegion(void)
{
	u32 Local_u32ActiveDataWord       = BL_INITIALIZE_WITH_ZERO;
	u32 Local_u32ActiveDataAddress    = BL_INITIALIZE_WITH_ZERO;
	u32 Local_u32BackupDataAddress    = BL_INITIALIZE_WITH_ZERO;
	u32 Local_u32ActiveSizeInWord     = MFPEC_voidReadWord(ACTIVE_IMAGE_SIZE_ADDRESS);
	u32 Local_u32ActiveCRCValue       = MFPEC_voidReadWord(ACTIVE_IMAGE_CRC_ADDRESS);
	// Erase the Backup region.
	MFPEC_voidEraseAppArea(FIRST_PAGE_NUMBER_IN_BACKUP_IMAGE_REGION, LAST_PAGE_NUMBER_IN_BACKUP_IMAGE_REGION);
	//Copy data from active region to backup to region.
	for(u32 Local_u32WordCounter      = 0;Local_u32WordCounter < Local_u32ActiveSizeInWord;Local_u32WordCounter++)
  {
	  Local_u32BackupDataAddress      = (ADRESS_OF_BACKUP_IMAGE_STARTUP + (WORD_SIZE_IN_BYTE * Local_u32WordCounter));
	  Local_u32ActiveDataAddress      = (ADRESS_OF_ACTIVE_IMAGE_STARTUP + (WORD_SIZE_IN_BYTE * Local_u32WordCounter));
	  Local_u32ActiveDataWord         = *((volatile u32*)(Local_u32ActiveDataAddress));
	  MFPEC_u8ProgramOneWordFlash(Local_u32BackupDataAddress, Local_u32ActiveDataWord);
  }
  // Update headers.
  FEE_voidEraseRestoreHeaderPage(BACKUP_IMAGE_SIZE_ADDRESS,   Local_u32ActiveSizeInWord);
  FEE_voidEraseRestoreHeaderPage(BACKUP_IMAGE_CRC_ADDRESS,    Local_u32ActiveCRCValue);
  FEE_voidEraseRestoreHeaderPage(BACKUP_IMAGE_STATUS_ADDRESS, BR_SET_IMAGE_BACKUP);
  FEE_voidEraseRestoreHeaderPage(ACTIVE_IMAGE_STATUS_ADDRESS, BR_SET_IMAGE_ACTIVE);
}
/*************** END OF FUNCTIONS ***************************************************************************/
