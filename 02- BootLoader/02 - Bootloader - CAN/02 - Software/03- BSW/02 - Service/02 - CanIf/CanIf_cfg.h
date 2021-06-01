/*******************************************************************************
**  FILENAME     : ComM_cfg.h         			                                  **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2021-04-29                                                 **
**                                                                             **                                                                            **
**  PLATFORM     : stm32f103		                                              **
**                                                                            **
**  AUTHOR       : osamahijazi	                                              **
                                                                              **
**  DESCRIPTION  : Canif Driver configurations file                             **
**                                                                            **
*******************************************************************************/

/* Define to prevent recursive inclusion */

#ifndef CanIf_CFG_H
#define CanIf_CFG_H



/*****************************************************************************************/
/*                                   Include headres                                     */
/*****************************************************************************************/


/******************************************************************************************/
/*                                    Macro Definition                                    */
/*******************************************************************************************/

#define NODE_ONE_ID          0X00
#define NODE_TWO_ID          0X01

/*Transmit structure statis configurations*/
#define CONFOIG_DLC        8
#define CONFOIG_RTR        0
#define CONFOIG_IDE        0




#endif
/******************************************END OF FILE************************************/
