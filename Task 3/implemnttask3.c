#include "headertask3.h"
void CreateProducts(Manot** kit, FILE* mana,FILE *instruction)
{
	char temp_name[NAME], ch;
	int quantity, price;// geting values if there is duplicates in the name of the manot.
	Manot* temp;
	int len, flag = 1;
	while (fscanf(mana, "%s ", temp_name) != EOF)
	{
		rewind(stdin);
		fscanf(mana, "%d %d %c", &quantity, &price, &ch);
		if (CheckName(*kit, temp_name) == 0)//if name is already exists
		{
			flag = 0;
			fprintf(stderr, "%s  already exits in Manot list!\n", temp_name);
		}
		if (flag == 1) {
			len = strlen(temp_name);
			temp = (Manot*)malloc(sizeof(Manot));
			if (temp == NULL)
			{
				DeleteManotFromKitchen(kit);
				fclose(mana);
				Error_Msg("The kitchen has not created.!\n",instruction);
			}
			temp->ProductName = (char*)malloc(sizeof(char) * (len + 1));//allocating place for the name of the meal.
			if (temp->ProductName == NULL)
			{
				DeleteManotFromKitchen(kit);
				fclose(mana);
				Error_Msg("The kitchen has not created.!\n",instruction);
			}
			strcpy(temp->ProductName, temp_name);
			temp->Quantity = quantity;
			temp->Price = price;
			temp->Premium = ch;
			if (flag == 1) {
				if (temp->Quantity <= 0)
				{
					flag = 0;
					fprintf(stderr, "quantity need to be positive number!\n");//error msg.
				}
				if (flag == 1) {
					if (temp->Price < 0)
					{
						flag = 0;
						fprintf(stderr, "price need to be positive number!\n");//error msg.
					}
					if (flag == 1)
					{
						if (NULL == *kit) //if its the first time to get mana in kitchen.
						{
							*kit = temp;
							(*kit)->next = NULL;//makes the right block in the list NULL.
						}
						else // if its not the first time to get mana to the kitchen.
						{
							temp->next = *kit;
							*kit = temp;
						}
					}
				}
			}
		}
		else//if the product is in the list.
		{
			ADDQuantity(*kit, price, quantity, temp_name);
			flag = 1;
		}
	}
}
void ADDQuantity(Manot* kit, int price, int quantity, char* str)//Update the quantity of the meal.
{
	char ch;
	Manot* p = NULL;
	int  flag = 1;// geting values if there is duplicates in the name of the meals.
	p = kit;

	while (p != NULL)//while p!=null seach if the name exists
	{
		if (quantity <= 0)
		{
			flag = 0;
			fprintf(stderr, "Cannot be negetive quantity!\n");
		}
		if (flag == 1) {
			if (price <= 0) {
				flag = 0;
				fprintf(stderr, "Cannot be negetive price!\n");
			}
		}
		if (flag == 1) {
			if (strcmp(p->ProductName, str) == 0)
				(p->Quantity) += quantity;
		}
		p = p->next;
	}
}

void DeleteManotFromKitchen(Manot** kit)
{
	Manot* temp;
	while (*kit)
	{
		temp = *kit;
		*kit = (*kit)->next;
		free(temp->ProductName);
		free(temp);
	}
}

void AddItems(Manot** kit, char* ProductName, int q)
{

	int flag = 1;
	Manot* temp;
	temp = *kit;
	if (CheckName(temp, ProductName) == 0)//if (0) its means product name is in the kitchen.
	{
		if (q <= 0)
		{
			flag = 0;
			fprintf(stderr, "quantity need to be positive number!\n");
		}
		if (flag == 1) {
			while (strcmp(temp->ProductName, ProductName) != 0)//loop to find the name in list.
			{
				temp = temp->next;
			}
			temp->Quantity += q;//Update the new quantity of the meal in the kitchen.
			fprintf(stdout, "%d %s were added to the kitchen\n", q, ProductName);//print msg that quantity added to the kitchen
		}

	}
	else 	fprintf(stderr, "there is no meal in the name of %s in the kithcen.\n", ProductName);
}

