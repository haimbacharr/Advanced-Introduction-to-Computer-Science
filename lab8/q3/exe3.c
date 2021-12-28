#include "header3.h"

void main()
{
	int Arr[N] = { 1,2,3,4,5 };
	int i, flag;
	int del_value;
	Queue start;
	start.head = NULL;
	start.size = 0;
	start.tail = NULL;

	for (i = 0; i < N; i++)           //Geting numbers into the Queue.
	{
		Enqueue(&start, Arr[i]);
	}
	while (start.size)         //Realsing the Queue in FIFO way.
	{
		flag = Dequeue(&start, &del_value);
		if (flag)
			fprintf(stdout,"\n%d was deleted", del_value);
	}
	fprintf(stdout,"\nThe Queue is empty.");
}
