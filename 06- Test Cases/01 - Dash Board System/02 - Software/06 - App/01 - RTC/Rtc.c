/*****************************************************/
 /* Author      : Mosad                              */
 /* Version     : v01                                */
 /* date        : 28/5/2021                          */
/*****************************************************/
/* Library includes */
#include "BIT_MATH.h"
#include "Std_Types.h"
#include "Rte_RtcPort.h"

/* Module includes */
#include "Rtc_Interface.h"
#include "Rtc_Private.h"
#include "Rtc_Cfg.h"

/* MCAL includes */
#include "I2c_Interface.h"

/**************************************************************************/
/*                         Global Variables                               */
/**************************************************************************/
uint8   Global_DataArr [7] ;

void Rtc_Init (void)
{
    /* Init variables */
}

void Rtc_MainFunction(void)
{
    /* Get the new readdings from RTC */
    Rtc_GetTime (Global_DataArr);

    /* Update the RTE shared buffer */
    RTE_WRITE_TIME_PTR(Global_DataArr);

    /* Set ready flag for the data */
    RTE_WRITE_TIME_PTR_FLAG(FLAG_SET);
}

static Std_ReturnType Rtc_GetTime(uint8 *Cpy_DataPtr)
{
    uint8 Local_SendData[2] = {0x00};
    uint8 Local_RecData[7] = {0x00};
    uint8 Local_Counter = 0 ;
    /* Set Pointer at first address */
    I2C_voidMasterSendData(I2C1 , Local_SendData, 1 ,RTC_I2C_ADDRESS , I2C_NO_REPEAT_S);

    /* Get the data */
    I2C_voidMasterReceiveData(I2C1 , Local_RecData , 7 , RTC_I2C_ADDRESS);

    /* Conver from BCD to Decimal */
    Cpy_DataPtr[RTC_SECONDS_INDEX] = (Local_RecData[RTC_SECONDS_INDEX] & MASK_LOWER_FOUR_BITS) +
                                     ((Local_RecData[RTC_SECONDS_INDEX]>>SHIFT_BY_4) & MASK_LOWER_FOUR_BITS) * 10;

    Cpy_DataPtr[RTC_MINUTES_INDEX] = (Local_RecData[RTC_MINUTES_INDEX] & MASK_LOWER_FOUR_BITS) +
                                     ((Local_RecData[RTC_MINUTES_INDEX]>>SHIFT_BY_4) & MASK_LOWER_FOUR_BITS) * 10;

    Cpy_DataPtr[RTC_HOURS_INDEX] = (Local_RecData[RTC_HOURS_INDEX] & MASK_LOWER_FOUR_BITS) +
                                     ((Local_RecData[RTC_HOURS_INDEX]>>SHIFT_BY_4) & MASK_FIRST_BIT) * 10;

    Cpy_DataPtr[RTC_DAY_INDEX] = (Local_RecData[RTC_DAY_INDEX] & MASK_LOWER_FOUR_BITS) ;
                                     
    Cpy_DataPtr[RTC_DATE_INDEX] = (Local_RecData[RTC_DATE_INDEX] & MASK_LOWER_FOUR_BITS) +
                                     ((Local_RecData[RTC_DATE_INDEX]>>SHIFT_BY_4) & MASK_LOWER_FOUR_BITS) * 10;

    Cpy_DataPtr[RTC_MONTH_INDEX] = (Local_RecData[RTC_MONTH_INDEX] & MASK_LOWER_FOUR_BITS) +
                                     ((Local_RecData[RTC_MONTH_INDEX]>>SHIFT_BY_4) & MASK_LOWER_FOUR_BITS) * 10;

    Cpy_DataPtr[RTC_YEAR_INDEX] = (Local_RecData[RTC_YEAR_INDEX] & MASK_LOWER_FOUR_BITS) +
                                     ((Local_RecData[RTC_YEAR_INDEX]>>SHIFT_BY_4) & MASK_LOWER_FOUR_BITS) * 10;

    return 0;
}

/* To be implemented */
Std_ReturnType Rtc_SetTime(uint8 *Cpy_DataPtr)
{

}
