#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define CAPACITY 1000000

typedef struct node
{
	int key;
	struct node* left;
	struct node* right;
} NODE;

int test[CAPACITY];
int duplicates;

NODE* insertNode(NODE* node, int key);
NODE* searchNode(NODE* node, int key);
NODE* deleteNode(NODE* node, int key);
NODE* splayNode(NODE* node, int key);
NODE* newNode(int key);
NODE* leftRotate(NODE* x);
NODE* rightRotate(NODE* x);

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

// Left rotate
NODE* leftRotate(NODE* x) {
	NODE* y = x->right;
	NODE* temp = y->left;

	y->left = x;
	x->right = temp;

	return y;
}

// Right rotate
NODE* rightRotate(NODE* x) {
	NODE* y = x->left;
	NODE* temp = y->right;

	y->right = x;
	x->left = temp;

	return y;
}

// Splaying node to root
NODE* splayNode(NODE* node, int key) {
	//if key is at node or node is NULL
	if (node == NULL || node->key == key)
		return node;

	// If key is in right subtree
	if (node->key < key) 
	{
		//if left subtree doesn't exist return node
		if (node->right == NULL) return node;

		// Zag-Zag
		if (node->right->key < key)
		{
			// Splay key to the grandparent of root
			node->right->right = splay(node->right->right, key);
			node = leftRotate(node);
		}
		else if (node->right->key > key)// Zag-Zig
		{
			// Splay key to the grandparent of root
			node->right->left = splayNode(node->right->left, key);

			if (node->right->left != NULL)
				node->right = rightRotate(node->right);
		}

		// Do second rotation for root
		if (node->right == NULL)
			return node;
		else
			return leftRotate(node);
	}
	//else key is in the left subtree
	else {
		//if left subtree doesn't exist return node
		if (node->left == NULL) return node;

		if (node->left->key > key)//Zig-Zig
		{
			// Splay key to the grandparent of root
			node->left->left = splayNode(node->left->left, key);
			node = rightRotate(node);
		}
		else if (node->left->key < key) // Zig-Zag
		{
			// Splay key to the grandparent of root
			node->left->right = splayNode(node->left->right, key);

			if (node->left->right != NULL)
				node->left = leftRotate(node->left);
		}
		// Do second rotation for root Zig
		if (node->left == NULL)
			return node;
		else
			return rightRotate(node);
	}
}

NODE* newNode(int key) {
	NODE* node = (NODE*)malloc(sizeof(NODE));
	node->key = key;
	node->left = NULL;
	node->right = NULL;
	return (node);
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
	NODE* temp;
	if (node == NULL)
		return (newNode(key));
	temp = node;
	while (temp != NULL) {
		if (temp->key == key) {
			duplicates++;
			break;
		}
		if (temp->key < key)
			temp = temp->right;
		else
			temp = temp->left;
	}
	temp = newNode(key);
	return splayNode(node, key);

}

//Search for a node
NODE* searchNode(NODE* node, int key) {
	NODE* temp;
	if (node == NULL)
		return NULL;
	temp = node;
	while (temp != NULL) {
		if (temp->key == key) {
			break;
		}
		if (temp->key < key && temp->right != NULL)
			temp = temp->right;
		else if (temp->key > key && temp->left != NULL)
			temp = temp->left;
		else
			break;
	}
	return splayNode(node, temp->key);
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

	

	return node;
}