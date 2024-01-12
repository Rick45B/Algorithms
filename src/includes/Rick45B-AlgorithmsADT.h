/*
 * MIT License

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

#include "Rick45B-Utils.h"

/*function's variables*/
typedef int (*RICK45B_comparator_t)(const void *a, const void *b);
/*Function used to compare two key elements of an ADT. Must return -1 if a<b, 0 if a=b or else 1.*/

typedef int (*RICK45B_forEach_t)(void *elem, void *opt);
/*
 * Function used by the forEach functions of the various ADT's that, given an element (a node) of the ADT itself,
 * it manipulates it. Must return -1 if an error has occurred, 0 otherwise.
 * The 'opt' argument is optional, and can be used for whatever user-defined purpose.
*/

/*structs*/
struct listNode{
    void *key;
    struct listNode *next;
    struct listNode *previous;
};
typedef struct listNode* listNode_t;

struct doubleListNode{
    void *key;
    struct doubleListNode *next;
    struct doubleListNode *previous;
};
typedef struct doubleListNode* doubleListNode_t;

struct list{
    listNode_t head;
    listNode_t tail;
    RICK45B_comparator_t key_cmp;
    size_t size;
    listNode_t pointedNode;
};
typedef struct list* list_t;

struct doubleList{
    doubleListNode_t head;
    doubleListNode_t tail;
    RICK45B_comparator_t key_cmp;
    size_t size;
    doubleListNode_t pointedNode;
};
typedef struct doubleList* doubleList_t;

struct treeNode{
    void* key;
    void* value;
    struct treeNode **childs;
};
typedef struct treeNode* treeNode_t;

struct binaryTree{
    treeNode_t root;
    RICK45B_comparator_t key_cmp;
    unsigned int treeType;  /*this field is for private use only, and should NEVER be accessed!*/
};
typedef struct binaryTree* Btree_t;

struct stack{
    list_t head;
    unsigned long int dim;
};
typedef struct stack* stack_t;

struct queue{
    list_t list;
    unsigned long int dim;
};
typedef struct queue* queue_t;

/*functions*/
static int RICK45B_LibStart(malloc_t malloc_funct, free_t free_funct);
/*
 * Function that must be called BEFORE using any of the current library's functions.
 * Returns -1 if an error has occurred, 0 otherwise.
 * Arguments:
 * malloc_funct -> memory allocation function to be used by the library for allocating memory
 * needed by the ADTs.
 * free_funct -> memory deallocation function to be used by the library for deallocating
 * memory used by the ADTs.
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

/*  ***linked lists***  */

list_t RICK45BLISTS_ListCreate(RICK45B_comparator_t key_cmp);
/*
 * Function used to initialize a list.
 * Returns a list type, or NULL if an error occurred.
 * Arguments:
 * key_cmp -> function used to compare elements of the linked list.
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

void RICK45BLISTS_ListDestroy(list_t *linkedList, int delete_bool);
/*
 * Function that, given a linkedList, it destroys it.
 * Returns nothing.
 * Arguments:
 * linkedList -> the list which you'd like to destroy
 * delete_bool -> an integer number, used to interrogate the client if he wants to
 * delete the users data as well with the node. i.e:
 * 0 -> just delete (free) the node, and not its content.
 * A number different from 0 -> delete (free), together with the node, the user defined contents
 * as well.
 * Use a delete_bool different from 0 only if the list doesn't contains any stack-allocated data!!
*/

listNode_t RICK45BLISTS_GetNextNode(list_t linkedList);
/*
 * Function that, given a linkedList, it shifts the current pointed node forward (to the next adjacent node).
 * If the 'pointedNode' field already points to the tail of the list, nothing happens.
 * Returns the next node (if present), NULL otherwise.
 * Arguments:
 * linkedList -> the list containing the 'pointedNode' field to shift.
 *
 * it is STRONGLY RECOMMENDED to use this function together with the 'RICK45BLISTS_HasNext()' function.
 * If the current pointed node has been deleted, the new pointed node will be the previous one,
 * or the new head, if it was already pointing at the head of the list.
*/

int RICK45BLISTS_HasNext(list_t linkedList);
/*
 * Function that, given a linkedList, checks if its 'pointedNode' field has a next valid node.
 * Returns 1 if a valid node is present, -1 if an error has occurred, 0 otherwise.
 * Arguments:
 * linkedList -> the list containing the 'pointedNode' field to check.
 *
 * If the current pointed node has been deleted, the new pointed node will be the previous one,
 * or the new head, if it was already pointing at the head of the list.
*/

listNode_t RICK45BLISTS_GetCurrentNode(list_t linkedList);
/*
 * Function that, once called, returns the current pointed node in the list. Remember that you can
 * visit the lists (and eventually change the current pointed node) by using the functions
 * 'RICK45BLISTS_GetNextNode()', 'RICK45BLISTS_RewindList()' and 'RICK45BLISTS_GetCurrentNode()'.
 * Returns the current pointed node by the internal field 'pointedNode' or NULL, if an error has occurred.
 * Arguments:
 * linkedList -> the list from where you'd like to get the current pointed node.
 *
 * REMEMBER THAT YOU SHOULD USE THIS FUNCTION AFTER CALLING AT LEAST ONCE THE FUNCTION
 * 'RICK45BLISTS_RewindList()', OTHERWISE THE VALUE 'NULL' WILL ALWAYS BE RETURNED!
 * If the current pointed node has been deleted, the new pointed node will be the previous one,
 * or the new head, if it was already pointing at the head of the list.
*/

