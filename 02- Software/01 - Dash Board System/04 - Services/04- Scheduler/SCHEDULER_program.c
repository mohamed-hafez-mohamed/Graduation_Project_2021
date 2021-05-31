/*******************************************************************************
* Title                 :   SCHEDULER 
* Filename              :   SCHEDULER_program.c
* Author                :   Mohamed Hafez
* Origin Date           :   10/8/2020
* Version               :   1.0.0
* Compiler              :   TODO: COMPILER GOES HERE
* Target                :   TODO: MCU GOES HERE
* Notes                 :   None 
*
*****************************************************************************/
/*************** SOURCE REVISION LOG *****************************************
*
*    Date    Version   Author          Description 
*  04/08/20   1.0.0   Mohamed Hafez   Initial Release.
*
*******************************************************************************/
/** @file SCHEDULER_program.c
 *  @brief This is the source file for TODO: WHAT DO I DO? 
 */
/******************************************************************************
* Includes
*******************************************************************************/	

#include "BIT_MATH.h"
#include "Std_Types.h"
#include <stdlib.h>
#include "STK_interface.h"
#include "SCHEDULER_interface.h"
#include "SCHEDULER_config.h"
#include "SCHEDULER_private.h"

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
Queue_t ReadyQueue;
/******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************
* Function Definitions
*******************************************************************************/

void SCHEDULER_voidInitScheduler(Queue_t * Copy_PtrQueue)
{
    Copy_PtrQueue->Queue_Front = NULL;
    Copy_PtrQueue->Queue_Rear  = NULL;
    Copy_PtrQueue->Queue_Size  = 0;
	MSTK_voidSetIntervalPeriodic_ms(1, &SCHEDULER_voidUpdateScheduler, (void *)(&ReadyQueue)); 
}

void SCHEDULER_voidStartScheduler(void)
{
	//!<TODO: Enable Global Interrupt
}

uint8 SCHEDULER_u8AddTask(PtrStructTask_QueueENTRY  Copy_PtrQueueEntry,Queue_t * Copy_PtrQueue)
{
    QueueNode_t  * Local_PtrQueueNode = (QueueNode_t *)malloc(sizeof(QueueNode_t));
    if(! Local_PtrQueueNode)
    {
      return 0;
    }
    else
    {
      Local_PtrQueueNode->QueueNode_Entry = Copy_PtrQueueEntry;
      Local_PtrQueueNode->QueueNode_Next  = NULL;
      if(!Copy_PtrQueue->Queue_Rear)
      {
          Copy_PtrQueue->Queue_Front = Local_PtrQueueNode;
      }
      else
      {
          Copy_PtrQueue->Queue_Rear->QueueNode_Next = Local_PtrQueueNode;
      }
      Copy_PtrQueue->Queue_Rear = Local_PtrQueueNode;
      Copy_PtrQueue->Queue_Size++;
      return 1;
    }
}

uint8  SCHEDULER_u8CreateTask(uint8 Copy_u8Priority, uint16 Copy_u16ReleaseTime, uint16 Copy_u16Period, uint8 Copy_u8CoopFlag, ptr_TaskCode Copy_PtrTaskCode, void * Copy_PtrTaskParameter)
{
    PtrStructTask_QueueENTRY Task = (PtrStructTask_QueueENTRY)malloc(sizeof(Task_t));
    Task->TASK_u8Priority         = Copy_u8Priority;
    Task->Task_u16ReleaseTime     = Copy_u16ReleaseTime;
    Task->Task_u16Period          = Copy_u16Period;
    Task->Task_u8State            = SCHEDULER_TASK_STATE_DORMANT;
    Task->Task_CooperativeFlag    = Copy_u8CoopFlag;
    Task->Task_PtrCode            = Copy_PtrTaskCode;
    Task->Task_PtrVoidParameter   = Copy_PtrTaskParameter;
    SCHEDULER_u8AddTask(Task, &ReadyQueue);
	//!<TODO: Return Status
}

