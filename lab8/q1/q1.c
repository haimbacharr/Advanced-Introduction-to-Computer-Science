#include "head.h"

void Push(PStack s, int   new_elem)
{
	int flag = 1, i = 1;
	Item* temp, * run;
	if (s->size == NUM)
	{
		fprintf(stdout, "The stack is full!!\n");
		flag = 0;
	}
	if (flag) {
		run = s->head;
		temp = (Item*)malloc(sizeof(struct Item));
		if (temp == NULL)//If allocation failed.
		{
			DeleteList(s);
			Error_Msg("Memmory!");
		}
		temp->num = new_elem;
		temp->next = NULL;
		if (NULL == s->head)//if its the first time to insert a block.
		{
			s->head = temp;
			run = s->head;
			s->size++;
			fprintf(stdout, "%d was inserted\n", s->head->num);
		}
		else //if its not the first block in the list.
		{
			while (i < s->size)   //Makes the run pointer to point at the one block before the last one in the list.
			{
				i++;
				run = run->next;
			}
			run->next = temp;
			run = temp;
			s->size++;
			fprintf(stdout, "%d was inserted\n", run->num);
			
			if (s->size == NUM) fprintf(stdout, "The stack is full!!\n");
		}
	}
}

void DeleteList(PStack s)
{
	Item* temp;
	while (s->head)
	{
		temp = s->head;
		s->head = s->head->next;
		free(temp);
	}
	s->size = 0;
}
int Pop(PStack s, int* del_value)
{
	Item* run;
	int i = 1;
	run = s->head;
	while (i < s->size - 1)
	{
		run = run->next;
		i++;
	}
	if (NULL!=run->next) {
		*del_value = run->next->num;
		free(run->next); //free the last block in the list.
		run->next = NULL;
		s->size--;
		return 1;
	}
	else        //if its the last block in the list.
	{
		*del_value = run->num;
		free(run);
		s->size--;
		s = NULL;
		return 1;
	}
	return 0;
}
void Error_Msg(char* str)
{
	fprintf(stderr, "%s\n",str);
	exit(1);
}