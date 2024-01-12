/*
 * @LICENSE: This file has no copyright assigned and is placed in the Public Domain.
 * @AUTHOR: Riccardo Giovanni Gualiumi 2024
 * No Software Warranty. The Software and related documentation are provided “AS IS” and without any warranty of any kind and Seller EXPRESSLY DISCLAIMS ALL WARRANTIES, EXPRESS
 * OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include "Rick45B-AlgorithmsADT.h"

void destroy_createStackTEST();
void misc_StackTEST();
void error_StackQueueTEST();

int main()
{
    /*starting the library*/
    RICK45B_LibStart(malloc, free);

    /*list tests*/
    destroy_createStackTEST();
    printf("\n***destroy_createTreesTEST successful***\n\n");
    misc_StackTEST();
    printf("\n***misc_StackTEST successful***\n\n");
    error_StackQueueTEST();
    printf("\n***error_StackQueueTEST successful***\n\n");
    printf("\n***All test were successful***\n\n");
    return 0;
}

void destroy_createStackTEST()
{
    /*create stack*/
    stack_t stack = NULL;
    stack = RICK45BSTACK_StackCreate((RICK45B_comparator_t)strcmp, 0);
    assert(stack!=NULL);
    assert(stack->head!=NULL);

    /*destroy stack*/
    RICK45BSTACK_StackDestroy(stack, 0);
}

void misc_StackTEST()
{
    char strings[4][100] = {"car", "caterpillar", "Dave", "truck"};
    char *mallocData = malloc(sizeof(char)*8);
    strcpy(mallocData, "Timothy");

    /*create stack*/
    stack_t stack = NULL;
    stack = RICK45BSTACK_StackCreate((RICK45B_comparator_t)strcmp, 0);
    assert(RICK45BSTACK_IsEmpty(stack)==1 && RICK45BSTACK_IsFull(stack)==0);
    assert(stack!=NULL);
    assert(stack->head!=NULL);

    /*pushing elements into stack*/
    assert(RICK45BSTACK_StackPush(stack, strings[1])==0);
    assert(RICK45BSTACK_StackPush(stack, strings[3])==0);
    assert(RICK45BSTACK_StackPush(stack, mallocData)==0);
    assert(RICK45BSTACK_StackPush(stack, strings[0])==0);
    assert(RICK45BSTACK_GetStackSize(stack)==4);
    assert(RICK45BSTACK_IsEmpty(stack)==0 && RICK45BSTACK_IsFull(stack)==0);

    /*testing top / pop / boolean functions*/
    assert(RICK45BSTACK_IsTop(stack, mallocData)==0);
    assert(RICK45BSTACK_IsTop(stack, strings[0])==1);
    assert(strcmp(RICK45BSTACK_StackTop(stack), strings[0])==0);
    assert(RICK45BSTACK_ContainedInStack(stack, strings[3])==1);
    assert(RICK45BSTACK_ContainedInStack(stack, mallocData)==1);
    assert(strcmp(RICK45BSTACK_StackPop(stack), "car")==0);
    assert(strcmp(RICK45BSTACK_StackTop(stack), mallocData)==0);
    assert(strcmp(RICK45BSTACK_StackPop(stack), mallocData)==0);
    assert(strcmp(RICK45BSTACK_StackPop(stack), strings[3])==0);
    assert(strcmp(RICK45BSTACK_StackTop(stack), strings[1])==0);
    assert(RICK45BSTACK_GetStackSize(stack)==1);
    assert(RICK45BSTACK_ContainedInStack(stack, strings[3])==0);
    assert(RICK45BSTACK_ContainedInStack(stack, mallocData)==0);
    assert(RICK45BSTACK_ContainedInStack(stack, strings[1])==1);

    assert(strcmp(RICK45BSTACK_StackTop(stack), strings[1])==0);
    assert(RICK45BSTACK_IsTop(stack, strings[1])==1);
    assert(strcmp(RICK45BSTACK_StackPop(stack), strings[1])==0);
    assert(RICK45BSTACK_GetStackSize(stack)==0);
    assert(RICK45BSTACK_IsTop(stack, strings[1])==0);
    assert(RICK45BSTACK_IsTop(stack, mallocData)==0);

    /*destroy stack*/
    free(mallocData);
    RICK45BSTACK_StackDestroy(stack, 0);

    /*testing stack with malloc'd values*/
    char *mallocData1 = malloc(sizeof(char)*100);
    char *mallocData2 = malloc(sizeof(char)*100);
    char *mallocData3 = malloc(sizeof(char)*100);
    char *mallocData4 = malloc(sizeof(char)*100);
    strcpy(mallocData1, "Blues");
    strcpy(mallocData2, "Water");
    strcpy(mallocData3, "Bike");
    strcpy(mallocData4, "Overflow");
    stack = RICK45BSTACK_StackCreate((RICK45B_comparator_t)strcmp, 3);
    assert(RICK45BSTACK_IsEmpty(stack)==1 && RICK45BSTACK_IsFull(stack)==0);

    assert(RICK45BSTACK_StackTop(stack)==NULL);
    assert(RICK45BSTACK_StackPop(stack)==NULL);
    RICK45BSTACK_StackPush(stack, mallocData1);
    RICK45BSTACK_StackPush(stack, mallocData2);
    RICK45BSTACK_StackPush(stack, mallocData3);
    assert(RICK45BSTACK_GetStackSize(stack)==3);
    assert(RICK45BSTACK_StackPush(stack, mallocData4)==-1 && strcmp("Cannot push element into stack: stack is full!", RICK45B_GetError())==0);
    assert(RICK45BSTACK_GetStackSize(stack)==3);  /*No data has been added!*/
    assert(RICK45BSTACK_IsEmpty(stack)==0 && RICK45BSTACK_IsFull(stack)==1);
    assert(strcmp(RICK45BSTACK_StackTop(stack), mallocData3)==0);
    assert(strcmp(RICK45BSTACK_StackTop(stack), mallocData1)!=0);
    assert(RICK45BSTACK_ContainedInStack(stack, mallocData2)==1);
    assert(strcmp(RICK45BSTACK_StackPop(stack), mallocData3)==0);
    assert(RICK45BSTACK_GetStackSize(stack)==2);
    assert(RICK45BSTACK_StackPush(stack, mallocData4)==0); /*since some space from the stack has been free'd, i can finally push mallocData4*/
    assert(RICK45BSTACK_GetStackSize(stack)==3);

    RICK45BSTACK_StackDestroy(stack, 1);
    free(mallocData3);
}

