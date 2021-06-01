/****************************************************************************
* Title                 :   BL   
* Filename              :   BL_interface.h
* Author                :   Mohamed Hafez
* Origin Date           :   14/10/2020
* Version               :   1.0.0
* Compiler              :   TODO: COMPILER GOES HERE
* Target                :   TODO: MCU GOES HERE
* Notes                 :   None
*
*****************************************************************************/
/****************************************************************************
* Doxygen C Template 
*
*****************************************************************************/
/*************** INTERFACE CHANGE LIST **************************************
*
*    Date    Version   Author          Description 
*  14/10/20   1.0.0   Mohamed Hafez   Interface Created.
*
*****************************************************************************/
/** @file  BL_interface.h
 *  @brief This module TODO: WHAT DO I DO?
 * 
 *  This is the header file for the definition TODO: MORE ABOUT ME!
 */
//TODO: UPDATE MACRO BELOW
#ifndef BL_INTERFACE_H_
#define BL_INTERFACE_H_

/******************************************************************************
* Includes
*******************************************************************************/
#define SCB_VTOR                                   *((volatile u32 *)SCB_VTOR_ADDRESS)
/******************************************************************************
* Preprocessor Constants
*******************************************************************************/
// Active Image Information 
// Active Image Addresses                             
#define ADRESS_OF_ACTIVE_IMAGE_STARTUP              0x08001400
#define ADRESS_OF_ACTIVE_IMAGE                      0x08001404
#define ADRESS_OF_ACTIVE_IMAGE_DECIMAL              134222848
#define FIRST_PAGE_NUMBER_IN_ACTIVE_IMAGE_REGION    5
#define LAST_PAGE_NUMBER_IN_ACTIVE_IMAGE_REGION     33
// Active Image Header Info.
#define ACTIVE_IMAGE_HEADER_ADDRESS                 0x0800FC10

#define ACTIVE_IMAGE_ID_ADDRESS                     0x0800FC10
#define ACTIVE_IMAGE_STATUS_ADDRESS                 0x0800FC14
#define ACTIVE_IMAGE_SIZE_ADDRESS                   0x0800FC18
#define ACTIVE_IMAGE_CRC_ADDRESS                    0x0800FC1C
#define ACTIVE_IMAGE_ENTRY_POINT_VALUE_ADDRESS      0x0800FC20

// Backup Image Info
// Backup Image Address                              
#define ADRESS_OF_BACKUP_IMAGE_STARTUP              0x08008800
#define ADRESS_OF_BACKUP_IMAGE                      0x08008804 
#define ADRESS_OF_BACKUP_IMAGE_DECIMAL              134252544
#define FIRST_PAGE_NUMBER_IN_BACKUP_IMAGE_REGION    34
#define LAST_PAGE_NUMBER_IN_BACKUP_IMAGE_REGION     62
#define BACKUP_IMAGE_HEADER_ADDRESS                 0x0800FC30

