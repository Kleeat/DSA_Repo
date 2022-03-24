#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include "splay.h"
#include "options.h"

int test[CAPACITY];

void generator() {//generates a table of pseudorandom keys
	for (int i = 0; i < CAPACITY; i++) {
		test[i] = (rand() * rand()) + rand();
	}
	return  0;
}

void testTrees() {
	NODE* root = NULL;
	double seconds, elapsed;
	time_t start, end;
	generator();

	// Testing Splay tree
	// Inserting elements
	int i = 0;
	start = clock();
	while (i < CAPACITY)
	{
		root = SPLinsertNode(root, test[i]);
		i++;
	}
	end = clock();
	double time_taken = (double)(end - start);
	seconds = time_taken / (double)(CLOCKS_PER_SEC);
	printf("%ld nodes added in %g ticks / %g seconds. %d duplicates were not inserted.\n", CAPACITY, time_taken, seconds, getDuplicates());
	
	// Searching elements
	i = 0;
	start = clock();
	while (i < CAPACITY)
	{
		SPLsearchNode(root, test[i]);
		i++;
	}
	end = clock();
	time_taken = (double)(end - start);
	seconds = time_taken / (double)(CLOCKS_PER_SEC);
	printf("%ld elements searched in %g ticks / %g seconds.\n", CAPACITY, time_taken, seconds);
	
	// Deleting elements
	i = 0;
	start = clock();
	while (i < CAPACITY)
	{
		root = SPLdeleteNode(root, test[i]);
		i++;
	}
	end = clock();
	time_taken = (double)(end - start);
	seconds = time_taken / (double)(CLOCKS_PER_SEC);
	printf("%ld elements removed in %g ticks / %g seconds.\n", CAPACITY, time_taken, seconds);

	return 0;
}