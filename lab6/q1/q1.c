#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 5
#define NAME 11
typedef struct Item {

	int code;
	char name[NAME];
	struct Item* next;
}Item;

free_func(Item* head);//Function that delete the list from the head.


int main()
{
	int i;
	Item* Head = NULL, * temp;
	for (i = 1; i <= N; i++) //Loop that create the list.
	{
		temp = (Item*)malloc(sizeof(Item));
		if (NULL == temp)//if mallo failed, will realase all the list.
		{
			fprintf(stdout, "failed to allocate memory.\n");
			free_func(Head);
			exit(1);
		}
		fprintf(stdout,"Enter a new code and name: ");
		fscanf(stdin,"%d%s", &temp->code, temp->name);
		temp->next = Head;
		Head = temp;
	}
	temp = Head;//temp will point to the head of the list.

	fprintf(stdout,"\n\nThe List is:  ");
	while (temp)//Loop to print al the list from the right to the left.
	{
		fprintf(stdout,"%d %s --> ",temp->code,temp->name );
		temp = temp->next;
	}

	while (NULL!=Head) //Loop to free all the list.
	{
		temp = Head;
		Head = Head->next;
		free(temp);
	}
	return 0;
}

free_func(Item* head)//Function that get the head of the list, and free all the list.
{
	Item  *temp;
	while (NULL!=head)
	{
		temp = head;
		head = head->next;
		free(temp);
	}
}



