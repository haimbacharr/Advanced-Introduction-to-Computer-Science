#ifndef _header3
#define _header3

#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#define N 5          
typedef struct Item {
	int num;
	struct Item* next;
}Item;
typedef struct Que {
	Item* head, * tail;
	int size;      //a current number of items
}Queue, * PQue;

void Enqueue(PQue Q, int   new_elem);   //add a new member to list of the queue 
int Dequeue(PQue Q, int* del_value);     //delete member from the queue and  return the deleted value  using int *del_value.
void DeleteList(PQue a);
void Error_Msg(char* msg);

#endif