#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define N 3

typedef struct deparment
{
	char code[10];
	char *name;
	int product;
	int sales;

}deparment;
void Get_erorr(char* E);
void input_department(deparment **arr);
void best_dep(deparment arr[], deparment** pointers[]);

int main()
{
	int i;
	deparment arr[N] ,* pointers[N];
	input_department(&arr);
	for (i = 0; i < N; i++)//loop for the pointers get the address of the structres 
	{
		pointers[i] = &arr[i];
	}
	best_dep(arr, pointers);
	printf("the best selling deparment is %s - %s \nand the worst deparment is %s - %s", pointers[0]->code, pointers[0]->name, pointers[1]->code, pointers[1]->name);
	
	for (i = 0; i < N; i++)//freeing every memory allocation of all names one by one
	{
		free(arr[i].name);
	}
	return 0;
}
void input_department(deparment *arr)/*a function that recived the information of every deparment*/
{
	int i;
	char depname[20];//tempoprary string for the name of the deparment
	for (i = 0; i < N; i++)
	{
		printf("please enter the deparment %d code(max 10 charcters):", i + 1);
		scanf("%s", arr[i].code);
		printf("\nenter the name of the deparment:");
		scanf("%s", depname);
		if (strlen(depname) > 20)
		{
			Get_erorr("\ntoo much charcters!");
		}
		arr[i].name = (char*)malloc((strlen(depname)+1) * sizeof(char));//memory allocation for the string of the deparment name
		if (arr[i].name == NULL)
		{
			Get_erorr("\nMemory allocation failed");
		}
		strcpy(arr[i].name,depname );//copy the string from the temp string to the string of the name.
		printf("\nenter total items in the deparment:");
		scanf("%d", &arr[i].product);
		if (arr[i].product == 0)
		{
			Get_erorr("\nnumber of items must be more then zero!");
		}
		printf("\nenter the sales of the item's deparment for today:");
		scanf("%d", &arr[i].sales);
		if (arr[i].sales > arr[i].product)
		{
			Get_erorr("the sales cant be more then the number of product");
			while (arr[i].sales < arr[i].product)
			{
				printf("\nenter the sales of the item's deparment for today:");
				scanf("%d", &arr[i].sales);
			}
		}
	}
}
void best_dep(deparment arr[], deparment** pointers)/*a function to find the best selling dep and the worst one*/
{
	int i,j, imax = 0, imin = 0;
	float temp;
	temp = (float)arr[0].sales / arr[0].product;//temp is the first deparment
	for (i = 1; i < N; i++)//loop to find the best deparment
	{
		if(!(temp> (float)arr[i].sales / arr[i].product))
		{
			temp = (float)arr[i].sales / arr[i].product;
			imax = i;
		}
	}
	temp = (float)arr[0].sales / arr[0].product;
	for (i = 1; i < N; i++)//loop to find the worst deparment
	{
		if (!(temp < (float)arr[i].sales / arr[i].product))
		{
			temp = (float)arr[i].sales / arr[i].product;
			imin = i;
		}
	}
	pointers[0] = &arr[imax];//pointer number 1 get the address of the best deparment
	pointers[1] = &arr[imin];//pointer number 2 get the address of the worst deparment
	for (i = 2, j = 0; j < N; j++)//organize the pointers
	{
		if ((j != imax) && (j != imin))
			pointers[i] = &arr[j];
		else i++;
	}
}
void Get_erorr(char* E)/*a function to error message*/
{
	puts(E);
	exit(1);
}