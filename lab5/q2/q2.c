#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int Bit_Count(unsigned int x);//Function that get unsigned int and return the amount of the '1' bits.
void Bin_Print(unsigned int x);/* Function to get numbers of '1' bits in binary 
   representation of positive integer x */

int main()
{
	unsigned int x;

	fprintf(stdout,"Enter a number: ");
	scanf("%d", &x);
	fprintf(stdout, "There are %d bits equal to one in %d\n", Bit_Count(x), x);
	fprintf(stdout, "The binary representation of %d is ", x);
	Bin_Print(x);

	return 0;
}


int Bit_Count(unsigned int x)
{
	int i=0;
	unsigned int mask = 1;
	while (x) {
		if (x & mask == 1) {
			i++;//counte how much '1' bits are in the number.
		}
		x >>= 1;//moving the bits 1 place to the right.
	}
	return i;
}

void Bin_Print(unsigned int x)
{
	int numofbits = sizeof(unsigned int) * 8 - 1;//get the size of integer's bits.
	unsigned int mask;
	int i;
	for (i = numofbits; i >= 0; i--)
	{
		mask = x >> i;
		putchar(mask & 1 ? '1' : '0');
	}
}
