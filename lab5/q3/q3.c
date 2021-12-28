#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
void BinPrint(unsigned char ch);//Function to print the binary present.
unsigned  char  check_ms(unsigned char x);//Function that check if the MSB is '1' if not will change to '0'.
unsigned char change_bit(unsigned char ch, int n);//change the bit from left to right,if '1' to '0',if '0' to '1'.

int main()
{
	unsigned char num1 = 102, num2 = 58;
	int n;

	fprintf(stdout,"\nThe first part :");
	fprintf(stdout, "\nThe number is %d   ", num1);
	BinPrint(num1);
	num1 = check_ms(num1);
	fprintf(stdout, "\nThe new number is: %d   ", num1);
	BinPrint(num1);

	fprintf(stdout, "\n\nThe second part :");
	fprintf(stdout, "\nThe number is %d   ", num2);
	BinPrint(num2);
	fprintf(stdout, "\nEnter a number of the bit to change(1-8)");
	scanf("%d", &n);
	num2 = change_bit(num2, n);
	fprintf(stdout, "\nThe new number is: %d   ", num2);
	BinPrint(num2);     /*Binary representation of number*/
	return 0;
}

void BinPrint(unsigned char ch)
{
	int numofbits = sizeof(unsigned char) * 8 - 1;//get the size of integer's bits.
	unsigned char mask=1;
	int i;
	for (i = numofbits; i >= 0; i--)
	{
		mask = ch >> i;
		putchar(mask & 1 ? '1' : '0');
	}
}

unsigned  char  check_ms(unsigned char x)
{
	int size = (sizeof(unsigned char) * 8) - 1;
	unsigned char mask = 1;
	x = x | (mask<<size);//set the MSB.
	return x;
}

unsigned char change_bit(unsigned char ch, int n)
{
	int numofbits = sizeof(unsigned char) * 8 - 1;//get the size of unsigned char's bits.
	unsigned char mask = 1;
	if ((ch >> numofbits - n + 1) & 1)//check if the n bit is '1' or '0'.
		ch &= ~(mask << numofbits - n + 1);
	else
		ch |= mask << numofbits - n + 1;
	return ch;
}
