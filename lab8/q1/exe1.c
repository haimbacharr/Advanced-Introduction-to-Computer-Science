#include "head.h"

void main()
{
	int i, flag, del_value, arr[NUM] = { 1,4,3,2 };
	Stack s;
	s.head = NULL;
	s.size = 0;
	for (i = 0; i < NUM; i++)
	{
		Push(&s, arr[i]);
	}
	while (s.size)
	{
		flag = Pop(&s, &del_value);
		if (flag)
			fprintf(stdout, "\n%d was deleted", del_value);
	}
	fprintf(stdout, "\nThe stack is empty.");

}