#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

#define N 5

typedef struct Item
{
	int num;
	struct Item* next;
}*PItem;

void Error_Msg(char*);//Function that print a Messege.
void CreateListFromArray(PItem*, PItem*, int*);//Function that get two PItems pointers,and array of int. and create a list. 
void DeleteList(PItem*);//Function that get delete a linked list.
void ListDisplay(PItem);//Function that print Linked list in a recrusive way.
int ListLength(PItem);//Function that calculate the length of the linked list in a recrusive way.

int main()
{
	int Arr[N] = { 3,4,1,0,8 };

	PItem list = NULL, tail = NULL;

	CreateListFromArray(&list, &tail, Arr);
	printf("The length of the list is %d members\n", ListLength(list));
	printf("\nThe list is:\n");
	ListDisplay(list);

	DeleteList(&list);
	tail = NULL;
	return 0;
}

void Error_Msg(char* msg)
{
	printf("\n%s", msg);
	exit(1);
}


void CreateListFromArray(PItem* head, PItem* tail, int* Arr)
{
	int i;
	PItem temp;
	for (i = 0; i < N; i++)
	{
		temp = (PItem)malloc(sizeof(struct Item));
		if (temp == NULL)
		{
			DeleteList(head);//will free the linked list.
			Error_Msg("Memmory!");
		}
		temp->num = Arr[i];
		temp->next = NULL;
		if (*head == NULL)
			*head = temp;
		else
			(*tail)->next = temp;
		*tail = temp;
	}
}


void DeleteList(PItem* head)
{
	PItem tmp = *head;
	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp);
	}
}

int ListLength(PItem q)//Function that calculate how many blocks in the linked list.
{
	if (NULL == q) return 0;
	return 1 + (ListLength(q->next));
}

void ListDisplay(PItem q)//Function that print the blocks in the linked list.
{
	if (NULL == q) return 0;
	fprintf(stdout,"%d--> ", q->num);
	ListDisplay( q->next);

}
