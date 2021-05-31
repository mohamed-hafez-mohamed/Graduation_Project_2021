/*******************************************************************************
* Title                 :   NVIC 
* Filename              :   NVIC_program.c
* Author                :   Mohamed Hafez
* Origin Date           :   15/8/2020
* Version               :   1.0.0
* Compiler              :   TODO: COMPILER GOES HERE
* Target                :   TODO: MCU GOES HERE
* Notes                 :   None 
*
*****************************************************************************/
/*************** SOURCE REVISION LOG *****************************************
*
*    Date    Version   Author          Description 
*  15/08/20   1.0.0   Mohamed Hafez   Initial Release.
*
*******************************************************************************/
/** @file NVIC_program.c
 *  @brief This is the source file for TODO: WHAT DO I DO? 
 */
/******************************************************************************
* Includes
*******************************************************************************/	
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "NVIC_interface.h"
#include "NVIC_private.h"
#include "NVIC_config.h"
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

/******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************
* Function Definitions
*******************************************************************************/
uint8 MNVIC_u8EnableInt(NVIC_HW_PRIORITY  copy_IntId)
{
    if(copy_IntId >= 0 && copy_IntId <32)
    {
        NVIC_ISER0 = (SET << copy_IntId);
    }
    else if(copy_IntId < 60)
    {
        copy_IntId -= 32;
        NVIC_ISER1 = (SET << copy_IntId);
    }
    else
    {
        /*!<TODO: Error Code */
    }
}

uint8 MNVIC_u8DisableInt(NVIC_HW_PRIORITY  copy_IntId)
{
    if(copy_IntId >= 0 && copy_IntId <32)
    {
        NVIC_ICER0 = (SET << copy_IntId);
    }
    else if(copy_IntId < 60)
    {
        copy_IntId -= 32;
        NVIC_ICER1 = (SET << copy_IntId);
    }
    else
    {
        /*!<TODO: Error Code */
    }
}

uint8 MNVIC_u8EnableInts(NVIC_HW_PRIORITY copy_IntId[], uint8 copy_u8ArraySize)
{
    uint8 Local_u8Counter;
    for(Local_u8Counter = 0;Local_u8Counter < copy_u8ArraySize;Local_u8Counter++)
    {
        if(copy_IntId[Local_u8Counter] >= 0 && copy_IntId[Local_u8Counter] <32)
        {
            NVIC_ISER0 = (SET << copy_IntId[Local_u8Counter]);
        }
        else if(copy_IntId[Local_u8Counter] < 60)
        {
           copy_IntId[Local_u8Counter] -= 32;
           NVIC_ISER1 = (SET << copy_IntId[Local_u8Counter]);
        }
        else
        {
            /*!<TODO: Error Code */
        }
    }
}

uint8 MNVIC_u8DisableInts(NVIC_HW_PRIORITY copy_IntId[], uint8 copy_u8ArraySize)
{
    uint8 Local_u8Counter;
    for(Local_u8Counter = 0;Local_u8Counter < copy_u8ArraySize;Local_u8Counter++)
    {
        if(copy_IntId[Local_u8Counter] >= 0 && copy_IntId[Local_u8Counter] <32)
        {
            NVIC_ICER0 = (SET << copy_IntId[Local_u8Counter]);
        }
        else if(copy_IntId[Local_u8Counter] < 60)
        {
           copy_IntId[Local_u8Counter] -= 32;
           NVIC_ICER1 = (SET << copy_IntId[Local_u8Counter]);
        }
        else
        {
            /*!<TODO: Error Code */
        }
    }
}


uint8 MNVIC_u8IsIntActive(NVIC_HW_PRIORITY  copy_IntId)
{
    uint8 Local_u8IntStatus;
    if(copy_IntId >= 0 && copy_IntId <32)
    {
        Local_u8IntStatus = GET_BIT(NVIC_IABR0, copy_IntId);
    }
    else if(copy_IntId < 60)
    {
        copy_IntId -= 32;
        Local_u8IntStatus = GET_BIT(NVIC_IABR1, copy_IntId);
    }
    else
    {
        /*!<TODO: Error Code */
    }
    return Local_u8IntStatus;
}

uint8 MNVIC_u8SetIntpending(NVIC_HW_PRIORITY  copy_IntId)
{
    if(copy_IntId >= 0 && copy_IntId <32)
    {
        NVIC_ISPR0 = (SET << copy_IntId);
    }
    else if(copy_IntId < 60)
    {
        copy_IntId -= 32;
        NVIC_ISPR1 = (SET << copy_IntId);
    }
    else
    {
        /*!<TODO: Error Code */
    }
}

uint8 MNVIC_u8ClrIntpending(NVIC_HW_PRIORITY  copy_IntId)
{
    if(copy_IntId >= 0 && copy_IntId <32)
    {
        NVIC_ICPR0 = (SET << copy_IntId);
    }
    else if(copy_IntId < 60)
    {
        copy_IntId -= 32;
        NVIC_ICPR1 = (SET << copy_IntId);
    }
    else
    {
        /*!<TODO: Error Code */
    }
}