/*This function will be invocked inside tin timer overflow ISR*/
void SCHEDULER_voidUpdateScheduler(void * Copy_voidPtrQueue)
{
	Queue_t * Copy_PtrQueue = (Queue_t *)Copy_voidPtrQueue;
    QueueNode_t *Local_PtrQueueNode;
    uint8 Local_u8TaskPosition = 0;
    for(Local_PtrQueueNode = Copy_PtrQueue -> Queue_Front;Local_PtrQueueNode;Local_PtrQueueNode = Local_PtrQueueNode -> QueueNode_Next)
    {
        /*!<Check if there is a task at this location*/
        if(Local_PtrQueueNode->QueueNode_Entry->Task_PtrCode)
        {
            if(Local_PtrQueueNode->QueueNode_Entry->Task_u16ReleaseTime == SCHEDULER_TASK_READY_TO_RUN)
            {
               /*!<Check The Task, Is it Cooperative or Preemptive*/
                if(Local_PtrQueueNode->QueueNode_Entry->Task_CooperativeFlag)
                {
                    /*!<The task is ready to run*/
                    Local_PtrQueueNode->QueueNode_Entry->Task_u8State = SCHEDULER_TASK_STATE_READY_TO_RUN;
                }
                else
                {
                    /*!<Run the Preemptive Task Immediately */
                    Local_PtrQueueNode->QueueNode_Entry->Task_PtrCode(Local_PtrQueueNode->QueueNode_Entry->Task_PtrVoidParameter); 
                    Local_PtrQueueNode->QueueNode_Entry->Task_u8State = SCHEDULER_TASK_STATE_READY;                                                           
                    /*!<Periodic tasks will automatically run again*/
                    /*!<if this is a 'one shot' task, remove it from the array*/
                    if(Local_PtrQueueNode->QueueNode_Entry->Task_u16Period == SCHEDULER_ONE_SHOT_TASK)
                    {
                        SCHEDULER_voidDeleteTask(Local_u8TaskPosition,Copy_PtrQueue);
                    }
                }
                
               if(Local_PtrQueueNode->QueueNode_Entry->Task_u16Period)
               {
                    /*!<Schedule periodic tasks to run again*/
                    Local_PtrQueueNode->QueueNode_Entry->Task_u16ReleaseTime = Local_PtrQueueNode->QueueNode_Entry->Task_u16Period;
               }
            }
            else
            {
                /*!<Not yet ready to run: just decrement the delay*/
                Local_PtrQueueNode->QueueNode_Entry->Task_u16ReleaseTime -= 1;
            }
        }
        Local_u8TaskPosition++;
    }
}

void SCHEDULER_voidSuspendTask(uint8 Copy_u8TaskPosition,Queue_t * Copy_PtrQueue)
{
    uint8 Local_u8Counter;
    QueueNode_t * Local_PtrQueueNode;
    if(Copy_u8TaskPosition == 0)
    {
        Copy_PtrQueue->Queue_Front->QueueNode_Entry->Task_u8State = SCHEDULER_TASK_STATE_SUSPENDED;
    }
    else if(Copy_u8TaskPosition > 0)
    {
        for(Local_PtrQueueNode = Copy_PtrQueue->Queue_Front,Local_u8Counter = 0;Local_u8Counter < Copy_u8TaskPosition - 1;Local_u8Counter++)
       {
           Local_PtrQueueNode = Local_PtrQueueNode->QueueNode_Next;
       }
       
       Local_PtrQueueNode->QueueNode_Next->QueueNode_Entry->Task_u8State = SCHEDULER_TASK_STATE_SUSPENDED;
    }
    else
    {
        //!<TODO: Error Code
    }

}

