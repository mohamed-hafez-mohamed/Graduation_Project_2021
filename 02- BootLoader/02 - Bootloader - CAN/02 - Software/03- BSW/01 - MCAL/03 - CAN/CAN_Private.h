/*******************************************************************************
**  FILENAME     : Can_Private.h         			                              **
**                                                                            **
**  VERSION      : 1.2.0                                                      **
**                                                                            **
**  DATE         : 2021-02-2                                                  **
**                                                                            **                                                                            **
**  PLATFORM     : stm32f103		                                              **
**                                                                            **
**  AUTHOR       : osamahijazi	                                              **
                                                                              **
**  DESCRIPTION  : CAN Driver hardware definiton file                         **
**                                                                            **
*******************************************************************************/

/* Define to prevent recursive inclusion */

#ifndef CAN_PRIVATE_H
#define CAN_PRIVATE_H

/***********************************************************************************************************************************************************************************************************************************************************
                                               *******Controller Area Network Register Definition**********
***********************************************************************************************************************************************************************************************************************************************************/																																										 
/** 
  * @brief Controller Area Network TxMailBox 
  */

typedef struct
{
   u32 TIR;
   u32 TDTR;
   u32 TDLR;
   u32 TDHR;
} CAN_TxMailBoxType_Def;

/** 
  * @brief Controller Area Network FIFOMailBox 
  */
  
typedef struct
{
  u32 RIR;
  u32 RDTR;
  u32 RDLR;
  u32 RDHR;
} CAN_FIFOMailBoxType_Def;

/** 
  * @brief Controller Area Network FilterRegister 
  */
  
typedef struct
{
  u32 FR1;
  u32 FR2;
} CAN_FilterRegisterType_Def;

/** 
  * @brief Controller Area Network 
  */
  
typedef struct
{
   u32 MCR;
   u32 MSR;
   u32 TSR;
   u32 RF0R;
   u32 RF1R;
   u32 IER;
   u32 ESR;
   u32 BTR;
   u32  RESERVED0[88];
  CAN_TxMailBoxType_Def sTxMailBox[3];
  CAN_FIFOMailBoxType_Def sFIFOMailBox[2];
  u32  RESERVED1[12];
  u32 FMR;
  u32 FM1R;
  u32  RESERVED2;
  u32 FS1R;
  u32  RESERVED3;
  u32 FFA1R;
  u32  RESERVED4;
  u32  FA1R;
  u32  RESERVED5[8];
  CAN_FilterRegisterType_Def sFilterRegister[14];
} CAN_TypeDef;

/*Peripheral declaration*/


/***********************************************************************************************************************************************************************************************************************************************************
                                                   *******Base Address Macros**********
***********************************************************************************************************************************************************************************************************************************************************/																																										 
#define CAN1_BASE          0x40006400          
#define CAN2_BASE          0x40006800          


/***********************************************************************************************************************************************************************************************************************************************************
                                                   ****Peripheral declaration******
***********************************************************************************************************************************************************************************************************************************************************/																																										 

#define CAN1                ((volatile CAN_TypeDef*) CAN1_BASE)
#define CAN2                ((volatile CAN_TypeDef*) CAN2_BASE)	


/***********************************************************************************************************************************************************************************************************************************************************
                                                   *******Registers Bits Definitions**********
***********************************************************************************************************************************************************************************************************************************************************/																																										 


                                  /*!< CAN control and status registers */
/*******************  Bit definition for CAN_MCR register  ********************/
#define  CAN_MCR_INRQ                        ((u16)0x0001)            /*!< Initialization Request */
#define  CAN_MCR_SLEEP                       ((u16)0x0002)            /*!< Sleep Mode Request */
#define  CAN_MCR_TXFP                        ((u16)0x0004)            /*!< Transmit FIFO Priority */
#define  CAN_MCR_RFLM                        ((u16)0x0008)            /*!< Receive FIFO Locked Mode */
#define  CAN_MCR_NART                        ((u16)0x0010)            /*!< No Automatic Retransmission */
#define  CAN_MCR_AWUM                        ((u16)0x0020)            /*!< Automatic Wakeup Mode */
#define  CAN_MCR_ABOM                        ((u16)0x0040)            /*!< Automatic Bus-Off Management */
#define  CAN_MCR_TTCM                        ((u16)0x0080)            /*!< Time Triggered Communication Mode */

