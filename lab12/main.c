#include "ex.h"

void free_char(char* a)
{
	free((char*)a);
}
BOOL cmp_char(void* a, void* b)
{
	if (*(char*)a == *(char*)b) return TRUE;//if a and b equal.
	return FALSE;
}
void prnt_char(void* a)
{
	fprintf(stdout, "%c ", *(char*)a);
}

int main()
{
	char ch, * temp;
	int n, i;
	BOOL res;
	PNode head = NULL, tail = NULL;

	fprintf(stdout,"Enter number of characters ");
	fscanf(stdin,"%d", &n);
	fprintf(stdout,"\nEnter %d characters,separated by enter:", n);
	for (i = 0; i < n; i++)
	{
		temp = (char*)malloc(sizeof(char));
		if (NULL == temp)
		{
			fprintf(stdout,"\nCan't allocate data memory");
			freeAll(&head, free_char);
			return 1;
		}
		scanf(" %c", temp);
		res = insertEntry(&head, &tail, temp, cmp_char);
		if (FALSE == res)  /* Can't allocate node memory or data is allready exists*/
		{
			fprintf(stdout,"\nCan't allocate node memory or data is allready exists");
			freeAll(&head, free_char);
			return 1;
		}
	}
	printAll(head, prnt_char);

	fprintf(stdout,"\nEnter an element for deleting: ");
	scanf(" %c", &ch);
	res = deleteNode(&head, &tail, &ch, cmp_char, free_char);
	if (FALSE == res)
		fprintf(stdout,"%c don't exists in list\n", ch);

	printAll(head, prnt_char);

	freeAll(&head, free_char);
	fprintf(stdout,"\nYour list was destroyed\n");

	return 0;
}

