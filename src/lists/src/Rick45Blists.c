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

list_t RICK45BLISTS_ListCreate(RICK45B_comparator_t key_cmp){

    if (key_cmp == NULL)
    {
        RICK45B_CopyString("Invalid Argument: key_cmp function cannot be NULL!", RICK45B.GetError, sizeof("Invalid Argument: key_cmp function cannot be NULL!"));
        return NULL;
    }

    list_t out = NULL;
    out = mallocFun(sizeof(struct list));

    if (out == NULL)
    {
        RICK45B_CopyString("Fatal Error: Cannot allocate memory for new list_t type. Perhaps the heap is full?", RICK45B.GetError, sizeof("Fatal Error: Cannot allocate memory for new list_t type. Perhaps the heap is full?"));
        return NULL;
    }
    out->head = NULL;
    out->tail = NULL;
    out->pointedNode = NULL;
    out -> key_cmp = key_cmp;
    out -> size = 0;
    return out;
}

void RICK45BLISTS_ListDestroy(list_t *linkedList, int delete_bool){

    if (linkedList != NULL)
    {
        RICK45BLISTS_RemoveAllNodes(*linkedList, delete_bool);
        freeFun(*linkedList);
        *linkedList = NULL;
    }

}

listNode_t RICK45BLISTS_GetNextNode(list_t linkedList)
{
    if (linkedList == NULL)
    {
        RICK45B_CopyString("Fatal Error: List is NULL! Before using it, please consider using RICK45BLISTS_ListCreate to initialize the list.", RICK45B.GetError, sizeof("Fatal Error: List is NULL! Before using it, please consider using RICK45BLISTS_ListCreate to initialize the list."));
        return NULL;
    }
    if (RICK45BLISTS_GetListSize(linkedList)==0)
    {
        RICK45B_CopyString("List is empty!", RICK45B.GetError, sizeof("List is empty!"));
        return NULL;
    }
    if (linkedList->pointedNode->next!=NULL)
        linkedList->pointedNode = linkedList->pointedNode->next;
    return linkedList->pointedNode;

}

int RICK45BLISTS_HasNext(list_t linkedList)
{
    if (linkedList == NULL)
    {
        RICK45B_CopyString("Fatal Error: List is NULL! Before using it, please consider using RICK45BLISTS_ListCreate to initialize the list.", RICK45B.GetError, sizeof("Fatal Error: List is NULL! Before using it, please consider using RICK45BLISTS_ListCreate to initialize the list."));
        return -1;
    }
    if (RICK45BLISTS_GetListSize(linkedList)==0)
    {
        RICK45B_CopyString("List is empty!", RICK45B.GetError, sizeof("List is empty!"));
        return -1;
    }
    return linkedList->pointedNode->next!=NULL?1:0;
}

listNode_t RICK45BLISTS_GetCurrentNode(list_t linkedList)
{
    if (linkedList == NULL)
    {
        RICK45B_CopyString("Fatal Error: List is NULL! Before using it, please consider using RICK45BLISTS_ListCreate to initialize the list.", RICK45B.GetError, sizeof("Fatal Error: List is NULL! Before using it, please consider using RICK45BLISTS_ListCreate to initialize the list."));
        return NULL;
    }
    if (RICK45BLISTS_GetListSize(linkedList)==0)
    {
        RICK45B_CopyString("List is empty!", RICK45B.GetError, sizeof("List is empty!"));
        return NULL;
    }

    return linkedList->pointedNode;
}

int RICK45BLISTS_RewindList(list_t linkedList)
{
    if (linkedList == NULL)
    {
        RICK45B_CopyString("Fatal Error: List is NULL! Before using it, please consider using RICK45BLISTS_ListCreate to initialize the list.", RICK45B.GetError, sizeof("Fatal Error: List is NULL! Before using it, please consider using RICK45BLISTS_ListCreate to initialize the list."));
        return -1;
    }
    if (RICK45BLISTS_GetListSize(linkedList)==0 || linkedList->head == NULL)
    {
        RICK45B_CopyString("List is empty!", RICK45B.GetError, sizeof("List is empty!"));
        return -1;
    }

    linkedList->pointedNode = linkedList->head;


    return 0;
}

int RICK45BLISTS_HeadAddListNode(void *key, list_t linkedList){

    if (linkedList == NULL)
    {
        RICK45B_CopyString("Fatal Error: List is NULL! Before using it, please consider using RICK45BLISTS_ListCreate to initialize the list.", RICK45B.GetError, sizeof("Fatal Error: List is NULL! Before using it, please consider using RICK45BLISTS_ListCreate to initialize the list."));
        return -1;
    }
    if (key == NULL)
    {
        RICK45B_CopyString("Invalid Argument: key cannot be NULL!", RICK45B.GetError, sizeof("Invalid Argument: key cannot be NULL!"));
        return -1;
    }

    listNode_t node = NULL;
    node = mallocFun(sizeof(struct listNode));

    if (node == NULL)
    {
        RICK45B_CopyString("Fatal Error: Cannot allocate memory for new node. Maybe the heap is full?", RICK45B.GetError, sizeof("Fatal Error: Cannot allocate memory for new node. Maybe the heap is full?"));
        return -1;
    }

    node->key = key;
    node->next = linkedList->head;

    if (linkedList->head == NULL)
    {
        linkedList->head = node;
        linkedList->tail = node;
    }
    else
        linkedList->head = node;

    linkedList->size++;
    return 0;
}

int RICK45BLISTS_TailAddListNode(void *key, list_t linkedList){

    if (linkedList == NULL)
    {
        RICK45B_CopyString("Fatal Error: List is NULL! Before using it, please consider using RICK45BLISTS_ListCreate to initialize the list.", RICK45B.GetError, sizeof("Fatal Error: List is NULL! Before using it, please consider using RICK45BLISTS_ListCreate to initialize the list."));
        return -1;
    }
    if (key == NULL)
    {
        RICK45B_CopyString("Invalid Argument: key cannot be NULL!", RICK45B.GetError, sizeof("Invalid Argument: key cannot be NULL!"));
        return -1;
    }
    listNode_t node = mallocFun(sizeof(struct listNode));
    if (node == NULL)
    {
        RICK45B_CopyString("Fatal Error: Cannot allocate memory for new node. Maybe the heap is full?", RICK45B.GetError, sizeof("Fatal Error: Cannot allocate memory for new node. Maybe the heap is full?"));
        return -1;
    }

    node->next = NULL;
    node->key = key;

    if (linkedList->tail == NULL)  /*there's no Tail*/
    {
        linkedList->tail = node;
        linkedList->head = node;
    }
    else
    {
        linkedList->tail->next = node;
        linkedList->tail = node;
    }

    linkedList->size++;
    return 0;
}