int RICK45BLISTS_RewindList(list_t linkedList);
/*
 * Function that, given a list, it rewinds its pointedNode to the head of the list, if present. If the list appears to
 * not having a head anymore, the field will be set to NULL, until a new head will be added to the list,
 * and this function will be called.
 * Returns 0 if the rewind was succesful, -1 otherwise.
 *
 * if the function returns -1, it is advised to check for an error message.
*/

int RICK45BLISTS_HeadAddListNode(void *key, list_t linkedList);
/*
 * Function used to add a node at the HEAD of a linked list.
 * Returns -1 if an error has occurred, 0 otherwise.
 * Arguments:
 * key -> generic type key to be added to the head of the list.
 * linkedList -> the list in which add the key.
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

int RICK45BLISTS_TailAddListNode(void *key, list_t linkedList);
/*
 * Function used to add a node at the TAIL of a linked list.
 * Returns -1 if an error has occurred, 0 otherwise.
 * Arguments:
 * key -> generic type key to be added to the tail of the list
 * linkedList -> the list in which add the key
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

int RICK45BLISTS_AddListNode(void *key, list_t linkedList, size_t position);
/*
 * Function used to add a node at a specified position. Please note that if you'd like to
 * add a node at the head or tail position, you should use the proper functions!.
 * Returns -1 if an error has occurred, 0 otherwise.
 * Arguments:
 * key -> generic type key to be added to the head of the list.
 * linkedList -> the list in which add the key.
 * position -> the index where to add the node, starting from 0.
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

size_t RICK45BLISTS_GetListSize(list_t linkedList);
/*
 * Function that, given a list, it returns its size.
 * Returns the number of nodes in the given list.
 * Arguments:
 * linkedList -> the list to get the size from.
*/

listNode_t RICK45BLISTS_GetNodeByPosition(list_t linkedList, size_t position);
/*
 * Function used to get a Node by position.
 * Returns a listNode_t, or NULL if an error has occurred.
 * Arguments:
 * position -> position of the node to fetch.
 * linkedList -> the list where to search for the node.
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

listNode_t RICK45BLISTS_GetNodeByKey(list_t linkedList, void* key);
/*
 * Function used to get a Node by key.
 * Returns a the first listNode_t with that key, or NULL if an error has occurred.
 * Arguments:
 * key -> the key used for searching for the node.
 * linkedList -> the list where to search in.
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

void *RICK45BLISTS_GetKeyByNode(listNode_t node);
/*
 * Function that, given a Node, it returns its key. It is pretty useless, but
 * might be useful to obtain a more verbose programming.
 * Returns a key, or NULL if an error has occurred.
 * Arguments:
 * node -> the node where to get the key from.
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

void *RICK45BLISTS_GetKeyByPosition(list_t linkedList, size_t position);
/*
 * Function that, given a position and a list, it returns the key at that position.
 * Returns a key, or NULL if an error has occurred.
 * Arguments:
 * linkedList -> the list where to get the key from.
 * position -> the position of the key in the list to fetch.
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

void *RICK45BLISTS_SetKeyByPosition(list_t linkedList, void* newkey, size_t position);
/*
 * Function that, given a position, a list and a key, it sets the key of the node at that
 * position to newkey.
 * Return the previously stored key on that node, or NULL if an error has occurred.
 * Arguments:
 * linkedList -> the list where to set the key.
 * position -> the position of the node in the list at which to set the new key.
 * newkey -> the new key of the node at the specified position, that will replace the old one.
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

void *RICK45BLISTS_SetKeyByNode(list_t linkedList, void* newkey, listNode_t node);
/*
 * Function that given a node, a list, and a key, sets the key of the given node to newkey.
 * Return the previously stored key on that node, or NULL if an error has occurred.
 * Arguments:
 * linkedList -> the list where to set the key.
 * newkey -> the new key of the node at the specified position, that will replace the old one.
 * node -> the node to which set the new key.
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

int RICK45BLISTS_SetKeyByKey(list_t linkedList, void* newkey, void* oldkey);
/*
 * Function that, given a new key, a list and a old key, sets all the keys of the given list
 * that equals to oldkey, to newkey.
 * Returns the number of replaced keys, -1 if an error has occurred.
 * Arguments:
 * linkedList -> the list where to set the key.
 * newkey -> the new key of the node, that will replace the old one.
 * oldkey -> the key that identifies all the nodes which their keys must be updated.
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

int RICK45BLISTS_RemoveHead(list_t linkedList, int delete_bool);
/*
 * Function that, given a list, it deletes (if presents) the node at the head.
 * Returns -1 if an error has occurred, 0 otherwise.
 * Arguments:
 * linkedList -> the list to which delete the head.
 * delete_bool -> an integer number, used to interrogate the client if he wants to
 * delete the users data as well with the node. i.e:
 *
 * 0 -> just delete (free) the node, and not its content.
 * A number different from 0 -> delete (free), together with the node, the user defined contents
 * as well.
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

int RICK45BLISTS_RemoveNode(list_t linkedList, size_t position, int delete_bool);
/*
 * Function that, given a list and a position, it deletes the node at that position.
 * PLEASE, REMEMBER THAT THE LIST IS INDEXED LIKE AN ARRAY, STARTING FROM ZERO!
 * Returns -1 if an error has occurred, 0 otherwise.
 * Arguments:
 * linkedList -> the list to which delete the node.
 * position -> the index of the node to delete.
 * delete_bool -> an integer number, used to interrogate the client if he wants to
 * delete the users data as well with the node. i.e:
 *
 * 0 -> just delete (free) the node, and not its content.
 * A number different from 0 -> delete (free), together with the node, the user defined contents
 * as well.
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

void RICK45BLISTS_RemoveAllNodes(list_t linkedList, int delete_bool);
/*
 * Function that, given a list, it deletes (if presents) all its nodes.
 * Returns nothing.
 * Arguments:
 * linkedList -> the list to which delete all the nodes.
 * delete_bool -> an integer number, used to interrogate the client if he wants to
 * delete the users data as well with the nodes. i.e:
 *
 * 0 -> just delete (free) the node, and not its content.
 * A number different from 0 -> delete (free), together with the node, the user defined contents
 * as well.
 * Use a delete_bool different from 0 only if the list doesn't contains any stack-allocated data!!
*/

