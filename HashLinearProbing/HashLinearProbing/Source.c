#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<time.h>
#define CAPACITY 999983

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

int hashFunction(int key) { //Primitive hash function
	int index = key % CAPACITY;
	return index;
}

void addElement(int key, char data[], PAIR* table) { //ADDING an element to the table
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
	else { //if not a collision ha occured - Linear probing
		for (int i = 1; i < CAPACITY; i++) {
			if (table[(index + i) % CAPACITY].key == 0) {
				table[(index + i) % CAPACITY].key = key;
				strcpy(table[(index + i) % CAPACITY].data, data);
				//printf("Element %s inserted at index: %d\n", data, (index + i) % CAPACITY);
				return 0;
			}
			else if (table[(index + i) % CAPACITY].key == key) {
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
	if (table[index].key != -1) { //removing element if it matches the elemnt in the correct key
		table[index].key = 0;
		table[index].data[0] = '/0';
		//printf("Element removed from index: %d\n",index);
	}
	else//if not than send an error meaasage
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
		test[i].key = (rand() * rand()) % CAPACITY;
		strcpy(test[i].data, "Data\0");
	}
	return  0;
}

void main()//MAIN function
{
	double seconds, elapsed;
	time_t start, end;
	PAIR* table = initTable(&table);
	generator();
	//inserting elements
	int i = 0;
	start = clock();
	while (i < CAPACITY)
	{
		addElement(test[i].key, test[i].data, table);
		i++;
	}
	end = clock();
	double time_taken = (double)(end - start);
	seconds = time_taken / (double)(CLOCKS_PER_SEC);
	printf("%ld elements added in %g ticks / %g seconds. %d duplicates were not inserted.\n", CAPACITY, time_taken, seconds, duplicates);
	start = clock();
	i = 0;
	while (i < CAPACITY)
	{
		searchElement(test[i].key, table);
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
		removeElement(test[i].key, table);
		i++;
	}
	end = clock();
	time_taken = (double)(end - start);
	seconds = time_taken / (double)(CLOCKS_PER_SEC);
	printf("%ld elements removed in %g ticks / %g seconds.\n", CAPACITY, time_taken, seconds);
	return 0;
}