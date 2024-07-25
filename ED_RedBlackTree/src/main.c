#include <stdio.h>
#include <stdlib.h>
#include "RedBlackTree/RedBlakcTree.h"

void preencherVetor(int vetor[], int tam) {
	for (int i = 0; i < tam; i++)
		vetor[i] = rand() % 200;
}

int main() {
	RedBlackTree* tree = newRedBlackTree();
	int tam = 15;
	int vetor[tam];

	preencherVetor(vetor, tam);

	for (int i = 0; i < tam; i++)
		insertionRedBlackTree(tree, vetor[i]);
	printRedBlackTree(tree);

	return 0;
	removeRedBlackTree(tree, 124);
	printf("\n----------------------------------\n");
	printRedBlackTree(tree);

	removeRedBlackTree(tree, 105);
	printf("\n----------------------------------\n");
	printRedBlackTree(tree);
	return 0;
}