int RICK45BLISTS_RemoveTail(list_t linkedList, int delete_bool);
/*
 * Function that, given a list, it deletes (if presents) the node at it's tail.
 * Returns -1 if an error has occurred, 0 otherwise.
 * Arguments:
 * linkedList -> the list to which delete the tail.
 * delete_bool -> an integer number, used to interrogate the client if he wants to
 * delete the users data as well with the node. i.e:
 *
 * 0 -> just delete (free) the node, and not its content.
 * A number different from 0 -> delete (free), together with the node, the user defined contents
 * as well.
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

int RICK45BLISTS_RemoveNodeByKey(list_t linkedList, void *key, int delete_bool);
/*
 * Function that, given a list and a key value, it deletes (if presents) the first node it encounters with that key.
 * Returns 0 if nothing has been deleted, 1 if something has been deleted and -1 if an error has occurred.
 * Arguments:
 * linkedList -> the list to which delete the node.
 * key -> they key of the node to remove.
 * delete_bool -> an integer number, used to interrogate the client if he wants to
 * delete the users data as well with the node. i.e:
 *
 * 0 -> just delete (free) the node, and not its content.
 * A number different from 0 -> delete (free), together with the node, the user defined contents
 * as well.
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

int RICK45BLISTS_RemoveAllNodesByKey(list_t linkedList, void *key, int delete_bool);
/*
 * Function that, given a list and a key value, it deletes (if present) all the nodes it encounters with that key.
 * Returns the number of nodes that have been deleted, or -1 if an error has occurred.
 * Arguments:
 * linkedList -> the list to which delete the nodes.
 * key -> they key of the nodes to remove.
 * delete_bool -> an integer number, used to interrogate the client if he wants to
 * delete the users data as well with the node. i.e:
 *
 * 0 -> just delete (free) the node, and not its content.
 * A number different from 0 -> delete (free), together with the node, the user defined contents
 * as well.
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

/*  ***Double linked lists***   */

doubleList_t RICK45BLISTS_DoubleListCreate(RICK45B_comparator_t key_cmp);
/*
 * Function used to initialize a double linked list.
 * Returns a doubleList type, or NULL if an error occurred.
 * Arguments:
 * key_cmp -> function used to compare elements of the double linked list.
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

void RICK45BLISTS_DoubleListDestroy(doubleList_t *dlinkedList, int delete_bool);
/*
 * Function that, given a double linkedList, it destroys it.
 * Returns nothing.
 * Arguments:
 * dlinkedList -> the double linked list which you'd like to destroy
 * delete_bool -> an integer number, used to interrogate the client if he wants to
 * delete the users data as well with the node. i.e:
 * 0 -> just delete (free) the node, and not its content.
 * A number different from 0 -> delete (free), together with the node, the user defined contents
 * as well.
 * Use a delete_bool different from 0 only if the double linked list doesn't contains any stack-allocated data!!
*/

doubleListNode_t RICK45BLISTS_DoubleListGetNextNode(doubleList_t dlinkedList);
/*
 * Function that, given a dlinkedList, it shifts the current pointed node forward (to the next adjacent node).
 * If the 'pointedNode' field already points to the tail of the list, nothing happens.
 * Returns the next node (if present), NULL otherwise.
 * Arguments:
 * dlinkedList -> the double linkedList containing the 'pointedNode' field to shift.
 *
 * it is STRONGLY RECOMMENDED to use this function together with the 'RICK45BLISTS_DoubleListHasNext()' function.
 * If the current pointed node has been deleted, the new pointed node will be the previous one,
 * or the new head, if it was already already pointing at the head of the list.
*/

doubleListNode_t RICK45BLISTS_DoubleListGetPreviousNode(doubleList_t dlinkedList);
/*
 * Function that, given a dlinkedList, it shifts the current pointed node backward (to the previous adjacent node).
 * If the 'pointedNode' field already points to the head of the list, nothing happens.
 * Returns the previous node (if present), NULL otherwise.
 * Arguments:
 * dlinkedList -> the double linkedList containing the 'pointedNode' field to shift.
 *
 * it is STRONGLY RECOMMENDED to use this function together with the 'RICK45BLISTS_DoubleListHasPrevious()' and
 * 'RICK45BLISTS_DoubleListHasNext()' functions.
 * If the current pointed node has been deleted, the new pointed node will be the previous one,
 * or the new head, if it was already already pointing at the head of the list.
*/

