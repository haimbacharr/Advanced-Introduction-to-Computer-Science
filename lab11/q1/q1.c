#include "header1.h"
void free_char(void* elem)
{
	free(elem);
}

int main()
{
	PSTACKNODE stack = NULL;
	char* key;
	puts("Enter characters, separated by enter. Press enter to stop\n");
	do
	{
		key = (char*)malloc(sizeof(char));
		if (key == NULL)
		{
			printf("Error allocating memory!");
			exit(1);
		}
		*key = getchar();
		_flushall();
		push(key, &stack);
	} while (*key != '\n');

	puts("Here are the characters in reverse order:\n");

	while (!isempty(stack))
	{
		printf(" %c ", *(char*)top(stack));
		pop(&stack, free_char);
	}
	getch();
	return 0;
}
