#include <stdlib.h>
#include<time.h>
#include "options.h"

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
	}
	return table;
}

//Get duplicates
int getHashDuplicates() {
	return duplicates;
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
	}
	else if (table[index].key == key) {
		duplicates++;
		return 0;
	}

	//if not a collision ha occured - Linear probing
	else {
		for (int i = 1; i < CAPACITY; i++) {
			index = (index + 1) % CAPACITY;
			if (table[index].key == 0) {
				table[index].key = key;
				return 0;
			}
			else if (table[index].key == key) {
				return 0;
			}
		}
	}
	return 0;
}

void removeElement(int key, PAIR* table)//REMOVE element from table
{
	int index = searchElement(key, table);
	//removing element if it matches the element in the correct key
	if (table[index].key != -1) {
		table[index].key = 0;
	}
	//if not than send an error message
	else
		return 0;
}

int searchElement(int key, PAIR* table)//SEARCH element in table, returns index in table
{
	int index = hashFunction(key);
	if (table[index].key == key) {
		return index;
	}
	else if (table[index].key == 0) {
		return -1;
	}
	else {
		for (int i = 1; i < CAPACITY; i++) {
			if (table[(index + i) % CAPACITY].key == key) {
				return (index + i) % CAPACITY;
			}
		}
	}
	return -1;
}