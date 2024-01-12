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

Btree_t RICK45BTREES_BtreeCreate(RICK45B_comparator_t key_cmp)
{
    if (key_cmp == NULL)
    {
        RICK45B_CopyString("Invalid Argument: key_cmp function cannot be NULL!", RICK45B.GetError, sizeof("Invalid Argument: key_cmp function cannot be NULL!"));
        return NULL;
    }

    Btree_t out = NULL;
    out = mallocFun(sizeof(struct binaryTree));

    if (out == NULL)
    {
        RICK45B_CopyString("Fatal Error: Cannot allocate memory for new Btree_t type. Perhaps the heap is full?", RICK45B.GetError, sizeof("Fatal Error: Cannot allocate memory for new Btree_t type. Perhaps the heap is full?"));
        return NULL;
    }

    out->root = NULL;
    out->key_cmp = key_cmp;
    out->treeType = 2;  //the tree can have 2 childs max
    return out;
}

int RICK45BTREES_BtreeDestroy(Btree_t Btree, int delete_value, int delete_key)
{
    int opt[] = {delete_value, delete_key};
    int out = RICK45BTREES_BtreeforEach(Btree, RICK45BTREES_BtreeforEachDeleteNode, opt);
    freeFun(Btree);
    return out;
}

int RICK45BTREES_BtreeAddNode(Btree_t Btree, void *key, void *value)
{
    if (Btree == NULL)
    {
        RICK45B_CopyString("Invalid Argument: the binary search tree cannot be NULL!", RICK45B.GetError, sizeof("Invalid Argument: the binary search tree cannot be NULL!"));
        return -1;
    }
    treeNode_t node = RICK45BTREES_NodeCreate(key, value, Btree->treeType);
    if (node == NULL) return -1;

    if (Btree->root == NULL)
    {
        Btree->root = node;
        return 0;
    }
    treeNode_t visit = Btree->root;
    treeNode_t prev = NULL;
    int i = 0;
    while (visit!=NULL)
    {
        prev = visit;
        (Btree->key_cmp(key, visit->key)<0)?(visit=(visit->childs)[0]):(visit=(visit->childs)[1]);  /*go left = [0] or go right = [1]*/
    }
    (Btree->key_cmp(key, prev->key)<0)?((prev->childs)[0]=node):((prev->childs)[1]=node);
    return 0;
}

treeNode_t RICK45BTREES_NodeCreate(void *key, void *value, unsigned int treeType)
{
    if (key==NULL)
    {
        RICK45B_CopyString("Invalid Argument: key cannot be NULL!", RICK45B.GetError, sizeof("Invalid Argument: key cannot be NULL!"));
        return NULL;
    }
    if (value==NULL)
    {
        RICK45B_CopyString("Invalid Argument: value cannot be NULL!", RICK45B.GetError, sizeof("Invalid Argument: value cannot be NULL!"));
        return NULL;
    }

    treeNode_t out = NULL;
    out = mallocFun(sizeof(struct treeNode));

    if (out==NULL)
    {
        RICK45B_CopyString("Fatal Error: Cannot allocate memory for new treeNode_t type. Perhaps the heap is full?", RICK45B.GetError, sizeof("Fatal Error: Cannot allocate memory for new treeNode_t type. Perhaps the heap is full?"));
        return NULL;
    }
    out->key = key;
    out->value = value;
    out->childs = NULL;
    out->childs = mallocFun(sizeof(struct treeNode*)*treeType);
    if (out->childs==NULL)
    {
        RICK45B_CopyString("Fatal Error: Cannot allocate memory for all the childs of the new node. Perhaps the heap is full?", RICK45B.GetError, sizeof("Fatal Error: Cannot allocate memory for all the childs of the new node. Perhaps the heap is full?"));
        return NULL;
    }

    unsigned int i;
    for (i=0; i<treeType; i++)  /*Setting all childs to NULL*/
        (out->childs)[i]=NULL;


    return out;
}

