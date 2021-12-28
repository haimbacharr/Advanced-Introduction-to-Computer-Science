#include "task4header.h"
typedef struct tree_node
/*A general struct*/
{
	void *key;
	struct tree_node* left;
	struct tree_node* right;
}tree;

Ptree create_tree()
/*Function that create the first root of a tree, and return him.*/
{
	Ptree root;
	if (!(root = (Ptree)malloc(sizeof(tree)))) //if allocation failed, will free all the keys,and nodes in tree.
	{ 
		//ERR_msg("allocation failed.\n");
	}
	root->key = NULL;
	root->left = NULL;
	root->right = NULL;
	return root;
}

BOOL ADDNode(Ptree root, void* key, CMP_FUNC compare, DEL_FUNC del_func)
/*Function that get a tree,key,function to compare ,and function to delete, and return an enum answer.*/
{
	Ptree temp;
	if (NULL == root->key) {
		root->key = key;
	
		return TRUE;
	}
	if (compare(root->key, key) == TRUE) //If the key is already in the TREE,return FALSE.
		return FALSE;

	if (compare(root->key, key) == SMLR)
	{
		if (NULL == root->left) {
			if (!(temp = (Ptree)malloc(sizeof(tree))))//If allocation failed, will free all the keys,and nodes in tree.
			{
				fprintf(stderr, "Allocation failed.\n");
				free_tree(&root, del_func);
			}
			root->left = temp;
			temp->key = NULL;
			temp->left = NULL;
			temp->right = NULL;
			ADDNode(root->left, key, compare, del_func);
		}
		else
			if (ADDNode(root->left, key, compare, del_func) == FALSE) return FALSE;
	}
	if (compare(root->key, key) == BGR) {
		if (NULL == root->right) {
			if (!(temp = (Ptree)malloc(sizeof(tree))))//If allocation failed, will free all the keys,and nodes in tree.
			{
				fprintf(stderr, "Allocation failed.\n");
				free_tree(&root, del_func);
			}
			root->right = temp;
			temp->key = NULL;
			temp->left = NULL;
			temp->right = NULL;
			ADDNode(root->right, key, compare, del_func);
		}
		else
			if (ADDNode(root->right, key, compare, del_func) == FALSE) return FALSE;
	}
}

void tree_postorder(Ptree root, PNT_FUNC Print)
{
	if (NULL == root) return;
	tree_postorder(root->left,Print);
	tree_postorder(root->right, Print);
	Print(root->key);
}

Ptree Search(Ptree root, void* key,CMP_FUNC cmp)
{
	// Base Cases: root is null or key is present at root 
	if (root == NULL || cmp(root->key, key)==TRUE)
		return root;

	// Key is greater than root's key 
	if (cmp(root->key, key)==BGR)
		return Search(root->right, key,cmp);

	// Key is smaller than root's key 
	return Search(root->left, key,cmp);
}

int FindKey(Ptree root, void* key, CMP_FUNC cmp)
{
	if (root == NULL) //if the current tree is empty.
		return -1;
	if (cmp(root->key, key) == SMLR) {
		
		return 1 + FindKey(root->left, key, cmp);
	}
	if (cmp(root->key, key) == BGR) {

		return 1 + FindKey(root->right, key, cmp);
	}
	return 0;


}

BOOL check(Ptree root, int k)
/*Function that get a tree and int number,and compare if the number is bigger than the number of nodes in the tree
return the answer in enum.*/
{
	if (counter(root) < k) return FALSE;
	return TRUE;
}

int counter(Ptree root)
/*Function that get a tree,and counts the amount of nodes in the tree and return the number.*/
{
	if (NULL == root) return 0;
	{
		return (1 + counter(root->left) + counter(root->right));
	}
}


int Kkey(Ptree root, PNT_FUNC a, int k)
{
	if (NULL == root) return k;
	k = Kkey(root->left, a, k);
	if (k > 0) {
		a(root->key);
		k--;
	}
	k = Kkey(root->right, a, k);
}


int Menu()
{
	int ch;
	fprintf(stdout, "[1] \t\tAdding node to the tree\n");
	fprintf(stdout, "[2] \t\tPrinting the tree in post order\n");
	fprintf(stdout, "[3] \t\tFinding the Hight of a given node in the tree\n");
	fprintf(stdout, "[4] \t\tPrinting the k lowest keys in the tree\n");
	fprintf(stdout, "Please choose a number from the menu,999 to stop: ");
	fscanf(stdin, "%d", &ch);
	return ch;
}

void free_tree(Ptree* root, DEL_FUNC del_func)
/*Function that get a tree,and function to delete
free all keys and nodes in tree that we allocated  via specific function(del_func).*/
{
	if (*root == NULL)
		return;
	free_tree(&((*root)->left), del_func);
	free_tree(&((*root)->right), del_func);
	del_func((*root)->key);
	free(*root);
	*root = NULL;
}

