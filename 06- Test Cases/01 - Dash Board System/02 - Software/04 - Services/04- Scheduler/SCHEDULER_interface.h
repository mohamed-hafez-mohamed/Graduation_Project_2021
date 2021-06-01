/****************************************************************************
* Title                 :   SCHEDULER   
* Filename              :   SCHEDULER_interface.h
* Author                :   Mohamed Hafez
* Origin Date           :   10/08/2020
* Version               :   1.0.0
* Compiler              :   TODO: COMPILER GOES HERE
* Target                :   TODO: MCU GOES HERE
* Notes                 :   None
*
*****************************************************************************/
/****************************************************************************
* Doxygen C Template 
*
*****************************************************************************/
/*************** INTERFACE CHANGE LIST **************************************
*
*    Date    Version   Author          Description 
*  10/8/20   1.0.0   Mohamed Hafez   Interface Created.
*
*****************************************************************************/
/** @file  SCHEDULER_interface.h
 *  @brief This module TODO: WHAT DO I DO?
 * 
 *  This is the header file for the definition TODO: MORE ABOUT ME!
 */
//TODO: UPDATE MACRO BELOW
#ifndef SCHEDULER_INTERFACE_H_
#define SCHEDULER_INTERFACE_H_

/******************************************************************************
* Includes
*******************************************************************************/
#include "BIT_MATH.h"
#include "Std_Types.h"
/******************************************************************************
* Preprocessor Constants
*******************************************************************************/

/******************************************************************************
* Configuration Constants
*******************************************************************************/

/******************************************************************************
* Macros
*******************************************************************************/
	
/******************************************************************************
* Typedefs
*******************************************************************************/

typedef void (*ptr_TaskCode)(void *);

/*Task States*/
typedef enum
{
    SCHEDULER_TASK_STATE_DORMANT          = 0,
    SCHEDULER_TASK_STATE_READY,
    SCHEDULER_TASK_STATE_READY_TO_RUN,
    SCHEDULER_TASK_STATE_RUNNING,
    SCHEDULER_TASK_STATE_SUSPENDED
}Task_States_t;

/*!<Task Structure*/
typedef struct
{
   uint8          TASK_u8Priority;
   uint16         Task_u16ReleaseTime;
   uint16         Task_u16Period;
   Task_States_t  Task_u8State;
   uint8          Task_CooperativeFlag;
   ptr_TaskCode   Task_PtrCode;
   void    *      Task_PtrVoidParameter;
}Task_t;

typedef Task_t* PtrStructTask_QueueENTRY;

/*!<Queue Definitions*/
typedef struct queuenode
{
    PtrStructTask_QueueENTRY  QueueNode_Entry;
    struct queuenode        * QueueNode_Next;
}QueueNode_t;

typedef struct Queue
{
    QueueNode_t * Queue_Front;
    QueueNode_t * Queue_Rear;
    uint8         Queue_Size;
}Queue_t;

/******************************************************************************
* Variables
*******************************************************************************/

/******************************************************************************
* Function Prototypes
*******************************************************************************/

uint8  SCHEDULER_u8CreateTask(uint8 Copy_u8Priority, uint16 Copy_u16ReleaseTime, uint16 Copy_u16Period, uint8 Copy_u8CoopFlag, ptr_TaskCode Copy_PtrTaskCode, void * Copy_PtrTaskParameter);
void SCHEDULER_voidInitScheduler(Queue_t * Copy_PtrQueue);
void SCHEDULER_voidStartScheduler(void);
uint8  SCHEDULER_u8AddTask(PtrStructTask_QueueENTRY  Copy_PtrQueueEntry,Queue_t * Copy_PtrQueue);
void SCHEDULER_voidUpdateScheduler(void * Copy_voidPtrQueue);
void SCHEDULER_voidDispatchTasks(Queue_t * Copy_PtrQueue);
void SCHEDULER_voidSuspendTask(uint8 Copy_u8TaskPosition,Queue_t * Copy_PtrQueue);
void SCHEDULER_voidResumeTask(uint8 Copy_u8TaskPosition,Queue_t * Copy_PtrQueue);
void SCHEDULER_voidServeTask(PtrStructTask_QueueENTRY * Copy_PtrQueueEntry, Queue_t * Copy_PtrQueue);
void SCHEDULER_voidDeleteTask(uint8 Copy_u8TaskPosition,Queue_t * Copy_PtrQueue);
void SCHEDULER_voidServeDleteTask(PtrStructTask_QueueENTRY * Copy_PtrQueueEntry, Queue_t * Copy_PtrQueue);
void SCHEDULER_voidReplaceTask(uint8 Copy_u8TaskPosition, PtrStructTask_QueueENTRY * Copy_PtrQueueEntry, Queue_t * Copy_PtrQueue);
uint8  SCHEDULER_u8IsQueueEmpty(Queue_t * Copy_PtrQueue);
uint8  SCHEDULER_u8IsQueueFull(Queue_t * Copy_PtrQueue);
uint8  SCHEDULER_u8QueueSize(Queue_t * Copy_PtrQueue);
void SCHEDULER_voidClearQueue(Queue_t * Copy_PtrQueue);
void SCHEDULER_voidTraverseQueue(Queue_t * Copy_PtrQueue, void (*PF)(PtrStructTask_QueueENTRY Copy_QueueEntry));


#endif /*File_H_*/

/*** End of File **************************************************************/
