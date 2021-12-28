#include "Stack_Header_Array.h"

void InitStack(PStack s, int size)   //initialization of a new stack with capacity of size elements
{
	s->count = 0;
	s->size = size;
	s->top = 0;
	s->Array = NULL;
	s->Array = (int*)malloc(sizeof(int) * size); //Allocate size to the array.
	if (NULL == s->Array) {
		Error_Message("Allocation for the array has been failed!.");
		exit(1);
	}
}

void Push(PStack s, int   new_elem)  //add a new member to array of the stack 
{
	if (s->count != s->size) {
		s->Array[s->count] = new_elem;
		s->count++;
		s->top = s->count;
	}
	else
		fprintf(stdout,"\nThe Stack is full.");
}

int Pop(PStack s, int* del_value)   //delete member from the array of the stack and  return the deleted value  using  int * del_value.
{
	if (s->count != 0)
	{
		*del_value = s->Array[s->count - 1];
		s->count--;
		s->top = s->count;
		if (s->count == s->size - 1);
		fprintf(stdout,"\n");
		return 1;
	}
	else
		fprintf(stdout,"\nThe Stack is empty");
	return 0;

}

void Error_Message(char* str)
{
	fprintf(stderr, "%s\n", str);
}
