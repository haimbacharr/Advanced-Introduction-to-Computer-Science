#ifndef _headertask3
#define _headertask3

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#define TBL 15
#define NAME 101

typedef struct Manot
{
	char* ProductName;
	int Price;
	int Quantity;
	char Premium;
	struct Manot* next;
}Manot;

typedef struct data {
	struct Manot* mana;
	struct data* next, * prev;
}data;

typedef struct table {
	int TableNumber;
	int bill;
	struct data* head, * tail;
}table;

void ShowMenu();//show menu with function 1.
void ShowMenu2();//show menu without functuion 1.
void CreateProducts(Manot** kit, FILE* mana,FILE *in);//Function that Create list of manot in the kitchen.
int CheckName(Manot* kit, char* mana_name);//Function that checks if name exists, return 0 if exists else return 1
void ADDQuantity(Manot* kit, int price, int quantity, char* str);//Function that add quantity to a dish in the list.
void DeleteManotFromKitchen(Manot** kit);//Function that delete the dishes in the kitchen.
void AddItems(Manot** kit, char* ProductName, int q);//Function that Update the new quantity of the meal in the kitchen.
void OrderItem(table tbl[], Manot** kit, int Table_Number, char* name, int qua,FILE *f);/*Function that add dishes from the kitchen to a table as a node in the list,and reduce the amount of the ordered dish
from the kitchen.*/
void RemoveQuantity(Manot** kit, int quantity, char* mealname);//function that remove quantity of an meal in the kitchen.
data* SearchMealInTable(data* p, char* name);//Function that search if there is a node that we looking for,if it exist, it will return pointer to this node,else return null.
void DeleteManotFromTable(table tbl[]);//Function that remove the dishes in the tables.
void RemoveItem(table tbl[], Manot** kit, int i, char* name, int qua);/*Function that remove dishes from a table,it a dish will remove,the bill of the table
will be update ,the same dish will go to the garbge,wont return to the kitchen.*/
void RemoveTable(table tbl[], int i);/*View report with all ordered items + payment amount and clearing table) Release memory of -
The dishes.
If premium (one or more) dishes are ordered, the customer will be required to pay an additional 10% of the amount
The total of the entire table, due to accompanying extras (fine wines and personal waiter).
The report will indicate whether or not this is a "premium table" and the final amount to be paid*/
void Error_Msg(char* str,FILE * f);//Function that print a msg and close a file pointer.


#endif