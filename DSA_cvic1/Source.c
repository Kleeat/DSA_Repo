#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node
{
	int value;
	struct node* left;
	struct node* right;
	struct node* parent;
	int leaf;
} NODE;

void insert(NODE* root);
void insertNode(NODE* root, int value);
void printNodes(NODE* root);

void main()
{
	//initialising base node
	NODE* root = NULL;
	root = (NODE*)malloc(sizeof(NODE));
	root->value = 20;
	root->left = root->right = NULL;
	root->leaf = 1;
	root->parent = NULL;
	//adding base nodes
	insertNode(root, 15);
	insertNode(root, 17);
	insertNode(root, 11);
	insertNode(root, 21);
	insertNode(root, 26);
	insert(root);
	insert(root);
	printNodes(root);
	return 0;
}

void insert(NODE* root)//user guided insert
{
	int value;
	//fetching node value
	printf("Enter node value: ");
	scanf("%d", &value);
	insertNode(root, value);
	printf("Node successfully inserted.\n");
	return 0;
}

void insertNode(NODE* root, int value)//actual insert based on acquired value
{
	NODE* akt = root;
	NODE* parent = NULL;
	//traversing tree
	while (akt != NULL)
	{
		if (akt->value == value)
		{
			printf("Node already exists!\n");
			return 0;
		}
		else if (akt->value < value)
		{
			parent = akt;
			akt = akt->right;
		}	
		else
		{
			parent = akt;
			akt = akt->left;
		}
	}
	//inserting node
	akt = (NODE*)malloc(sizeof(NODE));
	akt->value = value;
	akt->left = akt->right = NULL;
	akt->leaf = 1;
	akt->parent = parent;
	akt->parent->leaf = 0;
	if (akt->parent->value < value)
		akt->parent->right = akt;
	else
		akt->parent->left = akt;
	return 0;
}

void printNodes(NODE* root)
{
	NODE* akt = root;
	//printing algorithm
	do
	{
		printf(" %d;", akt->value);
		if (akt->leaf == 1)
		{
			if (akt == root)
				return;
			if (akt->value < akt->parent->value)//BT2
			{
				while (akt->value < akt->parent->value) {
					akt = akt->parent;
					if (akt == root)
						return;
				}
			}
			if (akt->value > akt->parent->value)//BT1
			{
				do {
					akt = akt->parent;
				} while (akt->left == NULL);
				akt = akt->left;
				continue;
			}
		}
		if (akt->right != NULL)//branch right
		{
			akt = akt->right;
			continue;
		}
		else//branch left
		{
			akt = akt->left;
			continue;
		}
		
	} while (akt != root);
	return 0;
}