void OrderItem(table tbl[], Manot** kit, int Table_Number, char* name, int qua, FILE* instruction)
{
	Manot* manot;
	data* p;
	manot = *kit;//manot point to the beginning of the meals list in kitchen.
	int flag = 1, i, len;
	if (Table_Number <= 0 || Table_Number > TBL)//If the table number is not between 1-15,will print messege.
	{
		fprintf(stderr, "table %d is not exists!\n", Table_Number);
		flag = 0;
	}
	if (qua < 1)
	{
		fprintf(stderr, "Quantity need to be positive!\n", name);
		flag = 0;
	}
	if (flag == 1) {
		if (CheckName(manot, name) == 1)//If the meal doesnt exists in the kitchen ,messege will be printed and the program will continue.
		{
			fprintf(stderr, "We don't have %s in the kitchen, sorry!\n", name);
			flag = 0;
		}
		if (flag == 1)
		{
			if (CheckQuantity(manot, qua, name))//Check if there is enough quantity of the meal in the kitchen.
			{
				if (NULL == tbl[Table_Number - 1].head)//if it's the first order in the table.
				{
					p = (data*)malloc(sizeof(data));//Allocate new meal to the table.
					if (NULL == p)
					{                                   // If allocation failed.
						for (i = 0; i < TBL; i++)
							DeleteManotFromTable(tbl + i);
						DeleteManotFromKitchen(&kit);
						Error_Msg("Error allocation failed!\n",instruction);
					}
					p->mana = (Manot*)malloc(sizeof(Manot));
					if (NULL == p->mana)
					{                                   // If allocation failed.
						for (i = 0; i < TBL; i++)
							DeleteManotFromTable(tbl + i);
						DeleteManotFromKitchen(kit);
						Error_Msg("Error allocation failed!\n",instruction);
					}

					while (strcmp(manot->ProductName, name) != 0)//Search for the name of the ordered meal.
					{
						manot = manot->next;
					}
					//Getting the data into the new meal of the table.
					p->mana->Price = manot->Price;
					p->mana->Quantity = qua;
					RemoveQuantity(kit, qua, manot->ProductName);  //Update the new quantity of the ordered meal from the kitchen.
					p->mana->Premium = manot->Premium;
					len = strlen(manot->ProductName); //Geting the length of the name.
					p->mana->ProductName = (char*)malloc(sizeof(char) * (len + 1));//Allocating memory for the new temp ->Proudctname.
					if (NULL == p->mana->ProductName)
					{									// If allocation failed.
						for (i = 0; i < TBL; i++)
							DeleteManotFromTable(tbl + i);
						DeleteManotFromKitchen(kit);
						Error_Msg("Error allocation failed!\n",instruction);
					}
					p->mana->next = NULL;
					strcpy(p->mana->ProductName, manot->ProductName);//Geting the name of the meal.
					tbl[Table_Number - 1].bill = (qua * p->mana->Price);    //update the bill.
					tbl[Table_Number - 1].head = p;
					tbl[Table_Number - 1].tail = p;
					tbl[Table_Number - 1].head->prev = NULL;
					tbl[Table_Number - 1].tail->next = NULL;
					manot = *kit;//Update manot to point to the head of the kitchen again.
					fprintf(stdout, "%d %s were added to the table number %d\n", qua, name, Table_Number);
					flag = 0;
				}
				if (flag == 1) {
					if (NULL != tbl[Table_Number - 1].head)//If it's not the first meal in the table.	
					{
						p = tbl[Table_Number - 1].head;
						while (strcmp(p->mana->ProductName, name) != 0 && flag)//Search if the name of the meal is already in the table.
						{
							if (p->mana->next == NULL)
								flag = 0;
							else
								p->mana = p->mana->next;
						}
						if (flag == 0)//If the meal is not in the table.Allocating place for the new meal.
						{
							p = (data*)malloc(sizeof(data));//Allocate new meal to the table.
							if (NULL == p)
							{                                   // If allocation failed.
								for (i = 0; i < TBL; i++)
									DeleteManotFromTable(tbl + i);
								DeleteManotFromKitchen(kit);
								Error_Msg("Error allocation failed!\n",instruction);
							}
							p->mana = (Manot*)malloc(sizeof(Manot));
							if (NULL == p->mana)
							{                                   // If allocation failed.
								for (i = 0; i < TBL; i++)
									DeleteManotFromTable(tbl + i);
								DeleteManotFromKitchen(&kit);
								Error_Msg("Error allocation failed!\n",instruction);
							}

							while (strcmp(manot->ProductName, name) != 0)//Search for the name of the ordered meal.
							{
								manot = manot->next;
							}
							//Getting the data into the new meal of the table.
							p->prev = NULL;
							p->mana->Price = manot->Price;
							p->mana->Quantity = qua;
							RemoveQuantity(kit, qua, manot->ProductName);  //Update the new quantity of the ordered meal from the kitchen.
							p->mana->Premium = manot->Premium;
							len = strlen(manot->ProductName); //Geting the length of the name.
							p->mana->ProductName = (char*)malloc(sizeof(char) * (len + 1));//Allocating memory for the new temp ->Proudctname.
							if (NULL == p->mana->ProductName)
							{									// If allocation failed.
								for (i = 0; i < TBL; i++)
									DeleteManotFromTable(tbl + i);
								DeleteManotFromKitchen(kit);
								Error_Msg("Error allocation failed!\n",instruction);
							}
							strcpy(p->mana->ProductName, manot->ProductName);//Geting the name of the meal.
							p->mana->next = NULL;
							p->next = tbl[Table_Number - 1].head;
							tbl[Table_Number - 1].head->prev = p;
							tbl[Table_Number - 1].head = p;
							tbl[Table_Number - 1].bill = tbl[Table_Number - 1].bill + (qua * p->mana->Price);    //update the bill.
							fprintf(stdout, "%d %s were added to the table number %d\n", qua, name, Table_Number);
						}
						else //If the meal is  in the table.
						{
							p = tbl[Table_Number - 1].head;
							while (strcmp(manot->ProductName, name) != 0)//search the name of the ordered meal.
							{
								manot = manot->next;
							}
							manot->Quantity += qua;
							RemoveQuantity(kit, qua, manot->ProductName);  //update the new quantity of the ordered meal from the kitchen.
							tbl[Table_Number - 1].bill += (qua * manot->Price);//Update the bill of the table.
							manot = *kit;//update manot to point to the head of the kitchen again.
							//q = TBL[Table_Number - 1].head;
							fprintf(stdout, "%d %s were added to the table number %d\n", qua, name, Table_Number);
						}
					}
				}
			}
			else fprintf(stderr, "Sorry we don't have %d %s in the kitchen.\n", qua, name);
		}
	}
}