int RICK45BLISTS_DoubleListHasPrevious(doubleList_t dlinkedList);
/*
 * Function that, given a dlinkedList, checks if its 'pointedNode' field has a previous valid node.
 * Returns 1 if a valid node is present, -1 if an error has occurred, 0 otherwise.
 * Arguments:
 * dlinkedList -> the double linkedList containing the 'pointedNode' field to check.
 *
 * If the current pointed node has been deleted, the new pointed node will be the previous one,
 * or the new head, if it was already pointing at the head of the double linkedList.
*/

int RICK45BLISTS_DoubleListHasNext(doubleList_t dlinkedList);
/*
 * Function that, given a dlinkedList, checks if its 'pointedNode' field has a next valid node.
 * Returns 1 if a valid node is present, -1 if an error has occurred, 0 otherwise.
 * Arguments:
 * dlinkedList -> the double linkedList containing the 'pointedNode' field to check.
 *
 * If the current pointed node has been deleted, the new pointed node will be the previous one,
 * or the new head, if it was already pointing at the head of the double linkedList.
*/

doubleListNode_t RICK45BLISTS_DoubleListGetCurrentNode(doubleList_t dlinkedList);
/*
 * Function that, once called, returns the current pointed node in the list. Remember that you can
 * visit the lists (and eventually change the current pointed node) by using the functions
 * 'RICK45BLISTS_DoubleListGetNextNode()', 'RICK45BLISTS_RewindDoubleList()' and 'RICK45BLISTS_DoubleListGetCurrentNode()'.
 * Returns the current pointed node by the internal field 'pointedNode' or NULL, if an error has occurred.
 * Arguments:
 * dlinkedList -> the double linkedList from where you'd like to get the current pointed node.
 *
 * REMEMBER THAT YOU SHOULD USE THIS FUNCTION AFTER CALLING AT LEAST ONCE THE FUNCTION
 * 'RICK45BLISTS_RewindDoubleList()', OTHERWISE THE VALUE 'NULL' WILL ALWAYS BE RETURNED!
 * If the current pointed node has been deleted, the new pointed node will be the previous one,
 * or the new head, if it was already pointing at the head of the double linkedList.
*/

int RICK45BLISTS_RewindDoubleList(doubleList_t dlinkedList);
/*
 * Function that, given a list, it rewinds its pointedNode to the head of the double linkedList, if present. If the
 * double linkedList appears to not having a head anymore, the field will be set to NULL,
 * until a new head will be added to the double linkedList, and this function function will be called.
 * Returns 0 if the rewind was succesful, -1 otherwise.
 *
 * if the function returns -1, it is advised to check for an error message.
*/

int RICK45BLISTS_HeadAddDoubleListNode(void *key, doubleList_t dlinkedList);
/*
 * Function used to add a node at the HEAD of a double linked list.
 * Returns -1 if an error has occurred, 0 otherwise.
 * Arguments:
 * key -> generic type key to be added to the head of the list.
 * dlinkedList -> the list in which add the key.
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

size_t RICK45BLISTS_GetDoubleListSize(doubleList_t dlinkedList);
/*
 * Function that, given a double linked list, it returns its size.
 * Returns the int number of elements in the given double linked list.
 * Arguments:
 * dlinkedList -> the double linked list to get the size from.
*/

