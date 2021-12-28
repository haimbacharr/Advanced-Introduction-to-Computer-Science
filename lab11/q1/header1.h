#ifndef _header1
#define _header1
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


typedef struct node* PSTACKNODE; //declaring of a type.

void* top(PSTACKNODE stack);
void push(void* key, PSTACKNODE* stack);
void pop(PSTACKNODE* stack, void(*free_data)(void*));
int isempty(PSTACKNODE stack);

#endif