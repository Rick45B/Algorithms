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

void destroy_createListTEST();
void insert_removeListTEST();
void GetterSetterListTEST();
void ErrorListTEST();
void destroy_createDoubleListTEST();
void insert_removeDoubleListTEST();
void ErrorDoubleListTEST();
void nextPreviousTESTS();
void VisualizerDouble(list_t list)
{
    if (list == NULL)
        printf("list is null!\n");
    else
    {
        if (list->head == NULL)
            printf("list is empty!\n");
        else
        {
            listNode_t temp = list->head;
            while (temp!=NULL)
            {
                printf(" %f ->", *((double*)temp->key));
                temp = temp->next;
            }
            printf(" NULL\n\n");
        }
    }
}

void VisualizerString(list_t list)
{
    if (list == NULL)
        printf("list is null!\n");
    else
    {
        if (list->head == NULL)
            printf("list is empty!\n");
        else
        {
            listNode_t temp = list->head;
            while (temp!=NULL)
            {
                printf(" %s ->", ((char *)temp->key));
                temp = temp->next;
            }
            printf(" NULL\n\n");
        }
    }
}

void DoubleListVisualizerString(doubleList_t list)
{
    if (list == NULL)
        printf("double linked list is null!\n");
    else
    {
        if (list->head == NULL)
            printf("double linked list is empty!\n");
        else
        {
            doubleListNode_t temp = list->head;
            doubleListNode_t old = NULL;
            int cnt = 0;
            while (temp!=NULL)
            {
                if (cnt!=0)
                {
                    if (old!=temp->previous)
                    {
                        printf("corrupted double linked list!\n");
                        break;
                    }
                    printf(" %s <->", ((char *)temp->key));
                    old = temp;
                    temp = temp->next;
                }
                else
                {
                    printf(" %s <->", ((char *)temp->key));
                    old = temp;
                    temp = temp->next;
                }
                cnt++;
            }
            printf(" NULL\n\n");
        }
    }
}

int RICK45B_DoubleCMP(const void *a, const void *b);

int main()
{
    /*starting the library*/
    RICK45B_LibStart(malloc, free);

    /*list tests*/
    destroy_createListTEST();
    printf("\n***destroy_createListTEST successful***\n\n");
    insert_removeListTEST();
    printf("***insert_removeListTEST successful***\n\n");
    GetterSetterListTEST();
    printf("***GetterSetterListTEST successful***\n\n");
    ErrorListTEST();
    printf("***ErrorListTEST successful***\n\n");

    /*double linked list tests*/
    destroy_createDoubleListTEST();
    printf("***destroy_createDoubleListTEST successful***\n\n");
    ErrorDoubleListTEST();
    printf("***ErrorDoubleListTEST successful***\n\n");
    insert_removeDoubleListTEST();
    printf("\n***insert_removeDoubleListTEST successful***\n\n");

    /*misc tests*/
    nextPreviousTESTS();
    printf("***nextPreviousTESTS was successful***\n\n");
    printf("\n***All test were successful***\n\n");
    return 0;
}

int RICK45B_DoubleCMP(const void *a, const void *b){
    if (a==NULL || b==NULL)
    {
        perror("Fatal Error: arguments cannot be NULL!");
        exit(1);
    }
    const double *aa = a;
    const double *bb = b;
    return (*aa > *bb) - (*aa < *bb);

}

void destroy_createListTEST()
{
    /*create a new list*/
    list_t temp = NULL;
    temp = RICK45BLISTS_ListCreate(RICK45B_DoubleCMP);
    assert(temp != NULL);
    /*destroy list*/
    RICK45BLISTS_ListDestroy(&temp, 1);
}

