#ifndef _head
#define _head
#define _CRT_SECURE_NO_WARNINGS
#define NUM 4
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<math.h>

typedef struct Item {
	int num;
	struct Item* next;
}Item;
typedef struct Stack {
	Item* head;
	int size;         //a current number of items
}Stack, * PStack;

void Push(PStack s, int   new_elem);    //add a new member to list of the stack
int Pop(PStack s, int* del_value);       //delete member from the stack and  return the deleted value  using  int * del_value
void Error_Msg(char *str);
void DeleteList(PStack start);


#endif
