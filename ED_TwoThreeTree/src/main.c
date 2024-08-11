#include <stdio.h>
#include <stdlib.h>
#include "TwoThreeTree/TwoThreeTree.h"

static void moveVectorOneSpace(Int* vector[], int size, int index) {
	for (int i = (size - 1); i > (index); i--) {
		void* auxi = vector[i];
		vector[i] = vector[i - 1];
		vector[i - 1] = auxi;
	}
}

static void printInts(Int* num[], int size) {
	for (int i = 0; i < size; i++)
		printf("%d ", num[i]->num);
	printf("\n");
}

int main() {
	Int* vector[4] = {
	    newInt(10),
	    newInt(50),
	    newInt(70),
	    NULL};
	printInts(vector, 3);
	moveVectorOneSpace(vector, 4, 1);
	vector[1] = newInt(0);
	printInts(vector, 4);
	return 0;
}