int RICK45BTREES_BtreeforEach(Btree_t Btree, RICK45B_forEach_t funct, void *opt)
{
    if (Btree == NULL)
    {
        RICK45B_CopyString("Invalid Argument: the binary search tree cannot be NULL!", RICK45B.GetError, sizeof("Invalid Argument: the binary search tree cannot be NULL!"));
        return -1;
    }

    if (funct == NULL)
    {
        RICK45B_CopyString("Invalid Argument: the binary search tree cannot be NULL!", RICK45B.GetError, sizeof("Invalid Argument: the binary search tree cannot be NULL!"));
        return -1;
    }
    int state = 0;
    if (RICK45BTREES_BtreeforEachImpl(Btree->root, funct, opt, &state)==-1)
        return -1;
    return state;
}

int RICK45BTREES_BtreeforEachImpl(treeNode_t node, RICK45B_forEach_t funct, void *opt, int *state)
{
    if (node == NULL)
        *state = 0;
    else
    {
        RICK45BTREES_BtreeforEachImpl(node->childs[0], funct, opt, state);
        RICK45BTREES_BtreeforEachImpl(node->childs[1], funct, opt, state);
        *state = funct(node, opt);
        if (*state == -1)
        {
            RICK45B_CopyString("Provided function error!", RICK45B.GetError, sizeof("Provided function error!"));
            return -1;
        }
    }

}

int RICK45BTREES_BtreeforEachDeleteNode(void *nodeIn, void *optIn)
{
    treeNode_t node = (treeNode_t)nodeIn;
    int *opt = (int *)optIn;

    if (node == NULL)
        return -1;
    if (opt == NULL)
        return -1;
    if ((sizeof(opt)/sizeof(int)) != 2)  //the array 'opt' has a different lenght than the expected 2.
        return -1;

    if (opt[0] !=0 && opt[1] != 0)
    {
        freeFun(node->key);
        freeFun(node->value);
    }
    else
    {
        if (opt[0] == 0 && opt[1] != 0)
            freeFun(node->value);
        if (opt[0] !=0 && opt[1] == 0)
            freeFun(node->key);
    }
    freeFun(node->childs);
    freeFun(node);
    return 0;
}

int RICK45BTREES_BtreeRemoveNode(Btree_t Btree, void *key, int delete_value, int delete_key)
{
    if (Btree == NULL)
    {
        RICK45B_CopyString("Invalid Argument: the binary search tree cannot be NULL!", RICK45B.GetError, sizeof("Invalid Argument: the binary search tree cannot be NULL!"));
        return -1;
    }
    if (key == NULL)
    {
        RICK45B_CopyString("Invalid Argument: key cannot be NULL!", RICK45B.GetError, sizeof("Invalid Argument: key cannot be NULL!"));
        return -1;
    }
    Btree->root = RICK45BTREES_BtreeRemoveNodeImpl(Btree, Btree->root, key, delete_value, delete_key);
    return 0;

}

treeNode_t RICK45BTREES_BtreeRemoveNodeImpl(Btree_t Btree, treeNode_t node, void *key, int delete_value, int delete_key)
{
    if (node != NULL)
    {
        int cmp = Btree->key_cmp(key, node->key);
        if (cmp < 0)    node->childs[0] = RICK45BTREES_BtreeRemoveNodeImpl(Btree, node->childs[0], key, delete_value, delete_key);
        else if (cmp > 0)   node->childs[1] = RICK45BTREES_BtreeRemoveNodeImpl(Btree, node->childs[1], key, delete_value, delete_key);
        else /*node found. Prooceding with deletion*/
        {
            if (node->childs[0] != NULL && node->childs[1] != NULL)
            {
                /*Node has two children*/
                treeNode_t max = RICK45BTREES_BtreeMaxNode(node->childs[0]);
                if (delete_value)   freeFun(node->value);
                if (delete_key) freeFun(node->key);
                node->key = max->key;
                node->value = max->value;
                node->childs[0] = RICK45BTREES_BtreeRemoveNodeImpl(Btree, node->childs[0], node->key, delete_value, delete_key);
            }
            else
            {
                /*Node has one child or zero child*/
                treeNode_t old_node = node;
                if (node->childs[0] == NULL)    node = node->childs[1];
                else    node = node->childs[0];
                if (delete_value)   freeFun(old_node->value);
                if (delete_key) freeFun(old_node->key);
                if (old_node->childs != NULL)  freeFun(old_node->childs);
                freeFun(old_node);
            }
        }
    }
    return node;
}

