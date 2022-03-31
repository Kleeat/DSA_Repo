#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<time.h>
#define CAPACITY 20

typedef struct {
	int key;
	char data[10];
} PAIR;

int duplicates;
PAIR test[CAPACITY];

PAIR* initTable(PAIR* table) { //setting up the empty table
	table = (PAIR*)malloc(CAPACITY * sizeof(PAIR));
	for (int i = 0; i < CAPACITY; i++) {
		table[i].key = 0;
		table[i].data[0] = '/0';
	}
	return table;
}

//Primitive hash function
int hashFunction(int key) { 
	int index = key % CAPACITY;
	return index;
}

//ADDING an element to the table
void addElement(int key, char data[], PAIR* table) { 
	int index = hashFunction(key);
	if (table[index].key == 0) { //if an empty space can be found on the correct index insert element
		table[index].key = key;
		strcpy(table[index].data, data);
		//printf("Element %s inserted at index: %d\n",data , index);
	}
	else if (table[index].key == key) {
		//printf("Element %s already in table at index %d\n", data, index);
		duplicates++;
		return 0;
	}

	//if not a collision ha occured - Linear probing
	else { 
		for (int i = 1; i < CAPACITY; i++) {
			index = (index + 1) % CAPACITY;
			if (table[index].key == 0) {
				table[index].key = key;
				strcpy(table[index].data, data);
				//printf("Element %s inserted at index: %d\n", data, (index + i) % CAPACITY);
				return 0;
			}
			else if (table[index].key == key) {
				//printf("Element %s already in table at index %d\n", data, (index + i) % CAPACITY);
				return 0;
			}
		}
		//printf("There is no empty space in the table for %s\n", data);
	}
	return 0;
}

void removeElement(int key, PAIR* table)//REMOVE element from table
{
	int index = searchElement(key, table);
		//removing element if it matches the element in the correct key
	if (table[index].key != -1) { 
		table[index].key = 0;
		table[index].data[0] = '/0';
		//printf("Element removed from index: %d\n",index);
	}
	//if not than send an error message
	else
		//printf("Element is not in the table!\n");
	return 0;
}

int searchElement(int key, PAIR* table)//SEARCH element in table, returns index in table
{
	int index = hashFunction(key);
	if (table[index].key == key) {
		//printf("Element found at index %d\n", index);
		return index;
	}
	else if (table[index].key == 0) {
		//printf("Element not in table\n");
		return -1;
	}
	else {
		for (int i = 1; i < CAPACITY; i++) {
			if (table[(index + i) % CAPACITY].key == key) {
				//printf("Element found at index %d\n", (index + i) % CAPACITY);
				return (index + i) % CAPACITY;
			}
		}
		//printf("Element not in table\n");
	}
	return -1;
}

void generator() {//generates a table of pseudorandom keys and "data"
	int j = 1;
	for (int i = 0; i < CAPACITY; i++) {
		test[i].key = rand() % (2*CAPACITY);
		strcpy(test[i].data, "Data\0");
	}
	return  0;
}

void writeOut(PAIR* table) {
	for (int i = 0; i < CAPACITY; i++)
	{
		printf("%d, ", table[i].key);
	}
}

void main()//MAIN function
{
	double seconds, elapsed;
	time_t start, end;
	PAIR* table = initTable(&table);
	generator();
	//inserting elements
	int i = 0;
	while (i < CAPACITY)
	{
		addElement(test[i].key, test[i].data, table);
		i++;
	}
	printf("After insert:\n");
	writeOut(table);
	i = 0;
	while (i < CAPACITY)
	{
		searchElement(test[i].key, table);
		i++;
	}
	i = 0;
	while (i < CAPACITY / 2)
	{
		removeElement(test[i].key, table);
		i++;
	}
	printf("\nAfter delete:\n");
	writeOut(table);
	return 0;
}