int RICK45BLISTS_TailAddDoubleListNode(void *key, doubleList_t dlinkedList);
/*
 * Function used to add a node at the TAIL of a double linked list.
 * Returns -1 if an error has occurred, 0 otherwise.
 * Arguments:
 * key -> generic type key to be added to the tail of the double linked list
 * dlinkedList -> the double linked list in which add the key
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

int RICK45BLISTS_AddDoubleListNode(void *key, doubleList_t dlinkedList, size_t position);
/*
 * Function used to add a node at a specified position. Please note that if you'd like to
 * add a node at the head or tail position, you should use the proper functions!.
 * Returns -1 if an error has occurred, 0 otherwise.
 * Arguments:
 * key -> generic type key to be added to the head of the double linked list.
 * dlinkedList -> the double linked list in which add the key.
 * position -> the index where to add the node, starting from 0.
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

doubleListNode_t RICK45BLISTS_GetNodeByPositionDouble(doubleList_t dlinkedList, size_t position);
/*
 * Function used to get a Node by position.
 * Returns a doubleListNode_t, or NULL if an error has occurred.
 * Arguments:
 * position -> position of the node to fetch.
 * dlinkedList -> the double linked list where to search for the node.
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

doubleListNode_t RICK45BLISTS_GetNodeByKeyDouble(doubleList_t dlinkedList, void* key);
/*
 * Function used to get a Node by key.
 * Returns a the first doubleListNode_t with that key, or NULL if an error has occurred.
 * Arguments:
 * key -> the key used for searching for the node.
 * dlinkedList -> the double linked list where to search in.
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

void *RICK45BLISTS_GetKeyByNodeDouble(doubleListNode_t node);
/*
 * Function that, given a Node, it returns its key. It is pretty useless, but
 * might be useful to obtain a more verbose programming.
 * Returns a key, or NULL if an error has occurred.
 * Arguments:
 * node -> the node where to get the key from.
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

void *RICK45BLISTS_GetKeyByPositionDouble(doubleList_t dlinkedList, size_t position);
/*
 * Function that, given a position and a double linkedList, it returns the key at that position.
 * Returns a key, or NULL if an error has occurred.
 * Arguments:
 * dlinkedList -> the double linkedList where to get the key from.
 * position -> the position of the key in the double linkedList to fetch.
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

void *RICK45BLISTS_SetKeyByPositionDouble(doubleList_t dlinkedList, void* newkey, size_t position);
/*
 * Function that, given a position, a double linkedList and a key, it sets the key of the node at that
 * position to newkey.
 * Return the previously stored key on that node, or NULL if an error has occurred.
 * Arguments:
 * dlinkedList -> the double linkedList where to set the key.
 * position -> the position of the node in the double linkedList at which to set the new key.
 * newkey -> the new key of the node at the specified position, that will replace the old one.
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

void *RICK45BLISTS_SetKeyByNodeDouble(doubleList_t dlinkedList, void* newkey, doubleListNode_t node);
/*
 * Function that given a node, a double linkedList, and a key, sets the key of the given node to newkey.
 * Return the previously stored key on that node, or NULL if an error has occurred.
 * Arguments:
 * dlinkedList -> the double linkedList where to set the key.
 * newkey -> the new key of the node at the specified position, that will replace the old one.
 * node -> the node to which set the new key.
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

int RICK45BLISTS_SetKeyByKeyDouble(doubleList_t dlinkedList, void* newkey, void* oldkey);
/*
 * Function that, given a new key, a double linkedList and a old key, sets all the keys of the given double linkedList
 * that equals to oldkey, to newkey.
 * Returns the number of replaced keys, -1 if an error has occurred.
 * Arguments:
 * dlinkedList -> the list where to set the key.
 * newkey -> the new key of the node, that will replace the old one.
 * oldkey -> the key that identifies all the nodes which their keys must be updated.
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

int RICK45BLISTS_RemoveNodeDouble(doubleList_t dlinkedList, size_t position, int delete_bool);
/*
 * Function that, given a double linkedList and a position, it deletes the node at that position.
 * PLEASE, REMEMBER THAT THE LIST IS INDEXED LIKE AN ARRAY, STARTING FROM ZERO!
 * Returns -1 if an error has occurred, 0 otherwise.
 * Arguments:
 * dlinkedList -> the double linkedList to which delete the node.
 * position -> the index of the node to delete.
 * delete_bool -> an integer number, used to interrogate the client if he wants to
 * delete the users data as well with the node. i.e:
 *
 * 0 -> just delete (free) the node, and not its content.
 * A number different from 0 -> delete (free), together with the node, the user defined contents
 * as well.
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

int RICK45BLISTS_RemoveTailDouble(doubleList_t dlinkedList, int delete_bool);
/*
 * Function that, given a double linkedList, it deletes (if presents) the node at it's tail.
 * Returns -1 if an error has occurred, 0 otherwise.
 * Arguments:
 * dlinkedList -> the double linkedList to which delete the tail.
 * delete_bool -> an integer number, used to interrogate the client if he wants to
 * delete the users data as well with the node. i.e:
 *
 * 0 -> just delete (free) the node, and not its content.
 * A number different from 0 -> delete (free), together with the node, the user defined contents
 * as well.
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

int RICK45BLISTS_RemoveNodeByKeyDouble(doubleList_t dlinkedList, void *key, int delete_bool);
/*
 * Function that, given a double linkedList and a key value, it deletes (if presents) the first node it encounters with that key.
 * Returns 0 if nothing has been deleted, 1 if something has been deleted and -1 if an error has occurred.
 * Arguments:
 * dlinkedList -> the double linkedList to which delete the node.
 * key -> they key of the node to remove.
 * delete_bool -> an integer number, used to interrogate the client if he wants to
 * delete the users data as well with the node. i.e:
 *
 * 0 -> just delete (free) the node, and not its content.
 * A number different from 0 -> delete (free), together with the node, the user defined contents
 * as well.
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

int RICK45BLISTS_RemoveAllNodesByKeyDouble(doubleList_t dlinkedList, void *key, int delete_bool);
/*
 * Function that, given a double linkedList and a key value, it deletes (if present) all the nodes it encounters with that key.
 * Returns the number of nodes that have been deleted, or -1 if an error has occurred.
 * Arguments:
 * dlinkedList -> the double linkedList to which delete the nodes.
 * key -> they key of the nodes to remove.
 * delete_bool -> an integer number, used to interrogate the client if he wants to
 * delete the users data as well with the node. i.e:
 *
 * 0 -> just delete (free) the node, and not its content.
 * A number different from 0 -> delete (free), together with the node, the user defined contents
 * as well.
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

void RICK45BLISTS_DoubleListRemoveAllNodes(doubleList_t dlinkedList, int delete_bool);
/*
 * Function that, given a double linked list, it deletes (if presents) all its nodes.
 * Returns nothing.
 * Arguments:
 * dlinkedList -> the double linked list to which delete all the nodes.
 * delete_bool -> an integer number, used to interrogate the client if he wants to
 * delete the users data as well with the nodes. i.e:
 *
 * 0 -> just delete (free) the node, and not its content.
 * A number different from 0 -> delete (free), together with the node, the user defined contents
 * as well.
 * Use a delete_bool different from 0 only if the double linked list doesn't contains any stack-allocated data!!
*/

int RICK45BLISTS_DoubleListRemoveHead(doubleList_t dlinkedList, int delete_bool);
/*
 * Function that, given a double linked list, it deletes (if presents) the node at the head.
 * Returns -1 if an error has occurred, 0 otherwise.
 * Arguments:
 * dlinkedList -> the double linked list to which delete the head.
 * delete_bool -> an integer number, used to interrogate the client if he wants to
 * delete the users data as well with the node. i.e:
 *
 * 0 -> just delete (free) the node, and not its content.
 * A number different from 0 -> delete (free), together with the node, the user defined contents
 * as well.
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

/***stack / queue***/

