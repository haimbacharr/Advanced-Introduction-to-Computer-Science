#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef struct
{
	char name[20];
	int grades[3];
}student;

void Error_Msg(char*);//function that print error messege.
int InputData(student**, FILE*);//function that get data from a file and return the size of the array of structers.
void OutputData(int, student*, FILE*);//function to print data.
int High(student* a);//function to find the highest grade.

int main()
{
	FILE* fp;
	student* arr;
	int size, i;
	if (!(fp = fopen("Students.txt", "r")))
		Error_Msg("The input file is wrong");//if will failed to open the file.
	size = InputData(&arr, fp);//size=the size of the array.
	fclose(fp);//close the fp pointer to file.
	if (!(fp = fopen("Students.txt", "w")))
	{
		Error_Msg("The output file is wrong");//if will failed to open the file.
		free(arr);
	}
	OutputData(size, arr, fp);
	fclose(fp);//close the fp pointer to file.
	free(arr);//will free the array that was allocated.
	getch();
	return 0;
}


int InputData(student** p_array, FILE* fp)
{
	student* arr;
	int i = 1, j;
	arr = (student*)malloc(sizeof(student));
	if (NULL == arr) Error_Msg("Allocated failed.");

	while (fscanf(fp, "%s %d %d %d", arr[i - 1].name, &arr[i - 1].grades[0], &arr[i - 1].grades[1], &arr[i - 1].grades[2]) != EOF)//while not arrive to the end of file continue to receive data from the text file.
	{
		arr = realloc(arr, sizeof(student) * (i + 1));//will reallocte the original arr with more memory.
		if (NULL == arr)
		{
			free(arr);// will free the aray that was allocated.
			Error_Msg("allocated failed.");
		}
		i++;
	}
	arr = (student*)realloc(arr, sizeof(student) * (i-1));//the array will be one less block.
	*p_array = arr;//p_array will point to the new arr we created.
	return i - 1;    /*return the number of students*/
}

void OutputData(int arr_size, student* arr, FILE* fp)
{
	int i;
	for (i = 0; i < arr_size; i++)
	{
		fprintf(fp, "%s %d\n", arr[i].name, High(arr + i));
	}

}
int High(student* a)
{
	int i, high = 0;
	for (i = 0; i < 3; i++)//will update the new high grade from the other grades.
	{
		if (a->grades[i] >= high)
			high = a->grades[i];
	}
	return high;
}

void Error_Msg(char* msg)
{
	fprintf(stderr, "\n%s", msg);//will print error messege into an error window.
	exit(1);
}