int RICK45BLISTS_AddListNode(void *key, list_t linkedList, size_t position){

    if (linkedList == NULL)
    {
        RICK45B_CopyString("Fatal Error: List is NULL! Before using it, please consider using RICK45BLISTS_ListCreate to initialize the list.", RICK45B.GetError, sizeof("Fatal Error: List is NULL! Before using it, please consider using RICK45BLISTS_ListCreate to initialize the list."));
        return -1;
    }
    if (key == NULL)
    {
        RICK45B_CopyString("Invalid Argument: key cannot be NULL!", RICK45B.GetError, sizeof("Invalid Argument: key cannot be NULL!"));
        return -1;
    }

    if (position > linkedList->size)
    {
        RICK45B_CopyString("Invalid Argument: Position value out of range for the given linkedList!", RICK45B.GetError, sizeof("Invalid Argument: Position value out of range for the given linkedList!"));
        return -1;
    }

    if (position == linkedList->size)
        RICK45BLISTS_TailAddListNode(key, linkedList);
    else
    {
        if (position == 0)
            RICK45BLISTS_HeadAddListNode(key, linkedList);
        else
        {
            listNode_t node = NULL;
            node = mallocFun(sizeof(struct listNode));
            if (node==NULL)
            {
                RICK45B_CopyString("Fatal Error: Cannot allocate memory for new node. Maybe the heap is full?", RICK45B.GetError, sizeof("Fatal Error: Cannot allocate memory for new node. Maybe the heap is full?"));
                return -1;
            }

            node->key = key;
            node->next = RICK45BLISTS_GetNodeByPosition(linkedList, position);
            RICK45BLISTS_GetNodeByPosition(linkedList, position-1)->next = node;
            linkedList->size++;
        }
    }
    return 0;

}

size_t RICK45BLISTS_GetListSize(list_t linkedList){
    if (linkedList == NULL)
        return 0;
    return linkedList->size;
}

listNode_t RICK45BLISTS_GetNodeByPosition(list_t linkedList, size_t position){

    if (linkedList == NULL)
    {
        RICK45B_CopyString("Fatal Error: List is NULL! Before using it, please consider using RICK45BLISTS_ListCreate to initialize the list.", RICK45B.GetError, sizeof("Fatal Error: List is NULL! Before using it, please consider using RICK45BLISTS_ListCreate to initialize the list."));
        return NULL;
    }

    int i = 0;
    listNode_t temp = linkedList->head;

    if (position > linkedList->size)
    {
        RICK45B_CopyString("Invalid Argument: Position value out of range for the given linkedList!", RICK45B.GetError, sizeof("Invalid Argument: Position value out of range for the given linkedList!"));
        return NULL;
    }

    if (position==0)
        return linkedList->head;
    if (position == linkedList->size-1)
        return linkedList->tail;

    if (temp == NULL)
        return NULL;     /*no keys can be found*/

    while (temp->next!=NULL && i<(int)position)
    {
        temp = temp->next;
        i++;
    }

    if (i==(int)position)
        return temp;

    return NULL;

}

listNode_t RICK45BLISTS_GetNodeByKey(list_t linkedList, void* key){

    if (linkedList == NULL)
    {
        RICK45B_CopyString("Fatal Error: List is NULL! Before using it, please consider using RICK45BLISTS_ListCreate to initialize the list.", RICK45B.GetError, sizeof("Fatal Error: List is NULL! Before using it, please consider using RICK45BLISTS_ListCreate to initialize the list."));
        return NULL;
    }
    if (key == NULL)
    {
        RICK45B_CopyString("Invalid Argument: key cannot be NULL!", RICK45B.GetError, sizeof("Invalid Argument: key cannot be NULL!"));
        return NULL;
    }
    if (linkedList->head == NULL && linkedList->tail == NULL)
    {
        RICK45B_CopyString("RICK45BLISTS_GetNodeByKey error: no key can be found!", RICK45B.GetError, sizeof("RICK45BLISTS_GetNodeByKey error: no key can be found!"));
        return NULL;     /*no keys can be found*/
    }

    listNode_t temp = NULL;

    if (linkedList->key_cmp(linkedList->head->key, key)==0)
        temp = linkedList->head;
    else
    {
        if (linkedList->key_cmp(linkedList->tail->key, key)==0)
            temp = linkedList->tail;
        else
        {
            temp = linkedList->head;
            while (temp->next!=NULL && linkedList->key_cmp(temp->key, key))
                temp = temp->next;
        }
    }

    if (temp == NULL)
    {
        RICK45B_CopyString("RICK45BLISTS_GetNodeByKey error: no key can be found!", RICK45B.GetError, sizeof("RICK45BLISTS_GetNodeByKey error: no key can be found!"));
        return NULL;     /*no keys can be found*/
    }

    if (linkedList->key_cmp(temp->key, key)==0)
        return temp;

    RICK45B_CopyString("RICK45BLISTS_GetNodeByKey error: no key can be found!", RICK45B.GetError, sizeof("RICK45BLISTS_GetNodeByKey error: no key can be found!"));
    return NULL;
}

void *RICK45BLISTS_GetKeyByNode(listNode_t node){
    if (node==NULL)
    {
        RICK45B_CopyString("Invalid Argument: Node cannot be NULL!", RICK45B.GetError, sizeof("Invalid Argument: Node cannot be NULL!"));
        return NULL;
    }

    return node->key;
}

void *RICK45BLISTS_GetKeyByPosition(list_t linkedList, size_t position){

    if (linkedList == NULL)
    {
        RICK45B_CopyString("Fatal Error: List is NULL! Before using it, please consider using RICK45BLISTS_ListCreate to initialize the list.", RICK45B.GetError, sizeof("Fatal Error: List is NULL! Before using it, please consider using RICK45BLISTS_ListCreate to initialize the list."));
        return NULL;
    }

    if (position > linkedList->size)
    {
        RICK45B_CopyString("Invalid Argument: Position value out of range for the given linkedList!", RICK45B.GetError, sizeof("Invalid Argument: Position value out of range for the given linkedList!"));
        return NULL;
    }

    if (position==0)
        return linkedList->head->key;
    if (position == linkedList->size)
        return linkedList->tail->key;

    int i = 0;
    listNode_t temp = linkedList->head;

    if (temp == NULL)
    {
        RICK45B_CopyString("RICK45BLISTS_GetNodeByKey error: no key can be found!", RICK45B.GetError, sizeof("RICK45BLISTS_GetNodeByKey error: no key can be found!"));
        return NULL;     /*no keys can be found*/
    }

    while (temp->next!=NULL && i<(int)position)
    {
        temp = temp->next;
        i++;
    }

    if (i==(int)position)
        return temp->key;

    RICK45B_CopyString("RICK45BLISTS_GetNodeByKey error: no key can be found!", RICK45B.GetError, sizeof("RICK45BLISTS_GetNodeByKey error: no key can be found!"));
    return NULL;
}

