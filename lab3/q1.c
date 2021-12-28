#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef struct Person//declaring about structure.
{
	char ID[10];
	char F_name[11];
	char L_name[16];
	int Age;
	char Addr[51];
}Person;

void Error_Msg(char*);//function for printing errors messeges.

int main()
{
	Person temp;//variable from person type.
	FILE* in, * out;//pointer to files.

	in = fopen("the_first.txt", "rt");
	if (NULL == in)//if cannot read from the *file in will exit.
	{
		Error_Msg("Cannot open the file.");
	}
	fscanf(in,"%s %s %s %d %s", temp.ID, temp.F_name, temp.L_name, &temp.Age, temp.Addr);//getting the data to the person.
	out = fopen("The_second.txt", "wt");
	if (NULL == out)//if cannot create a *file out will exit.
	{
		Error_Msg("Cannot create output file.");
	}
	fprintf(out,"ID:%s\nFull name:%s %s\nAge:%d\nAddress:%s\n",temp.ID,temp.F_name,temp.L_name,temp.Age,temp.Addr );//will print te data into output file
	fclose(in);//will close the in file pointer.
	fclose(out);//will close the out file pointer.
	getch();
	return 0;
}

void Error_Msg(char* msg)
{
	printf("\n%s", msg);
	exit(1);
}
