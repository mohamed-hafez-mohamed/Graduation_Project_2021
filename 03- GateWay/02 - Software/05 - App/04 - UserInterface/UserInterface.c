/*****************************************************/
 /* Author      : Mosad                              */
 /* Version     : v01                                */
 /* date        : 6/5/2020                           */
/*****************************************************/
/* Library includes */
#include "BIT_MATH.h"
#include "Std_Types.h"
#include "Rte_UserInterfacePort.h"

/* Module includes */
#include "UserInterface_Interface.h"
#include "UserInterface_Cfg.h"
#include "UserInterface_Private.h"

/**************************************************************************/
/*                         Global Variables                              */
/**************************************************************************/
static UserInterfaceStateType Global_UiInternalState ;
static SystemStateType Global_SystemState ;
static UiCursorStateType Global_CursorState ;
static ButtonStateType Global_SwipeButtonState ;
static ButtonStateType Global_OkButtonState ;
static uint8 Global_DownloadProgress ;

/**************************************************************************/
/*                         Module Functions                               */
/**************************************************************************/

void UserInterface_voidInit(void)
{
	/* Init Variables */
	Global_UiInternalState = UI_IDLE ;
	Global_CursorState = UI_CURSOR_AT_ACCEPT ;
	Global_SwipeButtonState = RELEASED ;
	Global_OkButtonState = RELEASED ;
	Global_DownloadProgress = 0 ;
	/* Init Screan */
	Interface_IdleScreen();
}


void UserInterface_MainFunction (void)
{
	switch (Global_UiInternalState)
	{
		/*****************************UI_IDLE***********************************/
		case UI_IDLE :
		{
			Std_ReturnType Local_Error = RTE_READ_SYSTEM_STATE(&Global_SystemState);
			if (E_OK == Local_Error)
			{
				if (SYS_NEW_UPDATE_REQ == Global_SystemState)
				{
					/* Clear Screen first before writing*/
					Interface_CleanScrean();
					/* Init Get Response scereen */
					Interface_GetResponseScreen();
					/* Init Button Task */
					STK_voidSetIntervalPeriodic(BUTTON_TASK_PERIOD , TIME_MS , Button_MainFunction);
					/* Change internal state */
					Global_UiInternalState = UI_GET_RESPONSE ;
				}
				else
				{
					/* Stay in UI_IDLE state otherwise */
				}
			}
			else 
			{
				/* Error */
			}
			break;
		}
		
		/*****************************UI_GET_RESPONSE ***********************************/
		case UI_GET_RESPONSE :
		{
			Std_ReturnType Local_ErrorSwipeButton ; 
			Std_ReturnType Local_ErrorOkButton ;
			Local_ErrorSwipeButton = Button_GetState(BUTTON_SWIPE_ID , &Global_SwipeButtonState) ;
			Local_ErrorOkButton = Button_GetState(BUTTON_OK_ID , &Global_OkButtonState) ;
			if ((E_OK == Local_ErrorSwipeButton) && (E_OK == Local_ErrorOkButton))
			{
				Interface_ProcessSwipeButton();
				Interface_ProcessOkButton();
			}
			else
			{
				/* Report Error */
			}
			
			break;
		}
		
		/*****************************UI_ACCEPT_UPDATE***********************************/
		case UI_ACCEPT_UPDATE :
		{
			/* Clear Screan */
			Interface_CleanScrean();
			/* Init Download Screen */
			Interface_DownloadingScreen();
			
			/* Update user response */
			RTE_WRITE_USER_RESPONSE (ACCEPT_UPDATE);
			/* Update system state */
			RTE_WRITE_SYSTEM_STATE(SYS_REC_UPDATE);
			
			/* Update Internal state */
			Global_UiInternalState = UI_DOWNLOADING ;
			break;
		}
		
		/*****************************UI_REJECT_UPDATE***********************************/
		case UI_REJECT_UPDATE : 
		{
			/* Clear Screan */
			Interface_CleanScrean();
			
			/* Update user response */
			RTE_WRITE_USER_RESPONSE (REFUSE_UPDATE);
			/* Update system state */
			RTE_WRITE_SYSTEM_STATE(SYS_REC_UPDATE);
			
			/* Reinit vaiables */
			Global_UiInternalState = UI_IDLE ;
			Global_CursorState = UI_CURSOR_AT_ACCEPT ;
			Global_SwipeButtonState = RELEASED ;
			Global_OkButtonState = RELEASED ;
			Interface_IdleScreen();
			
			break;
		}
		
		/*****************************UI_DOWNLOADING***********************************/
		case UI_DOWNLOADING : 
		{
			Std_ReturnType Local_Error ;
			Local_Error = RTE_READ_DOWNLOAD_PROGRESS(&Global_DownloadProgress);
			
			if (E_OK == Local_Error)
			{
				Interface_UpdateDownloadingScreen(Global_DownloadProgress);
				if (100 == Global_DownloadProgress)
				{
					/* Clear Screan */
					Interface_CleanScrean();
					
					/* Update Screan */
					TFT_voidPrintText("Install" , UI_FIRST_ROW_Y ,UI_SECOND_LINE_X , UI_SECONARY_TEXT_SIZE ,UI_TEXT_COLOR ,UI_BACKGROUND_COLOR );
					/* Update internal state */
					Global_UiInternalState = UI_INSTALLING ;
				}
				else
				{
					
				}
			}
			else if (E_NOT_OK == Local_Error)
			{
				/* Report Error*/
			}
			else
			{
				
			}
			break;
		}
		
		/*****************************UI_INSTALLING***********************************/
		case UI_INSTALLING : 
		{
			Std_ReturnType Local_Error = RTE_READ_SYSTEM_STATE(&Global_SystemState);
			if (E_OK == Local_Error)
			{
				if (SYS_DONE_UPDATE == Global_SystemState)
				{
					/* CleanScrean*/
					Interface_CleanScrean();
					/* Update screan*/
					Interface_DoneScreen();
					/* Wait for a time */
					STK_voidSetBusyWait(WAIT_TIME_AFTER_DONE , TIME_MS);
					/* Update internal state */
					Global_UiInternalState = UI_END_STATE ;
					
				}
				
				else
				{
					
				}
			}
			else
			{
				/* Report error*/
			}
			break;
		}
		
		/*****************************UI_END_STATE***********************************/
		case UI_END_STATE : 
		{
			/* Reinit vaiables */
			Global_UiInternalState = UI_IDLE ;
			Global_CursorState = UI_CURSOR_AT_ACCEPT ;
			Global_SwipeButtonState = RELEASED ;
			Global_OkButtonState = RELEASED ;
			Global_DownloadProgress = 0 ;
			
			/* Update screen */
			Interface_IdleScreen();
			
			/* Return system state to idle */
			RTE_WRITE_SYSTEM_STATE(SYS_IDLE);
			break;
		}
		/*****************************DEFUALT (ERROR)***********************************/
		default :
			/* Error */
			break ;
	}
}

