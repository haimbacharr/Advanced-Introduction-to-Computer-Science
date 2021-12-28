#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define N 4
typedef struct Complex//Declaring about new typde of data
{
	float rel, im;
}Complex;

float CRadius(Complex* a);//function that get a complex number and caclculate and return his radius.
void Error_Msg(char* str);//function that print an error messege to stderr.
void InputAndWriteToFile(FILE* f);//function that get file pointer and write data of complex numbers into a text file.
int CheckFile(FILE* f, float m);//function that get a pointer fo file and a float number and check how many complex number bigger than him, and return the number of how many of them is bigger.

int main()
{
	FILE* f;
	f = fopen("complex_numbers.txt", "wt");//open the file pointer for writing only.
	if (NULL == f)//if cannot create file will exit.
	{
		Error_Msg("Cannot create output file.\n");
	}
	InputAndWriteToFile(f);
	fclose(f);//will close the file pointer.
	f = fopen("complex_numbers.txt", "rt");//open the file pointer for reading only.
	if (NULL == f)  // if cannot read from the file, will exit.
	{
		Error_Msg("Cannot read from the output file.\n");
	}
	printf("\nThere are %d big numbers\n", CheckFile(f, 4));
	fclose(f);//will close the file pointer.
	getch();
	return 0;
}

void InputAndWriteToFile(f)
{
	Complex arr[N];
	int i;
	fprintf(stdout, "Enter N numbers\n");
	for (i = 0; i < N; i++)//get the data of the complex numbers into the array of structers.
	{
		fscanf(stdin, "%f %f", &arr[i].im, &arr[i].rel);
	}
	for (i = 0; i < N; i++)   fprintf(f, "%.1f %.1f %.1f\n", arr[i].im, arr[i].rel, CRadius(arr + i));// will print the data of the arr into the file.
}

float CRadius(Complex* a)
{
	float r;
	r = sqrt(pow(a->rel, 2) + pow(a->im, 2));
	return r;
}

int CheckFile(FILE* f, float m)
{
	int i = 0;
	float temp,junk;
	while (EOF != fscanf(f, "%f %f %f", &junk, &junk, &temp))
	{
		if (temp > m) i++;
	}
	return i;
}

void Error_Msg(char* str)
{
	fprintf(stderr, "\n%s", str);
	exit(1);
}

