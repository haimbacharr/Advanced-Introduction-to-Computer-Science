#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define MAX 256
#define CODE 10
typedef struct Book {

	char code[CODE + 1];
	char* name;
}Book;

typedef struct Library {

	char name[MAX + 1];
	Book* books;
	int num_books;
}Library;

void Get_Lost(char* str);
void input_book(Book* B, FILE* in);
void input_library(Library* L, FILE* in);
void output_book(Book* B, FILE* out);
void output_library(Library* L, FILE* out);

int main()
{
	FILE* in, * out;
	Library Libr;
	int i;

	in = fopen("input.txt", "rt");
	if (NULL == in) Get_Lost("Cannot read the file.\n");
	input_library(&Libr, in);
	fclose(in);
	out = fopen("output.txt", "wt");
	output_library(&Libr, out);
	fclose(out);
	for (i = 0; i < Libr.num_books; i++)//realese the memory that  was alocate for the books names.
		free(Libr.books[i].name);
	free(Libr.books);//realese the memory that was alocate for the library.
		getch();
		return 0;
}

void input_library(Library* L, FILE* in)
{
	int i;
	Book *a;
	fscanf(in, "%s%d", L->name,&L->num_books);//get the library name and number of books from a text.
	L->books = (Book*)malloc(sizeof(Book) * L->num_books);//alocate memory for books.
	if (NULL == L->books) //if allocation failed.
	{
		Get_Lost("Not enough memory.");
	}
	for (i = 0; i < L->num_books; i++)
		input_book(&L->books[i], in);

}
void input_book(Book* B, FILE* in)
{
	char name[MAX+1];
	fscanf(in,"%s%s", B->code, name);//get the code for each books and his name.
	B->name = (char*)malloc(sizeof(char) * (strlen(name) + 1));
	if (NULL == B->name)	Get_Lost("Allocation failed.");
	strcpy(B->name, name);
}

void output_library(Library* L, FILE* out)// will print the library name to a new text. and summon output_book function.
{
	int i;
	fprintf(out, "%s\n", L->name);
	for (i = 0; i < L->num_books; i++)
	{
		output_book(&L->books[i],out);
	}
}

void output_book(Book* B, FILE* out)// will print the code and book name in each row with a tab between them.
{
	fprintf(out, "%s\t%s\n", B->code, B->name);
}

void Get_Lost(char* str)
{
	printf("\n%s", str);
	exit(1);
}