uint8 MNVIC_u8SetIntspending(NVIC_HW_PRIORITY copy_IntId[], uint8 copy_u8ArraySize)
{
    uint8 Local_u8Counter;
    for(Local_u8Counter = 0;Local_u8Counter < copy_u8ArraySize;Local_u8Counter++)
    {
        if(copy_IntId[Local_u8Counter] >= 0 && copy_IntId[Local_u8Counter] <32)
        {
            NVIC_ISPR0 = (SET << copy_IntId[Local_u8Counter]);
        }
        else if(copy_IntId[Local_u8Counter] < 60)
        {
           copy_IntId[Local_u8Counter] -= 32;
           NVIC_ISPR1 = (SET << copy_IntId[Local_u8Counter]);
        }
        else
        {
            /*!<TODO: Error Code */
        }
    }
}

uint8 MNVIC_u8ClrIntspending(NVIC_HW_PRIORITY copy_IntId[], uint8 copy_u8ArraySize)
{
    uint8 Local_u8Counter;
    for(Local_u8Counter = 0;Local_u8Counter < copy_u8ArraySize;Local_u8Counter++)
    {
        if(copy_IntId[Local_u8Counter] >= 0 && copy_IntId[Local_u8Counter] <32)
        {
            NVIC_ICPR0 = (SET << copy_IntId[Local_u8Counter]);
        }
        else if(copy_IntId[Local_u8Counter] < 60)
        {
           copy_IntId[Local_u8Counter] -= 32;
           NVIC_ICPR1 = (SET << copy_IntId[Local_u8Counter]);
        }
        else
        {
            /*!<TODO: Error Code */
        }
    }
}

uint8 MNVIC_u8IsIntPending(NVIC_HW_PRIORITY  copy_IntId)
{
    uint8 Int_Status;
    if(copy_IntId >= 0 && copy_IntId <32)
    {
        Int_Status = GET_BIT(NVIC_ISPR0, copy_IntId);
    }
    else if(copy_IntId < 60)
    {
        copy_IntId -= 32;
        Int_Status = GET_BIT(NVIC_ISPR1, copy_IntId);
    }
    else
    {
        /*!<TODO: Error Code */
    }
    return Int_Status;
}

uint8 MNVIC_u8SetPriority(sint8 copy_s8IntId, uint8 copy_u8GroupPriority, uint8 copy_u8SubPriority)
{
    #define SCB_AIRCR   *((volatile uint32 * const)(0xE000ED00  + 0X0C))
    //external int
    SCB_AIRCR = NVIC_GROUP_SUB_DISTRIBUTION;
    uint8 Local_u8Priority = copy_u8SubPriority | (copy_u8GroupPriority << ((NVIC_GROUP_SUB_DISTRIBUTION - BASE_GROUP_VALUE) / GROUP_STEP));
    if(copy_s8IntId >= 0)
    {
        NVIC_IPR[copy_s8IntId] = Local_u8Priority << MS_4Local_u8Counter;
    }
    else
    {
        //!<TODO: Error Code 
    }
    
}

//some additinal functions
uint8 MNVIC_u8EnableInterrupts(uint8 copy_RegId, uint32 copy_RegValue)
{
    if(copy_RegId == 0)
    {
        NVIC_ISER0 = copy_RegValue;
    }
    else if (copy_RegId == 1)
    {
        NVIC_ISER1 = copy_RegValue;
    }
    else
    {
        /*!<TODO: Error Code */
    }
}

uint8 MNVIC_u8DisableInterrupts(uint8 copy_RegId, uint32 copy_RegValue)
{
    if(copy_RegId == 0)
    {
        NVIC_ICER0 = copy_RegValue;
    }
    else if (copy_RegId == 1)
    {
        NVIC_ICER1 = copy_RegValue;
    }
    else
    {
        /*!<TODO: Error Code */
    }
}

uint8 MNVIC_u8SetInterruptspending(uint8 copy_RegId, uint32 copy_RegValue)
{
    if(copy_RegId == 0)
    {
        NVIC_ISPR0 = copy_RegValue;
    }
    else if (copy_RegId == 1)
    {
        NVIC_ISPR1 = copy_RegValue;
    }
    else
    {
        /*!<TODO: Error Code */
    }
}

uint8 MNVIC_u8ClrInterruptspending(uint8 copy_RegId, uint32 copy_RegValue)
{
    if(copy_RegId == 0)
    {
        NVIC_ICPR0 = copy_RegValue;
    }
    else if (copy_RegId == 1)
    {
        NVIC_ICPR1 = copy_RegValue;
    }
    else
    {
        /*!<TODO: Error Code */
    }
}


/*************** END OF FUNCTIONS ***************************************************************************/