void *RICK45BLISTS_SetKeyByPosition(list_t linkedList, void* newkey, size_t position)
{
    if (linkedList == NULL)
    {
        RICK45B_CopyString("Fatal Error: List is NULL! Before using it, please consider using RICK45BLISTS_ListCreate to initialize the list.", RICK45B.GetError, sizeof("Fatal Error: List is NULL! Before using it, please consider using RICK45BLISTS_ListCreate to initialize the list."));
        return NULL;
    }

    if (position > linkedList->size)
    {
        RICK45B_CopyString("Invalid Argument: Position value out of range for the given linkedList!", RICK45B.GetError, sizeof("Invalid Argument: Position value out of range for the given linkedList!"));
        return NULL;
    }

    if (newkey == NULL)
    {
        RICK45B_CopyString("Invalid Argument: new key cannot be NULL!", RICK45B.GetError, sizeof("Invalid Argument: new key cannot be NULL!"));
        return NULL;
    }

    listNode_t temp = NULL;
    temp = RICK45BLISTS_GetNodeByPosition(linkedList, position);
    if (temp == NULL)
    {
        RICK45B_CopyString("Fatal error: couldn't fetch node at that position!", RICK45B.GetError, sizeof("Fatal error: couldn't fetch node at that position!"));
        return NULL;
    }

    void *out = temp->key;
    temp->key = newkey;
    return out;
}

void *RICK45BLISTS_SetKeyByNode(list_t linkedList, void* newkey, listNode_t node)
{
    if (linkedList == NULL)
    {
        RICK45B_CopyString("Fatal Error: List is NULL! Before using it, please consider using RICK45BLISTS_ListCreate to initialize the list.", RICK45B.GetError, sizeof("Fatal Error: List is NULL! Before using it, please consider using RICK45BLISTS_ListCreate to initialize the list."));
        return NULL;
    }

    if (node == NULL)
    {
        RICK45B_CopyString("Fatal error: Node cannot be NULL!", RICK45B.GetError, sizeof("Fatal error: Node cannot be NULL!"));
        return NULL;
    }

    if (newkey == NULL)
    {
        RICK45B_CopyString("Invalid Argument: new key cannot be NULL!", RICK45B.GetError, sizeof("Invalid Argument: new key cannot be NULL!"));
        return NULL;
    }

    if (linkedList->head == NULL)
    {
        RICK45B_CopyString("Head of the list is NULL! Please consider adding some nodes first!", RICK45B.GetError, sizeof("Head of the list is NULL! Please consider adding some nodes first!"));
        return NULL;
    }

    listNode_t temp = NULL;
    if (node == linkedList->head)
        temp = linkedList->head;
    else
    {
        if (node == linkedList->tail)
            temp = linkedList->tail;
        else
        {
            temp = linkedList->head;
            while (temp->next!=NULL && temp!=node)
                temp = temp->next;
        }
    }

    void *out = node->key;
    temp->key = newkey;
    return out;
}

int RICK45BLISTS_SetKeyByKey(list_t linkedList, void* newkey, void* oldkey)
{
    if (linkedList == NULL)
    {
        RICK45B_CopyString("Fatal Error: List is NULL! Before using it, please consider using RICK45BLISTS_ListCreate to initialize the list.", RICK45B.GetError, sizeof("Fatal Error: List is NULL! Before using it, please consider using RICK45BLISTS_ListCreate to initialize the list."));
        return -1;
    }

    if (newkey == NULL || oldkey == NULL)
    {
        RICK45B_CopyString("Fatal Error: keys cannot be NULL!", RICK45B.GetError, sizeof("Fatal Error: keys cannot be NULL!"));
        return -1;
    }
    int cnt = 0;
    if (linkedList->head == NULL && linkedList->tail == NULL)
        return cnt;

    listNode_t temp = linkedList->head;

    while (temp!=NULL)
    {
        if (linkedList->key_cmp(temp->key, oldkey)==0)
        {
            temp->key = newkey;
            cnt++;
        }
        temp = temp->next;
    }
    return cnt;
}

int RICK45BLISTS_RemoveHead(list_t linkedList, int delete_bool){

    if (linkedList == NULL)
    {
        RICK45B_CopyString("Fatal Error: List is NULL! Before using it, please consider using RICK45BLISTS_ListCreate to initialize the list.", RICK45B.GetError, sizeof("Fatal Error: List is NULL! Before using it, please consider using RICK45BLISTS_ListCreate to initialize the list."));
        return -1;
    }

    if (linkedList->head != NULL)
    {
        listNode_t temp = linkedList->head;
        if (linkedList->head->next == NULL)
        {
            /*updating the 'pointed node' field*/
            if (linkedList->pointedNode == linkedList->head)
                linkedList->pointedNode = NULL;
            linkedList->head = NULL;
        }
        else
        {
            /*updating the 'pointed node' field*/
            if (linkedList->pointedNode == linkedList->head)
                linkedList->pointedNode = linkedList->head->next;
            linkedList->head = linkedList->head->next;
        }

        if (delete_bool==FALSE)
            freeFun(temp);
        else
        {
            freeFun(temp->key);
            freeFun(temp);
        }
        linkedList->size--;
    }
    else
        linkedList->tail = NULL;  /*if head is null, the tail must be as well.*/

    return 0;

}

int RICK45BLISTS_RemoveNode(list_t linkedList, size_t position, int delete_bool)
{
    if (linkedList == NULL)
    {
        RICK45B_CopyString("Fatal Error: List is NULL! Before using it, please consider using RICK45BLISTS_ListCreate to initialize the list.", RICK45B.GetError, sizeof("Fatal Error: List is NULL! Before using it, please consider using RICK45BLISTS_ListCreate to initialize the list."));
        return -1;
    }

    if (linkedList->head != NULL)
    {
        if (position > linkedList->size)    /*position is out of bound!!*/
        {
            RICK45B_CopyString("Invalid Argument: Position value out of range for the given linkedList!", RICK45B.GetError, sizeof("Invalid Argument: Position value out of range for the given linkedList!"));
            return -1;
        }

        listNode_t temp = NULL;

        if (position == linkedList->size-1)   /*i want to delete the tail!*/
            RICK45BLISTS_RemoveTail(linkedList, delete_bool);
        else
        {
            if (position == 0)  /*i want to delete the head!*/
                RICK45BLISTS_RemoveHead(linkedList, delete_bool);
            else
            {
                listNode_t tempPrev = NULL;
                temp = RICK45BLISTS_GetNodeByPosition(linkedList, position);
                tempPrev = RICK45BLISTS_GetNodeByPosition(linkedList, position-1);
                if (temp == linkedList->pointedNode)
                    linkedList->pointedNode = tempPrev;
                tempPrev->next = temp->next;
                if (delete_bool == FALSE)
                    freeFun(temp);
                else
                {
                    freeFun(temp->key);
                    freeFun(temp);
                }
                linkedList->size--;
            }
        }

        return 0;
    }
    else
    {
        RICK45B_CopyString("Head of the list is NULL! Please consider adding some nodes first!", RICK45B.GetError, sizeof("Head of the list is NULL! Please consider adding some nodes first!"));
        linkedList->tail = NULL;  /*if head is null, the tail must be as well.*/
        return -1;
    }

}