void SCHEDULER_voidResumeTask(uint8 Copy_u8TaskPosition,Queue_t * Copy_PtrQueue)
{
    uint8 Local_u8Counter;
    QueueNode_t * Local_PtrQueueNode;
    if(Copy_u8TaskPosition == 0)
    {
        Copy_PtrQueue->Queue_Front->QueueNode_Entry->Task_u8State = SCHEDULER_TASK_STATE_READY;
    }
    else if(Copy_u8TaskPosition > 0)
    {
        for(Local_PtrQueueNode = Copy_PtrQueue->Queue_Front,Local_u8Counter = 0;Local_u8Counter < Copy_u8TaskPosition - 1;Local_u8Counter++)
       {
           Local_PtrQueueNode = Local_PtrQueueNode->QueueNode_Next;
       }
       
       Local_PtrQueueNode->QueueNode_Next->QueueNode_Entry->Task_u8State = SCHEDULER_TASK_STATE_READY;
    }
    else
    {
        //!<TODO: Error Code
    }
}

void SCHEDULER_voidServeTask(PtrStructTask_QueueENTRY * Copy_PtrQueueEntry, Queue_t * Copy_PtrQueue)
{
    QueueNode_t * Local_PtrQueueNode = Copy_PtrQueue->Queue_Front;
    *Copy_PtrQueueEntry = Local_PtrQueueNode->QueueNode_Entry;
    if(!Copy_PtrQueue->Queue_Front)
    {
        Copy_PtrQueue->Queue_Rear = NULL;
    }
}

void SCHEDULER_voidServeDleteTask(PtrStructTask_QueueENTRY * Copy_PtrQueueEntry, Queue_t * Copy_PtrQueue)
{
    QueueNode_t *Local_PtrQueueNode = Copy_PtrQueue->Queue_Front;
    *Copy_PtrQueueEntry = Local_PtrQueueNode->QueueNode_Entry;
    Copy_PtrQueue->Queue_Front = Local_PtrQueueNode->QueueNode_Next;
    free(Local_PtrQueueNode->QueueNode_Entry);
    free(Local_PtrQueueNode);
    if(!Copy_PtrQueue->Queue_Front)
    {
        Copy_PtrQueue->Queue_Rear = NULL;
    }
    Copy_PtrQueue->Queue_Size--;
}

void SCHEDULER_voidDeleteTask(uint8 Copy_u8TaskPosition,Queue_t * Copy_PtrQueue)
{
    uint8 Local_u8Counter;
    QueueNode_t * Local_PtrQueueNodeTemp;
    QueueNode_t * Local_PtrQueueNode;
    if(Copy_u8TaskPosition == 0)
    {
        Local_PtrQueueNodeTemp = Copy_PtrQueue->Queue_Front->QueueNode_Next;
        free(Copy_PtrQueue->Queue_Front->QueueNode_Entry);
        free(Copy_PtrQueue->Queue_Front);
        Copy_PtrQueue->Queue_Front = Local_PtrQueueNodeTemp;
    }
    else
    {
       for(Local_PtrQueueNode = Copy_PtrQueue->Queue_Front,Local_u8Counter = 0;Local_u8Counter < Copy_u8TaskPosition - 1;Local_u8Counter++)
       {
           Local_PtrQueueNode = Local_PtrQueueNode->QueueNode_Next;
       }
       Local_PtrQueueNodeTemp = Local_PtrQueueNode->QueueNode_Next->QueueNode_Next;
       free(Local_PtrQueueNode->QueueNode_Next->QueueNode_Entry);
       free(Local_PtrQueueNode->QueueNode_Next);
       Local_PtrQueueNode->QueueNode_Next = Local_PtrQueueNodeTemp;
    }
    Copy_PtrQueue->Queue_Size--;
}