void insert_removeListTEST()
{
    /*create a new list*/
    list_t temp = NULL;
    temp = RICK45BLISTS_ListCreate(RICK45B_DoubleCMP);
    assert(temp != NULL);
    double array_keys[] = {1.0, 3.9, -2, 7.3, 9.81, 347, 8250.72};
    int cnt;  /*counter variable.ì, used for some loop iterations for comfier debug.*/
    double *mallocd = malloc(sizeof(double));
    *mallocd = 12.75;

    /*add a few elements to it*/
    RICK45BLISTS_HeadAddListNode(&array_keys[0], temp);  /*1 -> NULL*/
    RICK45BLISTS_TailAddListNode(&array_keys[1], temp);  /*1 -> 3.9 -> NULL*/
    RICK45BLISTS_AddListNode(&array_keys[5], temp, 0);   /*347 -> 1 -> 3.9 -> NULL*/
    RICK45BLISTS_TailAddListNode(&array_keys[2], temp);  /*347 -> 1 -> 3.9 -> -2 -> NULL*/
    /*check if i have the right amount of nodes*/
    assert(RICK45BLISTS_GetListSize(temp)==4);

    /*add some more nodes, and check if the amount is right*/
    RICK45BLISTS_AddListNode(&array_keys[5], temp, 3);   /*347 -> 1 -> 3.9 -> 347 -> -2 -> NULL*/
    RICK45BLISTS_AddListNode(&array_keys[4], temp, 1);   /*347 -> 9.81 -> 1 -> 3.9 -> 347 -> -2 -> NULL*/
    assert(RICK45BLISTS_GetListSize(temp)==6);

    RICK45BLISTS_TailAddListNode(&array_keys[3], temp);  /*347 -> 9.81 -> 1 -> 3.9 -> 347 -> -2 -> 7.3 -> NULL*/
    RICK45BLISTS_HeadAddListNode(&array_keys[6], temp);  /*8250.72 -> 347 -> 9.81 -> 1 -> 3.9 -> 347 -> -2 -> 7.3 -> NULL*/
    assert(RICK45BLISTS_GetListSize(temp)==8);
    printf("Initial list: \n");
    VisualizerDouble(temp);  /*used for debugging purposes :D*/

    /*removing some nodes, while checking if the list's size is correct*/
    printf("List after removing the head node: \n");
    RICK45BLISTS_RemoveHead(temp, 0);   /*347 -> 9.81 -> 1 -> 3.9 -> 347 -> -2 -> 7.3 -> NULL*/
    VisualizerDouble(temp);  /*used for debugging purposes :D*/
    assert(RICK45BLISTS_GetListSize(temp)==7);

    printf("List after removing some random nodes: \n");
    RICK45BLISTS_RemoveNode(temp, 3, 0);  /*347 -> 9.81 -> 1 -> 347 -> -2 -> 7.3 -> NULL*/
    RICK45BLISTS_RemoveNode(temp, 5, 0);  /*347 -> 9.81 -> 1 -> 347 -> -2 -> NULL*/
    VisualizerDouble(temp);  /*used for debugging purposes :D*/
    RICK45BLISTS_RemoveNode(temp, 3, 0);  /*347 -> 9.81 -> 1 -> -2 -> NULL*/
    RICK45BLISTS_RemoveNode(temp, 0, 0);  /*9.81 -> 1 -> -2 -> NULL*/
    assert(RICK45BLISTS_GetListSize(temp)==3);
    VisualizerDouble(temp);  /*used for debugging purposes :D*/

    /*testing the RICK45BLISTS_RemoveTail*/
    RICK45BLISTS_HeadAddListNode(&array_keys[0], temp);  /*1 -> 9.81 -> 1 -> -2 -> NULL*/
    RICK45BLISTS_TailAddListNode(&array_keys[1], temp);  /*1 -> 9.81 -> 1 -> -2 -> 3.9 -> NULL*/
    printf("List before removing some nodes in the tail: \n");
    VisualizerDouble(temp);
    RICK45BLISTS_RemoveTail(temp, 0);   /*1 -> 9.81 -> 1 -> -2 -> NULL*/
    RICK45BLISTS_RemoveTail(temp, 0);   /*1 -> 9.81 -> 1 -> NULL*/
    printf("List after removing some nodes in the tail: \n");
    VisualizerDouble(temp);

    /*clear the list, without destroying it. Then, add a node to it.*/
    printf("List after clearing it: \n");
    RICK45BLISTS_RemoveAllNodes(temp, 0);
    assert(RICK45BLISTS_GetListSize(temp) == 0);
    VisualizerDouble(temp);  /*used for debugging purposes :D*/
    printf("List after adding two nodes on the head: \n");
    RICK45BLISTS_HeadAddListNode(&array_keys[1], temp);
    RICK45BLISTS_HeadAddListNode(&array_keys[5], temp);
    assert(RICK45BLISTS_GetListSize(temp) == 2);
    VisualizerDouble(temp);

    /*clear the list, and add a few nodes to it*/
    RICK45BLISTS_RemoveAllNodes(temp, 0);
    for (cnt=0; cnt<4; cnt++)
        RICK45BLISTS_HeadAddListNode(&array_keys[cnt], temp);  /*7.300000 -> -2.000000 -> 3.900000 -> 1.000000 -> NULL*/
    assert(RICK45BLISTS_GetListSize(temp)==4);
    printf("New List after adding 4 elements to it: \n");
    VisualizerDouble(temp);
    RICK45BLISTS_RemoveNodeByKey(temp, &array_keys[2], 0);  /*7.300000 -> 3.900000 -> 1.000000 -> NULL*/
    printf("List after removing node with key '-2': \n");
    VisualizerDouble(temp);
    assert(RICK45BLISTS_GetListSize(temp)==3);
    RICK45BLISTS_RemoveNodeByKey(temp, &array_keys[3], 0);  /*3.900000 -> 1.000000 -> NULL*/
    printf("List after removing node with key '7.3': \n");
    VisualizerDouble(temp);
    assert(RICK45BLISTS_GetListSize(temp)==2);
    RICK45BLISTS_RemoveNodeByKey(temp, &array_keys[0], 0);  /*3.900000 -> NULL*/
    printf("List after removing node with key '1': \n");
    VisualizerDouble(temp);
    assert(RICK45BLISTS_GetListSize(temp)==1);

    /*destroy the list*/
    RICK45BLISTS_ListDestroy(&temp, 0);
    assert(temp==NULL);
    printf("List after destroying it: \n");
    VisualizerDouble(temp);  /*used for debugging purposes :D*/

    /*create a new one, with a few nodes with equal keys*/
    list_t temp2 = NULL;
    temp2 = RICK45BLISTS_ListCreate(RICK45B_DoubleCMP);
    for (cnt=0; cnt<4; cnt++)
        RICK45BLISTS_TailAddListNode(&array_keys[6], temp2);  /*8250.72 -> 8250.72 -> 8250.72 -> 8250.72 -> NULL*/
    RICK45BLISTS_HeadAddListNode(&array_keys[0], temp2);    /*1 -> 8250.72 -> 8250.72 -> 8250.72 -> 8250.72 -> NULL*/
    assert(RICK45BLISTS_GetListSize(temp2)==5);
    printf("New List with some duplicates: \n");
    VisualizerDouble(temp2);
    assert(RICK45BLISTS_RemoveAllNodesByKey(temp2, &array_keys[6], 0)==4);
    assert(RICK45BLISTS_GetListSize(temp2)==1);
    printf("List after removing all '8250.72' keys: \n");
    VisualizerDouble(temp2);

    /*testing library functions with heap-allocated data.*/
    RICK45BLISTS_HeadAddListNode(mallocd, temp2);    /*12.75 -> 1 -> NULL*/
    assert(RICK45BLISTS_GetListSize(temp2)==2);
    RICK45BLISTS_RemoveHead(temp2, 1);
    assert(RICK45BLISTS_GetListSize(temp2)==1);
    mallocd = malloc(sizeof(double));
    *mallocd = 12.75;
    RICK45BLISTS_TailAddListNode(mallocd, temp2);    /*1 -> 12.75 -> NULL*/
    assert(RICK45BLISTS_GetListSize(temp2)==2);
    RICK45BLISTS_RemoveNodeByKey(temp2, mallocd, 1);
    assert(RICK45BLISTS_GetListSize(temp2)==1);
    mallocd = malloc(sizeof(double));
    *mallocd = 12.75;
    double *mallocd2 = malloc(sizeof(double));
    *mallocd2 = 768.098;
    RICK45BLISTS_TailAddListNode(mallocd, temp2);
    RICK45BLISTS_AddListNode(mallocd2, temp2, 0);   /*768.098 -> 1 -> 12.75 -> NULL*/
    assert(RICK45BLISTS_GetListSize(temp2)==3);
    RICK45BLISTS_RemoveNode(temp2, 2, 1);   /*768.098 -> 1 -> NULL*/
    RICK45BLISTS_RemoveTail(temp2, 0);   /*768.098 -> NULL*/
    assert(RICK45BLISTS_GetListSize(temp2)==1);

    /*destroy the new list*/
    RICK45BLISTS_ListDestroy(&temp2, 1);
    assert(temp2==NULL);


    printf("\n");
}

