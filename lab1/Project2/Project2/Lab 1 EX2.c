#include<stdio.h>
#include<stdlib.h>
void set_2d(float** a, int m, int n);
void print_2d(float** a, int m, int n);
void freeAll(float** a, int m);
int main()
{
	int m, n, i;
	float** a;
	printf("\nenter m and n, for m*n array: \n");
	scanf("%d %d", &m, &n);
	a = (float **)malloc(m * sizeof(int));//memory allocation for the rows of a
	for (i = 0;i < m;i++)//memory allocation for the cols of a
	{
		a[i] = (float*)malloc(n * sizeof(int));
	}
	if (NULL == a)//checking if the memory allocation succed
	{
		printf("alloaction faild!\n");
	}
	else
	{
		set_2d(a, m, n);
		print_2d(a, m, n);
	}
	getch();
	return 0;
}
void set_2d(float **a, int m, int n) 
{
	int i, j, k = 1;
	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++)
			a[i][j] = k++;
}

void print_2d(float **a, int m, int n) //print the matrix.
{
	int i, j;
	for (i = 0;i < m;i++)
	{
		for (j = 0;j < n;j++)
		{
			printf("%6.1f\t",a[i][j]);
		}
		printf("\n");
	}
}
void freeAll(float** a, int m)//function for free the matrix.
{
	int i = 0;
	for (i = 0; i < m; i++)
		free(a[i]);
	free(a);
}