void SCHEDULER_voidReplaceTask(uint8 Copy_u8TaskPosition, PtrStructTask_QueueENTRY * Copy_PtrQueueEntry, Queue_t * Copy_PtrQueue)
{
    uint8 Local_u8Counter;
    QueueNode_t * Local_PtrQueueNode;
    if(Copy_u8TaskPosition == 0)
    {
        Copy_PtrQueue->Queue_Front->QueueNode_Entry = *Copy_PtrQueueEntry;
    }
    else
    {
        for(Local_PtrQueueNode = Copy_PtrQueue->Queue_Front, Local_u8Counter = 0;Local_u8Counter < Copy_u8TaskPosition;Local_u8Counter++)
       {
           Local_PtrQueueNode = Local_PtrQueueNode->QueueNode_Next;
       }
       Local_PtrQueueNode->QueueNode_Entry = *Copy_PtrQueueEntry;
    }

}

uint8  SCHEDULER_u8IsQueueEmpty(Queue_t * Copy_PtrQueue)
{
    return !Copy_PtrQueue->Queue_Size;
}

uint8  SCHEDULER_u8IsQueueFull(Queue_t * Copy_PtrQueue)
{
    return 0;
}

uint8  SCHEDULER_u8QueueSize(Queue_t * Copy_PtrQueue)
{
    return Copy_PtrQueue->Queue_Size;
}


void SCHEDULER_voidClearQueue(Queue_t * Copy_PtrQueue)
{
    while(Copy_PtrQueue->Queue_Front)
    {
        Copy_PtrQueue->Queue_Rear = Copy_PtrQueue->Queue_Front->QueueNode_Next;
        free(Copy_PtrQueue -> Queue_Front);
        Copy_PtrQueue->Queue_Front = Copy_PtrQueue->Queue_Rear;
    }
    Copy_PtrQueue->Queue_Size = 0;
}

void SCHEDULER_voidTraverseQueue(Queue_t * Copy_PtrQueue, void (*PF)(PtrStructTask_QueueENTRY))
{
    QueueNode_t *Local_PtrQueueNode;
    for(Local_PtrQueueNode = Copy_PtrQueue -> Queue_Front;Local_PtrQueueNode;Local_PtrQueueNode = Local_PtrQueueNode -> QueueNode_Next)
    {
        (*PF)(Local_PtrQueueNode -> QueueNode_Entry);
    }
}

/*!<Dispatch function*/
void SCHEDULER_voidDispatchTasks(Queue_t * Copy_PtrQueue)
{
    QueueNode_t *Local_PtrQueueNode;
    uint8 Local_u8TaskPosition = 0;
    for(Local_PtrQueueNode = Copy_PtrQueue -> Queue_Front;Local_PtrQueueNode;Local_PtrQueueNode = Local_PtrQueueNode -> QueueNode_Next)
    {
        if(Local_PtrQueueNode->QueueNode_Entry->Task_u8State == SCHEDULER_TASK_STATE_READY_TO_RUN)
        {
            Local_PtrQueueNode->QueueNode_Entry->Task_u8State = SCHEDULER_TASK_STATE_RUNNING;
            /*!<Run the task */
            Local_PtrQueueNode->QueueNode_Entry->Task_PtrCode(Local_PtrQueueNode->QueueNode_Entry->Task_PtrVoidParameter);        
            Local_PtrQueueNode->QueueNode_Entry->Task_u8State = SCHEDULER_TASK_STATE_READY;                                                           
            /*!<Periodic tasks will automatically run again*/
            /*!<if this is a 'one shot' task, remove it from the array*/
            if(Local_PtrQueueNode->QueueNode_Entry->Task_u16Period == SCHEDULER_ONE_SHOT_TASK)
            {
                SCHEDULER_voidDeleteTask(Local_u8TaskPosition,Copy_PtrQueue);
            }
        }
        Local_u8TaskPosition++;
    }
    /*!<Report system status*/
    //SCH_Report_Status();
    /*!<The scheduler enters idle mode at this point*/
    //SCH_Go_To_Sleep();
}


/*************** END OF FUNCTIONS ***************************************************************************/