void GetterSetterListTEST(){

    /*create a new list with a few elements to it*/
    list_t temp = NULL;
    temp = RICK45BLISTS_ListCreate((RICK45B_comparator_t)strcmp);
    assert(temp != NULL);

    char array_keys[][20] = {"car", "pipes", "navigator", "max", "dog", "foo", "bar"};
    char *temp_str = "table";
    RICK45BLISTS_HeadAddListNode(array_keys[0], temp);  /*car -> NULL*/
    RICK45BLISTS_TailAddListNode(array_keys[6], temp);  /*car -> bar -> NULL*/
    RICK45BLISTS_AddListNode(array_keys[3], temp, 1);   /*car -> max -> bar -> NULL*/
    assert(RICK45BLISTS_GetListSize(temp)==3);
    VisualizerString(temp);

    /*testing getter functions*/
    /*testing RICK45BLISTS_GetNodeByPosition*/
    listNode_t out = NULL;

    out = RICK45BLISTS_GetNodeByPosition(temp, 0);
    printf("Value of node of index 0: %s\n", (char *)(out->key));
    assert(out!=NULL && strcmp((char*)out->key, "car")==0);

    out = RICK45BLISTS_GetNodeByPosition(temp, 1);
    printf("Value of node of index 1: %s\n", (char *)(out->key));
    assert(out!=NULL && strcmp((char*)out->key, "max")==0);

    out = RICK45BLISTS_GetNodeByPosition(temp, 2);
    printf("Value of node of index 2: %s\n", (char *)(out->key));
    assert(out!=NULL && strcmp((char*)out->key, "bar")==0);

    out = RICK45BLISTS_GetNodeByPosition(temp, 3);
    printf("Value of node of index 3: NULL\n");
    assert(out==NULL);

    /*testing RICK45BLISTS_GetNodeByKey*/
    out = RICK45BLISTS_GetNodeByKey(temp, "max");
    assert(out!=NULL && strcmp((char*)out->key, "max")==0);
    out = RICK45BLISTS_GetNodeByKey(temp, "car");
    assert(out!=NULL && strcmp((char*)out->key, "car")==0);
    out = RICK45BLISTS_GetNodeByKey(temp, "dog");
    assert(out==NULL);

    /*testing RICK45BLISTS_GetKeyByNode*/
    char *key = NULL;
    out = RICK45BLISTS_GetNodeByKey(temp, "car");
    key = RICK45BLISTS_GetKeyByNode(out);
    printf("Key of node with address %p: %s\n\n", (void *)out, (char *)key);
    assert(strcmp((char *)key, "car")==0);

    /*testing RICK45BLISTS_GetKeyByPosition*/
    key = RICK45BLISTS_GetKeyByPosition(temp, 0);
    assert(strcmp((char *)key, "car")==0);
    key = RICK45BLISTS_GetKeyByPosition(temp, 1);
    assert(strcmp((char *)key, "max")==0);
    key = RICK45BLISTS_GetKeyByPosition(temp, 2);
    assert(strcmp((char *)key, "bar")==0);

    /*testing setter functions*/
    printf("List before using setter functions: \n");  /*car -> max -> bar -> NULL*/
    VisualizerString(temp);
    assert(strcmp(RICK45BLISTS_SetKeyByPosition(temp, array_keys[2], 0), "car")==0);  /*navigator -> max -> bar -> NULL*/
    assert(strcmp(RICK45BLISTS_SetKeyByPosition(temp, array_keys[1], 1), "max")==0);  /*navigator -> pipes -> bar -> NULL*/
    RICK45BLISTS_TailAddListNode(array_keys[4], temp);  /*navigator -> pipes -> bar -> dog -> NULL*/
    assert(strcmp(RICK45BLISTS_SetKeyByPosition(temp, array_keys[5], 3), "dog")==0);  /*navigator -> pipes -> bar -> foo -> NULL*/
    out = RICK45BLISTS_GetNodeByPosition(temp, 1);
    assert(strcmp(RICK45BLISTS_SetKeyByNode(temp, array_keys[0], out), "pipes")==0);    /*navigator -> car -> bar -> foo -> NULL*/
    assert(strcmp(RICK45BLISTS_SetKeyByNode(temp, temp_str, out), "car")==0);   /*navigator -> table -> bar -> foo -> NULL*/
    assert(RICK45BLISTS_SetKeyByKey(temp, "bread", "Wilson")==0);   /*navigator -> table -> bar -> foo -> NULL*/
    assert(RICK45BLISTS_SetKeyByKey(temp, "bread", NULL)==-1);   /*navigator -> table -> bar -> foo -> NULL*/
    assert(RICK45BLISTS_SetKeyByKey(temp, "bread", "table")==1);   /*navigator -> bread -> bar -> foo -> NULL*/
    assert(RICK45BLISTS_SetKeyByKey(temp, "bread", "foo")==1);   /*navigator -> bread -> bar -> bread -> NULL*/
    assert(RICK45BLISTS_SetKeyByKey(temp, "bread", "navigator")==1);   /*bread -> bread -> bar -> bread -> NULL*/
    assert(RICK45BLISTS_SetKeyByKey(temp, "paul", "bread")==3);   /*paul -> paul -> bar -> paul -> NULL*/

    printf("List after using setter functions: \n\n");
    VisualizerString(temp);

    /*testing the 'Next'/'hasNext' functions*/
    assert(RICK45BLISTS_GetCurrentNode(temp)==NULL);
    assert(RICK45BLISTS_RewindList(temp)==0);
    assert(RICK45BLISTS_GetCurrentNode(temp)==RICK45BLISTS_GetNodeByPosition(temp, 0));
    assert(RICK45BLISTS_HasNext(temp)==1);
    RICK45BLISTS_GetNextNode(temp);
    assert(RICK45BLISTS_GetCurrentNode(temp)==RICK45BLISTS_GetNodeByPosition(temp, 1));
    assert(RICK45BLISTS_GetNextNode(temp)==RICK45BLISTS_GetNodeByKey(temp, "bar"));
    RICK45BLISTS_RemoveNode(temp, 2, 0);    /*paul -> paul -> paul -> NULL*/
    assert(RICK45BLISTS_GetCurrentNode(temp)==RICK45BLISTS_GetNodeByPosition(temp, 1) && RICK45BLISTS_GetNextNode(temp)==RICK45BLISTS_GetNodeByPosition(temp, 2));
    RICK45BLISTS_RemoveAllNodes(temp, 0);
    assert(RICK45BLISTS_GetCurrentNode(temp)==NULL);

    /*destroy the list*/
    RICK45BLISTS_ListDestroy(&temp, 0);
    assert(temp==NULL);
}

