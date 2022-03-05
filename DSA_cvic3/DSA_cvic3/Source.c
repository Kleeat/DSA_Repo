#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 50

typedef struct node
{
	char symbol;
	int freq;
	struct node* left;
	struct node* right;
} NODE;

typedef struct heap
{
	int size;
	struct node* array;
} HEAP;

void eolrem(char temp[]) {
	int i;
	for ( i = 0; i < MAX -1; i++)
	{
		if (temp[i] == '\n') {
			break;
		}
	}
	temp[i] = '\0';
	return 0;
}

void heapMaker(char orig[], HEAP* minHeap) 
{
	char temp[MAX] = {'\0'};
	int freq = 0, i, j = 0, k;
	int oLength;
	oLength = strlen(orig);
	for ( i = 0; i < oLength; i++)
	{
		if (strchr(temp, orig[i]) == NULL) 
		{
			temp[j] = orig[i];
			freq = 0;
			for ( k = 0; k < oLength; k++)
			{
				if (orig[k] == orig[i])
					freq++;
			}
			minHeap->array[j].freq = freq;
			minHeap->array[j].symbol = orig[i];
			minHeap->size++;
			j++;
		}
	}
	return 0;
}

void heapPrint(HEAP minHeap)//DEBUG
{
	int i;
	for (i = 0; i < minHeap.size; i++)
	{
		printf("%c : %d\n", minHeap.array[i].symbol, minHeap.array[i].freq);
	}
	return 0;
}

void main() {
	char temp[MAX];
	printf("Type in your message: ");
	fgets(temp, MAX, stdin);
	eolrem(&temp);
	HEAP minHeap;
	minHeap.array = (NODE*)malloc(MAX * sizeof(NODE));
	minHeap.size = 0;
	heapMaker(temp, &minHeap);
	heapPrint(minHeap);

	return 0;
}