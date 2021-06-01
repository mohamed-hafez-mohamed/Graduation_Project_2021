/*******************************************************************************
* Title                 :   STK 
* Filename              :   STK_program.c
* Author                :   Mohamed Hafez
* Origin Date           :   26/8/2020
* Version               :   1.0.0
* Compiler              :   TODO: COMPILER GOES HERE
* Target                :   TODO: MCU GOES HERE
* Notes                 :   None 
*
*****************************************************************************/
/*************** SOURCE REVISION LOG *****************************************
*
*    Date    Version   Author          Description 
*  26/08/20   1.0.0   Mohamed Hafez   Initial Release.
*
*******************************************************************************/
/** @file STK_program.c
 *  @brief This is the source file for TODO: WHAT DO I DO? 
 */
/******************************************************************************
* Includes
*******************************************************************************/	
#include "BIT_MATH.h"
#include "Std_Types.h"
#include "STK_interface.h"
#include "STK_config.h"
#include "STK_private.h"

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
static STK_PtrToFunction CallBackFunction[4];
static void *            ParameterCallBack[4];
static uint8  volatile   Static_u8SingleUs;
static uint8  volatile   Static_u8PeriodcUs;
static uint8  volatile   Static_u8SingleMs;
static uint8  volatile   Static_u8PeriodicMs;
static uint8  volatile   Static_u8DelayFlag;
static uint32 volatile   Static_u32Ticks;
/******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************
* Function Definitions
*******************************************************************************/
static uint16 STK_u16ConfigIntervalMs(void)
{
    uint32 Local_u32STKClock;
    #if   STK_CLOCK_SOURCE == STK_AHB_CLOCK_SOURCE_DIV_8
        Local_u32STKClock = AHP_CLOCK_FREQ / STK_DIVIDE_AHP_BY_8;
    #elif STK_CLOCK_SOURCE == STK_AHB_CLOCK_SOURCE
        Local_u32STKClock = AHP_CLOCK_FREQ;
    #else
        //!<TODO: Error Code
    #endif
    return Local_u32STKClock / STK_GENERATE_1_MS;
}

static uint8 STK_u8ConfigIntervalUs(void)
{
    uint32 Local_u32STKClock;
    #if   STK_CLOCK_SOURCE == STK_AHB_CLOCK_SOURCE_DIV_8
        Local_u32STKClock = AHP_CLOCK_FREQ / STK_DIVIDE_AHP_BY_8;
    #elif STK_CLOCK_SOURCE == STK_AHB_CLOCK_SOURCE
        Local_u32STKClock = AHP_CLOCK_FREQ;
    #else
        //!<TODO: Error Code
    #endif
    return Local_u32STKClock / STK_GENERATE_1_US;
}

void MSTK_voidInit(void)
{
    STK->CTRL  = STK_CLR_REG;
    STK->CTRL |= STK_CLOCK_SOURCE;
    Static_u8SingleUs   = 0;
    Static_u8PeriodcUs  = 0;
    Static_u8SingleMs   = 0;
    Static_u8PeriodicMs = 0;
}

uint8 MSTK_u8StartStkSingle_ms(uint16 Copy_u16DelayMs)
{
    uint16 Local_u16Ticks = STK_u16ConfigIntervalMs();
    //CLR_BIT(STK->CTRL, ENABLE);
    STK->VAL  = STK_CLR_REG;
    STK->LOAD = (Local_u16Ticks * Copy_u16DelayMs);
    SET_BIT(STK->CTRL, ENABLE);
}

uint8 MSTK_u8StartStkPeriodic_ms(uint16 Copy_u16DelayMs)
{
    uint16 Local_u16Ticks = STK_u16ConfigIntervalMs();
    CLR_BIT(STK->CTRL, ENABLE);
    STK->VAL  = STK_CLR_REG;
    STK->LOAD = (Local_u16Ticks * Copy_u16DelayMs) - STK_SUB_1_FOR_PERIODIC;
    SET_BIT(STK->CTRL, ENABLE);
}