void RICK45BLISTS_RemoveAllNodes(list_t linkedList, int delete_bool){


    if (linkedList->size != 0)
    {
        listNode_t head = linkedList->head;
        while (head!=NULL)
        {
            RICK45BLISTS_RemoveHead(linkedList, delete_bool);
            head = linkedList->head;
        }
        linkedList->tail = NULL;
        linkedList->pointedNode = NULL;
    }
}

int RICK45BLISTS_RemoveTail(list_t linkedList, int delete_bool){

    if (linkedList == NULL)
    {
        RICK45B_CopyString("Fatal Error: List is NULL! Before using it, please consider using RICK45BLISTS_ListCreate to initialize the list.", RICK45B.GetError, sizeof("Fatal Error: List is NULL! Before using it, please consider using RICK45BLISTS_ListCreate to initialize the list."));
        return -1;
    }

    if (linkedList->tail != NULL)
    {
        listNode_t temp = NULL;
        temp = RICK45BLISTS_GetNodeByPosition(linkedList, RICK45BLISTS_GetListSize(linkedList)-2);
        temp -> next = NULL;
        if (linkedList->pointedNode == linkedList->tail)
            linkedList->pointedNode = temp;

        if (delete_bool == TRUE)
            freeFun(linkedList->tail->key);
        freeFun(linkedList->tail);

        linkedList->tail = temp;
        linkedList->size--;

        return 0;
    }
    else                        /*if tail is null, head must be as well.*/
    {
        RICK45B_CopyString("Tail of the list is NULL! Please consider adding some nodes first!", RICK45B.GetError, sizeof("Tail of the list is NULL! Please consider adding some nodes first!"));
        linkedList->head = NULL;
        return -1;
    }
}

int RICK45BLISTS_RemoveNodeByKey(list_t linkedList, void *key, int delete_bool)
{
    if (linkedList == NULL)
    {
        RICK45B_CopyString("Fatal Error: List is NULL! Before using it, please consider using RICK45BLISTS_ListCreate to initialize the list.", RICK45B.GetError, sizeof("Fatal Error: List is NULL! Before using it, please consider using RICK45BLISTS_ListCreate to initialize the list."));
        return -1;
    }

    if (key == NULL)
    {
        RICK45B_CopyString("Invalid Argument: key cannot be NULL!", RICK45B.GetError, sizeof("Invalid Argument: key cannot be NULL!"));
        return -1;
    }

    listNode_t temp = linkedList->head;
    listNode_t old = linkedList->head;

    if (temp == NULL)
    {
        return 0;
    }

    while (temp->next!=NULL && linkedList->key_cmp(temp->key, key))
    {
        old = temp;
        temp = temp->next;
    }

    if (linkedList->key_cmp(temp->key, key)==0)   /*node with given key was found.*/
    {
        if (linkedList->head == temp)
            RICK45BLISTS_RemoveHead(linkedList, delete_bool);
        else
        {
            if (linkedList->tail == temp)
                RICK45BLISTS_RemoveTail(linkedList, delete_bool);
            else
            {
                if (linkedList->pointedNode == temp)
                    linkedList->pointedNode = old;
                old->next = temp->next;
                if (delete_bool == TRUE)
                    freeFun(temp->key);
                freeFun(temp);
                linkedList->size--;
            }
        }

        return 1;
    }
    return 0;
}

int RICK45BLISTS_RemoveAllNodesByKey(list_t linkedList, void *key, int delete_bool)
{
    int cnt = 0;
    if (RICK45BLISTS_RemoveNodeByKey(linkedList, key, delete_bool)==-1)
        return -1;
    cnt++;
    while (RICK45BLISTS_RemoveNodeByKey(linkedList, key, delete_bool)>0)
        cnt++;
    return cnt;
}

doubleList_t RICK45BLISTS_DoubleListCreate(RICK45B_comparator_t key_cmp)
{
    if (key_cmp == NULL)
    {
        RICK45B_CopyString("Invalid Argument: key_cmp function cannot be NULL!", RICK45B.GetError, sizeof("Invalid Argument: key_cmp function cannot be NULL!"));
        return NULL;
    }

    doubleList_t out = NULL;
    out = mallocFun(sizeof(struct doubleList));
    out->head = NULL;
    out->tail = NULL;
    out->pointedNode = NULL;

    if (out == NULL)
    {
        RICK45B_CopyString("Fatal Error: Cannot allocate memory for new doubleList_t type. Maybe the heap is full?", RICK45B.GetError, sizeof("Fatal Error: Cannot allocate memory for new doubleList_t type. Maybe the heap is full?"));
        return NULL;
    }
    out -> key_cmp = key_cmp;
    out -> size = 0;
    return out;
}

void RICK45BLISTS_DoubleListDestroy(doubleList_t *dlinkedList, int delete_bool){

    if (dlinkedList != NULL)
    {
        RICK45BLISTS_DoubleListRemoveAllNodes(*dlinkedList, delete_bool);
        freeFun(*dlinkedList);
        *dlinkedList = NULL;
    }

}

doubleListNode_t RICK45BLISTS_DoubleListGetNextNode(doubleList_t dlinkedList){

    if (dlinkedList == NULL)
    {
        RICK45B_CopyString("Fatal Error: double linkedList is NULL! Before using it, please consider using RICK45BLISTS_DoubleListCreate to initialize the double linked list.", RICK45B.GetError, sizeof("Fatal Error: double linkedList is NULL! Before using it, please consider using RICK45BLISTS_DoubleListCreate to initialize the double linked list."));
        return NULL;
    }
    if (RICK45BLISTS_GetDoubleListSize(dlinkedList)==0)
    {
        RICK45B_CopyString("double linkedList is empty!", RICK45B.GetError, sizeof("double linkedList is empty!"));
        return NULL;
    }
    if (dlinkedList->pointedNode->next!=NULL)
        dlinkedList->pointedNode = dlinkedList->pointedNode->next;
    return dlinkedList->pointedNode;
}

doubleListNode_t RICK45BLISTS_DoubleListGetPreviousNode(doubleList_t dlinkedList){

    if (dlinkedList == NULL)
    {
        RICK45B_CopyString("Fatal Error: double linkedList is NULL! Before using it, please consider using RICK45BLISTS_DoubleListCreate to initialize the double linked list.", RICK45B.GetError, sizeof("Fatal Error: double linkedList is NULL! Before using it, please consider using RICK45BLISTS_DoubleListCreate to initialize the double linked list."));
        return NULL;
    }
    if (RICK45BLISTS_GetDoubleListSize(dlinkedList)==0)
    {
        RICK45B_CopyString("double linkedList is empty!", RICK45B.GetError, sizeof("double linkedList is empty!"));
        return NULL;
    }
    if (dlinkedList->pointedNode->previous!=NULL)
        dlinkedList->pointedNode = dlinkedList->pointedNode->previous;
    return dlinkedList->pointedNode;
}