#define BACKUP_IMAGE_ID_ADDRESS                     0x0800FC30
#define BACKUP_IMAGE_STATUS_ADDRESS                 0x0800FC34
#define BACKUP_IMAGE_SIZE_ADDRESS                   0x0800FC38
#define BACKUP_IMAGE_CRC_ADDRESS                    0x0800FC3C
#define BACKUP_IMAGE_ENTRY_POINT_VALUE_ADDRESS      0x0800FC40
// Header Info
#define HEADER_PAGE_NUMBER                          63
// Branching Flag Address
#define BL_BRANCHING_FLAG_ADDRESS                   0x0800FC00
// UDS Information
#define UDS_RECEIVED_PROGRAM_SESSION                1
#define UDS_CONTROL_SEESION                         0X10
#define UDS_PROGRAM_CONTROL_SESSION                 0x03
#define UDS_MCU_ACKNOWLEDGE_UPGRADE_REQUEST         0x50
#define UDS_GWY_PROVIDE_HEADER                      0x34
#define UDS_MCU_ACCEPT_RECEIVING_HEADER             0x73
#define UDS_MCU_ACKNOWLEDGE_HEADER_RECEIVED         0x74
#define UDS_MCU_ACCEPT_RECEIVING_PACKET_OF_CODE     0x75
#define UDS_GWY_REQUEST_SENDING_LINE_OF_CODE        0x36
#define UDS_MCU_ACKNOWLEDGE_LINE_OF_CODE_RECEIVED   0x76 // 0x76 but my tool send "ok"
#define UDS_GWY_ACKNOWLEDGE_FINISHING_SENDING_CODE  0x37
#define UDS_GWY_ACKNOWLEDGE_FINISHING               0x04
#define UDS_MCU_ACKNOWLEDGE_FINISHING               0x77
#define UDS_MCU_ACKNOWLEDGE_ACTIVE_CODE_CORRECT     0x78
#define UDS_MCU_ACKNOWLEDGE_ACTIVE_CODE_NOT_CORRECT 0x79
#define UDS_MCU_ACKNOWLEDGE_BACKUP_CODE_CORRECT     0x7A
#define UDS_MCU_ACKNOWLEDGE_BACKUP_CODE_NOT_CORRECT 0x7B
// Branch Constants
#define BR_SHIFT_LEFT_24_BIT                        24
#define BR_SHIFT_LEFT_16_BIT                        16
#define BR_SHIFT_LEFT_8_BIT                         8
#define BR_ACTIVE_IMAGE_ID                          1
#define BR_BACKUP_IMAGE_ID                          2
#define BR_SET_IMAGE_NOT_EXISTING                   0xFFFFFFFF
#define BR_SET_IMAGE_ACTIVE                         0xFFFFFFF1
#define BR_SET_IMAGE_CORRECT                        0xFFFFFFF2
#define BR_SET_IMAGE_BACKUP                         0xFFFFFFF3
#define BR_SET_IMAGE_CORRUPTED                      0xFFFFFFF4
#define BR_IMAGE_IS_NOT_EXISTING                    0xFFFFFFFF
#define BR_IMAGE_IS_ACTIVE                          0xFFFFFFF1
#define BR_IMAGE_IS_CORRECT                         0xFFFFFFF2
#define BR_IMAGE_IS_BACKUP                          0xFFFFFFF3
#define BR_IMAGE_IS_CORRUPTED                       0xFFFFFFF4
#define BR_IMAGES_NOT_EXISTING_OR_CORRUPTTED        1 
#define BR_IMAGES_EXISTING                          0  
/******************************************************************************
* Configuration Constants
*******************************************************************************/
// BootLoader Constants
#define BL_INCREASE_RECORD_ADDRESS_WITH_16_BYTE     0x10
#define BL_NUMBER_OF_DIGITS_IN_RECORD               35
#define BL_THE_LAST_DIGIT_IN_RECORD                '\n'
#define BL_RECEIVED_DATA                            1
#define BL_RESET_COUNTER_TO_START_NEW_REC           0
#define BLNOT_RECEIVED                              0
#define BL_BRANCHING_FLAG_RESET                     0xFFFFFFFF
#define BL_BRANCHING_FLAG_SET                       0x00000000
#define BL_RESET_BRANCHING_FLAG                     0xFFFFFFFF
#define BL_SET_BRANCHING_FLAG                       0x00000000
#define BL_INITIALIZE_WITH_FALSE                    0
#define BL_INITIALIZE_WITH_ZERO                     0
#define BL_NOT_FIRST_FLASHING                       0
#define BL_FIRST_FLASHING                           1
#define BL_INITIALIZE_EITH_CORRUPTED                0xFFFFFFF3
#define WORD_SIZE_IN_BYTE                           4
/******************************************************************************
* Macros
*******************************************************************************/
	
/******************************************************************************
* Typedefs
*******************************************************************************/
typedef void (*Function_t)(void);
/******************************************************************************
* Variables
*******************************************************************************/

