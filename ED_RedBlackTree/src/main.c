#include <stdio.h>
#include <stdlib.h>
#include "RedBlackTree/RedBlakcTree.h"

int main() {
	RedBlackTree* tree = newRedBlackTree();
	int vetor[] = {10, 20, 30, 0, 50, 70, 90, 80, 25, 35, 15, 5, 55, 75};

	for (int i = 0; i < 14; i++)
		insertionRedBlackTree(tree, vetor[i]);
	printRedBlackTree(tree);

	// return 0;
	removeRedBlackTree(tree, 25);

	printf("\n----------------------------------\n");

	printRedBlackTree(tree);
	return 0;
}