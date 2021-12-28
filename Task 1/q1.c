#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define NAME 100
#define GRADES 6
typedef struct student //declaring of a new type.
{
	char* name;
	long id;
	int grade;
	char flag;
	char tasks[GRADES];
	char final_grade;
}stud;

typedef struct university //declaring of a new type.
{
	stud* arr;
	int size;
}university;

void Error_Msg(char* str);//Printing error messege and close the program.
void Build_Uni(university** uni, FILE* in);//Geting pointer from university and fill it with data from text file,get FILE pointer.
void PrintUniversity(FILE* out, university* uni);// Printing the data of the students into a file text,together with '1' or '0', depands on the homeworks that the student did.
void AddFinalMark(FILE* out, university* uni);//Printing into a file and calculating to the end of each student raw the final grade.
void Static(FILE* out, university* uni);//Printing into a file statistic data of the students grades.
void Above_avg(FILE* out, university* uni);//Printing into a file the student from the old/new matkonet that are above the avg grade.
void free_func(university** uni);//Function that free all the memory that was allocated for the univresity.

void main()
{
	float avg;
	int flag = 2,i;
	int option;
	char ch;
	university *uni;
	FILE* in, * out;
	uni = (university*)malloc(sizeof(university));//allocating memory for the uni.
	if (NULL == uni) Error_Msg("Memory allocated failed.\n");
	do {
		if (flag == 2) //If its the first time that the user insert char.
		{
			printf("Please enter char between '1-6':");
			scanf("%d", &option); //Geting the character from the user.
			rewind(stdin);
		}
		else //If the user insert already '1' before.
		{
			printf("Please enter char between '2-6':");
			scanf("%d", &option); //Geting the character from the user.
			rewind(stdin);
		}

		ch = option + '0';
		switch(ch)
		{
			case '1':
				if (flag == 2) {
					if ((in = fopen("input.txt", "rt")) == NULL)
					{
						free(uni);//free the memory that was allocated for the uni.
						Error_Msg("Cannot open the file text.\n");
					}
					Build_Uni(&uni, in);
					fclose(in);//close the pointer file.
					flag--;
				}
				else fprintf(stdout,"Can't choose '1' again!!\n");
				rewind(stdin);//Clean the stdin.
				break;
			case '2':// Printing the data of the students into new file text.
				if (flag == 1) {
					if ((out = fopen("output.txt", "wt")) == NULL) {
						free_func(&uni);
						Error_Msg("Cannot open the file text.\n");
					}
					PrintUniversity(out, uni);// Printing the data of students to new file text.
					fclose(out);// Close the FILE pointer.
				}
				else fprintf(stdout,"Wrong input, Please enter '1' to begin!\n");
				rewind(stdin);//Clean the stdin.
				break;
			case '3'://Calculating the final mark of each student in the university.
				if (flag == 1)
				{
					if ((out = fopen("output.txt", "wt")) == NULL) {
						free_func(&uni);
						Error_Msg("Cannot open the file text.\n");
					}
					AddFinalMark(out, uni);//Calculating the final mark of each student in the university,and printing after and before the change.
					fclose(out);//Clean the stdin.
				}
				else fprintf(stdout,"Wrong input, Please enter '1' to begin!\n");
				rewind(stdin);//Clean the stdin.
				break;
			case '4'://Calculating Average,Standard Deviation,Num of students in the university, the Range mark,and how many students are in the old\new matkonet.
				if (flag == 1) {
					if ((out = fopen("output.txt", "wt")) == NULL) {
						free_func(&uni);
						Error_Msg("Cannot open the file text.\n");
					}
					Static(out, uni);
					fclose(out);//Close the FILE pointer.
				}
				else fprintf(stdout,"Wrong input, Please enter '1' to begin!\n");
				rewind(stdin);//Clean the stdin.
				break;
			case '5':
				if (flag == 1)
				{
					if ((out = fopen("output.txt", "wt")) == NULL) {
						free_func(&uni);
						Error_Msg("Cannot open the file text.\n");
					}
					Above_avg(out, uni);
					fclose(out);//Close the FILE pointer.
				}
				else fprintf(stdout,"Wrong input, Please enter '1' to begin!\n");
				rewind(stdin);//Clean the stdin.
				break;
			case '6':
				if ((out = fopen("output.txt", "wt")) == NULL) {
					free_func(&uni);
					Error_Msg("Cannot open the file text.\n");
				}
				fprintf(out, "End Of Program");
				fclose(out);//Close the FILE pointer.
				if (flag < 2) {
					for (i = 0; i < uni->size; i++)//Free the memory that was allocated for each student names.
					{
						free(uni->arr[i].name);
					}
					free(uni->arr);//free the memory that was allocated for the student array.
					free(uni);//Free the memory that was allocated to the university.
				}
				exit(1);
				break;
			default: fprintf(stderr,"Wrong input!!\n");//If the user insert wrong input, this messege will pop up.
		}
	} while (flag != 0);//Stop term.
}
void Build_Uni(university** uni, FILE* in)
{
	char tempname[NAME];
	int i = 1, j,len;
	(*uni)->arr = (stud*)malloc(sizeof(stud));//allocating memory for the arr of students in the university.
	if ((*uni)->arr == NULL) {
		free(*uni);//free the universita that was allocated in the main function.
		Error_Msg("Allocation for the students array has been failed.");
	}
	while (fscanf(in, "%s", tempname) != EOF)//Geting data from the file until End of FILE.
	{
		(*uni)->arr = (stud*)realloc((*uni)->arr, i * sizeof(stud));//Reallocating memory for all students.
		if (NULL == (*uni)->arr) //If the allocation failed, all the memory of the students from the beginning will release.
		{
			free((*uni)->arr);
			free(*uni);//free the universita that was allocated in the main function.
			Error_Msg("Not enought memory for arr.");
		}
		len = strlen(tempname);
		(*uni)->arr[i - 1].name = (char*)malloc(sizeof(char) * (len + 1));//Allocating memory for the name of the student.
		if (NULL == (*uni)->arr[i - 1].name)//if allocating the name has failed.
		{
			for (j = i-1; j>0; j--)//loop to free the last names that was allocated.
			{
				free((*uni)->arr[j - 1].name);
			}
			free((*uni)->arr);//free the array of students that was allocated.
			free(*uni);//free the universita that was allocated in the main function.
		}
		strcpy(((*uni)->arr[i - 1].name), tempname);
		fscanf(in, "%ld%d%s %c", &(*uni)->arr[i - 1].id, &(*uni)->arr[i - 1].grade, (*uni)->arr[i - 1].tasks,&(*uni)->arr[i-1].flag);//Getting the data of each student from the input file.
		i++;
		
	}
	(*uni)->size = i - 1;//Getting the size of the students number in the university.
}
void PrintUniversity(FILE* out, university* uni)
{
	int i, j, sum;
	for (i = 1; i <= uni->size; i++)
	{
		sum = 0;//Variable  for summing the number of the homeworks that the student did('1').
		fprintf(out, "Student %d: %s %ld %d ", i, uni->arr[i - 1].name, uni->arr[i - 1].id, uni->arr[i - 1].grade);
		for (j = 0; j < GRADES-1; j++)
			sum += (uni->arr[i - 1].tasks[j]) - '0';
		if (sum >= 3) //If the student did 3 or more homeworks his final mark for the homework will be 1.
			uni->arr[i - 1].final_grade = '1';
		else//Else the final mark of the homework will be 0.
			uni->arr[i - 1].final_grade = '0';
		fprintf(out, "%c ", uni->arr[i - 1].final_grade);
		fprintf(out, "%c\n", uni->arr[i - 1].flag);
	}
}
void AddFinalMark(FILE* out, university* uni)
{
	int i, j, sum = 0,tempgrade=0;
	fprintf(out, "BEFORE:\n");
	PrintUniversity(out, uni);
	fprintf(out, "AFTER:\n");
	for (i = 1; i <= uni->size; i++)
	{
		sum = 0;
		fprintf(out, "Student %d: %s %ld %d ", i, uni->arr[i - 1].name, uni->arr[i - 1].id, uni->arr[i - 1].grade);
		
		if (uni->arr[i - 1].grade > 55){//if not above or equal to 55 the student has been failed.
			for (j = 0; j < GRADES - 1; j++)
				sum += (uni->arr[i - 1].tasks[j]) - '0';
			if (sum >= 3)
				uni->arr[i - 1].final_grade = '1';
			else
				uni->arr[i - 1].final_grade = '0';

				if (uni->arr[i - 1].final_grade == '1')//If the students done 3 or more of the homeworks.
				{
					if (uni->arr[i - 1].flag == 'Y')//the student in the new matkonet
					{
						tempgrade = uni->arr[i - 1].grade;
						if ((uni->arr[i - 1].grade * 0.8 + 20) > tempgrade) {
							tempgrade = uni->arr[i - 1].grade * 0.8 + 20;
							fprintf(out, "%c final : %d\n", uni->arr[i - 1].final_grade, tempgrade);
						}
					}
					if (uni->arr[i - 1].flag == 'N')//the student in the old matkonet
					{
						tempgrade = uni->arr[i - 1].grade;
						if ((uni->arr[i - 1].grade * 0.9 + 10) > tempgrade) {
							tempgrade = uni->arr[i - 1].grade * 0.9 + 10;
							fprintf(out, "%c final : %d\n", uni->arr[i - 1].final_grade, tempgrade);
						}
					}
				}
				else//If the student done less then 3 homeworks.
					fprintf(out, "%c final: %d\n", uni->arr[i - 1].final_grade, uni->arr[i - 1].grade);
		}
		else //if not above or equal to 55 the student has been failed.
		{
			fprintf(out, "%c final: %d\n", uni->arr[i - 1].final_grade, uni->arr[i - 1].grade);
		}
	}
}
void Static(FILE* out, university* uni)
{
	int i;
	int sumY=0,sumN=0,sum = 0;
	int max = 0, min = 100;
	float avg, newsum = 0, sd;
	for (i = 0; i < uni->size; i++)//Loop for finding the max and min grade of the students in the university and how many are learning in the old or new matkonet.
	{
		if (uni->arr[i].flag == 'Y') sumY++;
		else sumN++;
		if (uni->arr[i].grade > max) {
			max = uni->arr[i].grade;
		}
		if (uni->arr[i].grade < min) {
			min = uni->arr[i].grade;
		}
		sum += uni->arr[i].grade;//Sum all the students marks.
	}
	avg = sum / (float)uni->size;//Geting the averag.
	for (i = 0; i < uni->size; i++)//Geting newsum value for calculate the Standard Deviation(sd).
	{
		newsum += pow((float)uni->arr[i].grade - avg, 2);
	}
	sd = sqrt(newsum / uni->size);
	fprintf(out, "Average: %.2f\nStandard Deviation: %.2f\nAmount of students:%d\nRange:%d ", avg, sd, uni->size, max - min);
	fprintf(out, "There are %d student in the new matkoent and %d in the old matkonet.\n", sumY, sumN);
}
void Above_avg(FILE* out, university* uni)
{
	char new_old;
	int i, j, k = 1, sum = 0;
	float avg;
	for (i = 0; i < uni->size; i++)//Loop for finding calculating the avg of the students.
	{
		sum += uni->arr[i].grade;//Sum all the students marks.
	}
	avg = sum / (float)uni->size;//Geting the average.
	do {
		fprintf(stdout, "which data of the students you want to know? old(N) or new(Y): \n");
		fscanf(stdin, "%c", &new_old);
		rewind(stdin);//clear the stdin.
	} while (!(new_old == 'Y' || new_old == 'N'));
	for (i = 1; i <= uni->size; i++)
	{
		if (uni->arr[i - 1].flag == new_old)
		{
			if (uni->arr[i - 1].grade > avg) {
				sum = 0;
				for (j = 0; j < GRADES - 1; j++)
					sum += (uni->arr[i - 1].tasks[j]) - '0';
				if (sum >= 3) //If the student did 3 or more homeworks his final mark for the homework will be 1.
					uni->arr[i - 1].final_grade = '1';
				else//Else the final mark of the homework will be 0.
					uni->arr[i - 1].final_grade = '0';
				fprintf(out, "Student %d: %s %ld %d ", k, uni->arr[i - 1].name, uni->arr[i - 1].id, uni->arr[i - 1].grade);
				fprintf(out, "%c ", uni->arr[i - 1].final_grade);
				fprintf(out, "%c\n", uni->arr[i - 1].flag);
				k++;
			}
		}
	}
}
void free_func(university** uni)
{
	int i;
	for (i = 0; i < (*uni)->size; i++)//Free the memory that was allocated for each student names.
	{
		free((*uni)->arr[i].name);
	}
	free((*uni)->arr);
	free(*uni);
}
void Error_Msg(char* str)//Printing error messege and close the program.
{
	fprintf(stderr, "\n%s", str);
	exit(1);
}