void RemoveItem(table tbl[], Manot** kit, int i, char* name, int qua)
{
	int flag = 1;
	Manot* manot;
	data* p, * q;
	p = tbl[i - 1].head;
	if (i < 0 || i > 15)
	{
		fprintf(stderr, "There is no %d Tables in the resturant!\n", i);
		flag = 0;
	}
	if (flag == 1) {
		if (qua <= 0)
		{
			fprintf(stderr, "Quantity has to be positive!\n");
			flag = 0;
		}
		if (flag == 1) {
			if (CheckName(*kit, name) != 0)//if the name is not in the list,will show msg.
			{
				fprintf(stderr, "There is no %s in the kitchen.\n", name);
				flag = 0;
			}
			if (tbl[i - 1].head == NULL)//If the table have no meals.
			{
				fprintf(stderr, "The table number %d is not ordered yet,there are no meal to remove.\n", i);
				flag = 0;
			}
			if (flag == 1) {
				if (NULL == (p = SearchMealInTable(p, name)))//If the name of the meal doesnt ordered yet.
				{
					fprintf(stderr, "There is no %s in the table.\n", name);
					flag = 0;
				}
				if (flag == 1)
				{
					if (p->mana->Quantity < qua)
					{
						fprintf(stderr, "Quantity is bigger then ordered to the table\n");
						flag = 0;
					}
					if (flag == 1)
					{
						p->mana->Quantity -= qua;//Update the quantity of the new meal in the table.
						tbl[i - 1].bill -= (qua * p->mana->Price);//Update the bill of the table.
						if (p->mana->Quantity == 0)//need to remove the mana from the table.
						{
							if (NULL == tbl[i - 1].head->next) //if we have only 1 meal in the table.
							{
								free(p->mana->ProductName);
								free(p->mana);
								free(p);
								tbl[i - 1].head = NULL;
								tbl[i - 1].tail = NULL;
								flag = 0;
								fprintf(stdout, "%d %s was returned and will go to the garbage from table number %d\n", qua, name, i);
							}
							if (flag == 1 && (tbl[i - 1].tail->prev != NULL))//if we have more than 1 meal in the table.
							{
								if (!(strcmp(p->mana->ProductName, tbl[i - 1].head->mana->ProductName)))//if the meal that we wanted to delete is the head of the list.
								{
									tbl[i - 1].head = tbl[i - 1].head->next;
									free(p->mana->ProductName);
									free(p->mana);
									free(p);
									tbl[i - 1].head->prev = NULL;
									flag = 0;
									fprintf(stdout, "%d %s was returned and will go to the garbage from table number %d\n", qua, name, i);
								}
								if (flag == 1) {
									if (!(strcmp(p->mana->ProductName, tbl[i - 1].tail->mana->ProductName)))//if the meal that we wanted to delete is the end of  the list.
									{

										q = tbl[i - 1].tail->prev;
										free(p->mana->ProductName);
										free(p->mana);
										free(p);
										tbl[i - 1].tail = q;
										tbl[i - 1].tail->next = NULL;
										flag = 0;
										fprintf(stdout, "%d %s was returned and will go to the garbage from table number %d\n", qua, name, i);
									}
								}
								if (flag == 1) { //the meal is in the middle of the list.
									{
										q = tbl[i - 1].head;//p point to the head of the list.
										while (p->mana->ProductName != q->next->mana->ProductName)
										{
											q = q->next;
										}
										q->prev = q->next;
										q->next = q->prev;
										free(p->mana->ProductName);
										free(p->mana);
										free(p);
										flag = 0;
										fprintf(stdout, "%d %s was returned and will go to the garbage from table number %d\n", qua, name, i);
									}
								}
							}
						}
						else fprintf(stdout, "%d %s was returned and will go to the garbage from table number %d\n", qua, name, i);
					}
				}
			}
		}
	}
}


