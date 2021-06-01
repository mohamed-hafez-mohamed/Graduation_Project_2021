/*****************************************************/
 /* Author      : Mosad                              */
 /* Version     : v01                                */
 /* date        : 6/5/2020                           */
/*****************************************************/
#ifndef USER_INTERFACE_PRIVATE_H
#define USER_INTERFACE_PRIVATE_H

/* Other Modules */
#include "TFT_interface.h"
#include "Button_Interface.h"
#include "STK_interface.h"

/**************************************************************************/
/*                         Private DataTypes                              */
/**************************************************************************/
/********** Internal state of Module ***********/
typedef    uint8    UserInterfaceStateType ;
/**** Values *****/
#define     UI_IDLE               0x00u
#define     UI_GET_RESPONSE       0x01u
#define     UI_ACCEPT_UPDATE      0x02u
#define     UI_REJECT_UPDATE      0x03u
#define     UI_DOWNLOADING        0x04u
#define     UI_INSTALLING         0x05u
#define     UI_END_STATE          0x06u

/********** Cursor state  ***********/
typedef    uint8    UiCursorStateType ;
/**** Values *****/
#define    UI_CURSOR_AT_ACCEPT   0x01u
#define    UI_CURSOR_AT_REJECT   0x02u




/**************************************************************************/
/*                         Private Macros                                 */
/**************************************************************************/
/******* TFT *****/
#define     UI_BACKGROUND_COLOR   TFT_BLUE
#define     UI_BORDER_COLOR       TFT_GREEN
#define     UI_SCREEN_WIDTH      128
#define     UI_SCREEN_HIGHT      160
#define     UI_BORDER_WIDTH      8

#define     UI_FIRST_LINE_X      10 
#define     UI_SECOND_LINE_X     40 
#define     UI_THIRD_LINE_X      80
#define     UI_FOURTH_LINE_X     120

#define     UI_FIRST_ROW_Y       10
#define     UI_SECOND_ROW_Y      30
#define     UI_THIRD_ROW_Y       60
#define     UI_FOURTH_ROW_Y      90

#define     UI_TEXT_COLOR      TFT_RED
#define     UI_MAIN_TEXT_SIZE       3 
#define     UI_SECONARY_TEXT_SIZE   2 

/***** Buttons *****/
#define      BUTTON_TASK_PERIOD    20
#define      BUTTON_SWIPE_ID       0x01u
#define      BUTTON_OK_ID          0x00u


#define    WAIT_TIME_AFTER_DONE  2000 
/**************************************************************************/
/*                 Private Functions proto types                           */
/**************************************************************************/
static void Interface_IdleScreen (void);
static void Interface_CleanScrean(void);
static void Interface_GetResponseScreen (void);
static void Interface_DownloadingScreen (void);
static void Interface_UpdateDownloadingScreen (uint8 Cpy_Progress);
static void Interface_DoneScreen (void);

static void Interface_ProcessSwipeButton (void);
static void Interface_ProcessOkButton (void);

#endif
