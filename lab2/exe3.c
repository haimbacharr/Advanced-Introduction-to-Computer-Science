#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define NUM 3
typedef struct Complex//Declaring about new typde of data
{
	double rel, im;
}Complex;

float CRadius(Complex a);//Get a complex number,and return his radius(float).
Complex* Cmax(Complex* a);//Get an array of structers(compelx),and return pointer to the biggest complex number in the array.

void main()
{
	Complex x[NUM], * big;
	int i;
	printf("Enter %d complex numbers:\n", NUM);
	for (i = 0; i < NUM; i++)//Loop for geting the data into the array of structers.
	{
		scanf("%lf %lf", &x[i].rel, &x[i].im);
	}
	big = Cmax(&x);//big will point to the biggest complex number from the array of structers.
	printf("\nThe max number is %.2f+%.2fi\n", big->rel, big->im);
	printf("The radius of the max number is %.2f\n", CRadius(*big));
	getch();
	return 0;
}
Complex* Cmax(Complex* a)
{
	int i, imax = 0;
	double r, temp;
	r = (CRadius(*a));//r will be the radius of the first complex number in the array.
	for (i = 1; i < NUM; i++)
	{
		temp = CRadius(a[i]);
		if (temp > r)
		{
			imax = i;//will be index for the biggest complex number in the array.
			r = temp;
		}
	}
	return (a + imax);
}

float CRadius(Complex a)
{
	double r;
	r = sqrt(pow(a.rel, 2) + pow(a.im, 2));
	return r;
}

