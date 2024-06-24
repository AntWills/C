#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TreeAVL/TreeAVL.h"

int main() {
	TreeAVL* tree = newTreeAVL();
	int vector[] = {5, 7, 8, 0, 3, 10, 10};
	for (int i = 0; i < 6; i++)
		insertTreeAVL(tree, vector[i]);
	printf("Obj: %d.", searchTreeAVL(tree, 10));
	return 0;
}