/**************************************************************************/
/*                        Private Functions                               */
/**************************************************************************/
static void Interface_IdleScreen (void)
{
	/* Set Backgroun color */
	TFT_voidFillDisplay(UI_BACKGROUND_COLOR);
	/* SetBorder */
	TFT_voidDrawRectangle(0 , 0 , UI_BORDER_WIDTH , UI_SCREEN_HIGHT , UI_BORDER_COLOR);
	TFT_voidDrawRectangle(0 , 0 , UI_SCREEN_WIDTH , UI_BORDER_WIDTH , UI_BORDER_COLOR);
	TFT_voidDrawRectangle((UI_SCREEN_WIDTH - UI_BORDER_WIDTH) , 0 , UI_BORDER_WIDTH , UI_SCREEN_HIGHT , UI_BORDER_COLOR);
	TFT_voidDrawRectangle(0 , (UI_SCREEN_HIGHT - UI_BORDER_WIDTH) , UI_SCREEN_WIDTH , UI_BORDER_WIDTH , UI_BORDER_COLOR);

	/* Writeing Text */
	TFT_voidPrintText("Hello>" , UI_FIRST_ROW_Y ,UI_FIRST_LINE_X , UI_MAIN_TEXT_SIZE ,UI_TEXT_COLOR ,UI_BACKGROUND_COLOR );
	TFT_voidPrintText("Wait" , UI_SECOND_ROW_Y ,UI_SECOND_LINE_X , UI_MAIN_TEXT_SIZE ,UI_TEXT_COLOR ,UI_BACKGROUND_COLOR );
	TFT_voidPrintText("Update" , UI_FIRST_ROW_Y ,UI_THIRD_LINE_X , UI_MAIN_TEXT_SIZE ,UI_TEXT_COLOR ,UI_BACKGROUND_COLOR );
}


static void Interface_GetResponseScreen (void)
{
	/* Writeing Text */
	TFT_voidPrintText("New>" , UI_SECOND_ROW_Y ,UI_FIRST_LINE_X , UI_MAIN_TEXT_SIZE ,UI_TEXT_COLOR ,UI_BACKGROUND_COLOR );
	TFT_voidPrintText("Update" , UI_FIRST_ROW_Y ,UI_SECOND_LINE_X , UI_MAIN_TEXT_SIZE ,UI_TEXT_COLOR ,UI_BACKGROUND_COLOR );
	TFT_voidPrintText(">" , UI_FIRST_ROW_Y ,UI_THIRD_LINE_X , UI_MAIN_TEXT_SIZE ,UI_TEXT_COLOR ,UI_BACKGROUND_COLOR );
	TFT_voidPrintText("Accept" , UI_SECOND_ROW_Y ,UI_THIRD_LINE_X , UI_SECONARY_TEXT_SIZE ,UI_TEXT_COLOR ,UI_BACKGROUND_COLOR );
	TFT_voidPrintText("Reject" , UI_SECOND_ROW_Y ,UI_FOURTH_LINE_X , UI_SECONARY_TEXT_SIZE ,UI_TEXT_COLOR ,UI_BACKGROUND_COLOR );
}

