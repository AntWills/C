#ifndef TwoThreeTree

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define NumKey 2

typedef struct Int {
	int num;
} Int;

Int* newInt(int num);
void freeInt(Int* num);

typedef struct Node {
	int sizeKeys;
	Int* vectorKeys[NumKey];
	struct Node* vectorNodes[NumKey + 1];
	struct Node* parent;
} Node;

typedef struct TwoThreeTree {
	Node* root;
} TwoThreeTree;

void insertionTwoThreeTree(TwoThreeTree* tree, Int* num);
void removeTwoThreeTree(TwoThreeTree* tree, Int* num);
Int* searchTwoThreeTree(TwoThreeTree* tree, int num);

void printTwoThreeTree(TwoThreeTree* tree);

#endif