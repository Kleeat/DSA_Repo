#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 50
#define MAXTH 6

typedef struct node //huffman tree nodes
{
	char symbol;
	int freq;
	struct node* left;
	struct node* right;
} NODE;

typedef struct heap //structure for priority queue
{
	int size;
	struct node** array;
} HEAP;

void eolrem(char temp[]) //removes the end of line
{
	temp[strlen(temp) - 1] = '\0';
	return 0;
}

NODE* getLeaf(NODE* node)//returns 1 if node is a leaf
{
	if (node->left == NULL && node->right == NULL)
		return 1;
	else
		return 0;
}

void swap(NODE* node1, NODE* node2)//swaps out two nodes
{
	NODE temp;
	temp = *node1;
	*node1 = *node2;
	*node2 = temp;
	return 0;
}

void heapPrint(HEAP minHeap)//DEBUG
{
	int i;
	for (i = 0; i < minHeap.size; i++)
	{
		printf("%c : %d\n", minHeap.array[i]->symbol, minHeap.array[i]->freq);
	}
	return 0;
}

void heapify(HEAP* minHeap)//heapifying the array
{
	int i = minHeap->size / 2 - 1;
	int r;
	int l;
	int smallest;
	if (minHeap->size == 1)
	{
		return 0;
	}
	for (i; i >= 0; i--)
	{
		smallest = i;
		r = 2 * i + 1;
		l = 2 * i + 2;
		if (l < minHeap->size && minHeap->array[l]->freq < minHeap->array[i]->freq)
			smallest = l;
		if (r < minHeap->size && minHeap->array[r]->freq < minHeap->array[i]->freq)
			smallest = r;
		swap(minHeap->array[smallest], minHeap->array[i]);
	}
	return 0;
}

void heapMaker(char orig[], HEAP* minHeap) //extracts unique characters and their frequiencies and saves them in nodes
{
	char temp[MAX] = {'\0'};
	int freq = 0, i, j = 0, k;
	int oLength;
	oLength = strlen(orig);
	for ( i = 0; i < oLength; i++)
	{
		if (strchr(temp, orig[i]) == NULL) 
		{
			temp[j] = orig[i];//temp stores unique characters
			freq = 0;
			for ( k = 0; k < oLength; k++)
			{
				if (orig[k] == orig[i])
					freq++;
			}
			minHeap->array[j] = (NODE*)malloc(sizeof(NODE));//creating the nodes
			minHeap->array[j]->freq = freq;
			minHeap->array[j]->symbol = orig[i];
			minHeap->array[j]->left = minHeap->array[j]->right = NULL;
			minHeap->size++;
			heapify(minHeap);
			j++;
		}
	}
	return 0;
}

NODE* extractMin(HEAP* minHeap)//extracts the minimum node from the priority queue and returns it
{
	NODE* temp = minHeap->array[minHeap->size - 1];
	swap(minHeap->array[0], minHeap->array[minHeap->size - 1]);
	minHeap->size--;
	heapify(minHeap);
	return temp;
}

NODE* huffTreeMaker(HEAP* minHeap)//creates the huffman tree
{
	NODE* temp;
	while (minHeap->size > 1)//building nodes and adding them to the queue until only the root is left
	{
		temp = (NODE*)malloc(sizeof(NODE));
		temp->left = extractMin(minHeap);
		temp->right = extractMin(minHeap);
		temp->freq = temp->left->freq + temp->right->freq;
		minHeap->array[minHeap->size] = temp;
		minHeap->size++;
	}
	return minHeap->array[0];//return the root node of the tree
}

void printTree(NODE* root, int code[], int pos)//recursive function for exploring and printing the tree.
{
	int i;
	if (root->left != NULL)
	{
		code[pos] = 0;
		printTree(root->left, code, pos + 1);
	}
	if (root->right != NULL)
	{
		code[pos] = 1;
		printTree(root->right, code, pos + 1);
	}
	if (getLeaf(root) == 1) {
		printf("  %c | ", root->symbol);
		for ( i = 0; i < pos; i++)
			printf("%d", code[i]);
		printf("\n");
	}
}

void main() //MAIN function
{
	char temp[MAX];
	printf("Type in your message: ");
	fgets(temp, MAX, stdin);
	eolrem(&temp);
	HEAP minHeap;
	NODE* root;
	minHeap.array = (NODE**)malloc(MAX * sizeof(NODE*));
	minHeap.size = 0;
	heapMaker(temp, &minHeap);
	//heapPrint(minHeap);
	root = huffTreeMaker(&minHeap);
	int code[MAXTH];
	int pos = 0;
	printf("Huffman codes:\n");
	printTree(root, code, pos);

	return 0;
}