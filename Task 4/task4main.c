#include "task4header.h"
typedef struct/*Specific struct of a Person*/
{
	int id; 
	char *name; 
} Person;

void free_float(void* key)
/*Specific function that free a given key.*/
{
	fprintf(stdout, "%.2f has been removed from the tree\n", *(float*)key);
	free((float*)key);
	key = NULL;
}
void free_Person(void* key)
/*Specific function that free a given key.*/
{
	Person* temp;
	temp = key;
	if (temp != NULL) {
		fprintf(stdout, "%d -->%s has been removed from the tree\n", temp->id, temp->name);
		free(temp->name);
		free(temp);
		temp = NULL;
	}
	key = temp;
}
void print_float(void* key)
/*Specific func to print float.*/
{
	fprintf(stdout, "%.2f ", *(float*)key);
}
void print_Person(void* key)
/*Specific func to print struct Person.*/
{
	fprintf(stdout, "%d--> ", ((Person*)key)->id);
	fprintf(stdout, "%s ", ((Person*)key)->name);
}
Person* CreatePerson(Ptree root,DEL_FUNC del_func,int *flag)/*Specific Func that create Person node and return pointer to the node,if allocation failed will
															update the int pointer to 0.*/
{
	Person *temp;
	char name[NAME];
	int id;
	*flag = 1;
	fprintf(stdout, "Please enter and id and name for the person:");
	fscanf(stdin, "%d %s", &id, name);
	temp = (Person*)malloc(sizeof(Person));
	if (NULL == temp)
	{
		fprintf(stderr, "Allocation failed.\n");
		*flag = 0;
	}
	if (*flag) {
		temp->id = id;
		temp->name = (char*)malloc((strlen(name)) + 1);
		if (NULL == temp->name)
		{
			fprintf(stderr, "Allocation failed.\n");
			free(temp);
			*flag = 0;
		}
		if (*flag) {
			strcpy(temp->name, name);
			return temp;
		}
	}
}
BOOL float_cmp(void* root_key, void* key)
/*Specific func to compare between two void* keys,and return enum value.*/
{
	if(*(float*)root_key == *(float*)key) return TRUE;
	if (*(float*)root_key < *(float*)key) return BGR;
	if (*(float*)root_key > *(float*)key) return SMLR;
}
BOOL Person_cmp(void* a, void*key)
{
	if(((Person*)a)->id == *(int*)key) return TRUE;//if there is the key we wanted to find.
	if (((Person*)a)->id < *(int*)key) return BGR;
	if (((Person*)a)->id > * (int*)key) return SMLR;
}

int  main()
{
	Ptree root=NULL,temp =NULL;
	int ch,k,option,*flag;
	float *key,search;
	Person *node;
	fprintf(stdout, "which data you want (1) for float,(2),for Person: ");
	fscanf(stdin, "%d", &option);
	if (option == 1) {
		do {
			ch = Menu();
			fprintf(stdout, "\n");
			switch (ch) //Switch case
			{
			case 1:
				if (NULL == root)
					root = create_tree();
				key = (float*)malloc(sizeof(float));
				if (NULL == key)
				{
					fprintf(stderr, "Allocation failed.\n");
					free_tree(&root, free_float);
				}
				fprintf(stdout, "Enter float number: ");
				fscanf(stdin, "%f", key);
				if (ADDNode(root, key, float_cmp, free_float) == FALSE)
				{
					fprintf(stdout, "The key %.2f already exist\n", *(float*)key);
					free(key);//If the key is already exists in the tree, will free the current key that we allocated.
				}
				else
				{
					fprintf(stdout, "%.2f was add to the tree\n", *(float*)key);
				}
				break;
			case 2:
				fprintf(stdout, "Tree postorder: ");
				tree_postorder(root, print_float);//Will print the tree in postorder method.
				fprintf(stdout, "\n");
				break;
			case 3:
				fprintf(stdout, "Enter the node that you want to search: ");
				fscanf(stdin, "%f", &search);
				temp = Search(root, &search, float_cmp);
				if (NULL == temp) fprintf(stdout, "the key that you search not exist in the tree.\n");
				else	fprintf(stdout, "The height of the tree is %d\n", FindKey(root, &search, float_cmp));


				break;
			case 4:
				fprintf(stdout, "How many nodes you want to search? ");
				fscanf(stdin, "%d", &k);
				if (check(root, k) == TRUE) {
					fprintf(stdout, "There are %d smallest elements in this tree: ", k);
					Kkey(root, print_float, k);
					fprintf(stdout, "\n");
				}
				else  fprintf(stdout, "There are no %d elements in this tree\n", k);
				break;
			default://Assuming that the input is correct!!,so no default.
				break;
			}
		} while (ch != 999);
		free_tree(&root, free_float);
	}
	else//if you chose Person.
	{
		do {
			ch = Menu();
			fprintf(stdout, "\n");
			switch (ch) //Switch case
			{
			case 1:
				if (NULL == root)
					root = create_tree();
				if (!(node = (Person*)malloc(sizeof(Person)))) //If allocation failed will free the tree and the keys.
				{
					fprintf(stderr, "Allocation failed.\n");
					free_tree(&root, free_Person);
				}
				node = CreatePerson(root,free_Person,&flag);
				if (flag == 0)
				{
					free_tree(&root, free_Person);
					exit(1);
				}
				if (ADDNode(root, node, Person_cmp, free_Person) == FALSE)
				{
					fprintf(stdout, "The id %d already exist\n", ((Person*)node->id));
					free_Person(node);//If the key is already exists in the tree, will free the current key that we allocated.
				}
				else
				{
					fprintf(stdout, "%d was add to the tree\n", ((Person*)node->id));
				}
				break;
			case 2:
				fprintf(stdout, "Tree postorder: ");
				tree_postorder(root, print_Person);//Will print the tree in postorder method.
				fprintf(stdout, "\n");
				break;
			case 3:
				fprintf(stdout, "Enter the node that you want to search: ");
				fscanf(stdin, "%d", &search);
				temp = Search(root, &search, Person_cmp);
				if (NULL == temp) fprintf(stdout, "the key that you search not exist in the tree.\n");
				else	fprintf(stdout, "The height of the tree is %d\n", FindKey(root, &search, Person_cmp));
				break;
			case 4:
				fprintf(stdout, "How many nodes you want to search? ");
				fscanf(stdin, "%d", &k);
				if (check(root, k) == TRUE) {
					fprintf(stdout, "There are %d smallest elements in this tree: ", k);
					Kkey(root, print_Person, k);
					fprintf(stdout, "\n");
				}
				else  fprintf(stdout, "There are no %d elements in this tree\n", k);
				break;
			default://Assuming that the input is correct!!,if no will go to default.
				break;
			}
		} while (ch != 999);
		free_tree(&root, free_Person);
	}

	return 0;
}