int RICK45BLISTS_DoubleListHasPrevious(doubleList_t dlinkedList){

    if (dlinkedList == NULL)
    {
        RICK45B_CopyString("Fatal Error: double linkedList is NULL! Before using it, please consider using RICK45BLISTS_DoubleListCreate to initialize the double linked list.", RICK45B.GetError, sizeof("Fatal Error: double linkedList is NULL! Before using it, please consider using RICK45BLISTS_DoubleListCreate to initialize the double linked list."));
        return -1;
    }
    if (RICK45BLISTS_GetDoubleListSize(dlinkedList)==0)
    {
        RICK45B_CopyString("double linkedList is empty!", RICK45B.GetError, sizeof("double linkedList is empty!"));
        return -1;
    }
    return dlinkedList->pointedNode->previous!=NULL?1:0;
}

int RICK45BLISTS_DoubleListHasNext(doubleList_t dlinkedList){

    if (dlinkedList == NULL)
    {
        RICK45B_CopyString("Fatal Error: double linkedList is NULL! Before using it, please consider using RICK45BLISTS_DoubleListCreate to initialize the double linked list.", RICK45B.GetError, sizeof("Fatal Error: double linkedList is NULL! Before using it, please consider using RICK45BLISTS_DoubleListCreate to initialize the double linked list."));
        return -1;
    }
    if (RICK45BLISTS_GetDoubleListSize(dlinkedList)==0)
    {
        RICK45B_CopyString("double linkedList is empty!", RICK45B.GetError, sizeof("double linkedList is empty!"));
        return -1;
    }
    return dlinkedList->pointedNode->next!=NULL?1:0;
}

doubleListNode_t RICK45BLISTS_DoubleListGetCurrentNode(doubleList_t dlinkedList){

    if (dlinkedList == NULL)
    {
        RICK45B_CopyString("Fatal Error: double linkedList is NULL! Before using it, please consider using RICK45BLISTS_DoubleListCreate to initialize the double linked list.", RICK45B.GetError, sizeof("Fatal Error: double linkedList is NULL! Before using it, please consider using RICK45BLISTS_DoubleListCreate to initialize the double linked list."));
        return NULL;
    }
    if (RICK45BLISTS_GetDoubleListSize(dlinkedList)==0)
    {
        RICK45B_CopyString("double linkedList is empty!", RICK45B.GetError, sizeof("double linkedList is empty!"));
        return NULL;
    }

    return dlinkedList->pointedNode;
}

int RICK45BLISTS_RewindDoubleList(doubleList_t dlinkedList){

    if (dlinkedList == NULL)
    {
        RICK45B_CopyString("Fatal Error: double linkedList is NULL! Before using it, please consider using RICK45BLISTS_DoubleListCreate to initialize the double linked list.", RICK45B.GetError, sizeof("Fatal Error: double linkedList is NULL! Before using it, please consider using RICK45BLISTS_DoubleListCreate to initialize the double linked list."));
        return -1;
    }
    if (RICK45BLISTS_GetDoubleListSize(dlinkedList)==0 || dlinkedList->head == NULL)
    {
        RICK45B_CopyString("double linkedList is empty!", RICK45B.GetError, sizeof("double linkedList is empty!"));
        return -1;
    }

    dlinkedList->pointedNode = dlinkedList->head;
    dlinkedList->pointedNode->previous = NULL;
    return 0;
}

void RICK45BLISTS_DoubleListRemoveAllNodes(doubleList_t dlinkedList, int delete_bool){

    doubleListNode_t head = dlinkedList->head;
    while (head!=NULL)
    {
        RICK45BLISTS_DoubleListRemoveHead(dlinkedList, delete_bool);
        head = dlinkedList->head;
    }
    dlinkedList->tail = NULL;
    dlinkedList->pointedNode = NULL;
}

int RICK45BLISTS_DoubleListRemoveHead(doubleList_t dlinkedList, int delete_bool){

    if (dlinkedList == NULL)
    {
        RICK45B_CopyString("Fatal Error: double linkedList is NULL! Before using it, please consider using RICK45BLISTS_DoubleListCreate to initialize the double linked list.", RICK45B.GetError, sizeof("Fatal Error: double linkedList is NULL! Before using it, please consider using RICK45BLISTS_DoubleListCreate to initialize the double linked list."));
        return -1;
    }

    if (dlinkedList->head != NULL)
    {
        doubleListNode_t temp = dlinkedList->head;
        if (dlinkedList->head->next == NULL)
        {
            /*updating the 'pointed node' field*/
            if (dlinkedList->pointedNode == dlinkedList->head)
                dlinkedList->pointedNode = NULL;
            dlinkedList->head = NULL;
        }
        else
        {
            /*updating the 'pointed node' field*/
            if (dlinkedList->pointedNode == dlinkedList->head)
                dlinkedList->pointedNode = dlinkedList->head->next;
            dlinkedList->head = dlinkedList->head->next;
        }

        if (delete_bool==FALSE)
            freeFun(temp);
        else
        {
            freeFun(temp->key);
            freeFun(temp);
        }
        dlinkedList->size--;
    }
    else
        dlinkedList->tail = NULL;  /*if head is null, the tail must be as well.*/

    return 0;

}

int RICK45BLISTS_HeadAddDoubleListNode(void *key, doubleList_t dlinkedList)
{
    if (dlinkedList == NULL)
    {
        RICK45B_CopyString("Fatal Error: double linkedList is NULL! Before using it, please consider using RICK45BLISTS_DoubleListCreate to initialize the double linked list.", RICK45B.GetError, sizeof("Fatal Error: double linkedList is NULL! Before using it, please consider using RICK45BLISTS_DoubleListCreate to initialize the double linked list."));
        return -1;
    }
    if (key == NULL)
    {
        RICK45B_CopyString("Invalid Argument: key cannot be NULL!", RICK45B.GetError, sizeof("Invalid Argument: key cannot be NULL!"));
        return -1;
    }

    doubleListNode_t node = NULL;
    node = mallocFun(sizeof(struct doubleListNode));

    if (node == NULL)
    {
        RICK45B_CopyString("Fatal Error: Cannot allocate memory for new node. Maybe the heap is full?", RICK45B.GetError, sizeof("Fatal Error: Cannot allocate memory for new node. Maybe the heap is full?"));
        return -1;
    }

    node->key = key;
    node->next = dlinkedList->head;
    node->previous = NULL;

    if (dlinkedList->head == NULL)
    {
        dlinkedList->head = node;
        dlinkedList->tail = node;
    }
    else
    {
        dlinkedList->head->previous = node;
        dlinkedList->head = node;
    }

    dlinkedList->size++;
    return 0;
}

