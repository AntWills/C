#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AvlTree/AvlTree.h"

int main() {
	AvlTree* tree = newTreeAVL();
	int vector[] = {15, 10, 13, 11, 12, 20, 40, 30, 50, 8, 9, 4};
	for (int i = 0; i < 12; i++)
		insertAvlTree(tree, vector[i]);
	printAvlTree(tree);
	removeAvlTree(tree, 8);
	printf("\n-----------------------------------\n");
	printAvlTree(tree);
	clearAvlTree(tree);
	return 0;
}