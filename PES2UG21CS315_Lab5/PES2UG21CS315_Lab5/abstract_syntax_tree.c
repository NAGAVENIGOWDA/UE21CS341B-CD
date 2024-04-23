#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abstract_syntax_tree.h"

expression_node* init_exp_node(char* val, expression_node* left, expression_node* right)
{
	// function to allocate memory for an AST node and set the left and right children of the nodes
	expression_node* newNode = (expression_node*)malloc(sizeof(expression_node*));
	newNode->left = left;
	newNode->right = right;
	newNode->val = val;
}

void display_exp_tree(expression_node* exp_node)
{
	// traversing the AST in preorder and displaying the nodes
	if (exp_node == NULL)return;

	printf("%s ", exp_node->val);
	display_exp_tree(exp_node->left);
	display_exp_tree(exp_node->right);
	
}