void ErrorListTEST()
{
    list_t list = NULL;
    list = RICK45BLISTS_ListCreate((RICK45B_comparator_t)strcmp);

    /*testing errors and error messages*/
    list_t temp = NULL;
    temp = RICK45BLISTS_ListCreate(NULL);
    assert(temp == NULL && strcmp(RICK45B_GetError(), "Invalid Argument: key_cmp function cannot be NULL!")==0);

    assert(RICK45BLISTS_HeadAddListNode(NULL, list)==-1 && strcmp(RICK45B_GetError(), "Invalid Argument: key cannot be NULL!")==0);
    assert(RICK45BLISTS_HeadAddListNode("bob", NULL)==-1 && strcmp(RICK45B_GetError(), "Fatal Error: List is NULL! Before using it, please consider using RICK45BLISTS_ListCreate to initialize the list.")==0);
    assert(RICK45BLISTS_TailAddListNode(NULL, list)==-1 && strcmp(RICK45B_GetError(), "Invalid Argument: key cannot be NULL!")==0);
    assert(RICK45BLISTS_TailAddListNode("bob", NULL)==-1 && strcmp(RICK45B_GetError(), "Fatal Error: List is NULL! Before using it, please consider using RICK45BLISTS_ListCreate to initialize the list.")==0);
    assert(RICK45BLISTS_AddListNode(NULL, list, 0)==-1 && strcmp(RICK45B_GetError(), "Invalid Argument: key cannot be NULL!")==0);
    assert(RICK45BLISTS_AddListNode("bob", NULL, 0)==-1 && strcmp(RICK45B_GetError(), "Fatal Error: List is NULL! Before using it, please consider using RICK45BLISTS_ListCreate to initialize the list.")==0);
    assert(RICK45BLISTS_AddListNode("bob", list, 4)==-1 && strcmp(RICK45B_GetError(), "Invalid Argument: Position value out of range for the given linkedList!")==0);

    assert(RICK45BLISTS_GetNodeByPosition(NULL, 0)==NULL && strcmp(RICK45B_GetError(), "Fatal Error: List is NULL! Before using it, please consider using RICK45BLISTS_ListCreate to initialize the list.")==0);
    assert(RICK45BLISTS_GetNodeByPosition(list, 100)==NULL && strcmp(RICK45B_GetError(), "Invalid Argument: Position value out of range for the given linkedList!")==0);
    assert(RICK45BLISTS_GetNodeByKey(NULL, "bob")==NULL && strcmp(RICK45B_GetError(), "Fatal Error: List is NULL! Before using it, please consider using RICK45BLISTS_ListCreate to initialize the list.")==0);
    assert(RICK45BLISTS_GetNodeByKey(list, NULL)==NULL && strcmp(RICK45B_GetError(), "Invalid Argument: key cannot be NULL!")==0);
    assert(RICK45BLISTS_GetNodeByKey(list, "alice")==NULL && strcmp(RICK45B_GetError(), "RICK45BLISTS_GetNodeByKey error: no key can be found!")==0);
    assert(RICK45BLISTS_GetKeyByNode(NULL)==NULL && strcmp(RICK45B_GetError(), "Invalid Argument: Node cannot be NULL!")==0);
    assert(RICK45BLISTS_GetKeyByPosition(NULL, 0)==NULL && strcmp(RICK45B_GetError(), "Fatal Error: List is NULL! Before using it, please consider using RICK45BLISTS_ListCreate to initialize the list.")==0);
    assert(RICK45BLISTS_GetKeyByPosition(list, 300)==NULL && strcmp(RICK45B_GetError(), "Invalid Argument: Position value out of range for the given linkedList!")==0);

    assert(RICK45BLISTS_SetKeyByPosition(NULL, "can", 0)==NULL && strcmp(RICK45B_GetError(), "Fatal Error: List is NULL! Before using it, please consider using RICK45BLISTS_ListCreate to initialize the list.")==0);
    assert(RICK45BLISTS_SetKeyByPosition(list, NULL, 0)==NULL && strcmp(RICK45B_GetError(), "Invalid Argument: new key cannot be NULL!")==0);
    assert(RICK45BLISTS_SetKeyByPosition(list, "can", 300)==NULL && strcmp(RICK45B_GetError(), "Invalid Argument: Position value out of range for the given linkedList!")==0);
    assert(RICK45BLISTS_SetKeyByNode(NULL, "can", NULL)==NULL && strcmp(RICK45B_GetError(), "Fatal Error: List is NULL! Before using it, please consider using RICK45BLISTS_ListCreate to initialize the list.")==0);
    assert(RICK45BLISTS_SetKeyByNode(list, NULL, NULL)==NULL && strcmp(RICK45B_GetError(), "Fatal error: Node cannot be NULL!")==0);
    RICK45BLISTS_HeadAddListNode("brick", list);
    listNode_t temp_node = RICK45BLISTS_GetNodeByKey(list, "brick");
    assert(RICK45BLISTS_SetKeyByNode(list, NULL, temp_node)==NULL && strcmp(RICK45B_GetError(), "Invalid Argument: new key cannot be NULL!")==0);
    RICK45BLISTS_RemoveAllNodes(list, 0);
    assert(RICK45BLISTS_SetKeyByNode(list, "can", temp_node)==NULL && strcmp(RICK45B_GetError(), "Head of the list is NULL! Please consider adding some nodes first!")==0);
    assert(RICK45BLISTS_SetKeyByKey(list, "can", NULL)==-1 && strcmp(RICK45B_GetError(), "Fatal Error: keys cannot be NULL!")==0);
    assert(RICK45BLISTS_SetKeyByKey(list, NULL, "can")==-1 && strcmp(RICK45B_GetError(), "Fatal Error: keys cannot be NULL!")==0);
    assert(RICK45BLISTS_SetKeyByKey(NULL, "dog", "can")==-1 && strcmp(RICK45B_GetError(), "Fatal Error: List is NULL! Before using it, please consider using RICK45BLISTS_ListCreate to initialize the list.")==0);

    assert(RICK45BLISTS_RemoveHead(NULL, 0)==-1 && strcmp(RICK45B_GetError(), "Fatal Error: List is NULL! Before using it, please consider using RICK45BLISTS_ListCreate to initialize the list.")==0);
    assert(RICK45BLISTS_RemoveNode(NULL, 0, 0)==-1 && strcmp(RICK45B_GetError(), "Fatal Error: List is NULL! Before using it, please consider using RICK45BLISTS_ListCreate to initialize the list.")==0);
    assert(RICK45BLISTS_RemoveNode(list, 300, 0)==-1 && strcmp(RICK45B_GetError(), "Head of the list is NULL! Please consider adding some nodes first!")==0);
    RICK45BLISTS_HeadAddListNode("brick", list);
    assert(RICK45BLISTS_RemoveNode(list, 300, 0)==-1 && strcmp(RICK45B_GetError(), "Invalid Argument: Position value out of range for the given linkedList!")==0);
    RICK45BLISTS_RemoveAllNodes(list, 0);
    assert(RICK45BLISTS_RemoveTail(NULL, 0)==-1 && strcmp(RICK45B_GetError(), "Fatal Error: List is NULL! Before using it, please consider using RICK45BLISTS_ListCreate to initialize the list.")==0);
    assert(RICK45BLISTS_RemoveTail(list, 0)==-1 && strcmp(RICK45B_GetError(), "Tail of the list is NULL! Please consider adding some nodes first!")==0);
    assert(RICK45BLISTS_RemoveNodeByKey(NULL, "bob", 0)==-1 && strcmp(RICK45B_GetError(), "Fatal Error: List is NULL! Before using it, please consider using RICK45BLISTS_ListCreate to initialize the list.")==0);
    assert(RICK45BLISTS_RemoveNodeByKey(list, NULL, 0)==-1 && strcmp(RICK45B_GetError(), "Invalid Argument: key cannot be NULL!")==0);
    assert(RICK45BLISTS_RemoveAllNodesByKey(list, NULL, 0)==-1 && strcmp(RICK45B_GetError(), "Invalid Argument: key cannot be NULL!")==0);

    RICK45BLISTS_ListDestroy(&list, 0);
}

