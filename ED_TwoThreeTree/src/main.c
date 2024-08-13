#include <stdio.h>
#include <stdlib.h>
#include "TwoThreeTree/TwoThreeTree.h"

static void printInts(Int* num[], int size) {
	for (int i = 0; i < size; i++)
		printf("%d ", num[i]->num);
	printf("\n");
}

int main() {
	int size = 2;
	Int* vector[4] = {
	    newInt(70),
	    newInt(50),
	    newInt(10),
	    NULL};
	printInts(vector, 3);
	printf("\n");

	TwoThreeTree tree;
	tree.root = NULL;

	for (int i = 0; i < size; i++)
		insertionTwoThreeTree(&tree, vector[i]);
	printTwoThreeTree(&tree);
	return 0;
}