/*******************  Bit definition for CAN_MSR register  ********************/
#define  CAN_MSR_INAK                        ((u16)0x0001)            /*!< Initialization Acknowledge */
#define  CAN_MSR_SLAK                        ((u16)0x0002)            /*!< Sleep Acknowledge */
#define  CAN_MSR_WKUI                        ((u16)0x0008)            /*!< Wakeup Interrupt */

/*******************  Bit definition for CAN_TSR register  ********************/
#define  CAN_TSR_RQCP0                       ((u32)0x00000001)        /*!< Request Completed Mailbox0 */
#define  CAN_TSR_TXOK0                       ((u32)0x00000002)        /*!< Transmission OK of Mailbox0 */
#define  CAN_TSR_ALST0                       ((u32)0x00000004)        /*!< Arbitration Lost for Mailbox0 */
#define  CAN_TSR_TERR0                       ((u32)0x00000008)        /*!< Transmission Error of Mailbox0 */
#define  CAN_TSR_ABRQ0                       ((u32)0x00000080)        /*!< Abort Request for Mailbox0 */
#define  CAN_TSR_RQCP1                       ((u32)0x00000100)        /*!< Request Completed Mailbox1 */
#define  CAN_TSR_TXOK1                       ((u32)0x00000200)        /*!< Transmission OK of Mailbox1 */
#define  CAN_TSR_ALST1                       ((u32)0x00000400)        /*!< Arbitration Lost for Mailbox1 */
#define  CAN_TSR_TERR1                       ((u32)0x00000800)        /*!< Transmission Error of Mailbox1 */
#define  CAN_TSR_ABRQ1                       ((u32)0x00008000)        /*!< Abort Request for Mailbox 1 */
#define  CAN_TSR_RQCP2                       ((u32)0x00010000)        /*!< Request Completed Mailbox2 */
#define  CAN_TSR_TXOK2                       ((u32)0x00020000)        /*!< Transmission OK of Mailbox 2 */
#define  CAN_TSR_ALST2                       ((u32)0x00040000)        /*!< Arbitration Lost for mailbox 2 */
#define  CAN_TSR_TERR2                       ((u32)0x00080000)        /*!< Transmission Error of Mailbox 2 */
#define  CAN_TSR_ABRQ2                       ((u32)0x00800000)        /*!< Abort Request for Mailbox 2 */
#define  CAN_TSR_CODE                        ((u32)0x03000000)        /*!< Mailbox Code */

#define  CAN_TSR_TME                         ((u32)0x1C000000)        /*!< TME[2:0] bits */
#define  CAN_TSR_TME0                        ((u32)0x04000000)        /*!< Transmit Mailbox 0 Empty */
#define  CAN_TSR_TME1                        ((u32)0x08000000)        /*!< Transmit Mailbox 1 Empty */
#define  CAN_TSR_TME2                        ((u32)0x10000000)        /*!< Transmit Mailbox 2 Empty */

/*******************  Bit definition for CAN_RF0R register  *******************/
#define  CAN_RF0R_FMP0                       ((u8)0x03)               /*!< FIFO 0 Message Pending */
#define  CAN_RF0R_FULL0                      ((u8)0x08)               /*!< FIFO 0 Full */
#define  CAN_RF0R_FOVR0                      ((u8)0x10)               /*!< FIFO 0 Overrun */
#define  CAN_RF0R_RFOM0                      ((u8)0x20)               /*!< Release FIFO 0 Output Mailbox */

