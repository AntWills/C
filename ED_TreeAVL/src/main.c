#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TreeAVL/TreeAVL.h"

int main() {
	TreeAVL* tree = newTreeAVL();
	int vector[] = {15, 10, 13, 11, 12, 20, 40, 30, 50, 8, 9, 4};
	for (int i = 0; i < 12; i++)
		insertTreeAVL(tree, vector[i]);
	printTreeAVL(tree);
	removeTreeAVL(tree, 8);
	printf("\n-----------------------------------\n");
	printTreeAVL(tree);
	clearTreeAVL(tree);
	return 0;
}