stack_t RICK45BSTACK_StackCreate(RICK45B_comparator_t key_cmp, unsigned long int dim);
/*
 * Function that, given a RICK45B_comparator_t function, creates a new stack, with max dimension 'dim'.
 * The RICK45B_comparator_t function will be used to compare the stack's elements.
 * Returns NULL if an error has occurred, a stack_t variable otherwise.
 * Arguments:
 * key_cmp -> used to compare the stack's keys. The function must accept two generic arguments, and
 * return 0 if the two keys were the same, a value of <0 if the first argument was less than the second, >0 otherwise.
 * dim -> specify the max number of elements that can be contained inside the stack. A number equal to 0 creates a stack
 * with no max dimension.
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

void RICK45BSTACK_StackDestroy(stack_t stack, int delete_bool);
/*
 * Function that, given a stack, it destroys it.
 * Arguments:
 * stack -> the stack which you'd like to destroy.
 * delete_bool -> an integer number, used to interrogate the client if he wants to
 * delete the users data as well with the node. i.e:
 * 0 -> just delete (free) the node, and not its content.
 * A number different from 0 -> delete (free), together with the node, the user defined contents
 * as well.
 * Use a delete_bool different from 0 only if the stack doesn't contains
 * any stack-allocated data!!
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

void *RICK45BSTACK_StackTop(stack_t stack);
/*
 * Function that, provided a stack variable, returns the key at the top of it, but WITHOUT removing it from the stack.
 * Returns the key if no errors occurred, NULL otherwise.
 * Arguments:
 * stack -> the stack containing the key to TOP.
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

void *RICK45BSTACK_StackPop(stack_t stack);
/*
 * Function that, provided a stack variable, returns the key at the top of it, while also removing it from the stack.
 * Returns the key if no errors occurred, NULL otherwise.
 * Arguments:
 * stack -> the stack containing the key to POP.
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

int RICK45BSTACK_StackPush(stack_t stack, void *key);
/*
 * Function that, provided a stack and a key, pushes the key at the top of the stack, if space is avaiable.
 * Return -1 if an error has occurred, 0 otherwise.
 * Arguments:
 * stack -> the stack where to PUSH the given key.
 * key -> the generic key to PUSH on top of the stack.
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

int RICK45BSTACK_IsEmpty(stack_t stack);
/*
 * Function that, given a stack, checks if it's empty or not.
 * Returns 1 if the stack is empty, -1 if an error has occurred, 0 otherwise.
 * Arguments:
 * stack -> the stack to which perform the test.
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

int RICK45BSTACK_IsFull(stack_t stack);
/*
 * Function that, given a stack, checks if it's full or not.
 * Returns 1 if the stack is full, -1 if an error has occurred, 0 otherwise.
 * Arguments:
 * stack -> the stack to which perform the test.
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

size_t RICK45BSTACK_GetStackSize(stack_t stack);
/*
 * Function that, given a stack, it returns its size.
 * Returns the number of keys stored in the given stack.
 * Arguments:
 * stack -> the stack from where to get the size from.
*/

int RICK45BSTACK_IsTop(stack_t stack, void *key);
/*
 * Function that checks if a generic key is on top of the given stack.
 * Returns 1 if TRUE, 0 if FALSE, -1 if an error has occurred.
 * Arguments:
 * stack -> the stack where to perform the current test.
 * key -> the key to search in the given stack.
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

int RICK45BSTACK_ContainedInStack(stack_t stack, void *key);
/*
 * Function that checks if a generic key is contained in the given stack.
 * Returns 1 if TRUE, 0 if FALSE, -1 if an error has occurred.
 * Arguments:
 * stack -> the stack where to perform the current test.
 * key -> the key to search in the given stack.
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

queue_t RICK45BQUEUE_QueueCreate(RICK45B_comparator_t key_cmp, unsigned long int dim);
/*
 * Function that, given a RICK45B_comparator_t function, creates a new queue, with max dimension 'dim'.
 * The RICK45B_comparator_t function will be used to compare the queue's elements.
 * Returns NULL if an error has occurred, a queue_t variable otherwise.
 * Arguments:
 * key_cmp -> used to compare the queue's keys. The function must accept two generic arguments, and
 * return 0 if the two keys were the same, a value of <0 if the first argument was less than the second, >0 otherwise.
 * dim -> specify the max number of elements that can be contained inside the queue. A number equal to 0 creates a queue
 * with no max dimension.
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

void RICK45BQUEUE_QueueDestroy(queue_t queue, int delete_bool);
/*
 * Function that, given a queue, it destroys it.
 * Arguments:
 * queue -> the queue which you'd like to destroy.
 * delete_bool -> an integer number, used to interrogate the client if he wants to
 * delete the users data as well with the node. i.e:
 * 0 -> just delete (free) the node, and not its content.
 * A number different from 0 -> delete (free), together with the node, the user defined contents
 * as well.
 * Use a delete_bool different from 0 only if the queue doesn't contains
 * any stack-allocated data!!
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

int RICK45BQUEUE_Enqueue(queue_t queue, void *key);
/*
 * Function that, given a key, enques it into the given queue, if space is avaiable.
 * Returns -1 if an error has occurred, 0 otherwise.
 * Arguments:
 * queue -> the queue inside which enqueueing the key.
 * key -> the key to enqueue.
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

void *RICK45BQUEUE_Dequeue(queue_t queue);
/*
 * Function that, provided a queue, returns the key at the end of it, while also removing it from the queue.
 * Returns the key if no errors occurred, NULL otherwise.
 * Arguments:
 * queue -> the queue containing the key to dequeue.
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

int RICK45BQUEUE_IsEmpty(queue_t queue);
/*
 * Function that, given a queue, checks if it's empty or not.
 * Returns 1 if the queue is empty, -1 if an error has occurred, 0 otherwise.
 * Arguments:
 * queue -> the queue to which perform the test.
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

int RICK45BQUEUE_IsFull(queue_t queue);
/*
 * Function that, given a queue, checks if it's full or not.
 * Returns 1 if the queue is full, -1 if an error has occurred, 0 otherwise.
 * Arguments:
 * queue -> the queue to which perform the test.
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

size_t RICK45BQUEUE_GetQueueSize(queue_t queue);
/*
 * Function that, given a queue, it returns its size.
 * Returns the number of keys stored in the given queue.
 * Arguments:
 * queue -> the queue from where to get the size from.
*/

