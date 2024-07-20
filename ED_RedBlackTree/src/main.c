#include <stdio.h>
#include <stdlib.h>
#include "RedBlackTree/RedBlakcTree.h"

int main() {
	RedBlackTree* tree = newRedBlackTree();
	int vetor[] = {10, 20, 30, 0, 5, 7, 9, 8};

	for (int i = 0; i < 8; i++)
		insertionRedBlackTree(tree, vetor[i]);
	printRedBlackTree(tree);
	return 0;
}