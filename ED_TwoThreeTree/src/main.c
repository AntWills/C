#include <stdio.h>
#include <stdlib.h>
#include "TwoThreeTree/TwoThreeTree.h"

static void printInts(Int* num[], int size) {
	for (int i = 0; i < size; i++)
		printf("%d ", num[i]->info);
	printf("\n");
}

int main() {
	int size = 12;
	Int* vector[] = {
	    newInt(70),
	    newInt(50),
	    newInt(10),
	    newInt(60),
	    newInt(80),
	    newInt(0),
	    newInt(55),
	    newInt(90),
	    newInt(85),
	    newInt(20),
	    newInt(65),
	    newInt(61)};
	printInts(vector, size);
	printf("\n");

	TwoThreeTree tree;
	tree.root = NULL;

	for (int i = 0; i < size; i++) {
		printf("\n\n---------------------------\n");
		printf("Inserindo: %d.\n\n", vector[i]->info);
		insertionTwoThreeTree(&tree, vector[i]);

		printTwoThreeTree(&tree);
	}

	// printTwoThreeTree(&tree);
	return 0;
}