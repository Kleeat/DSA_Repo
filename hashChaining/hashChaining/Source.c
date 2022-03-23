#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#define CAPACITY 999983
#define PRIME 999983

typedef struct {
	int key;
	char data[10];
} PAIR;

PAIR test[CAPACITY];
int duplicates;

PAIR* initTable(PAIR* table) { //setting up the empty table
	table = (PAIR*)malloc(CAPACITY * sizeof(PAIR));
	for (int i = 0; i < CAPACITY; i++) {
		table[i].key = 0;
		table[i].data[0] = '/0';
	}
	return table;
}

int hashFunction1(int key) { //Primitive hash function
	int index = key % CAPACITY;
	return index;
}

int hashFunction2(int key) { //Second hashing function
	int index = PRIME - (key % PRIME);
	return index;
}

void addElement(int key, char data[], PAIR* table) { //ADDING an element to the table
	long index = hashFunction1(key);
	if (table[index].key == 0) { //if an empty space can be found on the correct index insert element
		table[index].key = key;
		strcpy(table[index].data, data);
		//printf("Element %d inserted at index: %d\n",key , index);
	}
	else if (table[index].key == key) {
		//printf("Element %s already in table at index %d\n", data, index);
		duplicates++;
		return 0;
	}

	//if not a collision ha occured - DoubleHashing
	else { 
		for (int i = 1; i <= CAPACITY; i++) {
			index = (hashFunction1(key) + i * hashFunction2(key)) % CAPACITY; //Double hashing
			if (table[index].key == 0) {
				table[index].key = key;
				strcpy(table[index].data, data);
				//printf("Element %d inserted at index: %d\n", key, index);
				return 0;
			}
			else if (table[index].key == key) {
				//printf("Element %s already in table at index %d\n", data, index);
				return 0;
			}
		}
		//printf("There is no empty space in the table for %d\n", key);
	}
	return 0;
}

int searchElement(int key, PAIR* table)//SEARCH element in table, returns index in table
{
	long index = hashFunction1(key);
	if (table[index].key == key) {//check if element is at the correct index
		//printf("Element found at index %d\n", index);
		return index;
	}
	else if (table[index].key == 0) {//if the space at the index is empty element cannot be found
		//printf("Element not in table\n");
		return -1;
	}
	else {
		for (int i = 1; i < CAPACITY; i++) {
			index = (hashFunction1(key) + i * hashFunction2(key)) % CAPACITY; //Double hashing
			if (table[index].key == key) {
				//printf("Element found at index %d\n", index);
				return index;
			}
		}
		//printf("Element not in table\n");
	}
	return -1;
}

void removeElement(int key, PAIR* table)//REMOVE element from table
{
	long index = searchElement(key, table);
	//removing element if it matches the element in the correct key
	if (table[index].key != -1) { 
		table[index].key = 0;
		table[index].data[0] = '/0';
		//printf("Element removed from index: %d\n", index);
	}
	else//if not than send an error message
		//printf("Element is not in the table!\n");
	return 0;
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
	while(i < CAPACITY)
	{
		addElement(test[i].key, test[i].data, table);
		i++;
	}
	end = clock();
	double time_taken = (double)(end - start);
	seconds = time_taken / (double)(CLOCKS_PER_SEC);
	printf("%ld elements added in %g ticks / %g seconds. %d duplicates were not inserted.\n", CAPACITY, time_taken,seconds, duplicates);
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