#include "header3.h"
void Enqueue(PQue Q, int   new_elem)
{
	Item* temp;
	temp = (Item*)malloc(sizeof(Item));       //Allocating memory for the new block.
	if (temp == NULL)       //If the allocating failed, will remove all the queue, and will print a messege.
	{
		DeleteList(Q);
		Error_Msg("Allocation has been failed!");
	}
	temp->num = new_elem;
	temp->next = NULL;
	if (Q->size == 0) //If it is the first block in the list.
	{
		Q->head = temp;
		Q->size++;
	}
	else     //If it is not the first block in the list.
	{
		Q->tail->next = temp;
		Q->size++;
	}
	Q->tail = temp;       //tail will points to the last block in the Queue.
	fprintf(stdout,"%d was inserted\n", Q->tail->num);
	if (Q->size == N)
		fprintf(stdout,"The queue is full!!!");
}
int Dequeue(PQue Q, int* del_value)//Function that deletes the first block in the Queue and update the deleted num into del_value.
{
	Item* run;
	if (Q->size != 0) {
		run = Q->head;
		*del_value = Q->head->num;
		Q->head = Q->head->next;
		Q->size--;
		free(run);
		return 1;
	}
	return 0;
}
void DeleteList(PQue Q)//Function to delete the queue.
{
	Item* temp;
	while (Q->head)//Loop will continue untill the Queue will be empty..
	{
		temp = Q->head;
		Q->head = Q->head->next;
		free(temp);// Free the allocated memory.
	}
	Q->size = 0;
	Q->head = NULL;
	Q->tail = NULL;
}
void Error_Msg(char* str)//Function to print a messege.
{
	fprintf(stderr,"\n%s", str);
	exit(1);
}
