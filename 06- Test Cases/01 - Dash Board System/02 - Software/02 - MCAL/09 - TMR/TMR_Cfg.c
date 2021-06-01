/*****************************************************/
 /* Author      : Mosad                              */
 /* Version     : v01                                */
 /* date        : 10/9/2020                          */
/*****************************************************/

#include "Std_Types.h"
#include "TMR_Interface.h"
#include "TMR_Cfg.h"


/** Timer configurations table **/
const TMR_config_t configTable[TMR_NUMBER] = {
//   Timer      Timer        Timer          Interrupt    CLK         Prescaller       Interval
//   channel	enable       mode           enable       source                       in US
	{TIM1    ,  DISABLE     , UP_COUNTER    , DISABLE    , APB2_CLK    , 128            , 0 } ,
	{TIM2    ,  DISABLE     , UP_COUNTER    , DISABLE    , APB1_CLK    , 8              , 0 } ,
	{TIM3    ,  ENABLE      , UP_COUNTER    , DISABLE    , APB1_CLK    , 128            , 0 } ,
	{TIM4    ,  DISABLE     , UP_COUNTER    , DISABLE    , APB1_CLK    , 128            , 0 }
};
