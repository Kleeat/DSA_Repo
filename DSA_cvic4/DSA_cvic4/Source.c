#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define CAPACITY 20

typedef struct
{
	int value;
} PAIR;

PAIR* initTable(PAIR* table)//setting up the empty table
{
	table = (PAIR*)malloc(CAPACITY * sizeof(PAIR));
	for (int i = 0; i < CAPACITY; i++)
	{
		table[i].value = 0;
	}
	return table;
}

int hashFunction(int value)//Primitive hash function
{
	int key = value % CAPACITY;
	return key;
}

void addElement(int value, PAIR* table)//ADDING an element to the table
{
	int key = hashFunction(value);
	if (table[key].value == 0)//if an empty space can be found on the correct space insert element
	{
		table[key].value = value;
		printf("Element %d inserted at key: %d\n", value, key);
	}
	else//if not a collision ha occured, send error message
		printf("Hash collision ha occured for element %d !\n", value);
	return 0;
}

void removeElement(int value, PAIR* table)//REMOVE element from table
{
	int key = hashFunction(value);
	if (table[key].value == value)//removing element if it matches the elemnt in the correct key
	{
		table[key].value = 0;
		printf("Element %d removed from key: %d\n", value, key);
	}
	else//if not than send an error meaasage
		printf("Element %d is not in the table!\n", value);
	return 0;
}

void searchElement(int value, PAIR* table)//SEARCH element in table
{
	int key = hashFunction(value);
	if (table[key].value == value)
		printf("Element %d found at position %d\n", value, key);
	else
		printf("Element %d cannot be found!\n", value);
	return 0;
}

void main()//MAIN function
{
	PAIR* table = initTable(&table);
	addElement(9, table);
	addElement(29, table);
	addElement(16, table);
	addElement(23, table);
	removeElement(9, table);
	searchElement(9, table);
	searchElement(16, table);
	searchElement(23, table);
	return 0;
}