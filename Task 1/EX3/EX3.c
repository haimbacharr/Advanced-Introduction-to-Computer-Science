//mtm homework ex 3 by sahar oz and danor sinai
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define H 60

typedef struct  Clock
{
	int  hour, minute;
} clock_t;

void newtime(clock_t* time, int add);

void main()
{
	clock_t time, * ptr = &time;
	int add;
	printf("Enter time and minutes to add: ");
	scanf("%d %d %d", &time.hour, &time.minute, &add);
	while (time.hour > 23 || time.hour < 0 || time.minute < 0 || time.minute > H - 1) { //For correct input
		printf("Wrong input!, try again\n");
		printf("Enter time and minutes to add: ");
		scanf("%d %d %d", &time.hour, &time.minute, &add);
	}
	if (time.minute < 10 && time.hour < 10)//for printing clock model (XX:XX)
		printf("The time is 0%d:0%d \n", time.hour, time.minute);
	else
		if (time.minute < 10 && time.hour>10)
		{
			printf("The time is %d:0%d \n", time.hour, time.minute);
		}
		else
			if (time.minute > 10 && time.hour < 10)
				printf("The time is 0%d:%d \n", time.hour, time.minute);
			else
				printf("The time is %d:%d \n", time.hour, time.minute);

	newtime(ptr, add);

	if (time.minute < 10 && time.hour < 10)//for printing clock model (XX:XX)
		printf("The new time is 0%d:0%d \n", time.hour, time.minute);
	else
		if (time.minute < 10 && time.hour>10)
		{
			printf("The new time is %d:0%d \n", time.hour, time.minute);
		}
		else
			if (time.minute > 10 && time.hour < 10)
				printf("The new time is 0%d:%d \n", time.hour, time.minute);
			else
				printf("The new time is %d:%d \n", time.hour, time.minute);
}
void newtime(clock_t* time, int add)/*/new time funtion
input: sturct pointer (clock_t),how many time to add(int)
output: changing the time according to adding time
algorithm: checking if hours and minutes are lower then 24 (hours) and 60 (min)
calculting the new time by while loop and if condition
change the time by pointer./*/
{
	time->minute += add;
	while (time->minute > H - 1)
	{
		time->minute -= H; //if minutes bigger then 60 (H)
		time->hour++; //adding in hour
	}
	if (time->hour > 23)
	{
		time->hour -= 24;//if the hours bigger then 23, start "new day" by subtraction 1 day (24H)
	}

}
//end of the program