static void Interface_DownloadingScreen (void)
{
	/* Writeing Text */
	TFT_voidPrintText("Download" , UI_FIRST_ROW_Y ,UI_FIRST_LINE_X , UI_SECONARY_TEXT_SIZE ,UI_TEXT_COLOR ,UI_BACKGROUND_COLOR );
	TFT_voidPrintText("  in" , UI_FIRST_ROW_Y ,UI_SECOND_LINE_X , UI_SECONARY_TEXT_SIZE ,UI_TEXT_COLOR ,UI_BACKGROUND_COLOR );
	TFT_voidPrintText("Progress" , UI_FIRST_ROW_Y ,UI_THIRD_LINE_X , UI_SECONARY_TEXT_SIZE ,UI_TEXT_COLOR ,UI_BACKGROUND_COLOR );
	TFT_voidPrintText("  0%" , UI_SECOND_ROW_Y ,UI_FOURTH_LINE_X , UI_MAIN_TEXT_SIZE ,UI_TEXT_COLOR ,UI_BACKGROUND_COLOR );
}

static void Interface_UpdateDownloadingScreen (uint8 Cpy_Progress)
{
	/**/
	sint8 loacl_DateBuffer[4];
	/* Clear Current Progress Text */
	TFT_voidPrintText("   " , UI_SECOND_ROW_Y ,UI_FOURTH_LINE_X , UI_MAIN_TEXT_SIZE ,UI_TEXT_COLOR ,UI_BACKGROUND_COLOR );
	sprintf(loacl_DateBuffer, "%.3i", Cpy_Progress);
	TFT_voidPrintText(loacl_DateBuffer , UI_SECOND_ROW_Y ,UI_FOURTH_LINE_X , UI_MAIN_TEXT_SIZE ,UI_TEXT_COLOR ,UI_BACKGROUND_COLOR );
}

static void Interface_DoneScreen (void)
{
	/* Writeing Text */
	TFT_voidPrintText("Done" , UI_FIRST_ROW_Y ,UI_FIRST_LINE_X , UI_SECONARY_TEXT_SIZE ,UI_TEXT_COLOR ,UI_BACKGROUND_COLOR );
	TFT_voidPrintText("Install" , UI_FIRST_ROW_Y ,UI_SECOND_LINE_X , UI_SECONARY_TEXT_SIZE ,UI_TEXT_COLOR ,UI_BACKGROUND_COLOR );
	TFT_voidPrintText("^_^" , UI_SECOND_ROW_Y ,UI_THIRD_LINE_X , UI_MAIN_TEXT_SIZE ,UI_TEXT_COLOR ,UI_BACKGROUND_COLOR );
}

static void Interface_CleanScrean(void)
{
	TFT_voidDrawRectangle(9 , 9 , 112 , 144 , UI_BACKGROUND_COLOR);
}

static void Interface_ProcessSwipeButton (void)
{
	if (PRESSED == Global_SwipeButtonState)
	{
		switch (Global_CursorState)
		{
			case UI_CURSOR_AT_ACCEPT : 
				/* Delete cursor from the current option */
				TFT_voidPrintText(" " , UI_FIRST_ROW_Y ,UI_THIRD_LINE_X , UI_MAIN_TEXT_SIZE ,UI_TEXT_COLOR ,UI_BACKGROUND_COLOR );
				
				/* Put the cursor at the next option */
				TFT_voidPrintText(">" , UI_FIRST_ROW_Y ,UI_FOURTH_LINE_X , UI_MAIN_TEXT_SIZE ,UI_TEXT_COLOR ,UI_BACKGROUND_COLOR );
				
				/* Update cursor state */
				Global_CursorState = UI_CURSOR_AT_REJECT ;
				break ;
			
			case UI_CURSOR_AT_REJECT :
				/* Delete cursor from the current option */
				TFT_voidPrintText(" " , UI_FIRST_ROW_Y ,UI_FOURTH_LINE_X , UI_MAIN_TEXT_SIZE ,UI_TEXT_COLOR ,UI_BACKGROUND_COLOR );
				
				/* Put the cursor at the next option */
				TFT_voidPrintText(">" , UI_FIRST_ROW_Y ,UI_THIRD_LINE_X , UI_MAIN_TEXT_SIZE ,UI_TEXT_COLOR ,UI_BACKGROUND_COLOR );
				
				/* Update cursor state */
				Global_CursorState = UI_CURSOR_AT_ACCEPT ;
				
				break ;
		}
	}
	else 
	{
		/*Do Nothing */
	}
}

static void Interface_ProcessOkButton (void)
{
	if (PRESSED == Global_OkButtonState)
	{
		switch (Global_CursorState)
		{
			case UI_CURSOR_AT_ACCEPT : 
				/* Update System State */
				Global_UiInternalState = UI_ACCEPT_UPDATE ;
				break ;
			
			case UI_CURSOR_AT_REJECT :
				Global_UiInternalState = UI_REJECT_UPDATE ;
				break ;
		}
		/* Stop Button Task */
		STK_voidStop();
		Button_voidInit();
	}
}



