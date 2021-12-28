#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define KORS 4
#define ID 5
#define NAME 17
typedef struct Student {
	char Kors[KORS];
	char name[NAME];
	char id[ID];
}stud;

void Get_Lost(char*);
void Find(FILE* f, char* course);

int main()
{
	char course[4];
	FILE* file;
	file = fopen("Stud.txt", "rt");
	if (file == NULL)
		Get_Lost("Cannot open file");
	printf("\nEnter the name of course,up to 3 letters");
	scanf("%s", course);
	Find(file, course);
	fclose(file);//close the File pointer.
	getch();
	return 0;
}
void Find(FILE* f, char* course)//Function that get pointer to file,and a string(name of course),and if the student learn the same course as the course that the function get
//will print him to a new text file with all of his details,each studnent in one row.first will be his binary id code,second his Full name and Last HIS CODE of course.
//The head of the text name will be the "course".txt
{
	FILE *out;
	stud s;
	int a;
	char tempkors[KORS+4],bin[15];

	strcpy(tempkors, course);//tempkors=course.
	strcat(tempkors, ".txt");//"course.txt"
	out = fopen(tempkors, "wt");//open file for writing.
	if (NULL == out)//if cannot open the output file.
	{
		Get_Lost("Cannot open output file.\n");
	}
	
	while (!(feof(f)))//while not EOF continue.
	{
		fgets(s.Kors, KORS, f);//getting the kors name.
		fgets(s.id, ID, f);//getting the id.
		fgets(s.name, NAME, f);//geting the name;
		if (strcmp(s.Kors, course) == 0) //if equal.
		{
			a = atoi(s.id);
			_itoa(a, bin, 2);
			fprintf(out, "%s, %s, %s\n", bin, s.name, s.Kors);
		}
	}
	fclose(out);//Close the output file.
}

void Get_Lost(char* s)//function that get string and print it to the console.
{
	puts(s);
	exit(1);
}