int RICK45BQUEUE_ContainedInQueue(queue_t queue, void *key);
/*
 * Function that checks if a generic key is contained in the given queue.
 * Returns 1 if TRUE, 0 if FALSE, -1 if an error has occurred.
 * Arguments:
 * queue -> the queue where to perform the current test.
 * key -> the key to search in the given queue.
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

void *RICK45BQUEUE_Peek(queue_t queue);
/*
 * Function that, given a queue, acquires the element at the front of the queue, without removing it.
 * Returns the element at the front of the queue, or NULL if an error has occurred / the queue is empty.
 * Arguments:
 * queue -> the queue where to acquire the element from.
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

void *RICK45BQUEUE_Rear(queue_t queue);
/*
 * Function that, given a queue, acquires the element at the rear of the queue, without removing it.
 * Returns the element at the rear of the queue, or NULL if an error has occurred / the queue is empty.
 * Arguments:
 * queue -> the queue where to acquire the element from.
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

/***binary search tree***/

Btree_t RICK45BTREES_BtreeCreate(RICK45B_comparator_t key_cmp);
/*
 * Function that, given a RICK45B_comparator_t function, creates a new binary search tree.
 * The RICK45B_comparator_t function will be used to compare the tree's keys.
 * Returns NULL if an error has occurred, a valid Btree_t pointer otherwise.
 * Arguments:
 * key_cmp -> used to compare the tree's keys. The function must accept two generic arguments, and
 * return 0 if the two keys were the same, a value of <0 if the first argument was less than the second, >0 otherwise.
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

int RICK45BTREES_BtreeDestroy(Btree_t Btree, int delete_value, int delete_key);
/*
 * Function that, given a binary search tree, it destroys it.
 * Returns -1 if an error has occurred, 0 otherwise.
 * Arguments:
 * Btree -> the binary search tree which you'd like to destroy
 * delete_value -> an integer number, used to interrogate the client if he wants to
 * delete the node's value as well with the node.
 * delete_key -> an integer number, used to interrogate the client if he wants to
 * delete the node's key as well with the node.
 * Use a delete_value / delete_key different from 0 only if the binary search tree doesn't contains
 * any stack-allocated data for the value / key of the node!!
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

int RICK45BTREES_BtreeAddNode(Btree_t Btree, void *key, void *value);
/*
 * Function that, given a binary search tree, it adds a new node to it.
 * Returns -1 if an error has occurred, 0 otherwise.
 * Arguments:
 * Btree -> the binary search tree to which you'd like to add a new node.
 * key -> the key of the new nod, which will be associated with the value of the new node.
 * value -> the value of the new node.
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

int RICK45BTREES_BtreeforEach(Btree_t Btree, RICK45B_forEach_t funct, void *opt);
/*
 * Function that, given a binary search tree, a function and an optional argument named 'opt', applies funct to
 * every element of the Btree, with a 'opt' optional argument. Returns -1 if an error has occurred, 0 otherwise.
 * Arguments:
 * Btree -> the binary search tree to which apply the function to every single element.
 * funct -> the function to apply to every single element of the binary search tree.
 * opt -> optional argument of the 'funct' function.
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
 * BE CAREFUL when using this function, as some tree's manipulations may lead to the disruption of the tree!
*/

