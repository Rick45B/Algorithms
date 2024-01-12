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

void destroy_createTreesTEST();
void insert_removeTreesTEST();
void miscTreesTest();
int doubleNodeValue(void *node, void *opt);
void treeVisualizerDouble(Btree_t Btree);
int treeVisualizerDoubleImpl(void *node, void *opt);

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

int main(){
    /*starting the library*/
    RICK45B_LibStart(malloc, free);

    /*list tests*/
    destroy_createTreesTEST();
    printf("\n***destroy_createTreesTEST successful***\n\n");
    insert_removeTreesTEST();
    printf("***insert_removeTreesTEST successful***\n\n");
    miscTreesTest();
    printf("***miscTreesTest successful***\n\n");
    printf("\n***All test were successful***\n\n");
    return 0;
}

void destroy_createTreesTEST(){
    double array_values[] = {1.0, 3.9, -2, 7.3, 9.81, 347, 8250.72};
    Btree_t binaryTree = NULL;
    binaryTree = RICK45BTREES_BtreeCreate(RICK45B_DoubleCMP);
    assert(binaryTree!=NULL);
    treeNode_t temp = RICK45BTREES_NodeCreate("A", &array_values[3], 2);
    assert(temp!=NULL && strcmp(temp->key, "A")==0 && RICK45B_DoubleCMP(temp->value, &array_values[3])==0);
    free(temp->childs);
    free(temp);
    assert(RICK45BTREES_BtreeDestroy(binaryTree, 0, 0)!=-1);
}

