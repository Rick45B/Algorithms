/*
    MIT License

    Copyright (c) 2024 Riccardo Giovanni Gualiumi

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#include "Rick45B-AlgorithmsADT.h"

/*stack functions*/
stack_t RICK45BSTACK_StackCreate(RICK45B_comparator_t key_cmp, unsigned long int dim)
{
    if (key_cmp == NULL)
    {
        RICK45B_CopyString("Invalid Argument: key_cmp function cannot be NULL!", RICK45B.GetError, sizeof("Invalid Argument: key_cmp function cannot be NULL!"));
        return NULL;
    }
    list_t list = NULL;
    list = RICK45BLISTS_ListCreate(key_cmp);

    if (list == NULL)
    {
        RICK45B_CopyString("Couldn't create stack: internal list creation failed!", RICK45B.GetError, sizeof("Couldn't create stack: internal list creation failed!"));
        return NULL;
    }

    stack_t out = NULL;
    out = mallocFun(sizeof(struct stack));
    if (out == NULL)
    {
        RICK45B_CopyString("Fatal Error: Cannot allocate memory for new stack_t type. Perhaps the heap is full?", RICK45B.GetError, sizeof("Fatal Error: Cannot allocate memory for new stack_t type. Perhaps the heap is full?"));
        return NULL;
    }
    out->head = list;
    out->dim = dim;
    return out;
}

void RICK45BSTACK_StackDestroy(stack_t stack, int delete_bool)
{
    if (stack !=NULL)
    {
        RICK45BLISTS_ListDestroy(&(stack->head), delete_bool);
        stack->head = NULL;
        freeFun(stack);
    }
}

void *RICK45BSTACK_StackTop(stack_t stack)
{
    if (stack == NULL)
    {
        RICK45B_CopyString("Invalid argument: stack cannot be NULL!", RICK45B.GetError, sizeof("Invalid argument: stack cannot be NULL!"));
        return NULL;
    }

    if (stack->head!=NULL)
    {
        if (stack->head->head!=NULL) return stack->head->head->key;
        else return NULL;
    }
    else
    {
        RICK45B_CopyString("Stack is corrupted!", RICK45B.GetError, sizeof("Stack is corrupted!"));
        return NULL;
    }
}

void *RICK45BSTACK_StackPop(stack_t stack)
{
    if (stack == NULL)
    {
        RICK45B_CopyString("Invalid argument: stack cannot be NULL!", RICK45B.GetError, sizeof("Invalid argument: stack cannot be NULL!"));
        return NULL;
    }

    void* out = NULL;
    if (stack->head!=NULL)
    {
        if (stack->head->head!=NULL) out = stack->head->head->key;
        else return NULL;
    }
    else
    {
        RICK45B_CopyString("Stack is corrupted!", RICK45B.GetError, sizeof("Stack is corrupted!"));
        return NULL;
    }

    if (RICK45BLISTS_RemoveHead(stack->head, 0)==-1)
    {
        RICK45B_CopyString("An error has occurred while popping the node from the stack!", RICK45B.GetError, sizeof("An error has occurred while popping the node from the stack!"));
        return NULL;
    }
    return out;
}

int RICK45BSTACK_StackPush(stack_t stack, void *key)
{
    if (stack == NULL)
    {
        RICK45B_CopyString("Invalid argument: stack cannot be NULL!", RICK45B.GetError, sizeof("Invalid argument: stack cannot be NULL!"));
        return -1;
    }
    if (key == NULL)
    {
        RICK45B_CopyString("Invalid argument: key cannot be NULL!", RICK45B.GetError, sizeof("Invalid argument: key cannot be NULL!"));
        return -1;
    }

    if (!stack->dim)    return RICK45BLISTS_HeadAddListNode(key, stack->head);  /*no max dimension set. No need to check.*/
    if (RICK45BSTACK_GetStackSize(stack)+1<=stack->dim)
        return RICK45BLISTS_HeadAddListNode(key, stack->head);
    else
    {
        RICK45B_CopyString("Cannot push element into stack: stack is full!", RICK45B.GetError, sizeof("Cannot push element into stack: stack is full!"));
        return -1;
    }

}

int RICK45BSTACK_IsEmpty(stack_t stack)
{
    if (stack == NULL)
    {
        RICK45B_CopyString("Invalid argument: stack cannot be NULL!", RICK45B.GetError, sizeof("Invalid argument: stack cannot be NULL!"));
        return -1;
    }
    return RICK45BSTACK_GetStackSize(stack)==0;
}

