#include "head.h"

int treeHight(TreeNode* tree) // returns the hight of a given tree
{
	int left_high, right_high;
	if (NULL == tree)//if the tree is empty.
		return -1;
	else {
		left_high = treeHight(tree->left);
		right_high = treeHight(tree->right);
		if (left_high > right_high) return (left_high + 1);
		else return (right_high + 1);//return the higher high of the tree.
	}
}



float sum_tree(TreeNode* tree) //returns the sum of values on all tree nodes
{
	if (tree == NULL)
		return 0;
	return tree->TreeNode_info.val + sum_tree(tree->left) + sum_tree(tree->right);
}



void empty_tree(TreeNode** root)   // frees all the allocated memory and sets the root to NULL
{
	if (NULL == *root) return;
	empty_tree(&(*root)->left);
	empty_tree(&(*root)->right);
	if ((!(*root)->left) && (!(*root)->right))//if the node is a leaf
	{
		free(*root);
		*root = NULL;//set *root to be null.
	}
}



TreeNode* create_tree_node(Data data)
{
	TreeNode* new_node;
	new_node = (TreeNode*)malloc(sizeof(TreeNode));//allocating memory to the new node.
	if (NULL == new_node)//if allocation failed.
	{
		fprintf(stderr, "Allocation has been failed.\n");
	}
	new_node->left = NULL;//left child NULL
	new_node->right = NULL;//right child NULL
	new_node->TreeNode_info.key = data.key;//getting the data.key.
	new_node->TreeNode_info.val = data.val;//getting the data.value.
	return new_node;//return the node.
}




void insert_info_by_key(TreeNode** root, TreeNode** root_original, Data data)
{
	static int times;
	if (!(*root))
	{
		*root = create_tree_node(data);			//get new node for tree
		if (times == 0)
			*root_original = *root;
		if (*root == NULL)
		{
			fprintf(stderr,"Allocation tree node failed");
			empty_tree(root_original);                    /*deleting the whole tree,since root_original is a pointer to the whole tree*/
			exit(1);
		}
	}
	else
	{
		if (data.key < (*root)->TreeNode_info.key)		//if the new node's key is smaller			
			insert_info_by_key(&((*root)->left), root_original, data); 	//call insert_node with the left child
		else
			insert_info_by_key(&((*root)->right), root_original, data);
	}
	times++;
}



TreeNode* create_search_tree()
{
	Data infoNode;
	char in_char;
	TreeNode* tree = NULL;

	do
	{
		printf("\n Do you want to enter another node? (y/n) :");
		in_char = _getche();
		if (in_char == 'y')
		{
			fprintf(stdout,"\nEnter key and value: ");
			scanf("%d %f", &(infoNode.key), &(infoNode.val));
			insert_info_by_key(&tree, &tree, infoNode);     /*sending the same parameter twice for deleting a whole tree*/
		}
	} while (in_char == 'y');
	return tree;
}


void empty_list(ListNode** head)   // frees all the allocated memory and sets the head to NULL
{
	if ((*head) == NULL)
		return;
	empty_list(&((*head)->next));
	free(*head);
	*head = NULL;
}


ListNode* create_list_node(Data data)
{
	ListNode* new_node = (ListNode*)malloc(sizeof(ListNode));	//allocate new node in heap

	if (new_node == NULL)
		return NULL;
	else
	{
		new_node->ListNode_info = data;
		new_node->next = NULL;
		return new_node;									//returns intialized node
	}
}



void print_list(ListNode* head)
{
	if (head == NULL)
	{
		printf("\nThe list is EMPTY\n");
		return;
	}
	printf("\nThe list is:\n");
	while (head != NULL)
	{
		printf("\n (key=%d , val=%.01f)", head->ListNode_info.key, head->ListNode_info.val);
		head = head->next;
	}
	printf("\n\n");
}



ListNode* append_lists(ListNode* firstList, ListNode* secondList)
{
	ListNode* res;

	res = secondList;   /*if firstList is empty*/
	if (firstList)
	{
		res = firstList;
		while (firstList->next)
			firstList = firstList->next;
		firstList->next = secondList;
	}
	return res;
}


ListNode* tree_to_inorder_list(TreeNode* root)
{
	ListNode* curr = NULL, * left = NULL, * right = NULL;
	if (root)
	{
		left = tree_to_inorder_list(root->left);
		right = tree_to_inorder_list(root->right);
		curr = create_list_node(root->TreeNode_info);
		curr->next = right;
		left = append_lists(left, curr);
	}
	return left;
}

ListNode* tree_to_preorder_list(TreeNode* root)//function that print in pre_order in recrusive way.
{
	ListNode* curr = NULL, * left = NULL, * right = NULL;
	if (root)
	{
		left = tree_to_preorder_list(root->left);
		right = tree_to_preorder_list(root->right);
		curr = create_list_node(root->TreeNode_info);
		left = append_lists(left, right);
		curr->next = left;
	}
	return curr;
}