void destroy_createDoubleListTEST()
{
    /*create double linked list*/
    doubleList_t temp = NULL;
    temp = RICK45BLISTS_DoubleListCreate((RICK45B_comparator_t)strcmp);
    assert(temp!=NULL);

    /*destroy double linked list*/
    RICK45BLISTS_DoubleListDestroy(&temp, 1);
    assert(temp==NULL);
}

void ErrorDoubleListTEST()
{
    doubleList_t dlist = NULL;
    dlist = RICK45BLISTS_DoubleListCreate((RICK45B_comparator_t)strcmp);

    /*testing errors and error messages*/
    doubleList_t temp = NULL;
    temp = RICK45BLISTS_DoubleListCreate(NULL);
    assert(temp == NULL && strcmp(RICK45B_GetError(), "Invalid Argument: key_cmp function cannot be NULL!")==0);

    assert(RICK45BLISTS_DoubleListRemoveHead(temp, 1)==-1);
    assert(strcmp(RICK45B_GetError(), "Fatal Error: double linkedList is NULL! Before using it, please consider using RICK45BLISTS_DoubleListCreate to initialize the double linked list.")==0);

    temp = RICK45BLISTS_DoubleListCreate((RICK45B_comparator_t)strcmp);

    assert(RICK45BLISTS_HeadAddDoubleListNode(NULL, temp)==-1 && strcmp(RICK45B_GetError(), "Invalid Argument: key cannot be NULL!")==0);
    assert(RICK45BLISTS_HeadAddDoubleListNode("bob", NULL)==-1 && strcmp(RICK45B_GetError(), "Fatal Error: double linkedList is NULL! Before using it, please consider using RICK45BLISTS_DoubleListCreate to initialize the double linked list.")==0);
    assert(RICK45BLISTS_TailAddDoubleListNode(NULL, temp)==-1 && strcmp(RICK45B_GetError(), "Invalid Argument: key cannot be NULL!")==0);
    assert(RICK45BLISTS_TailAddDoubleListNode("bob", NULL)==-1 && strcmp(RICK45B_GetError(), "Fatal Error: double linkedList is NULL! Before using it, please consider using RICK45BLISTS_DoubleListCreate to initialize the double linked list.")==0);
    assert(RICK45BLISTS_AddDoubleListNode(NULL, temp, 0)==-1 && strcmp(RICK45B_GetError(), "Invalid Argument: key cannot be NULL!")==0);
    assert(RICK45BLISTS_AddDoubleListNode("bob", NULL, 0)==-1 && strcmp(RICK45B_GetError(), "Fatal Error: double linkedList is NULL! Before using it, please consider using RICK45BLISTS_DoubleListCreate to initialize the double linked list.")==0);
    assert(RICK45BLISTS_AddDoubleListNode("bob", temp, 4)==-1 && strcmp(RICK45B_GetError(), "Invalid Argument: Position value out of range for the given double linkedList!")==0);

    assert(RICK45BLISTS_GetNodeByPositionDouble(NULL, 0)==NULL && strcmp(RICK45B_GetError(), "Fatal Error: double linkedList is NULL! Before using it, please consider using RICK45BLISTS_DoubleListCreate to initialize the double linked list.")==0);
    assert(RICK45BLISTS_GetNodeByPositionDouble(temp, 100)==NULL && strcmp(RICK45B_GetError(), "Invalid Argument: Position value out of range for the given double linkedList!")==0);
    assert(RICK45BLISTS_GetNodeByKeyDouble(NULL, "bob")==NULL && strcmp(RICK45B_GetError(), "Fatal Error: double linkedList is NULL! Before using it, please consider using RICK45BLISTS_DoubleListCreate to initialize the double linked list.")==0);
    assert(RICK45BLISTS_GetNodeByKeyDouble(temp, NULL)==NULL && strcmp(RICK45B_GetError(), "Invalid Argument: key cannot be NULL!")==0);
    assert(RICK45BLISTS_GetNodeByKeyDouble(temp, "alice")==NULL && strcmp(RICK45B_GetError(), "RICK45BLISTS_GetNodeByKeyDouble error: no key can be found!")==0);
    assert(RICK45BLISTS_GetKeyByNodeDouble(NULL)==NULL && strcmp(RICK45B_GetError(), "Invalid Argument: Node cannot be NULL!")==0);
    assert(RICK45BLISTS_GetKeyByPositionDouble(NULL, 0)==NULL && strcmp(RICK45B_GetError(), "Fatal Error: double linkedList is NULL! Before using it, please consider using RICK45BLISTS_DoubleListCreate to initialize the double linked list.")==0);
    assert(RICK45BLISTS_GetKeyByPositionDouble(temp, 300)==NULL && strcmp(RICK45B_GetError(), "Invalid Argument: Position value out of range for the given double linkedList!")==0);

    assert(RICK45BLISTS_SetKeyByPositionDouble(NULL, "can", 0)==NULL && strcmp(RICK45B_GetError(), "Fatal Error: double linkedList is NULL! Before using it, please consider using RICK45BLISTS_DoubleListCreate to initialize the double linked list.")==0);
    assert(RICK45BLISTS_SetKeyByPositionDouble(temp, NULL, 0)==NULL && strcmp(RICK45B_GetError(), "Invalid Argument: new key cannot be NULL!")==0);
    assert(RICK45BLISTS_SetKeyByPositionDouble(temp, "can", 300)==NULL && strcmp(RICK45B_GetError(), "Invalid Argument: Position value out of range for the given double linkedList!")==0);
    assert(RICK45BLISTS_SetKeyByNodeDouble(NULL, "can", NULL)==NULL && strcmp(RICK45B_GetError(), "Fatal Error: double linkedList is NULL! Before using it, please consider using RICK45BLISTS_DoubleListCreate to initialize the double linked list.")==0);
    assert(RICK45BLISTS_SetKeyByNodeDouble(temp, NULL, NULL)==NULL && strcmp(RICK45B_GetError(), "Fatal error: Node cannot be NULL!")==0);
    RICK45BLISTS_HeadAddDoubleListNode("brick", temp);
    doubleListNode_t temp_node = RICK45BLISTS_GetNodeByKeyDouble(temp, "brick");
    assert(RICK45BLISTS_SetKeyByNodeDouble(temp, NULL, temp_node)==NULL && strcmp(RICK45B_GetError(), "Invalid Argument: new key cannot be NULL!")==0);
    RICK45BLISTS_DoubleListRemoveAllNodes(temp, 0);
    assert(RICK45BLISTS_SetKeyByNodeDouble(temp, "can", temp_node)==NULL && strcmp(RICK45B_GetError(), "Head of the double linkedList is NULL! Please consider adding some nodes first!")==0);
    assert(RICK45BLISTS_SetKeyByKeyDouble(temp, "can", NULL)==-1 && strcmp(RICK45B_GetError(), "Fatal Error: keys cannot be NULL!")==0);
    assert(RICK45BLISTS_SetKeyByKeyDouble(temp, NULL, "can")==-1 && strcmp(RICK45B_GetError(), "Fatal Error: keys cannot be NULL!")==0);
    assert(RICK45BLISTS_SetKeyByKeyDouble(NULL, "dog", "can")==-1 && strcmp(RICK45B_GetError(), "Fatal Error: double linkedList is NULL! Before using it, please consider using RICK45BLISTS_DoubleListCreate to initialize the double linked list.")==0);

    assert(RICK45BLISTS_DoubleListRemoveHead(NULL, 0)==-1 && strcmp(RICK45B_GetError(), "Fatal Error: double linkedList is NULL! Before using it, please consider using RICK45BLISTS_DoubleListCreate to initialize the double linked list.")==0);
    assert(RICK45BLISTS_RemoveNodeDouble(NULL, 0, 0)==-1 && strcmp(RICK45B_GetError(), "Fatal Error: double linkedList is NULL! Before using it, please consider using RICK45BLISTS_DoubleListCreate to initialize the double linked list.")==0);
    assert(RICK45BLISTS_RemoveNodeDouble(temp, 300, 0)==-1 && strcmp(RICK45B_GetError(), "Head of the double linkedList is NULL! Please consider adding some nodes first!")==0);
    RICK45BLISTS_HeadAddDoubleListNode("brick", temp);
    assert(RICK45BLISTS_RemoveNodeDouble(temp, 300, 0)==-1 && strcmp(RICK45B_GetError(), "Invalid Argument: Position value out of range for the given double linkedList!")==0);
    RICK45BLISTS_DoubleListRemoveAllNodes(temp, 0);
    assert(RICK45BLISTS_RemoveTailDouble(NULL, 0)==-1 && strcmp(RICK45B_GetError(), "Fatal Error: double linkedList is NULL! Before using it, please consider using RICK45BLISTS_DoubleListCreate to initialize the double linked list.")==0);
    assert(RICK45BLISTS_RemoveTailDouble(temp, 0)==-1 && strcmp(RICK45B_GetError(), "Tail of the double linkedList is NULL! Please consider adding some nodes first!")==0);
    assert(RICK45BLISTS_RemoveNodeByKeyDouble(NULL, "bob", 0)==-1 && strcmp(RICK45B_GetError(), "Fatal Error: double linkedList is NULL! Before using it, please consider using RICK45BLISTS_DoubleListCreate to initialize the double linked list.")==0);
    assert(RICK45BLISTS_RemoveNodeByKeyDouble(temp, NULL, 0)==-1 && strcmp(RICK45B_GetError(), "Invalid Argument: key cannot be NULL!")==0);
    assert(RICK45BLISTS_RemoveAllNodesByKeyDouble(temp, NULL, 0)==-1 && strcmp(RICK45B_GetError(), "Invalid Argument: key cannot be NULL!")==0);

    RICK45BLISTS_DoubleListDestroy(&dlist, 0);
    RICK45BLISTS_DoubleListDestroy(&temp, 0);
}