/*******************  Bit definition for CAN_RF1R register  *******************/
#define  CAN_RF1R_FMP1                       ((u8)0x03)               /*!< FIFO 1 Message Pending */
#define  CAN_RF1R_FULL1                      ((u8)0x08)               /*!< FIFO 1 Full */
#define  CAN_RF1R_FOVR1                      ((u8)0x10)               /*!< FIFO 1 Overrun */
#define  CAN_RF1R_RFOM1                      ((u8)0x20)               /*!< Release FIFO 1 Output Mailbox */

/********************  Bit definition for CAN_IER register  *******************/
#define  CAN_IER_TMEIE                       ((u32)0x00000001)        /*!< Transmit Mailbox Empty Interrupt Enable */
#define  CAN_IER_FMPIE0                      ((u32)0x00000002)        /*!< FIFO 0 Message Pending Interrupt Enable */
#define  CAN_IER_FMPIE1                      ((u32)0x00000010)        /*!< FIFO 1 Message Pending Interrupt Enable */

/********************  Bit definition for CAN_ESR register  *******************/
#define  CAN_ESR_LEC                         ((u32)0x00000070)        /*!< LEC[2:0] bits (Last Error Code) */

                                  /*!< Mailbox registers */
/******************  Bit definition for CAN_TI0R register  ********************/
#define  CAN_TI0R_TXRQ                       ((u32)0x00000001)        /*!< Transmit Mailbox Request */
#define  CAN_TI0R_RTR                        ((u32)0x00000002)        /*!< Remote Transmission Request */
#define  CAN_TI0R_IDE                        ((u32)0x00000004)        /*!< Identifier Extension */
#define  CAN_TI0R_EXID                       ((u32)0x001FFFF8)        /*!< Extended Identifier */
#define  CAN_TI0R_STID                       ((u32)0xFFE00000)        /*!< Standard Identifier or Extended Identifier */

/******************  Bit definition for CAN_TDT0R register  *******************/
#define  CAN_TDT0R_DLC                       ((u32)0x0000000F)        /*!< Data Length Code */
#define  CAN_TDT0R_TGT                       ((u32)0x00000100)        /*!< Transmit Global Time */
#define  CAN_TDT0R_TIME                      ((u32)0xFFFF0000)        /*!< Message Time Stamp */

/******************  Bit definition for CAN_TDL0R register  *******************/
#define  CAN_TDL0R_DATA0                     ((u32)0x000000FF)        /*!< Data byte 0 */
#define  CAN_TDL0R_DATA1                     ((u32)0x0000FF00)        /*!< Data byte 1 */
#define  CAN_TDL0R_DATA2                     ((u32)0x00FF0000)        /*!< Data byte 2 */
#define  CAN_TDL0R_DATA3                     ((u32)0xFF000000)        /*!< Data byte 3 */

/******************  Bit definition for CAN_TDH0R register  *******************/
#define  CAN_TDH0R_DATA4                     ((u32)0x000000FF)        /*!< Data byte 4 */
#define  CAN_TDH0R_DATA5                     ((u32)0x0000FF00)        /*!< Data byte 5 */
#define  CAN_TDH0R_DATA6                     ((u32)0x00FF0000)        /*!< Data byte 6 */
#define  CAN_TDH0R_DATA7                     ((u32)0xFF000000)        /*!< Data byte 7 */

/*******************  Bit definition for CAN_TI1R register  *******************/
#define  CAN_TI1R_TXRQ                       ((u32)0x00000001)        /*!< Transmit Mailbox Request */
#define  CAN_TI1R_RTR                        ((u32)0x00000002)        /*!< Remote Transmission Request */
#define  CAN_TI1R_IDE                        ((u32)0x00000004)        /*!< Identifier Extension */
#define  CAN_TI1R_EXID                       ((u32)0x001FFFF8)        /*!< Extended Identifier */

