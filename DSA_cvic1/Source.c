#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

typedef struct node
{
	int value;
	struct node* left;
	struct node* right;
	struct node* parent;
	int leaf;
} NODE;

void main()
{
	//initialising base binary tree
	NODE* start = NULL;
	start = (NODE*)malloc(sizeof(NODE));
	start->left = (NODE*)malloc(sizeof(NODE));
	start->right = (NODE*)malloc(sizeof(NODE));
	start->right->right = (NODE*)malloc(sizeof(NODE));
	start->right->left = NULL;
	start->left->right = (NODE*)malloc(sizeof(NODE));
	start->left->left = (NODE*)malloc(sizeof(NODE));
	//setting base values
	start->value = 20;
	start->right->value = 21;
	start->left->value = 15;
	start->right->left = NULL;
	start->right->right->value = 26;
	start->left->left->value = 11;
	start->left->right->value = 17;
	start->leaf = start->right->leaf = start->left->leaf = 0;
	start->right->right->leaf = start->left->left->leaf = start->left->right->leaf = 1;

	return 0;
}
