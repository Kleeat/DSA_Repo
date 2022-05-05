#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLENGHT 40


// Defining the node structure for the BDD
typedef struct bddNode{
	char expression[MAXLENGHT];
	struct bddNode* parent;
	struct bddNode* highChild;
	struct bddNode* lowChild;
	char variable;
} BDDNODE;

// Defining the BDD structure
typedef struct bdd {
	int numberOfVariables;
	int numberOfNodes;
	BDDNODE* root;
}BDD;

BDDNODE* newNode();
BDD* bddCreate(char bfunction[], char variableOrder[]);

// Creating a new BDD node
BDDNODE* newNode() {
	BDDNODE* newNode;
	newNode = (BDDNODE*)malloc(sizeof(BDDNODE));
	// TODO set parameters
	return newNode;
}

// Push the variable order to the left
char* popOrder(char string[]) {
	char variables[MAXLENGHT];
	strcpy(variables, string);
	int i = 0;
	while (variables[i] != '\0') {
		variables[i] = variables[i++ + 1];
	}
	return variables;
}

// Extract high function
char* extractHigh(char bfunction[], char variable) {
	char highFunction[MAXLENGHT];
	int i = 0;
	int j = 0;
	while (bfunction[i] != '\0') {
		if (bfunction[i] != variable) {
			while (bfunction[i] != '+') {
				i++;
				if (bfunction[i] == '\0') {
					highFunction[j] = '\0';
					return highFunction;
				}
			}
			i++;
		}
		else {
			if (j != 0) {
				highFunction[j] = '+';
				j++;
			}
			i++;
			while(bfunction[i] != '+' && bfunction[i] != '\0') {
				highFunction[j] = bfunction[i];
				i++;
				j++;
			}
			if (bfunction[i] == '\0') {
				highFunction[j] = '\0';
				return highFunction;
			}
			i++;
		}
	}
}
// Extract low function
char* extractLow(char bfunction[], char variable) {
	char lowFunction[MAXLENGHT];
	int i = 0;
	int j = 0;
	while (bfunction[i] != '\0') {
		if (bfunction[i+1] != variable || bfunction[i] != '!') {
			while (bfunction[i] != '+') {
				i++;
				if (bfunction[i] == '\0') {
					lowFunction[j] = '\0';
					return lowFunction;
				}
			}
			i++;
		}
		else {
			if (j != 0) {
				lowFunction[j] = '+';
				j++;
			}
			i += 2;
			while (bfunction[i] != '+' && bfunction[i] != '\0') {
				lowFunction[j] = bfunction[i];
				i++;
				j++;
			}
			if (bfunction[i] == '\0') {
				lowFunction[j] = '\0';
				return lowFunction;
			}
			i++;
		}
	}
}
// Creating the reduced binary decision diagram
BDDNODE* createBDD(BDDNODE* root, BDDNODE* zero, BDDNODE* one, BDDNODE* parent, char bfunction[], char variableOrder[]) {
	char newVariableOrder[MAXLENGHT];
	char highFunction[MAXLENGHT];
	char lowFunction[MAXLENGHT];

	strcpy(root->expression, bfunction);
	root->variable = variableOrder[0];
	root->parent = parent;

	// Return leaf nodes
	if (strlen(variableOrder) == 1) {
		if (bfunction[0] != '!') {
			root->highChild = one;
			root->lowChild = zero;
		}
		else {
			root->highChild = zero;
			root->lowChild = one;
		}
		//root->highChild->highChild = root->lowChild->highChild = NULL;
		//root->highChild->lowChild = root->lowChild->lowChild = NULL;
		root->highChild->parent = root->lowChild->parent = root;
		return root;
	}

	strcpy(newVariableOrder, popOrder(variableOrder));
	strcpy(highFunction, extractHigh(bfunction, root->variable));
	strcpy(lowFunction, extractLow(bfunction, root->variable));
	// Create y functions from base function
	root->highChild = createBDD(newNode(), zero, one, root, highFunction, newVariableOrder);
	root->lowChild = createBDD(newNode(), zero, one, root, lowFunction, newVariableOrder);
	return root;
}

// BDD cerate
BDD* bddCreate(char bfunction[], char variableOrder[]) {
	BDD* bdDiagram = (BDD*)malloc(sizeof(BDD));
	BDDNODE* root = newNode();
	BDDNODE* zero = newNode();
	strcpy(zero->expression, "0");
	zero->variable = '0';
	BDDNODE* one = newNode();
	strcpy(one->expression, "1");
	one->variable = "1";
	bdDiagram->root = root;
	root = createBDD(root, zero, one, NULL, bfunction, variableOrder);
	return bdDiagram;
}

// Main function for WIP testing
void main() {
	char string[] = { "a!b!c+!a!bc+ab!c+!ab!c" };
	char variables[] = { "abc" };
	printf("Original: %s\n", string);
	printf("High: %s\n", extractHigh(string, 'a'));
	printf("Low: %s\n", extractLow(string, 'a'));
	BDD* hello = bddCreate(string, variables);
	return 0;
}