void insert_removeDoubleListTEST()
{
    char array_keys[][20] = {"doctor", "surgeon", "wilson", "window", "tie", "tires", "desk"};
    char newkeys[][20] = {"home", "taxi", "chemist", "albert"};
    doubleList_t temp = NULL;
    temp = RICK45BLISTS_DoubleListCreate((RICK45B_comparator_t)strcmp);

    /*inserting a few nodes*/
    RICK45BLISTS_HeadAddDoubleListNode(array_keys[0], temp);
    assert(RICK45BLISTS_GetDoubleListSize(temp)==1);
    DoubleListVisualizerString(temp);  /*doctor <-> NULL*/
    RICK45BLISTS_HeadAddDoubleListNode(array_keys[2], temp);
    assert(RICK45BLISTS_GetDoubleListSize(temp)==2);
    DoubleListVisualizerString(temp);  /*wilson <-> doctor <-> NULL*/

    RICK45BLISTS_DoubleListRemoveHead(temp, 0);
    RICK45BLISTS_DoubleListRemoveHead(temp, 0);
    assert(RICK45BLISTS_GetDoubleListSize(temp)==0);

    /*testing all the insert/delete functions*/
    RICK45BLISTS_TailAddDoubleListNode(array_keys[2], temp);    /*wilson <-> NULL*/
    RICK45BLISTS_TailAddDoubleListNode(array_keys[4], temp);    /*wilson <-> tie <-> NULL*/
    assert(RICK45BLISTS_GetDoubleListSize(temp)==2);
    DoubleListVisualizerString(temp);
    RICK45BLISTS_DoubleListRemoveAllNodes(temp, 0);
    assert(RICK45BLISTS_GetDoubleListSize(temp)==0);
    RICK45BLISTS_TailAddDoubleListNode(array_keys[2], temp);    /*wilson <-> NULL*/
    RICK45BLISTS_TailAddDoubleListNode(array_keys[4], temp);    /*wilson <-> tie <-> NULL*/
    RICK45BLISTS_AddDoubleListNode(array_keys[6], temp, 2);     /*wilson <-> tie <-> desk <-> NULL*/
    RICK45BLISTS_AddDoubleListNode(array_keys[0], temp, 1);     /*wilson <-> doctor <-> tie <-> desk <-> NULL*/
    RICK45BLISTS_AddDoubleListNode(array_keys[5], temp, 0);     /*tires <-> wilson <-> doctor <-> tie <-> desk <-> NULL*/
    DoubleListVisualizerString(temp);
    assert(RICK45BLISTS_GetDoubleListSize(temp)==5);

    assert(RICK45BLISTS_GetNodeByKeyDouble(temp, array_keys[0])==RICK45BLISTS_GetNodeByPositionDouble(temp, 2));
    assert(RICK45BLISTS_GetNodeByKeyDouble(temp, array_keys[4])==RICK45BLISTS_GetNodeByPositionDouble(temp, 3));
    assert(RICK45BLISTS_GetNodeByKeyDouble(temp, array_keys[6])==RICK45BLISTS_GetNodeByPositionDouble(temp, 4));
    assert(RICK45BLISTS_GetKeyByNodeDouble(RICK45BLISTS_GetNodeByKeyDouble(temp, array_keys[0])) == array_keys[0]);
    assert(RICK45BLISTS_GetKeyByNodeDouble(RICK45BLISTS_GetNodeByKeyDouble(temp, array_keys[6])) == array_keys[6]);

    assert(RICK45BLISTS_GetKeyByPositionDouble(temp, 0)==array_keys[5]);
    assert(RICK45BLISTS_GetKeyByPositionDouble(temp, 2)==array_keys[0]);
    assert(RICK45BLISTS_GetKeyByPositionDouble(temp, 4)==array_keys[6]);

    RICK45BLISTS_SetKeyByPositionDouble(temp, newkeys[1], 0);   /*taxi <-> wilson <-> doctor <-> tie <-> desk <-> NULL*/
    RICK45BLISTS_SetKeyByPositionDouble(temp, newkeys[3], 4);   /*taxi <-> wilson <-> doctor <-> tie <-> albert <-> NULL*/
    RICK45BLISTS_SetKeyByPositionDouble(temp, newkeys[2], 2);   /*taxi <-> wilson <-> chemist <-> tie <-> albert <-> NULL*/
    DoubleListVisualizerString(temp);

    RICK45BLISTS_SetKeyByNodeDouble(temp, array_keys[3], RICK45BLISTS_GetNodeByPositionDouble(temp, 0));    /*window <-> wilson <-> chemist <-> tie <-> albert <-> NULL*/
    RICK45BLISTS_SetKeyByNodeDouble(temp, newkeys[0], RICK45BLISTS_GetNodeByPositionDouble(temp, 3));    /*window <-> wilson <-> chemist <-> home <-> albert <-> NULL*/
    assert(RICK45BLISTS_GetDoubleListSize(temp)==5);
    DoubleListVisualizerString(temp);
    RICK45BLISTS_SetKeyByPositionDouble(temp, newkeys[1], 0);   /*taxi <-> wilson <-> chemist <-> home <-> albert <-> NULL*/
    RICK45BLISTS_SetKeyByPositionDouble(temp, newkeys[1], 4);   /*taxi <-> wilson <-> chemist <-> home <-> taxi <-> NULL*/
    RICK45BLISTS_SetKeyByPositionDouble(temp, newkeys[1], 2);   /*taxi <-> wilson <-> taxi <-> home <-> taxi <-> NULL*/

    RICK45BLISTS_SetKeyByKeyDouble(temp, "setted!", newkeys[1]);    /*setted! <-> wilson <-> setted! <-> home <-> setted! <-> NULL*/
    assert(RICK45BLISTS_GetDoubleListSize(temp)==5);
    DoubleListVisualizerString(temp);

    RICK45BLISTS_RemoveNodeDouble(temp, 3, 0);  /*setted! <-> wilson <-> setted! <-> setted! <-> NULL*/
    RICK45BLISTS_RemoveNodeDouble(temp, 0, 0);  /*wilson <-> setted! <-> setted! <-> NULL*/
    RICK45BLISTS_RemoveNodeDouble(temp, 2, 0);  /*wilson <-> setted! <-> NULL*/
    assert(RICK45BLISTS_GetDoubleListSize(temp)==2);
    DoubleListVisualizerString(temp);

    RICK45BLISTS_TailAddDoubleListNode("cool", temp);   /*wilson <-> setted! <-> cool <-> NULL*/
    RICK45BLISTS_TailAddDoubleListNode("cool", temp);   /*wilson <-> setted! <-> cool <-> cool <-> NULL*/
    RICK45BLISTS_RemoveTailDouble(temp, 0);     /*wilson <-> setted! <-> cool <-> NULL*/
    assert(RICK45BLISTS_GetDoubleListSize(temp)==3);
    DoubleListVisualizerString(temp);

    assert(RICK45BLISTS_RemoveNodeByKeyDouble(temp, "setted!", 0)==1);     /*wilson <-> cool <-> NULL*/
    assert(RICK45BLISTS_RemoveNodeByKeyDouble(temp, "NotFound", 0)==0);    /*key not present inside the double linked list: function should return -1!*/
    assert(RICK45BLISTS_GetDoubleListSize(temp)==2);
    DoubleListVisualizerString(temp);
    RICK45BLISTS_SetKeyByKeyDouble(temp, "wilson", "cool");     /*wilson <-> wilson <-> NULL*/
    assert(RICK45BLISTS_RemoveAllNodesByKeyDouble(temp, "wilson", 0)==2);  /*empty list! -> function should return the number of deleted nodes: two!*/
    assert(RICK45BLISTS_GetDoubleListSize(temp)==0);
    DoubleListVisualizerString(temp);

    /*destroy double linked list*/
    RICK45BLISTS_DoubleListDestroy(&temp, 0);
    assert(temp==NULL);
}

