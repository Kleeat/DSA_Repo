#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define CAPACITY 20

typedef struct
{
	int key;
	char data[10];
} PAIR;

PAIR* initTable(PAIR* table)//setting up the empty table
{
	table = (PAIR*)malloc(CAPACITY * sizeof(PAIR));
	for (int i = 0; i < CAPACITY; i++)
	{
		table[i].key = 0;
		table[i].data[0] = '/0';
	}
	return table;
}

int hashFunction(int key)//Primitive hash function
{
	int index = key % CAPACITY;
	return index;
}

void addElement(int key, char data[], PAIR* table)//ADDING an element to the table
{
	int index = hashFunction(key);
	if (table[index].key == 0)//if an empty space can be found on the correct index insert element
	{
		table[index].key = key;
		strcpy(table[index].data, data);
		printf("Element %s inserted at index: %d\n",data , index);
	}
	else if (table[index].key == key) {
		printf("Element %s already in table at index %d\n", data, index);
		return 0;
	}
	else //if not a collision ha occured - Linear probing
	{
		for (int i = 1; i < CAPACITY; i++)
		{
			if (table[(index + i) % CAPACITY].key == 0) {
				table[(index + i) % CAPACITY].key = key;
				strcpy(table[(index + i) % CAPACITY].data, data);
				printf("Element %s inserted at index: %d\n", data, (index + i) % CAPACITY);
				return 0;
			}
			else if (table[(index + i) % CAPACITY].key == key) {
				printf("Element %s already in table at index %d\n", data, (index + i) % CAPACITY);
				return 0;
			}
		}
		printf("There is no empty space in the table for %s\n", data);
	}
	return 0;
}

void removeElement(int key, PAIR* table)//REMOVE element from table
{
	int index = searchElement(key, table);
	if (table[index].key != -1)//removing element if it matches the elemnt in the correct key
	{
		table[index].key = 0;
		table[index].data[0] = '/0';
		printf("Element removed from index: %d\n",index);
	}
	else//if not than send an error meaasage
		printf("Element is not in the table!\n");
	return 0;
}

int searchElement(int key, PAIR* table)//SEARCH element in table, returns index in table
{
	int index = hashFunction(key);
	if (table[index].key == key) {
		printf("Element found at index %d\n", index);
		return index;
	}
	else if (table[index].key == 0) {
		printf("Element not in table\n");
		return -1;
	}
	else {
		for (int i = 1; i < CAPACITY; i++)
		{
			if (table[(index + i) % CAPACITY].key == key) {
				printf("Element found at index %d\n", (index + i) % CAPACITY);
				return (index + i) % CAPACITY;
			}
		}
		printf("Element not in table\n");
	}
	return -1;
}

void main()//MAIN function
{
	PAIR* table = initTable(&table);
	addElement(2,"myData", table);
	addElement(22, "myData2", table);
	searchElement(22, table);
	searchElement(2, table);
	searchElement(24, table);
	removeElement(22, table);
	searchElement(22, table);
	return 0;
}