void insert_removeTreesTEST(){
    double array_values[] = {1.0, 3.9, -2, 7.3, 9.81, 347, 8250.72};
    double doubleArray_values[] = {2.0, 7.8, -4, 14.6, 19.62, 694, 16501.44};
    Btree_t binaryTree = NULL;
    binaryTree = RICK45BTREES_BtreeCreate(RICK45B_DoubleCMP);
    assert(binaryTree!=NULL);
    RICK45BTREES_BtreeAddNode(binaryTree, &array_values[1], "A");
    RICK45BTREES_BtreeAddNode(binaryTree, &array_values[0], "B");
    RICK45BTREES_BtreeAddNode(binaryTree, &array_values[6], "C");
    printf("Nodes before doubling them: \n");
    treeVisualizerDouble(binaryTree);
    /*
     *              3.9 = A
                    /     \
                1 = B   8250.72 = C
    */
    assert(strcmp(binaryTree->root->value,"A")==0 && strcmp(binaryTree->root->childs[0]->value, "B")==0 && strcmp(binaryTree->root->childs[1]->value, "C")==0);
    assert(RICK45B_DoubleCMP(binaryTree->root->key, &array_values[1])==0 && RICK45B_DoubleCMP(binaryTree->root->childs[0]->key, &array_values[0])==0 && RICK45B_DoubleCMP(binaryTree->root->childs[1]->key, &array_values[6])==0);

    /*doubling every node's value*/
    assert(RICK45BTREES_BtreeforEach(binaryTree, doubleNodeValue, NULL)==0);
    printf("Nodes after doubling their keys: \n");
    treeVisualizerDouble(binaryTree);
    assert(strcmp(binaryTree->root->value,"A")==0 && strcmp(binaryTree->root->childs[0]->value, "B")==0 && strcmp(binaryTree->root->childs[1]->value, "C")==0);
    assert(RICK45B_DoubleCMP(binaryTree->root->key, &doubleArray_values[1])==0 && RICK45B_DoubleCMP(binaryTree->root->childs[0]->key, &doubleArray_values[0])==0 && RICK45B_DoubleCMP(binaryTree->root->childs[1]->key, &doubleArray_values[6])==0);
    /*
     *              7.8 = A
                    /     \
                2 = B   16501.44 = C
    */

    /*deleting the binary search tree with all its nodes*/
    assert(RICK45BTREES_BtreeDestroy(binaryTree, 0, 0)!=-1);
    binaryTree = NULL;

    /*malloc'd key and values*/
    /*Initializing heap variables*/
    double *malloc_values = malloc(sizeof(double)*3);
    char *malloc_keys = malloc(sizeof(char)*3);
    int i;
    for (i = 0; i<3; i++)
        malloc_values[i] = i*2.1;
    for (i = 0; i<3; i++)
        malloc_keys[i] = (char)((int)'A'+i);

    double *mallocKey1 = malloc(sizeof(double));
    *mallocKey1 = 0;
    double *mallocKey2 = malloc(sizeof(double));
    *mallocKey2 = 4.2;
    double *mallocKey3 = malloc(sizeof(double));
    *mallocKey3 = 2.1;

    char *malloc1 = malloc(sizeof(char));
    *malloc1 = 'A';
    char *malloc2 = malloc(sizeof(char));
    *malloc2 = 'B';
    char *malloc3 = malloc(sizeof(char));
    *malloc3 = 'C';

    /*creating the binary tree, and adding nodes to it*/
    binaryTree = RICK45BTREES_BtreeCreate(RICK45B_DoubleCMP);
    assert(binaryTree!=NULL);
    RICK45BTREES_BtreeAddNode(binaryTree, mallocKey1, malloc1);
    RICK45BTREES_BtreeAddNode(binaryTree, mallocKey2, malloc2);
    RICK45BTREES_BtreeAddNode(binaryTree, mallocKey3, malloc3);
    /*
            0 = A
               \
              4.2 = B
               /
             2.1 = C
    */
    assert(*(char *)(binaryTree->root->value) == 'A' && *(char *)(binaryTree->root->childs[1]->value) == 'B' && *(char *)(binaryTree->root->childs[1]->childs[0]->value) == 'C');
    assert(RICK45B_DoubleCMP(binaryTree->root->key, &malloc_values[0])==0 && RICK45B_DoubleCMP(binaryTree->root->childs[1]->key, &malloc_values[2])==0 && RICK45B_DoubleCMP(binaryTree->root->childs[1]->childs[0]->key, &malloc_values[1])==0);
    treeVisualizerDouble(binaryTree);

    /*deleting the binary search tree with all its nodes*/
    assert(RICK45BTREES_BtreeDestroy(binaryTree, 1, 1)!=-1);
    free(malloc_values);
    free(malloc_keys);
    binaryTree = NULL;

    /*creating a new binary search tree, and deleting some nodes*/
    double array_keys[] = {1.0, 3.9, -2, 7.3, 9.81, 347, 8250.72};
    binaryTree = NULL;
    binaryTree = RICK45BTREES_BtreeCreate(RICK45B_DoubleCMP);
    /*
                    347
                    / \
                  7.3   8250.72
                  / \
                -2  9.81
    */
    RICK45BTREES_BtreeAddNode(binaryTree, &array_keys[5], "A");
    RICK45BTREES_BtreeAddNode(binaryTree, &array_keys[3], "B");
    RICK45BTREES_BtreeAddNode(binaryTree, &array_keys[4], "C");
    RICK45BTREES_BtreeAddNode(binaryTree, &array_keys[2], "D");
    RICK45BTREES_BtreeAddNode(binaryTree, &array_keys[6], "E");
    assert(RICK45BTREES_BtreeHeight(binaryTree)==3);
    assert(RICK45BTREES_BtreeNodesNum(binaryTree)==5);
    printf("Tree before deleting some nodes\n");
    treeVisualizerDouble(binaryTree);
    /*
                    347
                    /
                  7.3
                  / \
                -2  9.81
    */

    assert(RICK45BTREES_BtreeRemoveNode(binaryTree, &array_keys[6], 0, 0)==0);
    assert(RICK45BTREES_BtreeNodesNum(binaryTree)==4);
    printf("Tree after deleting node with key 8250.72:\n");
    treeVisualizerDouble(binaryTree);
    assert(RICK45BTREES_BtreeRemoveNode(binaryTree, &array_keys[3], 0, 0)==0);
    assert(RICK45BTREES_BtreeNodesNum(binaryTree)==3);
    /*
                    347
                    /
                  -2
                    \
                    9.81
    */
    printf("Tree after deleting node with key 7.3:\n");
    treeVisualizerDouble(binaryTree);
    assert(RICK45BTREES_BtreeRemoveNode(binaryTree, &array_keys[5], 0, 0)==0);
    assert(RICK45BTREES_BtreeNodesNum(binaryTree)==2);
    /*
                  -2
                    \
                    9.81
    */
    printf("Tree after deleting node with key 347:\n");
    assert(binaryTree->root->childs[1]->childs[0]==NULL);
    assert(binaryTree->root->childs[1]->childs[1]==NULL);
    assert(RICK45BTREES_BtreeHeight(binaryTree)==2);
    treeVisualizerDouble(binaryTree);

    /*inserting a malloc'd 7.*/
    double *mallocD = malloc(sizeof(double));
    *mallocD = 7;
    char *mallocC = malloc(sizeof(char));
    *mallocC = 'F';
    assert(RICK45BTREES_BtreeAddNode(binaryTree, mallocD, mallocC)==0);
    assert(RICK45BTREES_BtreeNodesNum(binaryTree)==3);
    /*
                  -2
                    \
                    9.81
                    /
                    7
    */
    assert(RICK45BTREES_BtreeHeight(binaryTree)==3);
    printf("Tree after adding node with key 7:\n");
    treeVisualizerDouble(binaryTree);
    /*deleting 9.81*/
    assert(RICK45BTREES_BtreeRemoveNode(binaryTree, &array_keys[4], 0, 0)==0);
    assert(RICK45BTREES_BtreeNodesNum(binaryTree)==2);
    /*
                  -2
                    \
                    7
    */
    assert(RICK45BTREES_BtreeHeight(binaryTree)==2);
    printf("Tree after deleting node with key 9.81:\n");
    treeVisualizerDouble(binaryTree);

    /*deleting 7*/
    assert(RICK45BTREES_BtreeRemoveNode(binaryTree, mallocD, 1, 1)==0);
    assert(RICK45BTREES_BtreeNodesNum(binaryTree)==1);
    printf("Tree after deleting node with key 7:\n");
    treeVisualizerDouble(binaryTree);
    /*
                  -2
    */

    /*deleting -2*/
    assert(RICK45BTREES_BtreeHeight(binaryTree)==1);
    assert(RICK45BTREES_BtreeRemoveNode(binaryTree, &array_keys[2], 0, 0)==0);
    assert(RICK45BTREES_BtreeNodesNum(binaryTree)==0);
    assert(RICK45BTREES_BtreeHeight(binaryTree)==0);
    printf("Tree after deleting node with key -2:\n");
    treeVisualizerDouble(binaryTree);

    /*destroying the binary search tree*/
    assert(RICK45BTREES_BtreeDestroy(binaryTree, 0, 0)!=-1);
    binaryTree = NULL;
    assert(RICK45BTREES_BtreeNodesNum(binaryTree)==-1); /*Testing error detection*/
}

