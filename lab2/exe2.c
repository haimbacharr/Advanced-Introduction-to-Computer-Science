#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define NAME 50

typedef struct stud
{
	char* name;
	int marks[4];
	float avg;
}student;

student* Create_Class(int);//get size,Creating the array of students. and return the a pointer to the array.
void Avg_Mark(student*);//Calculate the avg of the marks of each student in the array.
void Print_One(student*);//Function for printing the name of student and his average of marks.


int main()
{
	int size, i;
	student* arr;
	printf("\nEnter the number of students:");
	scanf("%d", &size);
	arr = Create_Class(size);//arr will be the array of structures.
	printf("\n");
	for (i = 0; i < size; i++)//check if the avg is above 85,if so will summon the Print_One function.
	{
		if (arr[i].avg > 85)
		{
			Print_One(arr + i);
		}
	}
	for (i = 0; i < size; i++)//free the name in each block of the array of structers.
	{
		free(arr[i].name);
	}
	free(arr);//free the array.
	getch();
	return 0;
}

student* Create_Class(int size)
{
	student* a;
	int i, j;
	char tempname[NAME];
	a = (student*)malloc(size * sizeof(student));//allocate memory to the array of structers.
	if (NULL == a)//if allocated failed.
	{
		printf("Allocation failed./n");
		return 1;
	}
	for (i = 0; i < size; i++)//loop for insert the data into each block of student in the array.
	{
		printf("\nEnter your name:");
		scanf("%s", tempname);
		a[i].name = (char*)malloc((strlen(tempname) + 1) * sizeof(char));//Allocate memory to the name.
		if (NULL == a[i].name)//if the name allocated failed, will free the previus names that were allocated and after that free the array it self.
		{
			printf("Allocation Failed.\n");
			for (j = 0; j < i; j++)
				free(a[j].name);//free the names that were allocated before.
			free(a);//free the array of structers.
			exit(1);
		}
		strcpy(a[i].name, tempname);//a[i].name=tempname.
		printf("\nEnter your marks:");//getting the 4 marks of the a[i] student.
		for (j = 0; j < 4; j++)//getting the marks into each student.
		{
			scanf("%d", &a[i].marks[j]);
		}
		Avg_Mark(&a[i]);
	}
	return a;
}


void Avg_Mark(student* s)
{
	int i;
	int sum = 0;
	for (i = 0; i < 4; i++)//sum all the marks.
	{
		sum += s->marks[i];
	}
	s->avg = (float)(sum / 4.0);
}


void Print_One(student* s)
{
	printf("The average of %s is %.1f\n", s->name, s->avg);
}