/*******************  Bit definition for CAN_TDT1R register  ******************/
#define  CAN_TDT1R_DLC                       ((u32)0x0000000F)        /*!< Data Length Code */
#define  CAN_TDT1R_TGT                       ((u32)0x00000100)        /*!< Transmit Global Time */
#define  CAN_TDT1R_TIME                      ((u32)0xFFFF0000)        /*!< Message Time Stamp */

/*******************  Bit definition for CAN_TDL1R register  ******************/
#define  CAN_TDL1R_DATA0                     ((u32)0x000000FF)        /*!< Data byte 0 */
#define  CAN_TDL1R_DATA1                     ((u32)0x0000FF00)        /*!< Data byte 1 */
#define  CAN_TDL1R_DATA2                     ((u32)0x00FF0000)        /*!< Data byte 2 */
#define  CAN_TDL1R_DATA3                     ((u32)0xFF000000)        /*!< Data byte 3 */

/*******************  Bit definition for CAN_TDH1R register  ******************/
#define  CAN_TDH1R_DATA4                     ((u32)0x000000FF)        /*!< Data byte 4 */
#define  CAN_TDH1R_DATA5                     ((u32)0x0000FF00)        /*!< Data byte 5 */
#define  CAN_TDH1R_DATA6                     ((u32)0x00FF0000)        /*!< Data byte 6 */
#define  CAN_TDH1R_DATA7                     ((u32)0xFF000000)        /*!< Data byte 7 */

/*******************  Bit definition for CAN_TI2R register  *******************/
#define  CAN_TI2R_TXRQ                       ((u32)0x00000001)        /*!< Transmit Mailbox Request */
#define  CAN_TI2R_RTR                        ((u32)0x00000002)        /*!< Remote Transmission Request */
#define  CAN_TI2R_IDE                        ((u32)0x00000004)        /*!< Identifier Extension */
#define  CAN_TI2R_EXID                       ((u32)0x001FFFF8)        /*!< Extended identifier */
#define  CAN_TI2R_STID                       ((u32)0xFFE00000)        /*!< Standard Identifier or Extended Identifier */

/*******************  Bit definition for CAN_TDT2R register  ******************/  
#define  CAN_TDT2R_DLC                       ((u32)0x0000000F)        /*!< Data Length Code */
#define  CAN_TDT2R_TGT                       ((u32)0x00000100)        /*!< Transmit Global Time */
#define  CAN_TDT2R_TIME                      ((u32)0xFFFF0000)        /*!< Message Time Stamp */

/*******************  Bit definition for CAN_TDL2R register  ******************/
#define  CAN_TDL2R_DATA0                     ((u32)0x000000FF)        /*!< Data byte 0 */
#define  CAN_TDL2R_DATA1                     ((u32)0x0000FF00)        /*!< Data byte 1 */
#define  CAN_TDL2R_DATA2                     ((u32)0x00FF0000)        /*!< Data byte 2 */
#define  CAN_TDL2R_DATA3                     ((u32)0xFF000000)        /*!< Data byte 3 */

/*******************  Bit definition for CAN_TDH2R register  ******************/
#define  CAN_TDH2R_DATA4                     ((u32)0x000000FF)        /*!< Data byte 4 */
#define  CAN_TDH2R_DATA5                     ((u32)0x0000FF00)        /*!< Data byte 5 */
#define  CAN_TDH2R_DATA6                     ((u32)0x00FF0000)        /*!< Data byte 6 */
#define  CAN_TDH2R_DATA7                     ((u32)0xFF000000)        /*!< Data byte 7 */

/*******************  Bit definition for CAN_RI0R register  *******************/
#define  CAN_RI0R_RTR                        ((u32)0x00000002)        /*!< Remote Transmission Request */
#define  CAN_RI0R_IDE                        ((u32)0x00000004)        /*!< Identifier Extension */
#define  CAN_RI0R_EXID                       ((u32)0x001FFFF8)        /*!< Extended Identifier */
#define  CAN_RI0R_STID                       ((u32)0xFFE00000)        /*!< Standard Identifier or Extended Identifier */