int RICK45BSTACK_IsFull(stack_t stack)
{
    if (stack == NULL)
    {
        RICK45B_CopyString("Invalid argument: stack cannot be NULL!", RICK45B.GetError, sizeof("Invalid argument: stack cannot be NULL!"));
        return -1;
    }
    if (!stack->dim)    return 0;
    return RICK45BSTACK_GetStackSize(stack)==stack->dim;
}

size_t RICK45BSTACK_GetStackSize(stack_t stack)
{
    if (stack == NULL)  return 0;
    if (stack->head == NULL) return 0;
    return RICK45BLISTS_GetListSize(stack->head);
}

int RICK45BSTACK_IsTop(stack_t stack, void *key)
{
    if (stack == NULL)
    {
        RICK45B_CopyString("Invalid argument: stack cannot be NULL!", RICK45B.GetError, sizeof("Invalid argument: stack cannot be NULL!"));
        return -1;
    }
    if (key == NULL)
    {
        RICK45B_CopyString("Invalid argument: key cannot be NULL!", RICK45B.GetError, sizeof("Invalid argument: key cannot be NULL!"));
        return -1;
    }
    listNode_t node = RICK45BLISTS_GetNodeByPosition(stack->head, 0);   /*retrieving the node at the head of the list*/
    if (node == NULL && (RICK45B_Stringcmp("Fatal Error: List is NULL! Before using it, please consider using RICK45BLISTS_ListCreate to initialize the list.", RICK45B_GetError())==0 || RICK45B_Stringcmp("Invalid Argument: Position value out of range for the given linkedList!", RICK45B_GetError())==0)) return -1;
    if (node == NULL)
        return 0;
    if (stack->head->key_cmp(key, node->key)==0)    return 1;
    return 0;
}

int RICK45BSTACK_ContainedInStack(stack_t stack, void *key)
{
    if (stack == NULL)
    {
        RICK45B_CopyString("Invalid argument: stack cannot be NULL!", RICK45B.GetError, sizeof("Invalid argument: stack cannot be NULL!"));
        return -1;
    }
    if (key == NULL)
    {
        RICK45B_CopyString("Invalid argument: key cannot be NULL!", RICK45B.GetError, sizeof("Invalid argument: key cannot be NULL!"));
        return -1;
    }
    if (RICK45BLISTS_GetNodeByKey(stack->head, key)==NULL)
        return 0;
    return 1;
}

/*queue functions*/
queue_t RICK45BQUEUE_QueueCreate(RICK45B_comparator_t key_cmp, unsigned long int dim)
{
    if (key_cmp == NULL)
    {
        RICK45B_CopyString("Invalid Argument: key_cmp function cannot be NULL!", RICK45B.GetError, sizeof("Invalid Argument: key_cmp function cannot be NULL!"));
        return NULL;
    }
    list_t list = NULL;
    list = RICK45BLISTS_ListCreate(key_cmp);

    if (list == NULL)
    {
        RICK45B_CopyString("Couldn't create queue: internal list creation failed!", RICK45B.GetError, sizeof("Couldn't create queue: internal list creation failed!"));
        return NULL;
    }

    queue_t out = NULL;
    out = mallocFun(sizeof(struct queue));
    if (out == NULL)
    {
        RICK45B_CopyString("Fatal Error: Cannot allocate memory for new queue_t type. Perhaps the heap is full?", RICK45B.GetError, sizeof("Fatal Error: Cannot allocate memory for new queue_t type. Perhaps the heap is full?"));
        return NULL;
    }
    out->list = list;
    out->dim = dim;
    return out;
}

void RICK45BQUEUE_QueueDestroy(queue_t queue, int delete_bool)
{
    if (queue !=NULL)
    {
        RICK45BLISTS_ListDestroy(&(queue->list), delete_bool);
        queue->list = NULL;
        freeFun(queue);
    }
}

int RICK45BQUEUE_Enqueue(queue_t queue, void *key)
{
    if (queue == NULL)
    {
        RICK45B_CopyString("Invalid argument: queue cannot be NULL!", RICK45B.GetError, sizeof("Invalid argument: queue cannot be NULL!"));
        return -1;
    }
    if (key == NULL)
    {
        RICK45B_CopyString("Invalid argument: key cannot be NULL!", RICK45B.GetError, sizeof("Invalid argument: key cannot be NULL!"));
        return -1;
    }
    if (!queue->dim)    return RICK45BLISTS_HeadAddListNode(key, queue->list);  /*no max dimension set. No need to check.*/
    if (RICK45BQUEUE_GetQueueSize(queue)+1<=queue->dim)
        return RICK45BLISTS_HeadAddListNode(key, queue->list);
    else
    {
        RICK45B_CopyString("Cannot enqueue element into queue: queue is full!", RICK45B.GetError, sizeof("Cannot enqueue element into queue: queue is full!"));
        return -1;
    }
}

