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
#include "Rick45B-Utils.h"

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

void Errors_Test();
void Functions_Test();

int main()
{
    Errors_Test();
    printf("\n***Errors_Test succesful***\n\n");
    Functions_Test();
    printf("\n***Functions_Test succesful***\n\n");
    printf("\n***All test were successful***\n\n");
    return 0;
}

void Errors_Test()
{
    /*testing the error setting and retrieval functions*/
    RICK45B_SetError("Something went wrong!");
    assert(strcmp("Something went wrong!", RICK45B_GetError())==0);
    RICK45B_SetError("Cat!!");
    assert(strcmp("Cat!!", RICK45B_GetError())==0);
    RICK45B_SetError("Can you can a can as a canner can can a can?");
    assert(strcmp("Can you can a can as a canner can can a can?", RICK45B_GetError())==0);
}

void Functions_Test()
{
    char *string1 = "Paul";
    char *string2 = "Bob\0";
    char *string3 = "Charles\0";
    char *string4 = "paul";
    char *string5 = "Paul";

    assert(RICK45B_Strlen(string1)==strlen(string1));
    assert(RICK45B_Strlen(string2)==strlen(string2));
    assert(RICK45B_Strlen(string3)==strlen(string3));
    assert(RICK45B_Strlen(string4)==strlen(string4));
    assert(RICK45B_Strlen(string5)==strlen(string5));

    assert(RICK45B_Stringcmp(string1, string5)==0);
    assert(RICK45B_Stringcmp(string1, string4)>0);
    assert(RICK45B_Stringcmp(string3, string2)==-1);
}