int RICK45BTREES_BtreeRemoveNode(Btree_t Btree, void *key, int delete_value, int delete_key);
/*
 * Function that, given a binary search tree, it removes the node identified by the argument 'key'.
 * Returns -1 if an error has occurred, 0 otherwise.
 * Arguments:
 * Btree -> the binary search tree to which you'd like to remove a node.
 * key -> the key identifying the node to remove.
 * delete_value -> an integer number, used to interrogate the client if he wants to
 * delete the node's value as well with the node.
 * delete_key -> an integer number, used to interrogate the client if he wants to
 * delete the node's key as well with the node.
 * Use a delete_value / delete_key different from 0 only if the node you'd like to remove doesn't contains
 * any stack-allocated data for the value / key of the node!!
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

treeNode_t RICK45BTREES_BtreeSearchNode(Btree_t Btree, void *key);
/*
 * Function that, given a binary search tree and a key, it searches for the node identified by 'key'.
 * Returns NULL if an error has occurred, a treeNode_t variable otherwise.
 * Arguments:
 * Btree -> the binary search tree where to search for the key.
 * key -> the key identifying the node to retrieve in the binary search tree.
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

int RICK45BTREES_BtreeIsLeaf(Btree_t Btree, void *key);
/*
 * Function that, given a binary search tree and a key, it determines if the node identified by 'key' is a leaf.
 * Returns 1 if TRUE, 0 if FALSE, and -1 if an error has occurred.
 * Arguments:
 * Btree -> the binary search tree where to test if node identified by the given key is actually a leaf.
 * key -> the key identifying the node to test.
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

treeNode_t RICK45BTREES_BtreeMaxNode(treeNode_t root);
/*
 * Function that, given a root of a binary search tree, it finds the node with the highest key value.
 * Returns NULL if an error has occurred and no node could be found, a treeNode_t variable otherwise.
 * Arguments:
 * root -> the root of the subtree in which to search for the node with the highest key value.
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

treeNode_t RICK45BTREES_BtreeMinNode(treeNode_t root);
/*
 * Function that, given a root of a binary search tree, it finds the node with the lowest key value.
 * Returns NULL if an error has occurred and no node could be found, a treeNode_t variable otherwise.
 * Arguments:
 * root -> the root of the subtree in which to search for the node with the lowest key value.
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

int RICK45BTREES_BtreeHeight(Btree_t Btree);
/*
 * Function that, given a binary tree, it calculates its height.
 * Returns -1 if an error has occurred, the height otherwise.
 * Arguments:
 * Btree -> the binary tree whose height is to be calculated.
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

int RICK45BTREES_BtreeLeavesNum(Btree_t Btree);
/*
 * Function that, given a binary tree, it calculates the number of its leaves.
 * Returns -1 if an error has occurred, the number of leaves otherwise.
 * Arguments:
 * Btree -> the binary tree whose number of leaves is to be calculated.
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

int RICK45BTREES_BtreeNodesNum(Btree_t Btree);
/*
 * Function that, given a binary tree, it calculates the number of its nodes.
 * Returns -1 if an error has occurred, the number of nodes otherwise.
 * Arguments:
 * Btree -> the binary tree whose number of nodes is to be calculated.
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

/***private functions***/

treeNode_t RICK45BTREES_NodeCreate(void *key, void *value, unsigned int treeType);
/*
 * Function used to create a new node, with the specs given by the treeType parameter.
 * Returns NULL if an error has occurred, a treeNode_t type value otherwise.
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

int RICK45BTREES_BtreeforEachImpl(treeNode_t node, RICK45B_forEach_t funct, void *opt, int *state);
/*
 * Private function that implements the 'RICK45BTREES_BtreeforEach' function. Returns -1 if an error has occurred,
 * 0 otherwise. It is a recursive function, hence why the node argument. The 'state' argument is the actual
 * return state of the function that will be catched by the 'RICK45BTREES_BtreeforEach' function itself.
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

int RICK45BTREES_BtreeforEachDeleteNode(void *nodeIn, void *optIn);
/*
 * Private function used in the 'RICK45BTREES_BtreeforEachImpl' private function. It deletes every node passed as an argument.
 * The 'optIn' argument decides if the value and key of the node must be free'd as well. OptIn must be an array of integers.
 * i.e:
 * 0 | x -> free the value, but not the key.
 * x | 0 -> free the key, but not the value.
 * x | x -> free both.
 * 0 | 0 -> free neither.
 *
 * Returns -1 if an error has occurred, 0 otherwise. It's an implementation of the 'RICK45B_forEach_t' function's variable.
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

treeNode_t RICK45BTREES_BtreeSearchNodeImpl(Btree_t Btree, treeNode_t root, void *key, int *state);
/*
 * Private recursive function that, given the root of the binary search tree, it searches for the node identified by key.
 * the state arguments will store the return code of the function.
*/

treeNode_t RICK45BTREES_BtreeFindPrev(Btree_t Btree, treeNode_t node, treeNode_t root);
/*
 * Private function, used to find the previous node of the 'node' argument.
 * Returns the previous node if succesful, NULL otherwise.
 * The root argument is the node base from where to search for the previous node.
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

treeNode_t RICK45BTREES_BtreeRemoveNodeImpl(Btree_t Btree, treeNode_t node, void *key, int delete_value, int delete_key);
/*
 * Private function that, given all the above arguments, it removes the node identified by key. The return status
 * can be probed with the returnStat variable.
 *
 * If an error has occurred, the error message can be retrieved by using the function 'RICK45B_GetError()'.
*/

int RICK45BTREES_BtreeHeightImpl(treeNode_t root);
/*
 * Private recursive function that calculates the height of a binary tree, given its root.
 * Used to implement RICK45BTREES_BtreeHeight;
*/

int RICK45BTREES_BtreeLeavesNumImpl(Btree_t Btree, treeNode_t root);
/*
 * Private recursive function that calculates the number of leaves of a binary tree, given its root.
 * Used to implement RICK45BTREES_BtreeLeavesNum;
*/

int RICK45BTREES_BtreeNodesNumImpl(Btree_t Btree, treeNode_t root);
/*
 * Private recursive function that calculates the number of nodes of a binary tree, given its root.
 * Used to implement RICK45BTREES_BtreeNodesNum;
*/

/***definition of shared functions***/

static __inline__ int RICK45B_LibStart(malloc_t malloc_funct, free_t free_funct){

    if(malloc_funct==NULL || free_funct==NULL)
    {
        RICK45B_CopyString("Failed to initialize library: malloc_funct and free_funct functions CANNOT be NULL!", RICK45B.GetError, sizeof("Failed to initialize library: malloc_funct and free_funct functions CANNOT be NULL!"));
        return -1;
    }
    mallocFun = malloc_funct;
    freeFun = free_funct;
    return 0;
}