/******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************
* Function : ABR_voidBranchCode()
*//** 
* \b Description:
*
* This function is used to check update branching flag to determine
* Executing Bootloader or Executing one of images.
*
* PRE-CONDITION:  None
*
* POST-CONDITION: None
*
* @param [in]     void
* 
* @return 		   void
*
* \b Example Example:
* @code
* 	ABR_voidBranchCode();
*
* @endcode
*
* @see ABR_voidBranchCode
*
*******************************************************************************/
void ABR_voidBranchCode(void);
/******************************************************************************
* Function : ABR_voidCheckActiveRegion()
*//** 
* \b Description:
*
* This function is used to check images for executing or not. 
*
* PRE-CONDITION:  FPEC Peripheral Initialized.
*
* POST-CONDITION: None
*
* @param [in]     void
* 
* @return 		   void
*
* \b Example Example:
* @code
* 	ABR_voidCheckActiveRegion();
*
* @endcode
*
* @see ABR_voidCheckActiveRegion
*
*******************************************************************************/
void ABR_voidCheckActiveRegion(void);
/******************************************************************************
* Function : ABR_32CheckBackupRegion()
*//** 
* \b Description:
*
* This function is used to check Backup Image for executing or not. 
*
* PRE-CONDITION:  FPEC Peripheral Initialized.
*
* POST-CONDITION: None
*
* @param [in]     void
* 
* @return 		   32
*
* \b Example Example:
* @code
* 	Local_u32BackupStatus = ABR_32CheckBackupRegion();
*
* @endcode
*
* @see ABR_32CheckBackupRegion
*
*******************************************************************************/
u32  ABR_32CheckBackupRegion(void);
/******************************************************************************
* Function : ABR_u8CheckImageExistingOrCorruptted()
*//** 
* \b Description:
*
* This function is used to check the status of images.
* 
*
* PRE-CONDITION:  FPEC Peripheral Initialized.
*
* POST-CONDITION: None
*
* @param [in]     void
* 
* @return 		   u8
*
* \b Example Example:
* @code
* 	u8 Local_u8FlashStatus = ABR_u8CheckImageExistingOrCorruptted();
*
* @endcode
*
* @see ABR_u8CheckImageExistingOrCorruptted
*
*******************************************************************************/
u8   ABR_u8CheckImageExistingOrCorruptted(void);
/******************************************************************************
* Function : ABR_u8BollingUntillAck()
*//** 
* \b Description:
*
* This function is used to wait untill receiving request from Gateway
* in case of there are no images in the flash.
*
* PRE-CONDITION:  UART Peripheral Initialized
*
* POST-CONDITION: None
*
* @param [in]     void
* 
* @return 		   u8
*
* \b Example Example:
* @code
* 	u8 Local_u8State = ABR_u8BollingUntillAck();
*
* @endcode
*
* @see ABR_u8BollingUntillAck
*
*******************************************************************************/
u8   ABR_u8BollingUntillAck(void);
/******************************************************************************
* Function : ABR_voidUpdateHeaders()
*//** 
* \b Description:
*
* This function is used to update headers using the received value on UART.
* And move the active Image to backup region.
*
* PRE-CONDITION:  UART Peripheral Initialized, FPEC Peripheral Initialized.
*
* POST-CONDITION: None
*
* @param [in]     void
* 
* @return 		   void
*
* \b Example Example:
* @code
* 	ABR_voidUpdateHeaders();
*
* @endcode
*
* @see ABR_voidUpdateHeaders
*
*******************************************************************************/
void ABR_voidUpdateHeaders(void);
/******************************************************************************
* Function :  ABR_voidJumpToBootloader()
*//** 
* \b Description:
*
* This function is used to jump to bootloader to execute it.
*
* PRE-CONDITION:  None
*
* POST-CONDITION: None
*
* @param [in]     void
* 
* @return 		   void
*
* \b Example Example:
* @code
* 	 ABR_voidJumpToBootloader();
*
* @endcode
*
* @see  ABR_voidJumpToBootloader
*
*******************************************************************************/
void ABR_voidJumpToBootloader(void);
/******************************************************************************
* Function :  ABR_voidJumpToAactiveRegion()
*//** 
* \b Description:
*
* This function is used to jump to active region.
*
* PRE-CONDITION:  None
*
* POST-CONDITION: None
*
* @param [in]     void
* 
* @return 		   void
*
* \b Example Example:
* @code
* 	 ABR_voidJumpToAactiveRegion();
*
* @endcode
*
* @see  ABR_voidJumpToAactiveRegion
*
*******************************************************************************/
void ABR_voidJumpToAactiveRegion(void);
/******************************************************************************
* Function :  ABR_u32CalculateActiveImageCRC()
*//** 
* \b Description:
*
* This function is used to Calaulate the CRC of the Active Image.
*
* PRE-CONDITION:  CRC Peripheral Initialized.
*
* POST-CONDITION: None
*
* @param [in]     void
* 
* @return 		   u32
*
* \b Example Example:
* @code
* 	 u32 Local_u3CalcaulatedCRC = ABR_u32CalculateActiveImageCRC();
*
* @endcode
*
* @see  ABR_u32CalculateActiveImageCRC
*
*******************************************************************************/
u32  ABR_u32CalculateActiveImageCRC(void);
/******************************************************************************
* Function :  ABR_u32CalculateBackupImageCRC()
*//** 
* \b Description:
*
* This function is used to Calaulate the CRC of the Backup Image.
*
* PRE-CONDITION:  CRC Peripheral Initialized.
*
* POST-CONDITION: None
*
* @param [in]     void
* 
* @return 		   u32
*
* \b Example Example:
* @code
* 	 u32 Local_u3CalcaulatedCRC = ABR_u32CalculateBackupImageCRC();
*
* @endcode
*
* @see  ABR_u32CalculateBackupImageCRC
*
*******************************************************************************/
u32  ABR_u32CalculateBackupImageCRC(void);
/******************************************************************************
* Function :  ABR_voidCopyImageToActiveRegion()
*//** 
* \b Description:
*
* This function is used to move the backup image to active region to be executed.
*
* PRE-CONDITION:  None
*
* POST-CONDITION: FPEC Peripheral Initialized.
*
* @param [in]     void
* 
* @return 		   void
*
* \b Example Example:
* @code
* 	 ABR_voidCopyImageToActiveRegion();
*
* @endcode
*
* @see  ABR_voidCopyImageToActiveRegion
*
*******************************************************************************/
void ABR_voidCopyImageToActiveRegion(void);
/******************************************************************************
* Function :  ABR_voidCopyImageToBackupRegion()
*//** 
* \b Description:
*
* This function is used to move the active image to backup region to be backup.
*
* PRE-CONDITION:  FPEC Peripheral Initialized.
*
* POST-CONDITION: None
*
* @param [in]     void
* 
* @return 		   void
*
* \b Example Example:
* @code
* 	 ABR_voidCopyImageToBackupRegion();
*
* @endcode
*
* @see  ABR_voidCopyImageToBackupRegion
*
*******************************************************************************/
void ABR_voidCopyImageToBackupRegion(void);
/******************************************************************************
* Function :  ABR_voidSetBranchingFlagAndMakeSWR()
*//** 
* \b Description:
*
* This function is used to set branching flag and make sw reset.
*
* PRE-CONDITION:  FPEC Peripheral Initialized.
*
* POST-CONDITION: None
*
* @param [in]     void
* 
* @return 		   void
*
* \b Example Example:
* @code
* 	 ABR_voidSetBranchingFlagAndMakeSWR();
*
* @endcode
*
* @see  ABR_voidSetBranchingFlagAndMakeSWR
*
*******************************************************************************/
void ABR_voidSetBranchingFlagAndMakeSWR(void);
/******************************************************************************
* Function :  ABL_voidReceiveCode()
*//** 
* \b Description:
*
* This function is used to receive code from gateway on uart and flash it in the active region.
*
* PRE-CONDITION:  UART peripheral initialized.
*
* POST-CONDITION: None
*
* @param [in]     void
* 
* @return 		   void
*
* \b Example Example:
* @code
* 	 ABL_voidReceiveCode();
*
* @endcode
*
* @see  ABL_voidReceiveCode
*
*******************************************************************************/
void ABL_voidReceiveCode(void);
/******************************************************************************
* Function :  ABL_voidStoreRecord()
*//** 
* \b Description:
*
* This function is used to store the record in the flash.
*
* PRE-CONDITION:  FPEC Peripheral Initialized.
*
* POST-CONDITION: None
*
* @param [in]     u8*, u32
* 
* @return 		   void
*
* \b Example Example:
* @code
* 	 ABL_voidStoreRecord(Local_u8RecordBuffer, Local_u32InactiveImageAddressCounter);
*
* @endcode
*
* @see  ABL_voidStoreRecord
*
*******************************************************************************/
void ABL_voidStoreRecord(u8 * Copy_u8BufferRecord, u32 Copy_u32RecordAdddress);
/******************************************************************************
* Function :  ABL_voidHandleActiveImageVectorTable()
*//** 
* \b Description:
*
* This function is used to move vector table to the start of the image.
*
* PRE-CONDITION:  None
*
* POST-CONDITION: None
*
* @param [in]     void
* 
* @return 		   void
*
* \b Example Example:
* @code
* 	 ABL_voidHandleActiveImageVectorTable();
*
* @endcode
*
* @see  ABL_voidHandleActiveImageVectorTable
*
*******************************************************************************/
void ABL_voidHandleActiveImageVectorTable(void);
/******************************************************************************
* Function :  ABL_voidFinishBootLoader()
*//** 
* \b Description:
*
* This function is used to update headers and make sw reset.
*
* PRE-CONDITION:  FPEC Peripheral Initialized.
*
* POST-CONDITION: None
*
* @param [in]     void
* 
* @return 		   void
*
* \b Example Example:
* @code
* 	 ABL_voidFinishBootLoader();
*
* @endcode
*
* @see  ABL_voidFinishBootLoader
*
*******************************************************************************/
void ABL_voidFinishBootLoader(void);


#endif /*File_H_*/

/*** End of File **************************************************************/
