#include "Stack_Header_Array.h"

int main()
{
	Stack st;
	int del_value, flag;
	InitStack(&st, 4);
	Push(&st, 3);
	Push(&st, 5);
	Push(&st, 1);
	Push(&st, 10);
	flag = Pop(&st, &del_value);

	if (flag)
		fprintf(stdout,"\n%d was deleted", del_value);
	Push(&st, 8);
	flag = Pop(&st, &del_value);
	if (flag)
		fprintf(stdout,"\n%d was deleted", del_value);
	flag = Pop(&st, &del_value);
	if (flag)
		fprintf(stdout, "\n%d was deleted", del_value);
	Push(&st, 7);
	Push(&st, 4);
	Push(&st, 100);
	flag = Pop(&st, &del_value);
	if (flag)
		fprintf(stdout, "\n%d was deleted", del_value);
	while (st.count)
	{
		flag = Pop(&st, &del_value);
		if (flag)
			fprintf(stdout, "\n%d was deleted", del_value);
	}
	fprintf(stdout,"\n");
	flag = Pop(&st, &del_value);
	if (flag)
		fprintf(stdout, "\n%d was deleted", del_value);

	return 0;
}