#ifndef _header
#define _header
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h> 
#define true 1
#define false 0
#define Max(a,b) ((a) > (b)? (a): (b)) 


typedef struct
{
	int key;
	float val;
} Data;

typedef struct TreeNode
{
	struct TreeNode* left;	 //left child
	struct TreeNode* right; //right child

	Data TreeNode_info;	 //info data in node
} TreeNode;

typedef struct ListNode
{
	struct ListNode* next;
	Data ListNode_info;	 //info data in node
} ListNode;

// TREE Handling prototypes
int treeHight(TreeNode*); // returns the hight of a given tree
float sum_tree(TreeNode*); //returns the sum of values on all tree nodes
void empty_tree(TreeNode**); // frees all the allocated memory and sets the root to NULL
TreeNode* create_tree_node(Data);
void insert_info_by_key(TreeNode**, TreeNode**, Data);
TreeNode* create_search_tree();

// LIST Handling prototypes
void empty_list(ListNode**);// frees all the allocated memory and sets the head to NULL
ListNode* create_list_node(Data);
void print_list(ListNode*);   // Prints the elements of the list from head to tail
ListNode* append_lists(ListNode*, ListNode*);

// LIST <-> TREE conversions
ListNode* tree_to_inorder_list(TreeNode*);
ListNode* tree_to_preorder_list(TreeNode*);

#endif 