#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define  N  5
typedef enum { FALSE, TRUE } BOOL;

void Insert(BOOL(*f)(void*, void*), void* Element, void** Parray);
BOOL Int_Comp(void* FirstElement, void* SecondElement);
BOOL IsFull();


int CurrentCount = 0;  /*global variable - only for the first ADT lab!Please,don't use!*/


int main()
{
	int Array[N], Value, i;
	void* PArray[N];                        /*pointers array*/

	printf("Enter numbers, -999 to stop: ");
	scanf("%d", &Value);

	while (Value != -999)
	{
		if (!IsFull())
		{
			Array[CurrentCount] = Value;
			Insert(Int_Comp, &Array[CurrentCount], PArray);  /*call the general function*/
			scanf("%d", &Value);
		}
		else
		{
			fprintf(stdout,"The array is full");
			break;
		}
	}
	fprintf(stdout,"\n Your sorted array is:\n");             /*print the array in sorted order*/
	for (i = 0; i < CurrentCount; i++)
		fprintf(stdout," %d ", *(int*)PArray[i]);

	return 0;
}

BOOL IsFull()
{
	if (CurrentCount == N)
		return TRUE;
	return FALSE;
}

BOOL Int_Comp(void* FirstElement, void* SecondElement)
{
	if (*(int*)FirstElement > * (int*)SecondElement)
		return TRUE;
	return FALSE;
}

void Insert(BOOL(*comp)(void*, void*), void* Element, void** Parray)
/*General Function that get pointer to function ,element (void*)and aray and sorted the array.*/
{
	int i = 0, j = CurrentCount;
	
	while ((i < CurrentCount) && (comp(Element, Parray[i]) != FALSE))
		i++;
	while (j > i)
	{
		Parray[j] = Parray[j - 1]; //shifting the array.
		j--;
	}
	Parray[i] = Element;
	CurrentCount++;
}
