#include <stdio.h>
#include <stdlib.h>
#include "RedBlackTree/RedBlakcTree.h"

void preencherVetor(int vetor[], int tam) {
	for (int i = 0; i < tam; i++)
		vetor[i] = rand() % 100;
}

void printVetor(int vetor[], int tam) {
	for (int i = 0; i < tam; i++)
		printf("%d ", vetor[i]);
	printf("\n\n");
}

int main() {
	RedBlackTree* tree = newRedBlackTree();
	int tam = 20;
	int vetor[tam];

	preencherVetor(vetor, tam);
	printVetor(vetor, tam);

	for (int i = 0; i < tam; i++)
		insertionRedBlackTree(tree, vetor[i]);
	printRedBlackTree(tree);

	// return 0;
	removeRedBlackTree(tree, 61);
	printf("\n----------------------------------\n");
	printRedBlackTree(tree);

	return 0;
	removeRedBlackTree(tree, 105);
	printf("\n----------------------------------\n");
	printRedBlackTree(tree);
	return 0;
}