void MSTK_voidSetBusyWait_ms(uint16 Copy_u16DelayMs)
{
    uint16 Local_u16Ticks = STK_u16ConfigIntervalMs();
    STK->VAL  = STK_CLR_REG;
    STK->LOAD = Local_u16Ticks * Copy_u16DelayMs;
    SET_BIT(STK->CTRL, ENABLE);
    while(GET_BIT(STK->CTRL, COUNTFLAG) == 0);
}

void MSTK_voidSetIntervalPeriodic_ms(uint16 Copy_u16DelayMs, STK_PtrToFunction Copy_PtrFunction, void * Copy_Parameter)
{
    uint16 Local_u16Ticks = STK_u16ConfigIntervalMs();
    CLR_BIT(STK->CTRL, TICKINT);
    CLR_BIT(STK->CTRL, ENABLE);
    STK->VAL  = STK_CLR_REG;
    STK->LOAD = (Local_u16Ticks * Copy_u16DelayMs) - STK_SUB_1_FOR_PERIODIC;
    __disable_irq();
    Static_u8PeriodicMs = 1;
    __enable_irq();
    CallBackFunction[0]  = Copy_PtrFunction;
    ParameterCallBack[0] = Copy_Parameter;
    SET_BIT(STK->CTRL, TICKINT);
    SET_BIT(STK->CTRL, ENABLE);
}

void MSTK_voidSetIntervalSingle_ms(uint16 Copy_u16DelayMs, STK_PtrToFunction Copy_PtrFunction, void * Copy_Parameter)
{
    uint16 Local_u16Ticks = STK_u16ConfigIntervalMs();
	CLR_BIT(STK->CTRL, TICKINT);
    CLR_BIT(STK->CTRL, ENABLE);
    STK->VAL  = STK_CLR_REG;
    STK->LOAD = Local_u16Ticks * Copy_u16DelayMs;
    __disable_irq();
    Static_u8SingleMs = 1;
    __enable_irq();
    CallBackFunction[1]  = Copy_PtrFunction;
    ParameterCallBack[1] = Copy_Parameter;
    SET_BIT(STK->CTRL, TICKINT);
    SET_BIT(STK->CTRL, ENABLE);
}

uint8   MSTK_u8StartStkSingle_us(uint32 Copy_u32DelayUs)
{
    uint8 Local_u8Ticks = STK_u8ConfigIntervalUs();
    //CLR_BIT(STK->CTRL, ENABLE);
    STK->VAL  = STK_CLR_REG;
    STK->LOAD = (Local_u8Ticks * Copy_u32DelayUs);
    SET_BIT(STK->CTRL, ENABLE);
}

uint8   MSTK_u8StartStkPeriodic_us(uint32 Copy_u32DelayUs)
{
    uint8 Local_u8Ticks = STK_u8ConfigIntervalUs();
    CLR_BIT(STK->CTRL, ENABLE);
    STK->VAL  = STK_CLR_REG;
    STK->LOAD = (Local_u8Ticks * Copy_u32DelayUs) - STK_SUB_1_FOR_PERIODIC;
    SET_BIT(STK->CTRL, ENABLE);
}

void MSTK_voidSetBusyWait_us(uint32 Copy_u32DelayUs)
{
    uint8 Local_u8Ticks = STK_u8ConfigIntervalUs();
    STK->VAL  = STK_CLR_REG;
    STK->LOAD = Local_u8Ticks * Copy_u32DelayUs;
    SET_BIT(STK->CTRL, ENABLE);
    while(GET_BIT(STK->CTRL, COUNTFLAG) == 0);
}

void MSTK_voidSetIntervalPeriodic_us(uint32 Copy_u32DelayUs, STK_PtrToFunction Copy_PtrFunction, void * Copy_Parameter)
{
    uint8 Local_u8Ticks = STK_u8ConfigIntervalUs();
    CLR_BIT(STK->CTRL, TICKINT);
    CLR_BIT(STK->CTRL, ENABLE);
    STK->VAL  = STK_CLR_REG;
    STK->LOAD = (Local_u8Ticks * Copy_u32DelayUs) - STK_SUB_1_FOR_PERIODIC;
    __disable_irq();
    Static_u8PeriodcUs = 1;
    __enable_irq();
    CallBackFunction[2]  = Copy_PtrFunction;
    ParameterCallBack[2] = Copy_Parameter;
    SET_BIT(STK->CTRL, TICKINT);
    SET_BIT(STK->CTRL, ENABLE);
}

