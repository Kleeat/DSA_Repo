#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define CAPACITY 1000000

typedef struct node
{
	int key;
	int height;
	struct node* left;
	struct node* right;
} NODE;

int test[CAPACITY];
int duplicates;

NODE* insertNode(NODE* node, int key);
NODE* searchNode(NODE* node, int key);
NODE* deleteNode(NODE* node, int key);
NODE* newNode(int key);
NODE* leftRotate(NODE* x);
int getHeight(NODE* node);
int getBalance(NODE* node);

void generator() {//generates a table of pseudorandom keys
	int j = 1;
	for (int i = 0; i < CAPACITY; i++) {
		test[i] = (rand() * rand()) + rand();
	}
	return  0;
}

void main() {
	NODE* root = NULL;
	double seconds, elapsed;
	time_t start, end;
	generator();
	//inserting elements
	int i = 0;
	start = clock();
	while (i < CAPACITY)
	{
		root = insertNode(root, test[i]);
		i++;
	}
	end = clock();
	double time_taken = (double)(end - start);
	seconds = time_taken / (double)(CLOCKS_PER_SEC);
	printf("%ld nodes added in %g ticks / %g seconds. %d duplicates were not inserted.\n", CAPACITY, time_taken, seconds, duplicates);
	start = clock();
	i = 0;
	while (i < CAPACITY)
	{
		searchNode(root, test[i]);
		i++;
	}
	end = clock();
	time_taken = (double)(end - start);
	seconds = time_taken / (double)(CLOCKS_PER_SEC);
	printf("%ld elements searched in %g ticks / %g seconds.\n", CAPACITY, time_taken, seconds);
	start = clock();
	i = 0;
	while (i < CAPACITY)
	{
		root = deleteNode(root, test[i]);
		i++;
	}
	end = clock();
	time_taken = (double)(end - start);
	seconds = time_taken / (double)(CLOCKS_PER_SEC);
	printf("%ld elements removed in %g ticks / %g seconds.\n", CAPACITY, time_taken, seconds);
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
	node->left = NULL;
	node->right = NULL;
	return (node);
}

// Returns the balance factor for the node
int getBalance(NODE* node) {
	if (node == NULL)
		return 0;
	else
		return getHeight(node->left) - getHeight(node->right);
}

//Returns inorder successor
NODE* getSuccessor(NODE* node) {
	NODE* temp = node;

	while (temp->left != NULL)
		temp = temp->left;

	return temp;
}

// Insert a new node
NODE* insertNode(NODE* node, int key){
	int balance;
	// Recursive function to traverse tree and find place to insert
	if (node == NULL)
		return (newNode(key));

	if (key > node->key)
		node->right = insertNode(node->right, key);
	else if (key < node->key)
		node->left = insertNode(node->left, key);
	else {
		return node;
		duplicates++;
	}
		

	// Update the balance factor of visited nodes
	node->height = max(getHeight(node->left), getHeight(node->right)) + 1;

	balance = getBalance(node);
	if (balance > 1 && key < node->left->key)
		return rightRotate(node);

	if (balance < -1 && key > node->right->key)
		return leftRotate(node);

	if (balance > 1 && key > node->left->key) {
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}

	if (balance < -1 && key < node->right->key) {
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}

	return node;
}

//Search for a node
NODE* searchNode(NODE* node, int key) {
	if (node == NULL)
		return node;

	if (key < node->key)
		node->left = searchNode(node->left, key);

	else if (key > node->key)
		node->right = searchNode(node->right, key);
	else
		return node;
}

// Delete a node
NODE* deleteNode(NODE* node, int key) {
	// Recursive function to traverse tree and find the node to delete
	NODE* temp;
	if (node == NULL)
		return node;

	if (key < node->key)
		node->left = deleteNode(node->left, key);

	else if (key > node->key)
		node->right = deleteNode(node->right, key);

	//We arrived to the node to be deleted
	else {
		//If node has 1 or 0 children
		if ((node->left == NULL) || (node->right == NULL)) {
			if (node->left != NULL) {
				temp = node->left;
				*node = *temp;
			}
			else if (node->right != NULL) {
				temp = node->right;
				*node = *temp;
			}
			else {
				temp = node;
				node = NULL;
			}
			free(temp);
		}
		//if node has 2 children
		else {
			temp = getSuccessor(node->right);

			node->key = temp->key;

			node->right = deleteNode(node->right, temp->key);
		}
	}

	if (node == NULL)
		return node;

	// Update the balance factor of visited nodes
	node->height = 1 + max(getHeight(node->left),
		getHeight(node->right));

	int balance = getBalance(node);
	if (balance > 1 && getBalance(node->left) >= 0)
		return rightRotate(node);

	if (balance > 1 && getBalance(node->left) < 0) {
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}

	if (balance < -1 && getBalance(node->right) <= 0)
		return leftRotate(node);

	if (balance < -1 && getBalance(node->right) > 0) {
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}

	return node;
}