void nextPreviousTESTS()
{
    char array_keys[][20] = {"doctor", "surgeon", "wilson", "window", "tie", "tires", "desk"};
    char newkeys[][20] = {"home", "taxi", "chemist", "albert"};

    /*initializing list*/
    list_t list = RICK45BLISTS_ListCreate((RICK45B_comparator_t)strcmp);
    RICK45BLISTS_HeadAddListNode(array_keys[1], list);  /*surgeon -> NULL*/
    RICK45BLISTS_TailAddListNode(newkeys[3], list);  /*surgeon -> albert -> NULL*/
    RICK45BLISTS_AddListNode(array_keys[4], list, 1);   /*surgeon -> tie -> albert -> NULL*/
    RICK45BLISTS_AddListNode(array_keys[0], list, 1);   /*surgeon -> doctor -> tie -> albert -> NULL*/
    RICK45BLISTS_HeadAddListNode(newkeys[1], list);    /*taxi -> surgeon -> doctor -> tie -> albert -> NULL*/

    /*initializing double linkedList*/
    doubleList_t listDouble = RICK45BLISTS_DoubleListCreate((RICK45B_comparator_t)strcmp);
    RICK45BLISTS_HeadAddDoubleListNode(array_keys[1], listDouble);  /*surgeon <-> NULL*/
    RICK45BLISTS_TailAddDoubleListNode(newkeys[3], listDouble);  /*surgeon <-> albert <-> NULL*/
    RICK45BLISTS_AddDoubleListNode(array_keys[4], listDouble, 1);   /*surgeon <-> tie <-> albert <-> NULL*/
    RICK45BLISTS_AddDoubleListNode(array_keys[0], listDouble, 1);   /*surgeon <-> doctor <-> tie <-> albert <-> NULL*/
    RICK45BLISTS_HeadAddDoubleListNode(newkeys[1], listDouble);    /*taxi <-> surgeon <-> doctor <-> tie <-> albert <-> NULL*/

    /*testing list's visiting functions*/
    assert(RICK45BLISTS_RewindList(list)==0);
    assert(RICK45BLISTS_HasNext(list)==1);
    assert(RICK45BLISTS_GetCurrentNode(list)==RICK45BLISTS_GetNodeByPosition(list, 0));
    assert(RICK45BLISTS_GetNextNode(list)==RICK45BLISTS_GetNodeByPosition(list, 1));
    assert(RICK45BLISTS_HasNext(list)==1);
    assert(RICK45BLISTS_GetNextNode(list)==RICK45BLISTS_GetNodeByPosition(list, 2));
    assert(RICK45BLISTS_HasNext(list)==1);
    assert(RICK45BLISTS_GetNextNode(list)==RICK45BLISTS_GetNodeByPosition(list, 3));
    assert(RICK45BLISTS_HasNext(list)==1);
    assert(RICK45BLISTS_GetNextNode(list)==RICK45BLISTS_GetNodeByPosition(list, 4));
    assert(RICK45BLISTS_HasNext(list)==0);
    assert(RICK45BLISTS_GetNextNode(list)==RICK45BLISTS_GetNodeByPosition(list, 4));
    /*removing and adding some nodes...*/
    RICK45BLISTS_RemoveTail(list, 0);   /*taxi -> surgeon -> doctor -> tie -> NULL*/
    assert(RICK45BLISTS_GetNextNode(list)==RICK45BLISTS_GetNodeByPosition(list, 3));
    assert(RICK45BLISTS_HasNext(list)==0);
    RICK45BLISTS_RemoveHead(list, 0);   /*surgeon -> doctor -> tie -> NULL*/
    RICK45BLISTS_RemoveNodeByKey(list, "tie", 0);  /*surgeon -> doctor -> NULL*/
    assert(strcmp(RICK45BLISTS_GetKeyByNode(RICK45BLISTS_GetCurrentNode(list)), "doctor")==0);
    assert(RICK45BLISTS_HasNext(list)==0);
    assert(RICK45BLISTS_GetNextNode(list)==RICK45BLISTS_GetNodeByPosition(list, 1));

    /*testing linkedList's visiting functions*/
    assert(RICK45BLISTS_RewindDoubleList(listDouble)==0);
    assert(RICK45BLISTS_DoubleListHasNext(listDouble)==1);
    assert(RICK45BLISTS_DoubleListHasPrevious(listDouble)==0);
    assert(RICK45BLISTS_DoubleListGetCurrentNode(listDouble)==RICK45BLISTS_GetNodeByPositionDouble(listDouble, 0));
    assert(RICK45BLISTS_DoubleListGetPreviousNode(listDouble)==RICK45BLISTS_GetNodeByPositionDouble(listDouble, 0));
    assert(RICK45BLISTS_DoubleListGetNextNode(listDouble)==RICK45BLISTS_GetNodeByPositionDouble(listDouble, 1));
    assert(RICK45BLISTS_DoubleListGetPreviousNode(listDouble)==RICK45BLISTS_GetNodeByPositionDouble(listDouble, 0));
    RICK45BLISTS_DoubleListGetNextNode(listDouble);
    assert(RICK45BLISTS_DoubleListHasPrevious(listDouble)==1);
    assert(RICK45BLISTS_DoubleListHasNext(listDouble)==1);
    assert(RICK45BLISTS_DoubleListGetNextNode(listDouble)==RICK45BLISTS_GetNodeByPositionDouble(listDouble, 2));
    assert(RICK45BLISTS_DoubleListGetPreviousNode(listDouble)==RICK45BLISTS_GetNodeByPositionDouble(listDouble, 1));
    RICK45BLISTS_DoubleListGetNextNode(listDouble);
    assert(RICK45BLISTS_DoubleListHasPrevious(listDouble)==1);
    assert(RICK45BLISTS_DoubleListHasNext(listDouble)==1);
    assert(RICK45BLISTS_DoubleListGetNextNode(listDouble)==RICK45BLISTS_GetNodeByPositionDouble(listDouble, 3));
    assert(RICK45BLISTS_DoubleListGetPreviousNode(listDouble)==RICK45BLISTS_GetNodeByPositionDouble(listDouble, 2));
    RICK45BLISTS_DoubleListGetNextNode(listDouble);
    assert(RICK45BLISTS_DoubleListHasPrevious(listDouble)==1);
    assert(RICK45BLISTS_DoubleListHasNext(listDouble)==1);
    assert(RICK45BLISTS_DoubleListGetNextNode(listDouble)==RICK45BLISTS_GetNodeByPositionDouble(listDouble, 4));
    assert(RICK45BLISTS_DoubleListGetPreviousNode(listDouble)==RICK45BLISTS_GetNodeByPositionDouble(listDouble, 3));
    RICK45BLISTS_DoubleListGetNextNode(listDouble);
    assert(RICK45BLISTS_DoubleListHasPrevious(listDouble)==1);
    assert(RICK45BLISTS_DoubleListHasNext(listDouble)==0);
    assert(RICK45BLISTS_DoubleListGetNextNode(listDouble)==RICK45BLISTS_GetNodeByPositionDouble(listDouble, 4));
    /*removing and adding some nodes...*/
    RICK45BLISTS_RemoveTailDouble(listDouble, 0);   /*taxi -> surgeon -> doctor -> tie -> NULL*/
    assert(RICK45BLISTS_DoubleListGetNextNode(listDouble)==RICK45BLISTS_GetNodeByPositionDouble(listDouble, 3));
    assert(RICK45BLISTS_DoubleListGetPreviousNode(listDouble)==RICK45BLISTS_GetNodeByPositionDouble(listDouble, 2));
    RICK45BLISTS_DoubleListGetNextNode(listDouble);
    assert(RICK45BLISTS_DoubleListHasPrevious(listDouble)==1);
    assert(RICK45BLISTS_DoubleListHasNext(listDouble)==0);
    RICK45BLISTS_DoubleListRemoveHead(listDouble, 0);   /*surgeon -> doctor -> tie -> NULL*/
    RICK45BLISTS_RemoveNodeByKeyDouble(listDouble, "tie", 0);  /*surgeon -> doctor -> NULL*/
    assert(strcmp(RICK45BLISTS_GetKeyByNodeDouble(RICK45BLISTS_DoubleListGetCurrentNode(listDouble)), "doctor")==0);
    assert(RICK45BLISTS_DoubleListGetPreviousNode(listDouble)==RICK45BLISTS_GetNodeByPositionDouble(listDouble, 0));
    RICK45BLISTS_DoubleListGetNextNode(listDouble);
    assert(RICK45BLISTS_DoubleListHasPrevious(listDouble)==1);
    assert(RICK45BLISTS_DoubleListHasNext(listDouble)==0);
    assert(RICK45BLISTS_DoubleListGetNextNode(listDouble)==RICK45BLISTS_GetNodeByPositionDouble(listDouble, 1));

    /*destroying both lists*/
    RICK45BLISTS_ListDestroy(&list, 0);
    RICK45BLISTS_DoubleListDestroy(&listDouble, 0);
}