void RemoveTable(table tbl[], int i)
{
	float sum = 0;
	int flag = 1, pre = 0;
	data* temp;
	temp = tbl[i - 1].head;//temp will point to first meal in the table. 
	if (i < 0 || i > 15)
	{
		fprintf(stdout, "There is no %d Tables in the resturant!\n", i);
		flag = 0;
	}
	if (flag == 1) {
		if (NULL == temp)
		{
			fprintf(stdout, "The table number %d is not ordered yet\n", i);
			flag = 0;
		}
		if (flag == 1)
		{
			fprintf(stdout, "*********************BILL*********************\n");
			fprintf(stdout, "Table Number : %d\n",i);
			while (temp != NULL && (!pre))//loop to find if there is any Premium meal in the table.
			{
				if (temp->mana->Quantity == 0)
					pre = 1;
				if (temp->mana->Premium == 'Y' || temp->mana->Premium == 'y')//check if we got premium order in table list
					pre = 1;
				temp = temp->next;
			}
			if (pre == 1)  //If there is premuim meal in the table.
			{

				sum = tbl[i - 1].bill;
				sum = sum * 1.1;//Calculation if there is a premium meal.
				fprintf(stdout, "\t    ^^^^ Premium Table ^^^^\n");
			}
			else//If there is no premuim meal in the table.
			{
				sum = tbl[i - 1].bill;
				fprintf(stdout, "^^^^ Basic Table ^^^^\n ");
			}

			temp = tbl[i - 1].head;//temp point to the head of the manot in the table.
			while (NULL != temp)//print table orders
			{
				fprintf(stdout, "%s X%d = %.2f NIS.\n",  temp->mana->ProductName, temp->mana->Quantity,(float)temp->mana->Quantity*temp->mana->Price);
				temp = temp->next;//temp getting the next meal in the table[i].
			}
			fprintf(stdout, "\nTotal Price: %.2f NIS.\n", sum);
			fprintf(stdout, "*********************BILL*********************");
			temp = tbl[i - 1].head;//temp point to the head of the manot in the table.
			while (tbl[i - 1].head != NULL)//Remove all meals in the table.
			{
				temp = tbl[i - 1].head;
				tbl[i - 1].head = tbl[i - 1].head->next;
				free(temp->mana->ProductName);//free the name of the mana
				free(temp->mana);//free the mana.
				free(temp);//free the data.
			}
			tbl[i - 1].tail = NULL;
			tbl[i - 1].bill = 0;//Zeroing the bill of the table for the next customers.
		}
	}
}

