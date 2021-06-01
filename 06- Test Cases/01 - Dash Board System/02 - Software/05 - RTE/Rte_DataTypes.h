/*****************************************************/
 /* Author      : Mosad                              */
 /* Version     : v01                                */
 /* date        : 25/5/2021                           */
/*****************************************************/
#ifndef RTE_DATA_TYPES_H
#define RTE_DATA_TYPES_H


typedef     uint8    FlagType ;
/* Header flag  values */
#define    FLAG_NOT_SET              0x0u
#define    FLAG_SET                  0x1u

/* Time Array Index */
#define    RTC_SECONDS_INDEX      0
#define    RTC_MINUTES_INDEX      1
#define    RTC_HOURS_INDEX        2
#define    RTC_DAY_INDEX          3
#define    RTC_DATE_INDEX         4
#define    RTC_MONTH_INDEX        5
#define    RTC_YEAR_INDEX         6

typedef   uint8    RtcDayType ;
/* Day */
#define     RTE_MONDAY     0x01
#define     RTE_TUESDAY    0x02
#define     RTE_WEDNSDAY   0x03
#define     RTE_THURSDAY   0x04
#define     RTE_FRIDAY     0x05
#define     RTE_SATURDAY   0x06
#define     RTE_SUNDAY     0x07


#endif
