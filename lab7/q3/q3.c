#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef struct Item
{
	int num;
	float price;
	struct Item* next;
}*PItem;

void Error_Msg(char*);//Function that print a Messege and exit the program.
void AddNewItem(PItem* head, PItem* tail, int n, int a, float b); //Function that get 2 pointers,index of where to put a new item into the linked list and data about this block.and add this new block into the linked list.
void CreateList(PItem*, PItem*, FILE*);//Function that create Linked list.
void PrintItem(PItem);//Function that print a Block.
void PrintList(PItem, char*);//Function that print a linked list.
void WriteListToFile(PItem head, FILE*);
void DeleteList(PItem*);//Function that delete the linked list.

int main()
{
	int a, n;
	float b;
	PItem head = NULL, tail = NULL;
	FILE* in = fopen("input_price.txt", "rt");
	if (in == NULL)
		Error_Msg("input file is wrong");
	CreateList(&head, &tail, in);
	PrintList(head, "\nThe Old List:\n");
	printf("\n\nEnter a number and the price\n");
	scanf("%d%f", &a, &b);
	printf("\nEnter a place for the new item:");
	scanf("%d", &n);
	AddNewItem(&head, &tail, n, a, b);
	PrintList(head, "\nThe New List:\n");
	fclose(in);
	in = fopen("input_price.txt", "wt");
	if (in == NULL) {
		DeleteList(&head);
		Error_Msg("input file is wrong");
	}


	WriteListToFile(head, in);
	fclose(in);
	DeleteList(&head);
	tail = NULL;
	return 0;
}


void Error_Msg(char* msg)
{
	printf("\n%s", msg);
	exit(1);
}


void CreateList(PItem* head, PItem* tail, FILE* f)
{
	int a;
	float b;
	PItem temp;
	while (fscanf(f, "%d %f", &a, &b) == 2)
	{
		temp = (PItem)malloc(sizeof(struct Item));
		if (temp == NULL)
		{
			DeleteList(head);
			Error_Msg("Memmory!");
		}
		temp->num = a;
		temp->price = b;
		temp->next = NULL;
		if (*head == NULL)
			*head = temp;
		else
			(*tail)->next = temp;
		*tail = temp;
	}
}


void PrintItem(PItem node)
{
	printf("%d,%.1f-->", node->num, node->price);
}



void PrintList(PItem head, char* title)
{
	printf("%s", title);
	while (head)
	{
		PrintItem(head);
		head = head->next;
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
void AddNewItem(PItem* head, PItem* tail, int n, int a, float b)
{
	PItem temp, run;
	run = *head;
	int len = 0;
	int i=1;
	temp = (PItem)malloc(sizeof(struct Item));
	if (NULL == temp)
	{
		DeleteList(&head);//will free the linked list.
		Error_Msg("Allocation failed.");

	}
	temp->num = a;//geting data.
	temp->price = b;//geting data.
	if (NULL == *head)//if the list is empty.
	{
		*head = temp;
		*tail = temp;
		(*head)->next = NULL;
		(*tail)->next = NULL;
	}
	if (n == 1)//if we want to add to the head of the list.
	{
		temp->next = *head;
		*head = temp;
	}
	else
	{
		while (run) //while run !=NULL,count how many blocks in the linked list.
		{
			len++;
			run = run->next;
		}
		run = *head;
		if (n == len)//if we want to add to the end of the list.
		{
			(*tail)->next = temp;
			temp->next = NULL;
			*tail = temp;
		}
		else//if we want to add into the middle of the list.
		{
			while (i<n-1)
			{
				run = run->next;
				i++;
			}
			temp->next = run->next;
			run->next = temp;
		}
	}
}
void WriteListToFile(PItem head, FILE*in)
{
	while (head)//while head!NULL.
	{
		fprintf(in, "%d %.2f ", head->num, head->price);// will print the data into the pointer file in.
		head = head->next;
	}
}