size_t RICK45BLISTS_GetDoubleListSize(doubleList_t dlinkedList){
    if (dlinkedList == NULL)
        return 0;
    return dlinkedList->size;
}

int RICK45BLISTS_TailAddDoubleListNode(void *key, doubleList_t dlinkedList)
{
    if (dlinkedList == NULL)
    {
        RICK45B_CopyString("Fatal Error: double linkedList is NULL! Before using it, please consider using RICK45BLISTS_DoubleListCreate to initialize the double linked list.", RICK45B.GetError, sizeof("Fatal Error: double linkedList is NULL! Before using it, please consider using RICK45BLISTS_DoubleListCreate to initialize the double linked list."));
        return -1;
    }
    if (key == NULL)
    {
        RICK45B_CopyString("Invalid Argument: key cannot be NULL!", RICK45B.GetError, sizeof("Invalid Argument: key cannot be NULL!"));
        return -1;
    }
    doubleListNode_t node = mallocFun(sizeof(struct doubleListNode));
    if (node == NULL)
    {
        RICK45B_CopyString("Fatal Error: Cannot allocate memory for new node. Maybe the heap is full?", RICK45B.GetError, sizeof("Fatal Error: Cannot allocate memory for new node. Maybe the heap is full?"));
        return -1;
    }

    node->next = NULL;
    node->previous = dlinkedList->tail;
    node->key = key;

    if (dlinkedList->tail == NULL || dlinkedList->head == NULL)  /*there's no Tail*/
    {
        dlinkedList->tail = node;
        dlinkedList->head = node;
    }
    else
    {
        dlinkedList->tail->next = node;
        dlinkedList->tail = node;
    }

    dlinkedList->size++;
    return 0;
}

int RICK45BLISTS_AddDoubleListNode(void *key, doubleList_t dlinkedList, size_t position)
{
    if (dlinkedList == NULL)
    {
        RICK45B_CopyString("Fatal Error: double linkedList is NULL! Before using it, please consider using RICK45BLISTS_DoubleListCreate to initialize the double linked list.", RICK45B.GetError, sizeof("Fatal Error: double linkedList is NULL! Before using it, please consider using RICK45BLISTS_DoubleListCreate to initialize the double linked list."));
        return -1;
    }
    if (key == NULL)
    {
        RICK45B_CopyString("Invalid Argument: key cannot be NULL!", RICK45B.GetError, sizeof("Invalid Argument: key cannot be NULL!"));
        return -1;
    }

    if (position > dlinkedList->size)
    {
        RICK45B_CopyString("Invalid Argument: Position value out of range for the given double linkedList!", RICK45B.GetError, sizeof("Invalid Argument: Position value out of range for the given double linkedList!"));
        return -1;
    }

    if (position == dlinkedList->size)
        RICK45BLISTS_TailAddDoubleListNode(key, dlinkedList);
    else
    {
        if (position == 0)
            RICK45BLISTS_HeadAddDoubleListNode(key, dlinkedList);
        else
        {
            doubleListNode_t node = NULL;
            node = mallocFun(sizeof(struct doubleListNode));
            if (node==NULL)
            {
                RICK45B_CopyString("Fatal Error: Cannot allocate memory for new node. Maybe the heap is full?", RICK45B.GetError, sizeof("Fatal Error: Cannot allocate memory for new node. Maybe the heap is full?"));
                return -1;
            }

            node->key = key;
            node->next = RICK45BLISTS_GetNodeByPositionDouble(dlinkedList, position);
            node->previous = node->next->previous;
            node->previous->next = node;
            node->next->previous = node;
            dlinkedList->size++;
        }
    }
    return 0;
}

doubleListNode_t RICK45BLISTS_GetNodeByPositionDouble(doubleList_t dlinkedList, size_t position)
{
    if (dlinkedList == NULL)
    {
        RICK45B_CopyString("Fatal Error: double linkedList is NULL! Before using it, please consider using RICK45BLISTS_DoubleListCreate to initialize the double linked list.", RICK45B.GetError, sizeof("Fatal Error: double linkedList is NULL! Before using it, please consider using RICK45BLISTS_DoubleListCreate to initialize the double linked list."));
        return NULL;
    }

    if (position > dlinkedList->size)
    {
        RICK45B_CopyString("Invalid Argument: Position value out of range for the given double linkedList!", RICK45B.GetError, sizeof("Invalid Argument: Position value out of range for the given double linkedList!"));
        return NULL;
    }

    if (position==0)
        return dlinkedList->head;
    if (position == dlinkedList->size-1)
        return dlinkedList->tail;

    doubleListNode_t temp = NULL;
    int i = 0;

    if (position>dlinkedList->size/2)   /*start from tail*/
    {
        temp = dlinkedList->tail;
        i = (int)dlinkedList->size-1;
        if (temp == NULL)
            return NULL;     /*no keys can be found*/

        while (temp->previous!=NULL && i>(int)position)
        {
            temp = temp->previous;
            i--;
        }
    }
    else    /*start from head*/
    {
        temp = dlinkedList->head;
        if (temp == NULL)
            return NULL;     /*no keys can be found*/

        while (temp->next!=NULL && i<(int)position)
        {
            temp = temp->next;
            i++;
        }
    }

    if (i==(int)position)
        return temp;

    return NULL;
}

doubleListNode_t RICK45BLISTS_GetNodeByKeyDouble(doubleList_t dlinkedList, void* key){

    if (dlinkedList == NULL)
    {
        RICK45B_CopyString("Fatal Error: double linkedList is NULL! Before using it, please consider using RICK45BLISTS_DoubleListCreate to initialize the double linked list.", RICK45B.GetError, sizeof("Fatal Error: double linkedList is NULL! Before using it, please consider using RICK45BLISTS_DoubleListCreate to initialize the double linked list."));
        return NULL;
    }
    if (key == NULL)
    {
        RICK45B_CopyString("Invalid Argument: key cannot be NULL!", RICK45B.GetError, sizeof("Invalid Argument: key cannot be NULL!"));
        return NULL;
    }
    if (dlinkedList->head == NULL && dlinkedList->tail == NULL)
    {
        RICK45B_CopyString("RICK45BLISTS_GetNodeByKeyDouble error: no key can be found!", RICK45B.GetError, sizeof("RICK45BLISTS_GetNodeByKeyDouble error: no key can be found!"));
        return NULL;     /*no keys can be found*/
    }

    doubleListNode_t temp = NULL;

    if (dlinkedList->key_cmp(dlinkedList->head->key, key)==0)
        temp = dlinkedList->head;
    else
    {
        if (dlinkedList->key_cmp(dlinkedList->tail->key, key)==0)
            temp = dlinkedList->tail;
        else
        {
            temp = dlinkedList->head;
            while (temp->next!=NULL && dlinkedList->key_cmp(temp->key, key))
                temp = temp->next;
        }
    }

    if (temp == NULL)
    {
        RICK45B_CopyString("RICK45BLISTS_GetNodeByKeyDouble error: no key can be found!", RICK45B.GetError, sizeof("RICK45BLISTS_GetNodeByKeyDouble error: no key can be found!"));
        return NULL;     /*no keys can be found*/
    }

    if (dlinkedList->key_cmp(temp->key, key)==0)
        return temp;

    RICK45B_CopyString("RICK45BLISTS_GetNodeByKeyDouble error: no key can be found!", RICK45B.GetError, sizeof("RICK45BLISTS_GetNodeByKeyDouble error: no key can be found!"));
    return NULL;
}

