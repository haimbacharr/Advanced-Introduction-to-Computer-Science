#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef struct Item
{
	int num;
	struct Item* next;
}Item;

typedef struct List
{
	int count;//counting how many block there are in the list.
	struct Item *head;//will point to the beginning of the list.
	struct Item* tail;//will point to the end of the list.

}List;

void Error_Msg(char*);
void AddAsFirst(Item*, List*);//create new list while adding the new blockes from the head.
void AddAsLast(Item*, List*);//create new list while adding the new blockes from the tail.
void MoveToAnotherList(List*, List*, List*);//Moves blockes from the main list to two others two lists.
void CreateList(List*, FILE*);//function that create new linked list from a file.
void PrintItem(Item*);//function that print one Item.
void PrintList(List*, char*);//Function that get a pointer to linked list, and print the linked list.
void DeleteList(List*);//Function that delete all the list.

int main()
{
	List L, Posit, Negat;
	FILE* in = fopen("ThreeLists.txt", "rt");
	if (in == NULL)
		Error_Msg("input file is wrong");
	L.head = NULL;
	L.tail = NULL;
	L.count = 0;

	Posit.head = NULL;
	Posit.tail = NULL;
	Posit.count = 0;

	Negat.head = NULL;
	Negat.tail = NULL;
	Negat.count = 0;

	CreateList(&L, in);
	PrintList(&L, "\nMy List:\n");
	MoveToAnotherList(&L, &Posit, &Negat);
	PrintList(&Posit, "\n\nThe Positive List:\n");
	PrintList(&Negat, "\n\nThe Negative List:\n\n");

	fclose(in);//close the file pointer.
	DeleteList(&Posit);
	DeleteList(&Negat);
	return 0;
}

void Error_Msg(char* msg)
{
	printf("\n%s", msg);
	exit(1);
}

void CreateList(List* L, FILE* f)
{
	int value;
	Item* temp;
	while (fscanf(f, "%d", &value) == 1)
	{
		temp = (Item*)malloc(sizeof(struct Item));//allocate memory for new block.
		if (temp == NULL)//if allocation failed.
		{
			DeleteList(L);//will free the memory that was allocated.
			Error_Msg("Memmory!");
		}

		temp->num = value;
		temp->next = NULL;
		if (L->head == NULL)
			L->head = temp;
		else
			L->tail->next = temp;
		L->tail = temp;
		L->count++;
	}
}


void PrintItem(Item* node)
{
	printf("%d--> ", node->num);
}


void PrintList(List* L, char* title)
{
	Item* temp = L->head;
	printf("%s", title);
	while (temp)
	{
		PrintItem(temp);
		temp = temp->next;
	}
	printf("\nThere are %d items in the list", L->count);
}

void AddAsFirst(Item*ptr, List*L)
{
	if (NULL==L->head)//if the list is empty.
	{
		L->head = ptr;
		L->tail = ptr;
	}
	else 
	{
		ptr->next = L->head;
		L->head = ptr;
	}
	L->tail->next = NULL;
	L->count++;
}
void AddAsLast(Item *ptr, List *L)
{
	if (NULL == L->head)//if the list is empty.
	{
		L->head = ptr;
	}
	else {
		L->tail->next = ptr;
	}
	L->tail= ptr;
	L->tail->next = NULL;
	L->count++;//COUNT++;

}
void DeleteList(List *l)
{
	Item* temp;
	
	while (l->head!=NULL) {
		temp = l->head;
		l->head = l->head->next;
		free(temp);
		l->count--;
	}
	l->head = NULL;
	l->tail = NULL;
}
void MoveToAnotherList(List*L, List*Posit, List*Negat)
{
	Item* temp;
	while (NULL != L->head)
	{
			if (L->head->num >= 0)//if not empty and the organ is positive.
			{
				temp = L->head->next;//for not losing the whole  L list.
				AddAsLast(L->head, Posit);
				L->head = temp;
			}
			else //if the organ is negative.
			{
				temp = L->head->next;//for not losing the whole L list.
				AddAsFirst(L->head, Negat);
				L->head = temp;
			}
			L->count--;
	}
	L->head = NULL;
	L->tail = NULL;
}
