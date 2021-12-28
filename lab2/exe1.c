#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct nekode //declaring a new type.
{
	double x1, x2;
}nekode;

typedef struct center //declaring a new type.
{
	nekode c;
	double r;//radius.
}center;

int is_in(nekode a, center b);

void main()
{
	nekode A;
	center B;
	printf("Enter the cordinates of your point:");
	scanf("%lf %lf", &A.x1, &A.x2);//getting the nekode.
	printf("\nEnter the  radius and the center of your circle:");
	scanf("%lf %lf %lf", &B.r, &B.c.x1, &B.c.x2);//getting the center of the circle and the radius.
	if (is_in(A, B))
		printf("\nThe point is included in the circle.\n");
	else
		printf("\nThe point is not included in the circle.\n");

	getch();
	return(0);
}

int is_in(nekode a, center b)//checking  if the nekode is in the circle.
{
	if (b.r <= sqrt(pow(a.x1 - b.c.x1, 2) + pow(a.x2 - b.c.x2, 2)))
		return 0;//if the nekode is not in the circle.
	return 1;// if the nekode is not in the circle.
}