treeNode_t RICK45BTREES_BtreeSearchNode(Btree_t Btree, void *key)
{
    if (Btree == NULL)
    {
        RICK45B_CopyString("Invalid Argument: the binary search tree cannot be NULL!", RICK45B.GetError, sizeof("Invalid Argument: the binary search tree cannot be NULL!"));
        return NULL;
    }
    if (key == NULL)
    {
        RICK45B_CopyString("Invalid Argument: key cannot be NULL!", RICK45B.GetError, sizeof("Invalid Argument: key cannot be NULL!"));
        return NULL;
    }
    int *returnCode;
    return RICK45BTREES_BtreeSearchNodeImpl(Btree, Btree->root, key, returnCode);
}

treeNode_t RICK45BTREES_BtreeSearchNodeImpl(Btree_t Btree, treeNode_t root, void *key, int *returnCode)
{
    if (key == NULL)
    {
        *returnCode = -1;
        return NULL;
    }
    if (root == NULL)
        return NULL;

    if (Btree->key_cmp(key, root->key)<0)
        return RICK45BTREES_BtreeSearchNodeImpl(Btree, root->childs[0], key, returnCode);
    if (Btree->key_cmp(key, root->key)>0)
        return RICK45BTREES_BtreeSearchNodeImpl(Btree, root->childs[1], key, returnCode);
    if (Btree->key_cmp(key, root->key)==0)
    {
        treeNode_t out = NULL;
        out = RICK45BTREES_BtreeSearchNodeImpl(Btree, root->childs[0], key, returnCode);
        if (out==NULL)  return root;
        else  return out;
    }
}

int RICK45BTREES_BtreeIsLeaf(Btree_t Btree, void *key)
{
    if (Btree == NULL)
    {
        RICK45B_CopyString("Invalid Argument: the binary search tree cannot be NULL!", RICK45B.GetError, sizeof("Invalid Argument: the binary search tree cannot be NULL!"));
        return -1;
    }
    if (key == NULL)
    {
        RICK45B_CopyString("Invalid Argument: key cannot be NULL!", RICK45B.GetError, sizeof("Invalid Argument: key cannot be NULL!"));
        return -1;
    }

    treeNode_t node = RICK45BTREES_BtreeSearchNode(Btree, key);
    if (node == NULL)
    {
        RICK45B_CopyString("Couldn't find given key inside the binary search tree!", RICK45B.GetError, sizeof("Couldn't find given key inside the binary search tree!"));
        return -1;
    }
    if (node->childs[0]==NULL && node->childs[1]==NULL)
        return 1;
    return 0;
}

treeNode_t RICK45BTREES_BtreeFindPrev(Btree_t Btree, treeNode_t node, treeNode_t root)
{
    if (node == NULL)
    {
        RICK45B_CopyString("Invalid Argument: node cannot be NULL!", RICK45B.GetError, sizeof("Invalid Argument: node cannot be NULL!"));
        return NULL;
    }
    if (root == NULL)
    {
        RICK45B_CopyString("Invalid Argument: passed base node cannot be NULL!", RICK45B.GetError, sizeof("Invalid Argument: passed base node cannot be NULL!"));
        return NULL;
    }

    if (root->childs[0] == NULL && root->childs[1] == NULL) return NULL;
    if (Btree->key_cmp(node->key, root->key)<0)
    {
        if (root->childs[0]==node)   return root;
        return RICK45BTREES_BtreeFindPrev(Btree, node, root->childs[0]);
    }
    else
    {
        if (root->childs[1]==node)   return root;
        return RICK45BTREES_BtreeFindPrev(Btree, node, root->childs[1]);
    }
}

