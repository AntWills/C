#ifndef TwoThreeTree

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MaxKey 2

typedef struct Int {
	int info;
} Int;

Int* newInt(int num);
void freeInt(Int* num);

typedef struct Node {
	int sizeKeys;
	Int* vectorKeys[2];
	struct Node* vectorNodes[3];
	// left - center - right
} Node;

typedef struct TwoThreeTree {
	Node* root;
} TwoThreeTree;

void insertionTwoThreeTree(TwoThreeTree* tree, Int* num);
void removeTwoThreeTree(TwoThreeTree* tree, Int* num);
Int* searchTwoThreeTree(TwoThreeTree* tree, int num);

void printTwoThreeTree(TwoThreeTree* tree);

#endif