void RemoveQuantity(Manot** kit, int quantity, char* mealname)
{
	Manot* temp;
	temp = *kit;
	while (strcmp(mealname, temp->ProductName) != 0)//Continue until we found the meal.
	{
		temp = temp->next;
	}
	temp->Quantity -= quantity;
}

void DeleteManotFromTable(table tbl[])
{
	data* temp;
	temp = tbl->head;
	while (tbl->head != NULL)
	{
		temp = (tbl)->head;
		(tbl)->head = (tbl)->head->next;
		free(temp->mana->ProductName);//free the name that was allocted.
		free(temp->mana);//free the mana that was allocated.
		free(temp);//free the data that was allocated.
	}
}
data* SearchMealInTable(data* p, char* name)
{
	while (p != NULL)//while p!=null seach if the name exists
	{
		if (strcmp(p->mana->ProductName, name) == 0)
			return p;// if the name exists.
		else
			p = p->next;
	}
	return NULL;//if the name is not exists.
}

int CheckQuantity(Manot* kit, int quantity, char* ProductName)// Return 1 if the quantity in the kitchen is bigger,else return 0.
{
	while (strcmp(kit->ProductName, ProductName) != 0)//Continue until we found the meal.
	{
		kit = kit->next;
	}
	if (kit->Quantity < quantity)
		return 0;
	return 1;
}

int CheckName(Manot* kit, char* mana_name)//check if name exists return 0 if exists else return 1
{
	while (kit != NULL)//while head!=null seach if the name exists
	{
		if (strcmp(kit->ProductName, mana_name) == 0)
			return 0;// if the name exists.
		else
			kit = kit->next;
	}
	return 1;//if the name is not exists.
}
void ShowMenu()
{
	fprintf(stdout, "~~~~~~~~~~~  Welcome to Haim's Restaurant ~~~~~~~~~~~\n\n");
	fprintf(stdout," '1' Absorption of dishes in the kitchen.\n");
	fprintf(stdout," '2' Adding stock to an existing dish in the kitchen\n");
	fprintf(stdout," '3' Order dishes for the table\n");
	fprintf(stdout," '4' Cancel (partial) ordering of items.\n");
	fprintf(stdout," '5' Closing table.\n");
	fprintf(stdout, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
}
void ShowMenu2()
{
	fprintf(stdout, "~~~~~~~~~~~  Welcome to Haim's Restaurant ~~~~~~~~~~~\n\n");
	fprintf(stdout, " '2' Adding stock to an existing dish in the kitchen\n");
	fprintf(stdout, " '3' Order dishes for the table\n");
	fprintf(stdout, " '4' Cancel (partial) ordering of items.\n");
	fprintf(stdout, " '5' Closing table.\n");
	fprintf(stdout, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
}
void Error_Msg(char* str,FILE *instruction)
{
	fprintf(stderr, "\n%s", str);
	fclose(instruction);
	exit(1);
}
