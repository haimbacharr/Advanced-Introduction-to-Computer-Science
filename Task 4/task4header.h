#ifndef _header
#define _header
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#define NAME 101
typedef struct tree_node* Ptree;//typedef for general struct.
typedef enum BOOL{FALSE,TRUE,BGR,SMLR} BOOL;

/*typedef for pointer to functions*/
typedef void (*DEL_FUNC)(void* a);
typedef void (*PNT_FUNC)(void* a);
typedef BOOL(*CMP_FUNC)(void* a, void* b);

/*General Functions*/
Ptree create_tree();//Function that initialize the root of the tree.
BOOL ADDNode(Ptree root, void* key, CMP_FUNC compare, DEL_FUNC del_func);/*Function that get the root of the tree,void*,pointer to PNT_FUNC,pointer to
CMP_FUNC and add the node to the given root. return TRUE(1) if the add success or FALSE(0) if not success.*/
void tree_postorder(Ptree root, PNT_FUNC Print);/*Function that get a root of a tree and point to PNT_FUNC and print the nodes in postorder.*/
int Menu();/*Function that show to the user the menu.*/
int FindKey(Ptree root, void* key, CMP_FUNC cmp);/*Function that get root,void* and pointer to CMP_FUNC,search in the tree if the key is already in the tree or not
and return the hight of the key in the tree.*/
BOOL check(Ptree root, int k);/*Function that get a tree and int number,and compare if the number is bigger than the number of nodes in the tree
return the answer in enum.*/
int Kkey(Ptree root, PNT_FUNC a, int k);/*Function that get root,pointer to PNT_FUNC and int number(k). and will print the k smallest nodes in the tree
in inorder method.*/
int counter(Ptree root);
/*Function that get a tree,and counts the amount of nodes in the tree and return the number.*/
Ptree Search(Ptree root, void* key, CMP_FUNC cmp);/*Function that get root of a tree ,void*, pointer to CMP_FUNC and return the pointer to the node.*/
void free_tree(Ptree *root, DEL_FUNC del);/*Function that get pointer to the root and pointer to DEL_FUNC and will free the whole tree.*/


#endif
