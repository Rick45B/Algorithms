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

/*This header and its source code implements a series of structures and functions needed to make all the other RICK45B libraries work.*/

/*defines*/
#define FALSE 0
#define TRUE 1

#include <stddef.h>

/*structs*/
typedef struct error{
    char GetError[100];
}error_rick45b;     /*needed for the client to get error info.*/

typedef void (*free_t)(void*);
/*This is a private function's variable, and should not be used*/

typedef void* (*malloc_t)(size_t);
/*This is a private function's variable, and should not be used*/

/*global variables*/
extern free_t freeFun;
extern malloc_t mallocFun;

/*needed for the client to get error info.*/
extern error_rick45b RICK45B;

char *RICK45B_GetError();
/*
 * Funcion that, once called, returns the latest error message of the library.
 * Returns: a string containing the error's message.
 * No arguments must be provided.
*/

/*private functions: DO NOT USE THEM.*/
void RICK45B_SetError(char *errorMsg);
/*
 * Simple function, used to set error msg in the "struct error" datatype, so that
 * string.h standard library is not necessarily required.
*/

void RICK45B_CopyString(char const*source, char *dest, size_t lenght);
/*
 * Simple function that mimics the string.h's 'strcpy' function.
 * returns nothing.
 * Arguments:
 * source -> the source string
 * dest -> the destination string
 * lenght -> the number of bytes to copy from source to dest.
*/

size_t RICK45B_Strlen(char const *string);
/*
 * Function that mimics the string.h's function 'strlen'.
 * Returns 0 if string is NULL.
*/

int RICK45B_Stringcmp(char const *string1, char const *string2);
/*
 * Function that mimics the string.h's function 'strcmp'.
 * Returns -1 if an error has occurred, 0 if the strings are equal, a number >0 otherwise.
*/
