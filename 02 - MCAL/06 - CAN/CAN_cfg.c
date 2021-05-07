/*******************************************************************************
**  FILENAME     : Can_cfg.c         			                                        **
**                                                                            **
**  VERSION      : 1.2.0                                                      **
**                                                                            **
**  DATE         : 2021-04-28                                                 **
**                                                                            **
**  PLATFORM     : stm32f103		                                              **
**                                                                            **
**  AUTHOR       : osamahijazi	                                              **
**                                                                            **                                                                           **                                                                          **
**  DESCRIPTION  : CAN Driver source configuration file                       **
**                                                                            **
*******************************************************************************/
#include "Std_Types.h"
#include "CAN_Interface.h"


/*FOR BIT RATE 500KHZ , PRESCALE = 1, SJW = 0 ,SEG1 = 0X0C , SEG2 = 0X01 , SAMPLE PIONT AT 87.5 , BTR=  0x001C0000 */	 
 
                        /* they are not stabdard containers but keep it now until new version become tested and safe :)*/
CAN_InitTypeDef        CAN_InitStruct         =	{ 1 , CAN_Mode_Normal   , 0 , 0X0C , 0X01, DISABLE , DISABLE , DISABLE , DISABLE , DISABLE , DISABLE } ;


CAN_FilterInitTypeDef  CAN_FilterInitStruct_1 = { 0x00600000 , 0x00600000 , CAN_FilterMode_IdMask ,  1  , CAN_FilterScale_32bit , CAN_Filter_FIFO0 , ENABLE}; // ID = 0X03 

CAN_FilterInitTypeDef  CAN_FilterInitStruct_2 = { 0x00400000 , 0x00400000 , CAN_FilterMode_IdMask ,  2  , CAN_FilterScale_32bit , CAN_Filter_FIFO0 , ENABLE}; // ID = 0X02 
 


/*
This is the type of the external data structure containing the overall initialization 
v*/

/*standard autosar container*/
/*
const Can_ConfigType Can_Configurations = 
{
    CAN_InitStruct,
	
    CAN_FilterInitStruct_1,
};
*/


















