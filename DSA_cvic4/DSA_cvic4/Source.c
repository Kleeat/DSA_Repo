#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define CAPACITY 20

typedef struct
{
	int key;
	int value;
} PAIR;

PAIR* initTable(PAIR* table)
{
	table = (PAIR*)malloc(CAPACITY * sizeof(PAIR));
	for (int i = 0; i < CAPACITY; i++)
	{
		table[i].key = 0;
		table[i].value = 0;
	}
	return table;
}

void addElement(int key, int value)
{

	return 0;
}

void main()
{
	PAIR* table = initTable(&table);
	return 0;
}