void miscTreesTest()
{
    double array_keys[] = {1.0, 3.9, -2, 7.3, 9.81, 347, 8250.72};
    Btree_t binaryTree = NULL;
    binaryTree = RICK45BTREES_BtreeCreate(RICK45B_DoubleCMP);
    /*
            7.3
            /  \
           1.0  347
           / \
         -2  3.9
    */
    RICK45BTREES_BtreeAddNode(binaryTree, &array_keys[3], "A");
    RICK45BTREES_BtreeAddNode(binaryTree, &array_keys[0], "B");
    RICK45BTREES_BtreeAddNode(binaryTree, &array_keys[2], "C");
    RICK45BTREES_BtreeAddNode(binaryTree, &array_keys[1], "D");
    RICK45BTREES_BtreeAddNode(binaryTree, &array_keys[5], "E");
    printf("Created tree: \n");
    treeVisualizerDouble(binaryTree);

    /*testing the RICK45BTREES_BtreeSearchNode function*/
    assert(strcmp(RICK45BTREES_BtreeSearchNode(binaryTree, &array_keys[1])->value, "D")==0);
    assert(strcmp(RICK45BTREES_BtreeSearchNode(binaryTree, &array_keys[0])->value, "B")==0);
    assert(strcmp(RICK45BTREES_BtreeSearchNode(binaryTree, &array_keys[3])->value, "A")==0);
    assert(strcmp(RICK45BTREES_BtreeSearchNode(binaryTree, &array_keys[5])->value, "E")==0);
    assert(strcmp(RICK45BTREES_BtreeSearchNode(binaryTree, &array_keys[2])->value, "C")==0);
    assert(strcmp(RICK45BTREES_BtreeSearchNode(binaryTree, &array_keys[1])->value, "A")!=0);
    assert(RICK45BTREES_BtreeSearchNode(binaryTree, &array_keys[4])==NULL);  /*Testing error detection*/

    /*testing the RICK45BTREES_BtreeIsLeaf function*/
    assert(RICK45BTREES_BtreeIsLeaf(binaryTree, &array_keys[1])==1);
    assert(RICK45BTREES_BtreeIsLeaf(binaryTree, &array_keys[5])==1);
    assert(RICK45BTREES_BtreeIsLeaf(binaryTree, &array_keys[2])==1);
    assert(RICK45BTREES_BtreeIsLeaf(binaryTree, &array_keys[0])==0);
    assert(RICK45BTREES_BtreeIsLeaf(binaryTree, &array_keys[3])==0);
    assert(RICK45BTREES_BtreeIsLeaf(binaryTree, &array_keys[6])==-1);   /*Testing error detection*/

    /*testing the RICK45BTREES_BtreeMaxNode function*/
    assert(*((double *)(RICK45BTREES_BtreeMaxNode(binaryTree->root)->key)) == 347);

    /*testing the RICK45BTREES_BtreeHeightImpl function*/
    assert(RICK45BTREES_BtreeHeight(binaryTree)==3);
    assert(RICK45BTREES_BtreeHeight(NULL)==-1);     /*Testing error detection*/

    /*testing the RICK45BTREES_BtreeLeavesNum function*/
    assert(RICK45BTREES_BtreeLeavesNum(binaryTree)==3);
    assert(RICK45BTREES_BtreeLeavesNum(NULL)==-1);      /*Testing error detection*/

    /*testing the RICK45BTREES_BtreeNodesNum function*/
    assert(RICK45BTREES_BtreeNodesNum(binaryTree)==5);
    assert(RICK45BTREES_BtreeNodesNum(NULL)==-1);   /*Testing error detection*/

    assert(RICK45BTREES_BtreeDestroy(binaryTree, 0, 0)!=-1);
}

int doubleNodeValue(void *node, void *opt)
{
    opt = NULL; /*opt must NOT be used in this particular function*/

    if (node == NULL || opt!=NULL)
        return -1;
    treeNode_t nodeTemp = (treeNode_t)node;
    double *doubleVal = malloc(sizeof(double *));
    doubleVal = (double *)(nodeTemp->key);
    *doubleVal = *(doubleVal)*2;
    nodeTemp->key = doubleVal;
    return 0;
}

void treeVisualizerDouble(Btree_t Btree)
{
    printf("Node's Keys of the tree (DFS view): \n");
    RICK45BTREES_BtreeforEach(Btree, treeVisualizerDoubleImpl, NULL);
}

int treeVisualizerDoubleImpl(void *node, void *opt)
{
    if (opt != NULL)
    {
        printf("treeVisualizerImpl error!\n");
        return 0;
    }
    if (node == NULL)
        printf("NULL!\n");
    else
    {
        treeNode_t nodeCast = (treeNode_t)node;
        printf("%f\n", *((double *)nodeCast->key));
    }
    printf("\n");
    return 1;
}
