/*****************************************************/
 /* Author      : Mosad                              */
 /* Version     : v01                                */
 /* date        : 28/5/2021                          */
/*****************************************************/
#ifndef RTC_PRIVATE_H
#define RTC_PRIVATE_H



/**************************************************************************/
/*                         Macros                                         */
/**************************************************************************/
#define     RTC_I2C_ADDRESS        0x68

#define    MASK_LOWER_FOUR_BITS    0x0f
#define    MASK_FIRST_BIT          0X01
#define    SHIFT_BY_4              4

#define    RTC_SECONDS_INDEX      0
#define    RTC_MINUTES_INDEX      1
#define    RTC_HOURS_INDEX        2
#define    RTC_DAY_INDEX          3
#define    RTC_DATE_INDEX         4
#define    RTC_MONTH_INDEX        5
#define    RTC_YEAR_INDEX         6

/**************************************************************************/
/*                        Private Functions                               */
/**************************************************************************/
static Std_ReturnType Rtc_GetTime(uint8 *Cpy_DataPtr);

#endif