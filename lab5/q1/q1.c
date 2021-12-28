#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//BaruchComp078045MichalMech090060PinhasElek100090YaelitComp080100DorotiMech100100
#define NAME 7
#define DEP 5
#define MARKS 4

typedef struct student
{
	char name[NAME];
	char course[DEP];
	char mark1[MARKS], mark2[MARKS];
}stud;

void Error_Msg(char* str);//geting string,and print error message.
void GetData(FILE* in, FILE* out);//Function that get 2 file pointers,getting data from students.txt into a structure,and writing to a new text(studentsnew.txt only the students that learn "Comp" and calculate their avg.
int main()
{
	FILE* in, * out;
	if (!(in = fopen("Students.txt", "r")))Error_Msg("The input file is wrong");
	if (!(out = fopen("StudentsNew.txt", "w")))Error_Msg("The output file is wrong");
	GetData(in, out);
	fclose(in);//close the in file pointer.
	fclose(out);//close the out file pointer.
	return 0;
}


void GetData(FILE* in, FILE* out)
{
	stud a;
	int sum = 0;
	while (NULL != fgets(a.name, NAME, in))//loop for geting the all data from the students text.
	{
		fgets(a.course, DEP, in);
		if (strcmp(a.course, "Comp") == 0)
		{
			sum = 0;
			fgets(a.mark1, MARKS, in);
			fgets(a.mark2, MARKS, in);
			sum += atoi(a.mark2) + atoi(a.mark1);//mark1+mark2=sum
			fprintf(out, "%s %.2f\n", a.name, sum / 2.0);//printing the data to StudentsNew.txt
		}
		else fseek(in,( MARKS-1) * 2, 1);//if its not a Comp student,will jump to the next student.
	}
}

void Error_Msg(char* str)
{
	fprintf(stderr,"\n%s", str);
	exit(1);
}