void error_StackQueueTEST()
{
    char strings[4][100] = {"car", "caterpillar", "Dave", "truck"};

    /*stack test*/
    stack_t stack = NULL;
    assert(RICK45BSTACK_StackCreate((RICK45B_comparator_t)NULL, 0)==NULL && strcmp("Invalid Argument: key_cmp function cannot be NULL!", RICK45B_GetError())==0);
    stack = RICK45BSTACK_StackCreate((RICK45B_comparator_t)strcmp, 2);

    assert(RICK45BSTACK_StackPush(NULL, strings[1])==-1 && strcmp("Invalid argument: stack cannot be NULL!", RICK45B_GetError())==0);
    assert(RICK45BSTACK_StackPush(stack, NULL)==-1 && strcmp("Invalid argument: key cannot be NULL!", RICK45B_GetError())==0);
    assert(RICK45BSTACK_IsEmpty(stack)==1 && RICK45BSTACK_IsFull(stack)==0);
    assert(RICK45BSTACK_StackPush(stack, strings[1])==0);
    assert(RICK45BSTACK_IsEmpty(stack)==0 && RICK45BSTACK_IsFull(stack)==0);

    assert(RICK45BSTACK_StackTop(NULL)==NULL && strcmp("Invalid argument: stack cannot be NULL!", RICK45B_GetError())==0);
    assert(RICK45BSTACK_StackPop(NULL)==NULL && strcmp("Invalid argument: stack cannot be NULL!", RICK45B_GetError())==0);

    assert(RICK45BSTACK_GetStackSize(NULL)==0 && RICK45BSTACK_IsEmpty(NULL)==-1 && RICK45BSTACK_IsFull(NULL)==-1);
    assert(RICK45BSTACK_GetStackSize(stack)==1);
    assert(RICK45BSTACK_StackPush(stack, strings[3])==0);
    assert(RICK45BSTACK_IsEmpty(stack)==0 && RICK45BSTACK_IsFull(stack)==1);
    assert(RICK45BSTACK_StackPush(stack, strings[2])==-1);
    assert(RICK45BSTACK_StackPush(stack, strings[0])==-1);
    assert(strcmp(RICK45BSTACK_StackTop(stack), strings[3])==0 && RICK45BSTACK_IsTop(stack, strings[3])==1);

    assert(RICK45BSTACK_IsTop(NULL, strings[1])==-1 && strcmp("Invalid argument: stack cannot be NULL!", RICK45B_GetError())==0);
    assert(RICK45BSTACK_IsTop(stack, NULL)==-1 && strcmp("Invalid argument: key cannot be NULL!", RICK45B_GetError())==0);
    assert(RICK45BSTACK_IsTop(NULL, NULL)==-1 && strcmp("Invalid argument: stack cannot be NULL!", RICK45B_GetError())==0);

    assert(RICK45BSTACK_ContainedInStack(NULL, strings[2])==-1 && strcmp("Invalid argument: stack cannot be NULL!", RICK45B_GetError())==0);
    assert(RICK45BSTACK_ContainedInStack(stack, NULL)==-1 && strcmp("Invalid argument: key cannot be NULL!", RICK45B_GetError())==0);
    assert(RICK45BSTACK_ContainedInStack(NULL, NULL)==-1 && strcmp("Invalid argument: stack cannot be NULL!", RICK45B_GetError())==0);

    RICK45BSTACK_StackDestroy(stack, 0);

    /*queue test*/
    queue_t queue = NULL;
    assert(RICK45BQUEUE_QueueCreate((RICK45B_comparator_t)NULL, 0)==NULL && strcmp("Invalid Argument: key_cmp function cannot be NULL!", RICK45B_GetError())==0);
    queue = RICK45BQUEUE_QueueCreate((RICK45B_comparator_t)strcmp, 0);

    assert(RICK45BQUEUE_Enqueue(NULL, strings[1])==-1 && strcmp("Invalid argument: queue cannot be NULL!", RICK45B_GetError())==0);
    assert(RICK45BQUEUE_Enqueue(queue, NULL)==-1 && strcmp("Invalid argument: key cannot be NULL!", RICK45B_GetError())==0);
    assert(RICK45BQUEUE_IsEmpty(queue)==1 && RICK45BQUEUE_IsFull(queue)==0);
    assert(RICK45BQUEUE_Enqueue(queue, strings[1])==0);
    assert(RICK45BQUEUE_IsEmpty(queue)==0 && RICK45BQUEUE_IsFull(queue)==0);

    assert(RICK45BQUEUE_Peek(NULL)==NULL && strcmp("Invalid argument: queue cannot be NULL!", RICK45B_GetError())==0);
    assert(RICK45BQUEUE_Dequeue(NULL)==NULL && strcmp("Invalid argument: queue cannot be NULL!", RICK45B_GetError())==0);

    assert(RICK45BQUEUE_GetQueueSize(NULL)==0 && RICK45BQUEUE_IsEmpty(NULL)==-1 && RICK45BQUEUE_IsFull(NULL)==-1);
    assert(RICK45BQUEUE_GetQueueSize(queue)==1);
    assert(RICK45BQUEUE_Enqueue(queue, strings[3])==0);
    assert(RICK45BQUEUE_IsEmpty(queue)==0 && RICK45BQUEUE_IsFull(queue)==0);
    assert(RICK45BQUEUE_Enqueue(queue, strings[2])==0);
    assert(RICK45BQUEUE_Enqueue(queue, strings[0])==0);
    assert(RICK45BQUEUE_GetQueueSize(queue)==4);
    assert(strcmp(RICK45BQUEUE_Peek(queue), strings[1])==0 && strcmp(RICK45BQUEUE_Rear(queue), strings[0])==0);
    assert(RICK45BQUEUE_ContainedInQueue(queue, strings[1])==1 && RICK45BQUEUE_ContainedInQueue(queue, strings[2])==1 && RICK45BQUEUE_ContainedInQueue(queue, strings[0])==1 && RICK45BQUEUE_ContainedInQueue(queue, strings[3])==1);

    //metto questo almeno ti ricordi di modificare sti test sotto. Fai inoltre qualche test di dequeue.
    /*
    assert(RICK45BSTACK_IsTop(NULL, strings[1])==-1 && strcmp("Invalid argument: stack cannot be NULL!", RICK45B_GetError())==0);
    assert(RICK45BSTACK_IsTop(stack, NULL)==-1 && strcmp("Invalid argument: key cannot be NULL!", RICK45B_GetError())==0);
    assert(RICK45BSTACK_IsTop(NULL, NULL)==-1 && strcmp("Invalid argument: stack cannot be NULL!", RICK45B_GetError())==0);
    */

    assert(RICK45BQUEUE_ContainedInQueue(NULL, strings[2])==-1 && strcmp("Invalid argument: queue cannot be NULL!", RICK45B_GetError())==0);
    assert(RICK45BQUEUE_ContainedInQueue(queue, NULL)==-1 && strcmp("Invalid argument: key cannot be NULL!", RICK45B_GetError())==0);
    assert(RICK45BQUEUE_ContainedInQueue(NULL, NULL)==-1 && strcmp("Invalid argument: queue cannot be NULL!", RICK45B_GetError())==0);
    RICK45BQUEUE_QueueDestroy(queue, 0);
}
