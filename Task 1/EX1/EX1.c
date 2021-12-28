#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

struct fraction//struct that include fraction
{
	int mone;
	int mehane;
}typedef fraction;
void printsum(fraction arr[], int size);
void zerodivide(char* errormsg);
int smallestdivider(int, int);
int main()
{
	char error[16] = "Divide by zero!";//error message
	int i = 0, flag = 0, fraccounter = 0, tempmone, tempmehane;
	fraction fracarr[10];//struct of 10 fraction (1 for 0 0)
	printf("Enter fractions(max 9) by pairs of integers(0 0 to finish) : ");
	while (i < 9 && flag == 0)//if flag==1 or the user and 9 fraction will end the loop
	{
		printf("\n%d (mone mehane): ", i + 1);
		scanf("%d %d", &tempmone, &tempmehane);//will scan the mone and the mehane of the fraction
		if (tempmone == 0 && tempmehane == 0) flag = 1;//check if the user want to end the reciving of the fraction
		if (flag == 0)//enter the data to the struct
		{
			fracarr[i].mone = tempmone;
			fracarr[i].mehane = tempmehane;
			i++;
		}
	}
	fraccounter = i;//will count the friction
	while (i-- >= 0)
		if (fracarr[i].mehane == 0) zerodivide(error);//check if dividing by 0,if yes will print error message
	printsum(fracarr, fraccounter);//function call (explain in the fucntion)

	getch();
	return 0;
}


void zerodivide(char* errormsg)//dividing by 0
{
	printf("%s", errormsg);
	getch();
	exit(1);
}

void printsum(fraction arr[], int size)
{
	fraction* temp1;//temp fraction that will help to print the original data
	int i, sum = 0, summone = 0, summehane = 0, temp, j = 0, mehalek;
	temp1 = (fraction*)malloc(size * sizeof(fraction));//dynamic allocation for printing the original data
	for (i = 0; i < size; i++)
	{
		temp1[i].mone = arr[i].mone;//copy of the struct
		temp1[i].mehane = arr[i].mehane;//copy of the struct
	}
	for (i = 0; i < size - 1; i++)
	{
		summone = arr[i].mone * arr[i + 1].mehane + arr[i].mehane * arr[i + 1].mone;//croos multiple of 2 terms (first and second)
		summehane = arr[i].mehane * arr[i + 1].mehane;//croos multiple of 2 terms (first and second)
		arr[i + 1].mone = summone;//keep the result to the second (for calculate the sum for the next terms)
		arr[i + 1].mehane = summehane;//keep the result to the second (for calculate the sum for the next terms)
	}
	sum = summone / summehane;//get the complete number
	temp = summone % summehane;//will get the remainder
	mehalek = smallestdivider(temp, summehane);//the function (uqlidisi) will find the biggest divider of the mone and mehane
	temp /= mehalek;//will divide temp with his biggest divider
	summehane /= mehalek;//will divide temp with his biggest divider
	if (sum != 0)
	{
		for (i = 0; i < size - 1; i++)
			printf("(%d/%d)+", temp1[i].mone, temp1[i].mehane);//will print all the addition of the fraction numbers
		if (temp == 0)
			printf("(%d/%d) = %d", temp1[i].mone, temp1[i].mehane, sum);//if there is only complete number and no remainder will print only the complete number
		else printf("(%d/%d)=%d and %d/%d", temp1[i].mone, temp1[i].mehane, sum, temp, summehane);//will print the last fraction and the complete number with the reminder
	}
	else
	{
		for (i = 0; i < size - 1; i++)//if the sum is 0 will print it
			printf("(%d/%d)+", temp1[i].mone, temp1[i].mehane);
		printf("(%d/%d)=%d/%d", temp1[i].mone, temp1[i].mehane, temp, summehane);
	}
	free(temp1);//free the dynamic allocation
}


int smallestdivider(int a, int b)//(uqlidisi) return the biggest divider of 2 numbers
{
	if (a == 0)
		return b;
	return smallestdivider(b % a, a);
}
