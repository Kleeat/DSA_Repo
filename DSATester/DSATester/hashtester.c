#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include "options.h"
#include "linear.h"

PAIR test[CAPACITY];

void hashGenerator() {//generates a table of pseudorandom keys and "data"
	int j = 1;
	for (int i = 0; i < CAPACITY; i++) {
		test[i].key = (rand() * rand()) % CAPACITY;
	}
	return  0;
}

void testHash() {

	printf("%s hash\n", used);
	double seconds, elapsed;
	time_t start, end;
	PAIR* table = initTable(&table);
	hashGenerator();
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
	printf("%ld elements added in %g ticks / %g seconds. %d duplicates were not inserted.\n", CAPACITY, time_taken, seconds, getHashDuplicates());
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