/*******************  Bit definition for CAN_RDT0R register  ******************/
#define  CAN_RDT0R_DLC                       ((u32)0x0000000F)        /*!< Data Length Code */
#define  CAN_RDT0R_FMI                       ((u32)0x0000FF00)        /*!< Filter Match Index */
#define  CAN_RDT0R_TIME                      ((u32)0xFFFF0000)        /*!< Message Time Stamp */

/*******************  Bit definition for CAN_RDL0R register  ******************/
#define  CAN_RDL0R_DATA0                     ((u32)0x000000FF)        /*!< Data byte 0 */
#define  CAN_RDL0R_DATA1                     ((u32)0x0000FF00)        /*!< Data byte 1 */
#define  CAN_RDL0R_DATA2                     ((u32)0x00FF0000)        /*!< Data byte 2 */
#define  CAN_RDL0R_DATA3                     ((u32)0xFF000000)        /*!< Data byte 3 */

/*******************  Bit definition for CAN_RDH0R register  ******************/
#define  CAN_RDH0R_DATA4                     ((u32)0x000000FF)        /*!< Data byte 4 */
#define  CAN_RDH0R_DATA5                     ((u32)0x0000FF00)        /*!< Data byte 5 */
#define  CAN_RDH0R_DATA6                     ((u32)0x00FF0000)        /*!< Data byte 6 */
#define  CAN_RDH0R_DATA7                     ((u32)0xFF000000)        /*!< Data byte 7 */

/*******************  Bit definition for CAN_RI1R register  *******************/
#define  CAN_RI1R_RTR                        ((u32)0x00000002)        /*!< Remote Transmission Request */
#define  CAN_RI1R_IDE                        ((u32)0x00000004)        /*!< Identifier Extension */
#define  CAN_RI1R_EXID                       ((u32)0x001FFFF8)        /*!< Extended identifier */
#define  CAN_RI1R_STID                       ((u32)0xFFE00000)        /*!< Standard Identifier or Extended Identifier */

/*******************  Bit definition for CAN_RDT1R register  ******************/
#define  CAN_RDT1R_DLC                       ((u32)0x0000000F)        /*!< Data Length Code */
#define  CAN_RDT1R_FMI                       ((u32)0x0000FF00)        /*!< Filter Match Index */
#define  CAN_RDT1R_TIME                      ((u32)0xFFFF0000)        /*!< Message Time Stamp */

/*******************  Bit definition for CAN_RDL1R register  ******************/
#define  CAN_RDL1R_DATA0                     ((u32)0x000000FF)        /*!< Data byte 0 */
#define  CAN_RDL1R_DATA1                     ((u32)0x0000FF00)        /*!< Data byte 1 */
#define  CAN_RDL1R_DATA2                     ((u32)0x00FF0000)        /*!< Data byte 2 */
#define  CAN_RDL1R_DATA3                     ((u32)0xFF000000)        /*!< Data byte 3 */

/*******************  Bit definition for CAN_RDH1R register  ******************/
#define  CAN_RDH1R_DATA4                     ((u32)0x000000FF)        /*!< Data byte 4 */
#define  CAN_RDH1R_DATA5                     ((u32)0x0000FF00)        /*!< Data byte 5 */
#define  CAN_RDH1R_DATA6                     ((u32)0x00FF0000)        /*!< Data byte 6 */
#define  CAN_RDH1R_DATA7                     ((u32)0xFF000000)        /*!< Data byte 7 */

/*****************************Private Macros************************************/
#define FRAME_DATA              8
#define ZERO                    0
#define BYTE_ZERO               0
#define BYTE_ONE                1
#define BYTE_TWO                2
#define BYTE_THREE              3

                            /*!< CAN filter registers */
/*******************  Bit definition for CAN_FMR register  ********************/
#define  CAN_FMR_FINIT                       ((u8)0x01)               /*!< Filter Init Mode */

typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;

#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrorStatus;


#endif
/******************************************END OF FILE************************************/