void *RICK45BLISTS_GetKeyByNodeDouble(doubleListNode_t node)
{
    return RICK45BLISTS_GetKeyByNode((listNode_t)node);
}

void *RICK45BLISTS_GetKeyByPositionDouble(doubleList_t dlinkedList, size_t position)
{
    if (dlinkedList == NULL)
    {
        RICK45B_CopyString("Fatal Error: double linkedList is NULL! Before using it, please consider using RICK45BLISTS_DoubleListCreate to initialize the double linked list.", RICK45B.GetError, sizeof("Fatal Error: double linkedList is NULL! Before using it, please consider using RICK45BLISTS_DoubleListCreate to initialize the double linked list."));
        return NULL;
    }

    if (position > dlinkedList->size)
    {
        RICK45B_CopyString("Invalid Argument: Position value out of range for the given double linkedList!", RICK45B.GetError, sizeof("Invalid Argument: Position value out of range for the given double linkedList!"));
        return NULL;
    }

    if (position==0)
        return dlinkedList->head->key;
    if (position == dlinkedList->size)
        return dlinkedList->tail->key;

    int i = 0;
    doubleListNode_t temp = NULL;

    if (position>dlinkedList->size/2)   /*start from tail*/
    {
        temp = dlinkedList->tail;
        i = (int)dlinkedList->size-1;
        if (temp == NULL)
        {
            RICK45B_CopyString("RICK45BLISTS_GetNodeByKeyDouble error: no key can be found!", RICK45B.GetError, sizeof("RICK45BLISTS_GetNodeByKeyDouble error: no key can be found!"));
            return NULL;     /*no keys can be found*/
        }

        while (temp->previous!=NULL && i>(int)position)
        {
            temp = temp->previous;
            i--;
        }
    }
    else    /*start from head*/
    {
        temp = dlinkedList->head;
        if (temp == NULL)
        {
            RICK45B_CopyString("RICK45BLISTS_GetNodeByKeyDouble error: no key can be found!", RICK45B.GetError, sizeof("RICK45BLISTS_GetNodeByKeyDouble error: no key can be found!"));
            return NULL;     /*no keys can be found*/
        }

        while (temp->next!=NULL && i<(int)position)
        {
            temp = temp->next;
            i++;
        }
    }

    if (i==(int)position)
        return temp->key;

    RICK45B_CopyString("RICK45BLISTS_GetNodeByKeyDouble error: no key can be found!", RICK45B.GetError, sizeof("RICK45BLISTS_GetNodeByKeyDouble error: no key can be found!"));
    return NULL;
}

void *RICK45BLISTS_SetKeyByPositionDouble(doubleList_t dlinkedList, void* newkey, size_t position)
{
    if (dlinkedList == NULL)
    {
        RICK45B_CopyString("Fatal Error: double linkedList is NULL! Before using it, please consider using RICK45BLISTS_DoubleListCreate to initialize the double linked list.", RICK45B.GetError, sizeof("Fatal Error: double linkedList is NULL! Before using it, please consider using RICK45BLISTS_DoubleListCreate to initialize the double linked list."));
        return NULL;
    }

    if (position > dlinkedList->size)
    {
        RICK45B_CopyString("Invalid Argument: Position value out of range for the given double linkedList!", RICK45B.GetError, sizeof("Invalid Argument: Position value out of range for the given double linkedList!"));
        return NULL;
    }

    if (newkey == NULL)
    {
        RICK45B_CopyString("Invalid Argument: new key cannot be NULL!", RICK45B.GetError, sizeof("Invalid Argument: new key cannot be NULL!"));
        return NULL;
    }

    doubleListNode_t temp = NULL;
    temp = RICK45BLISTS_GetNodeByPositionDouble(dlinkedList, position);
    if (temp == NULL)
    {
        RICK45B_CopyString("Fatal error: couldn't fetch node at that position!", RICK45B.GetError, sizeof("Fatal error: couldn't fetch node at that position!"));
        return NULL;
    }

    void *out = temp->key;
    temp->key = newkey;
    return out;
}

void *RICK45BLISTS_SetKeyByNodeDouble(doubleList_t dlinkedList, void* newkey, doubleListNode_t node)
{
    if (dlinkedList == NULL)
    {
        RICK45B_CopyString("Fatal Error: double linkedList is NULL! Before using it, please consider using RICK45BLISTS_DoubleListCreate to initialize the double linked list.", RICK45B.GetError, sizeof("Fatal Error: double linkedList is NULL! Before using it, please consider using RICK45BLISTS_DoubleListCreate to initialize the double linked list."));
        return NULL;
    }

    if (node == NULL)
    {
        RICK45B_CopyString("Fatal error: Node cannot be NULL!", RICK45B.GetError, sizeof("Fatal error: Node cannot be NULL!"));
        return NULL;
    }

    if (newkey == NULL)
    {
        RICK45B_CopyString("Invalid Argument: new key cannot be NULL!", RICK45B.GetError, sizeof("Invalid Argument: new key cannot be NULL!"));
        return NULL;
    }

    if (dlinkedList->head == NULL)
    {
        RICK45B_CopyString("Head of the double linkedList is NULL! Please consider adding some nodes first!", RICK45B.GetError, sizeof("Head of the double linkedList is NULL! Please consider adding some nodes first!"));
        return NULL;
    }

    doubleListNode_t temp = NULL;
    if (node == dlinkedList->head)
        temp = dlinkedList->head;
    else
    {
        if (node == dlinkedList->tail)
            temp = dlinkedList->tail;
        else
        {
            temp = dlinkedList->head;
            while (temp->next!=NULL && temp!=node)
                temp = temp->next;
        }
    }
    void *out = node->key;
    temp->key = newkey;
    return out;
}

