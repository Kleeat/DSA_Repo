#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node
{
	int key;
	int height;
	struct node* left;
	struct node* right;
} NODE;

NODE* insertNode(NODE* node, int key);
NODE* newNode(int key);
NODE* leftRotate(NODE* x);
int getHeight(NODE* node);
int getBalance(NODE* node);

void main() {
	NODE* root = NULL;
	return 0;
}

// Return height for ptr
int getHeight(NODE* node) {
	if(node == NULL)
		return 0;
	else
		return node->height;
}

// Left rotate
NODE* leftRotate(NODE* x) {
	NODE* y = x->right;
	NODE* temp = y->left;

	y->left = x;
	x->right = temp;

	x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
	y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

	return y;
}

// Right rotate
NODE* rightRotate(NODE* x) {
	NODE* y = x->left;
	NODE* temp = y->right;

	y->right = x;
	x->left = temp;

	x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
	y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

	return y;
}

NODE* newNode(int key) {
	NODE* node = (NODE*)malloc(sizeof(NODE));
	node->height = 1;
	node->key = key;
	node->left = node->right = NULL;
	return &node;
}

// Returns teh balance factor for the node
int getBalance(NODE* node) {
	if (node == NULL)
		return 0;
	else
		return getHeight(node->left) - getHeight(node->right);
}

// Insert a new node
NODE* insertNode(NODE* node, int key){
	int balance;
	// Recursive function to traverse tree and find place to insert.
	if (node == NULL)
		return newNode(key);
	if (key > node->key)
		node->right = insertNode(node->right, key);
	else if (key < node->key)
		node->left = newNode(node->left, key);
	else
		return node;

	// Update the balance factor of visited nodes
	node->height = max(node->left->height, node->right->height) + 1;

	balance = getBalance(node);


	return 0;
}