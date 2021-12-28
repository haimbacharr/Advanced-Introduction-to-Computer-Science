#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NAME 257
typedef struct node
{
	char code[11];
	char* name;
	char Dep[4];
	int marks[3];
	float avg;
	struct node* next;
}std;

void Error_Msg(char* str);//function to print error messege.
std* FromFileToList(std* head, FILE* in);//Function that get file pointer and pointer to std and make a linked list. and return the head of the list.
std* Delete_Stud(std* toDel, std* head);//Function that get pointer to std that we want to delete and pointer to a head of a linked list, and delete the todel* and make a new linked list.
void DeleteList(std* head);//Function that get the head of a linked list and delete all the list.
void PrintList(std* head);//Function that get the head of a linked list and print all the list.
std* FindMax(std* head);//Function that get the head of linked list and find the student with the higher avg,and return his block.

int main()
{
	int i;
	FILE* f;
	std* Head = NULL, * temp;
	if ((f = fopen("List.txt", "rt")) == NULL)
		Error_Msg("input error");
	Head = FromFileToList(Head, f);

	fprintf(stdout,"\nThe list is:\n");
	PrintList(Head);

	temp = FindMax(Head);
	fprintf(stdout,"\n\nthe student with max average:\n");
	fprintf(stdout,"%s %s %s ", temp->code, temp->name, temp->Dep);
	for (i = 0; i < 3; i++)
		fprintf(stdout," %d ", temp->marks[i]);

	fprintf(stdout,"\n\nThe list after change:");
	Head = Delete_Stud(FindMax(Head), Head);
	PrintList(Head);
	DeleteList(Head);
	fclose(f);//close to pointer to file.
	return 0;
}


std* Delete_Stud(std* toDel, std* head)
{
	if (head == NULL)//if the list is empty.
		return NULL;
	std* prev;
	prev = head;
	if (toDel == head)//if the block we want to delete its the head of the list.
	{
		head = head->next;
		free(toDel->name);
		free(toDel);
	}
	else//if the block that we want to delete is not the head of the list.
	{
		while (prev->next != toDel)
			prev = prev->next;
		prev->next = toDel->next;
		free(toDel->name);
		free(toDel);
	}
	return head;
}

std* FromFileToList(std* head, FILE* in)
{
	std* temp;
	char name[NAME];
	int i;
	temp = (std*)malloc(sizeof(std));
	if (NULL == temp)
	{
		Error_Msg("Allocation failed");
	}
	while (EOF != fscanf(in, "%s%s%s", temp->code, name, temp->Dep))
	{
		int sum = 0;
		temp->name = (char*)malloc((sizeof(char)* (strlen(name) + 1)));
		if (NULL == temp->name)
		{
			DeleteList(head);
			Error_Msg("Allocation failed");
		}
		strcpy(temp->name, name);
		for (i = 0; i < 3; i++) {//loop for getting the 3 mars of each student.
			fscanf(in, "%d", &temp->marks[i]);
			sum += temp->marks[i];
		}
		temp->avg = sum / 3.0;
	temp->next = head;
	head = temp;
	temp = (std*)malloc(sizeof(std));
	if (NULL == temp)//if allocation failed.
	{
		DeleteList(head);
		Error_Msg("Allocation failed");
	}
}
	free(temp);// will free the one spare block that was allocated.
	return head;//return the head of the new list.
}
void PrintList(std* head)
{
	int i;
	fprintf(stdout, "\n");
	while (head)//while head!=NULL
	{
		fprintf(stdout, "%s %s %s ", head->code, head->name, head->Dep);
		for (i = 0; i < 3; i++)
		{
			fprintf(stdout, "%d ", head->marks[i]);
		}
		fprintf(stdout, "\n");
		head = head->next;
	}
}

std* FindMax(std* head)
{
	std* temp,*max;
	temp = head;//temp will points to the head of the list.
	max = head;//max will point to the head of the list.
	while (temp)//while temp!=NULL.
	{
		if (temp->avg > max->avg)
			max = temp;
		temp = temp->next;
	}
	return max;//return pointer to the block with the max avg.
}

void DeleteList(std* head)//function that get head of the list and delete all the list.
{
	std* temp;
	while (head)
	{
		temp = head;
		head = head->next;
		free(temp->name);
		free(temp);
	}
}


void Error_Msg(char* str)//function that print error masseges.
{
	fprintf(stdout, "\n%s", str);
	exit(1);
}
