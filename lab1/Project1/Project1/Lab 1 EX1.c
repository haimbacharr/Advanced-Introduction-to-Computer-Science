#include<stdio.h>
#include<stdlib.h>
#define SIZE 10
int main()
{
	int i, Arr[SIZE] = { 3,5,10,1,2,7,6,9,0,8 };
	int **parr;
	parr = (int **)malloc(sizeof(int*)*SIZE);//memory allocation for parr
	if (NULL==parr)//check if the memory allocation succeded
		{
			printf("allocation faild!\n");
			free(parr);
		}
	else
	{
		for (i = 0;i < SIZE;i++)//copy every address of arr to parr
		{
			parr[i] = &Arr[i];
		}
		printf("my array is:");
		for (i = SIZE - 1;i >= 0;i--)//print the array from the end.
		{
			printf("%d ", *parr[i]);
		}
		getch();
		free(parr);
	}
	return 0;
}