int RICK45BQUEUE_IsEmpty(queue_t queue)
{
    if (queue == NULL)
    {
        RICK45B_CopyString("Invalid argument: queue cannot be NULL!", RICK45B.GetError, sizeof("Invalid argument: queue cannot be NULL!"));
        return -1;
    }
    return RICK45BQUEUE_GetQueueSize(queue)==0;
}

int RICK45BQUEUE_IsFull(queue_t queue)
{
    if (queue == NULL)
    {
        RICK45B_CopyString("Invalid argument: queue cannot be NULL!", RICK45B.GetError, sizeof("Invalid argument: queue cannot be NULL!"));
        return -1;
    }
    if (!queue->dim)    return 0;
    return RICK45BQUEUE_GetQueueSize(queue)==queue->dim;
}

void *RICK45BQUEUE_Dequeue(queue_t queue)
{
    if (queue == NULL)
    {
        RICK45B_CopyString("Invalid argument: queue cannot be NULL!", RICK45B.GetError, sizeof("Invalid argument: queue cannot be NULL!"));
        return NULL;
    }

    void *out = NULL;
    if (queue->list!=NULL)
    {
        if (queue->list->tail != NULL)
        {
            if (queue->list->tail->key != NULL) out = queue->list->tail->key;
            else
            {
                RICK45B_CopyString("Queue is corrupted!", RICK45B.GetError, sizeof("Queue is corrupted!"));
                return NULL;
            }
        }
        return NULL;
    }
    else
    {
        RICK45B_CopyString("Queue is corrupted!", RICK45B.GetError, sizeof("Queue is corrupted!"));
        return NULL;
    }
    if (RICK45BLISTS_RemoveTail(queue->list, 0)==-1)
    {
        RICK45B_CopyString("An error has occurred while dequeing the node!", RICK45B.GetError, sizeof("An error has occurred while dequeing the node!"));
        return NULL;
    }
    return out;
}

size_t RICK45BQUEUE_GetQueueSize(queue_t queue)
{
    if (queue == NULL)  return 0;
    if (queue->list == NULL)    return 0;
    return RICK45BLISTS_GetListSize(queue->list);
}

int RICK45BQUEUE_ContainedInQueue(queue_t queue, void *key)
{
    if (queue == NULL)
    {
        RICK45B_CopyString("Invalid argument: queue cannot be NULL!", RICK45B.GetError, sizeof("Invalid argument: queue cannot be NULL!"));
        return -1;
    }
    if (key == NULL)
    {
        RICK45B_CopyString("Invalid argument: key cannot be NULL!", RICK45B.GetError, sizeof("Invalid argument: key cannot be NULL!"));
        return -1;
    }
    if (RICK45BLISTS_GetNodeByKey(queue->list, key)==NULL)
        return 0;
    return 1;
}

void *RICK45BQUEUE_Peek(queue_t queue)
{
    if (queue == NULL)
    {
        RICK45B_CopyString("Invalid argument: queue cannot be NULL!", RICK45B.GetError, sizeof("Invalid argument: queue cannot be NULL!"));
        return NULL;
    }
    if (queue->list!=NULL)
    {
        if (queue->list->tail!=NULL)    return queue->list->tail->key;
        else    return NULL;
    }
    else
    {
        RICK45B_CopyString("Queue is corrupted!", RICK45B.GetError, sizeof("Queue is corrupted!"));
        return NULL;
    }
}

void *RICK45BQUEUE_Rear(queue_t queue)
{
    if (queue == NULL)
    {
        RICK45B_CopyString("Invalid argument: queue cannot be NULL!", RICK45B.GetError, sizeof("Invalid argument: queue cannot be NULL!"));
        return NULL;
    }
    if (queue->list!=NULL)
    {
        if (queue->list->head!=NULL)    return queue->list->head->key;
        else    return NULL;
    }
    else
    {
        RICK45B_CopyString("Queue is corrupted!", RICK45B.GetError, sizeof("Queue is corrupted!"));
        return NULL;
    }
}