treeNode_t RICK45BTREES_BtreeMaxNode(treeNode_t root)
{
    if (root == NULL)
    {
        RICK45B_CopyString("Invalid Argument: the root node cannot be NULL!", RICK45B.GetError, sizeof("Invalid Argument: the root node cannot be NULL!"));
        return NULL;
    }
    if (root->childs[1] != NULL)
        return RICK45BTREES_BtreeMaxNode(root->childs[1]);
    else
        return root;
}

treeNode_t RICK45BTREES_BtreeMinNode(treeNode_t root)
{
    if (root == NULL)
    {
        RICK45B_CopyString("Invalid Argument: the root node cannot be NULL!", RICK45B.GetError, sizeof("Invalid Argument: the root node cannot be NULL!"));
        return NULL;
    }
    if (root->childs[0] != NULL)
        return RICK45BTREES_BtreeMaxNode(root->childs[0]);
    else
        return root;
}

int RICK45BTREES_BtreeHeight(Btree_t Btree)
{
    if (Btree == NULL)
    {
        RICK45B_CopyString("Invalid Argument: the binary search tree cannot be NULL!", RICK45B.GetError, sizeof("Invalid Argument: the binary search tree cannot be NULL!"));
        return -1;
    }
    return RICK45BTREES_BtreeHeightImpl(Btree->root);
}

int RICK45BTREES_BtreeHeightImpl(treeNode_t root)
{
    if (root == NULL)   return 0;
    int sx,dx,max;
    sx = RICK45BTREES_BtreeHeightImpl(root->childs[0]);
    dx = RICK45BTREES_BtreeHeightImpl(root->childs[1]);
    if (sx>=dx) max = sx;
    else max = dx;
    return 1+max;
}

int RICK45BTREES_BtreeLeavesNum(Btree_t Btree)
{
    if (Btree == NULL)
    {
        RICK45B_CopyString("Invalid Argument: the binary search tree cannot be NULL!", RICK45B.GetError, sizeof("Invalid Argument: the binary search tree cannot be NULL!"));
        return -1;
    }
    return RICK45BTREES_BtreeLeavesNumImpl(Btree, Btree->root);
}

int RICK45BTREES_BtreeLeavesNumImpl(Btree_t Btree, treeNode_t root)
{
    if (root == NULL)   return 0;
    if (RICK45BTREES_BtreeIsLeaf(Btree, root->key)) return 1;
    int sx,dx;
    sx = RICK45BTREES_BtreeLeavesNumImpl(Btree, root->childs[0]);
    dx = RICK45BTREES_BtreeLeavesNumImpl(Btree, root->childs[1]);
    return sx+dx;
}

int RICK45BTREES_BtreeNodesNum(Btree_t Btree)
{
    if (Btree == NULL)
    {
        RICK45B_CopyString("Invalid Argument: the binary search tree cannot be NULL!", RICK45B.GetError, sizeof("Invalid Argument: the binary search tree cannot be NULL!"));
        return -1;
    }
    return RICK45BTREES_BtreeNodesNumImpl(Btree, Btree->root);
}

int RICK45BTREES_BtreeNodesNumImpl(Btree_t Btree, treeNode_t root)
{
    if (root == NULL)   return 0;
    if (RICK45BTREES_BtreeIsLeaf(Btree, root->key))   return 1;
    int sx,dx;
    sx = RICK45BTREES_BtreeNodesNumImpl(Btree, root->childs[0]);
    dx = RICK45BTREES_BtreeNodesNumImpl(Btree, root->childs[1]);
    return sx+dx+1;
}