void MSTK_voidSetIntervalSingle_us(uint32 Copy_u32DelayUs, STK_PtrToFunction Copy_PtrFunction, void * Copy_Parameter)
{
    uint8 Local_u8Ticks = STK_u8ConfigIntervalUs();
    CLR_BIT(STK->CTRL, TICKINT);
    CLR_BIT(STK->CTRL, ENABLE);
    STK->VAL  = STK_CLR_REG;
    STK->LOAD = Local_u8Ticks * Copy_u32DelayUs;
    __disable_irq();
    Static_u8SingleUs = 1;
    __enable_irq();
    CallBackFunction[3]  = Copy_PtrFunction;
    ParameterCallBack[3] = Copy_Parameter;
    SET_BIT(STK->CTRL, TICKINT);
    SET_BIT(STK->CTRL, ENABLE);
}

uint32  MSTK_u32GetElapsedTime_us(void)
{
    return (STK->LOAD - STK->VAL) * STK_u8ConfigIntervalUs();
}

uint32  MSTK_u32GetElapsedTime_ms(void)
{
    return (STK->LOAD - STK->VAL) * STK_u16ConfigIntervalMs();
}

uint32  MSTK_u32GetRemainingTime_us(void)
{
    return (STK->VAL) * STK_u8ConfigIntervalUs();
}

uint32  MSTK_u32GetRemainingTime_ms(void)
{
    return (STK->VAL) * STK_u16ConfigIntervalMs();
}

void MSTK_voidStopStk(void)
{
    CLR_BIT(STK->CTRL, ENABLE);
	CLR_BIT(STK->CTRL, TICKINT);
}

void MSTK_voidResumeStk(void)
{
  SET_BIT(STK->CTRL, ENABLE);
  SET_BIT(STK->CTRL, TICKINT);
}

uint32 MSTK_u32ReturnElapsedTicks(void)
{
    uint32 Local_u32CurrentTick;
    __disable_irq();
    Local_u32CurrentTick = Static_u32Ticks;
    __enable_irq();
    return Local_u32CurrentTick;
}

void MSTK_voidDelayUsingInterrupt(uint16 Copy_u16DelayMs)
{
	__disable_irq();
	Static_u32Ticks = 0;
	__enable_irq();
	uint16 Local_u16Ticks = STK_u16ConfigIntervalMs();
	CLR_BIT(STK->CTRL, TICKINT);
    CLR_BIT(STK->CTRL, ENABLE);
    STK->VAL  = STK_CLR_REG;
    STK->LOAD = Local_u16Ticks * Copy_u16DelayMs;
    Static_u8DelayFlag = 1;
    SET_BIT(STK->CTRL, TICKINT);
    SET_BIT(STK->CTRL, ENABLE);
	uint32 Local_u32IntialTick = MSTK_u32ReturnElapsedTicks();
	while((MSTK_u32ReturnElapsedTicks() - Local_u32IntialTick) < (Copy_u16DelayMs / Local_u16Ticks))
	{
			
	}
}

void SysTick_Handler(void)
{
	CLR_BIT(STK->CTRL, COUNTFLAG);
    if(Static_u8DelayFlag == 1)
    {
        __disable_irq();
        Static_u8DelayFlag = 0;
        __enable_irq();
        ++Static_u32Ticks;
    }
    if(Static_u8PeriodicMs == 1)
    {
        CallBackFunction[0](ParameterCallBack[0]);
    }
    if(Static_u8SingleMs == 1)
    {
        __disable_irq();
        Static_u8SingleMs = 0;
        __enable_irq();
        CallBackFunction[1](ParameterCallBack[1]);
    }
    if(Static_u8PeriodcUs == 1)
    {
        CallBackFunction[2](ParameterCallBack[2]);
    }
    if(Static_u8SingleUs == 1)
    {
        __disable_irq();
        Static_u8SingleUs = 0;
        __enable_irq();
        CallBackFunction[3](ParameterCallBack[3]);
    }
}

/*************************************** END OF FUNCTIONS **********************************************/
