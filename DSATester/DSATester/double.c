#include <stdlib.h>
#include "options.h"
#include "double.h"
#define PRIME 10000079


PAIR test[CAPACITY];
int duplicates;

PAIR* initTable(PAIR* table) { //setting up the empty table
	table = (PAIR*)malloc(PRIME * sizeof(PAIR));
	for (int i = 0; i < PRIME; i++) {
		table[i].key = 0;
	}
	return table;
}

int getHashDuplicates() {
	return duplicates;
}

int hashFunction1(int key) { //Primitive hash function
	int index = key % PRIME;
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
	}
	else if (table[index].key == key) {
		duplicates++;
		return 0;
	}

	//if not a collision ha occured - DoubleHashing
	else {
		for (int i = 1; i <= PRIME; i++) {
			index = (hashFunction1(key) + i * hashFunction2(key)) % PRIME; //Double hashing
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

int searchElement(int key, PAIR* table)//SEARCH element in table, returns index in table
{
	long index = hashFunction1(key);
	if (table[index].key == key) {//check if element is at the correct index
		return index;
	}
	else if (table[index].key == 0) {//if the space at the index is empty element cannot be found
		return -1;
	}
	else {
		for (int i = 1; i < PRIME; i++) {
			index = (hashFunction1(key) + i * hashFunction2(key)) % PRIME; //Double hashing
			if (table[index].key == key) {
				return index;
			}
		}
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
	}
	else//if not than send an error message
		return 0;
}