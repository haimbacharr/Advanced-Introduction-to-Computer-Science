#include "ex.h"

typedef struct  ListNode
{
	void* data;
	struct  ListNode* next;
} ListNode,*PNode;


BOOL insertEntry(PNode* head, PNode* tail, void* data, compare_func func)
{
	PNode temp;
	temp = *head;
	while (temp)
	{
		if (func(temp->data, data)) //If the "data" already exist in the linked list.
			return FALSE;
		temp = temp->next;
	}
	if ((temp = (PNode)malloc(sizeof(ListNode))) == NULL) //Allocate memory for the new node.
	{
		return FALSE;
	}
	if (NULL== *head)//If it is the first node in the list.
		*head = temp;
	else              //If it is not the first node in the list.
		(*tail)->next = temp;
	temp->next = NULL;
	*tail = temp;
	temp->data = data;
	return TRUE;
}

void freeAll(PNode* head, free_func func)
{
	PNode temp;
	while (NULL != *head)
	{
		temp = *head;
		(*head) = (*head)->next;
		func(temp->data); //Free the "data", summons specific function.
		free(temp);	//Free the node.
	}
}
BOOL deleteNode(PNode* head, PNode* tail, void* todel, compare_func func1, free_func func2)
{
	PNode temp = *head, tempToDelete = *head;
	while (temp != NULL)
	{
		if (func1(temp->data, todel))
		{
			if (temp == *head)			//If the head of the linked list is the node we want to delete.
				*head = (*head)->next;	//head will point to the next node.
			else
			{
				tempToDelete->next = temp->next;
				tempToDelete = temp; //tempToDelete = temp, the node we want to delete.
			}
			func2(tempToDelete->data); //Free data.
			free(tempToDelete);	//Free the node.
			return TRUE;
		}
		tempToDelete = temp; //"Saving" the prev node
		temp = temp->next;
	}
	return FALSE;
}



void printAll(PNode head, print_func func)
{
	PNode temp = head;
	while (temp != NULL)
	{
		func(temp->data); //Function to print.
		temp = temp->next;
	}
}