int RICK45BLISTS_SetKeyByKeyDouble(doubleList_t dlinkedList, void* newkey, void* oldkey)
{
    if (dlinkedList == NULL)
    {
        RICK45B_CopyString("Fatal Error: double linkedList is NULL! Before using it, please consider using RICK45BLISTS_DoubleListCreate to initialize the double linked list.", RICK45B.GetError, sizeof("Fatal Error: double linkedList is NULL! Before using it, please consider using RICK45BLISTS_DoubleListCreate to initialize the double linked list."));
        return -1;
    }

    if (newkey == NULL || oldkey == NULL)
    {
        RICK45B_CopyString("Fatal Error: keys cannot be NULL!", RICK45B.GetError, sizeof("Fatal Error: keys cannot be NULL!"));
        return -1;
    }

    int cnt = 0;
    if (dlinkedList->head == NULL && dlinkedList->tail == NULL)
        return cnt;

    doubleListNode_t temp = dlinkedList->head;

    while (temp!=NULL)
    {
        if (dlinkedList->key_cmp(temp->key, oldkey)==0)
        {
            temp->key = newkey;
            cnt++;
        }
        temp = temp->next;
    }
    return cnt;
}

int RICK45BLISTS_RemoveNodeDouble(doubleList_t dlinkedList, size_t position, int delete_bool)
{
    if (dlinkedList == NULL)
    {
        RICK45B_CopyString("Fatal Error: double linkedList is NULL! Before using it, please consider using RICK45BLISTS_DoubleListCreate to initialize the double linked list.", RICK45B.GetError, sizeof("Fatal Error: double linkedList is NULL! Before using it, please consider using RICK45BLISTS_DoubleListCreate to initialize the double linked list."));
        return -1;
    }

    if (dlinkedList->head != NULL)
    {
        if (position > dlinkedList->size)    /*position is out of bound!!*/
        {
            RICK45B_CopyString("Invalid Argument: Position value out of range for the given double linkedList!", RICK45B.GetError, sizeof("Invalid Argument: Position value out of range for the given double linkedList!"));
            return -1;
        }

        doubleListNode_t temp = NULL;
        temp = RICK45BLISTS_GetNodeByPositionDouble(dlinkedList, position);

        if (position == dlinkedList->size-1)   /*i want to delete the tail!*/
            RICK45BLISTS_RemoveTailDouble(dlinkedList, delete_bool);
        else
        {
            if (position == 0)  /*i want to delete the head!*/
                RICK45BLISTS_DoubleListRemoveHead(dlinkedList, delete_bool);
            else    /*i want to delete something else*/
            {

                if (temp==dlinkedList->pointedNode)
                    dlinkedList->pointedNode = dlinkedList->pointedNode->previous;
                temp->previous->next = temp->next;
                temp->next->previous = temp->previous;


                if (delete_bool == FALSE)
                    freeFun(temp);
                else
                {
                    freeFun(temp->key);
                    freeFun(temp);
                }
                dlinkedList->size--;
            }
        }
        return 0;
    }
    else
    {
        RICK45B_CopyString("Head of the double linkedList is NULL! Please consider adding some nodes first!", RICK45B.GetError, sizeof("Head of the double linkedList is NULL! Please consider adding some nodes first!"));
        dlinkedList->tail = NULL;  /*if head is null, the tail must be as well.*/
        return -1;
    }
}

int RICK45BLISTS_RemoveTailDouble(doubleList_t dlinkedList, int delete_bool)
{
    if (dlinkedList == NULL)
    {
        RICK45B_CopyString("Fatal Error: double linkedList is NULL! Before using it, please consider using RICK45BLISTS_DoubleListCreate to initialize the double linked list.", RICK45B.GetError, sizeof("Fatal Error: double linkedList is NULL! Before using it, please consider using RICK45BLISTS_DoubleListCreate to initialize the double linked list."));
        return -1;
    }

    if (dlinkedList->tail != NULL)
    {
        doubleListNode_t temp = NULL;
        temp = RICK45BLISTS_GetNodeByPositionDouble(dlinkedList, RICK45BLISTS_GetDoubleListSize(dlinkedList)-2);
        temp -> next = NULL;
        if (dlinkedList->tail == dlinkedList->pointedNode)
            dlinkedList->pointedNode = temp;

        if (delete_bool == TRUE)
            freeFun(dlinkedList->tail->key);
        freeFun(dlinkedList->tail);

        dlinkedList->tail = temp;
        dlinkedList->size--;

        return 0;
    }
    else                        /*if tail is null, head must be as well.*/
    {
        RICK45B_CopyString("Tail of the double linkedList is NULL! Please consider adding some nodes first!", RICK45B.GetError, sizeof("Tail of the double linkedList is NULL! Please consider adding some nodes first!"));
        dlinkedList->head = NULL;
        return -1;
    }
}

int RICK45BLISTS_RemoveNodeByKeyDouble(doubleList_t dlinkedList, void *key, int delete_bool)
{
    if (dlinkedList == NULL)
    {
        RICK45B_CopyString("Fatal Error: double linkedList is NULL! Before using it, please consider using RICK45BLISTS_DoubleListCreate to initialize the double linked list.", RICK45B.GetError, sizeof("Fatal Error: double linkedList is NULL! Before using it, please consider using RICK45BLISTS_DoubleListCreate to initialize the double linked list."));
        return -1;
    }

    if (key == NULL)
    {
        RICK45B_CopyString("Invalid Argument: key cannot be NULL!", RICK45B.GetError, sizeof("Invalid Argument: key cannot be NULL!"));
        return -1;
    }

    doubleListNode_t temp = dlinkedList->head;
    doubleListNode_t old = dlinkedList->head;

    if (temp == NULL)
    {
        return 0;
    }

    while (temp->next!=NULL && dlinkedList->key_cmp(temp->key, key))
    {
        old = temp;
        temp = temp->next;
    }

    if (dlinkedList->key_cmp(temp->key, key)==0)   /*node with given key was found.*/
    {
        if (dlinkedList->head == temp)
            RICK45BLISTS_DoubleListRemoveHead(dlinkedList, delete_bool);
        else
        {
            if (dlinkedList->tail == temp)
                RICK45BLISTS_RemoveTailDouble(dlinkedList, delete_bool);
            else
            {
                if (dlinkedList->pointedNode == temp)
                    dlinkedList->pointedNode = dlinkedList->pointedNode->previous;
                old->next = temp->next;
                temp->next->previous = old;

                if (delete_bool == TRUE)
                    freeFun(temp->key);
                freeFun(temp);
                dlinkedList->size--;
            }
        }
        return 1;
    }
    return 0;
}

int RICK45BLISTS_RemoveAllNodesByKeyDouble(doubleList_t dlinkedList, void *key, int delete_bool)
{
    int cnt = 0;
    if (RICK45BLISTS_RemoveNodeByKeyDouble(dlinkedList, key, delete_bool)==-1)
        return -1;
    cnt++;
    while (RICK45BLISTS_RemoveNodeByKeyDouble(dlinkedList, key, delete_bool)>0)
        cnt++;
    return cnt;
}
