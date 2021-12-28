#include "header1.h"
typedef struct node
{
	void* data;                       /* Store the keystroke by the user */
	struct node* next;                /* Pointer to the next node */

} STACKNODE;

void* top(PSTACKNODE stack)
{
	return stack->data;
}

void push(void* key, PSTACKNODE* stack)
{
	PSTACKNODE newnode;
	newnode = (PSTACKNODE)malloc(sizeof(STACKNODE));
	if (newnode == NULL)
	{
		printf("Error allocating memory!");
		exit(1);
	}
	newnode->data = key;
	newnode->next = (*stack);
	(*stack) = newnode;
}

void pop(PSTACKNODE* stack, void(*free_data)(void*))
{
	PSTACKNODE oldnode;
	oldnode = (*stack);
	(*stack) = (*stack)->next;
	free_data(oldnode->data); //Free the top data.
	free(oldnode);	//Free the top.
}

int isempty(PSTACKNODE stack)
{
	return (stack == NULL);
}
