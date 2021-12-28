#include "head.h"

int main()
{
	TreeNode* inputTree = NULL;
	ListNode* preList = NULL, * inList = NULL;

	printf("\n getting the input tree");
	inputTree = create_search_tree(); // get the tree from user
	printf("\nhight of tree is %d\n", treeHight(inputTree)); // print hight
	printf("\nsum of values of tree is %f\n", sum_tree(inputTree));

	printf("\n printing input tree inorder");
	inList = tree_to_inorder_list(inputTree); // inorder traverse the tree
	print_list(inList);

	printf("\n printing input tree preorder");
	preList = tree_to_preorder_list(inputTree); // preorder traverse the tree
	print_list(preList);

	empty_tree(&inputTree);
	empty_list(&preList);
	empty_list(&inList);
	return 0;
}


