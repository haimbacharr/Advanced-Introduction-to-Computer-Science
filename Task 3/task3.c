#include "headertask3.h"
int main()
{
	FILE* instruction, * mana;
	Manot* kitchen = NULL;//the kitchen for the all program.
	table tbl[TBL];
	char mealname[NAME];
	int i, num, quantity, flag = 0;
	for (i = 0; i < TBL; i++)  //reseting the table array.
	{
		tbl[i].bill = 0;
		tbl[i].head = NULL;
		tbl[i].tail = NULL;
		tbl[i].TableNumber = i + 1;
	}
	if (NULL == (instruction = fopen("Instructions.txt", "rt")))
	{
		fprintf(stderr, "Cannot open the instruction file.");
		exit(1);
	}
	fscanf(instruction, "%d", &num);
	do {
		fprintf(stdout, "\nPress 0 to recieve line from Instruction file:");
		fscanf(stdin, "%d", &flag);

		if (!flag) {
			if (num == 1) ShowMenu();
			else ShowMenu2();
			
			{
				switch (num) {
				case 1:
					if (NULL == (mana = fopen("Manot.txt", "rt")))
					{
						fprintf(stdout, "Cannot open the mana file text.");
	
						Error_Msg("Cannot open the mana file text.",instruction);
					}
					CreateProducts(&kitchen, mana,instruction);
					fprintf(stdout, "The kitchen was created\n");
					fclose(mana);// close the file pointer from Manot.txt.
					break;
				case 2:
					fscanf(instruction, "%s %d ", mealname, &quantity);
					AddItems(&kitchen, mealname, quantity);
					break;
				case 3:
					fscanf(instruction, "%d %s %d \n", &i, mealname, &quantity);
					OrderItem(tbl, &kitchen, i, mealname, quantity,instruction);
					break;
				case 4:
					fscanf(instruction, "%d %s %d\n", &i, mealname, &quantity);
					RemoveItem(tbl, &kitchen, i, mealname, quantity);
					break;
				case 5:
					fscanf(instruction, "%d", &i);
					RemoveTable(tbl, i);
					break;
				default:
					break;
				}
			}
		}
	} while ((fscanf(instruction, "%d", &num) != EOF) && (!flag));
	fclose(instruction);// close the file pointer from Instructions.txt.
	//release all allocation when finish
	DeleteManotFromKitchen(&kitchen);//free the manot in the kithcen.
	return 0;
}