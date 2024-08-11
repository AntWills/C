#include "TwoThreeTree.h"

Int* newInt(int num) {
	Int* numInt = (Int*)malloc(sizeof(Int));
	numInt->num = num;

	return numInt;
}

void freeInt(Int* num) {
	free(num);
}

static void setVetorInt(Int* setInts[],
                        Int* intValue,
                        int size) {
	for (int i = 0; i < size; i++)
		setInts[i] = intValue;
}

static void setVetorNode(Node* setNodes[],
                         Node* nodeValue,
                         int size) {
	for (int i = 0; i < size; i++)
		setNodes[i] = nodeValue;
}

static Node* newNode(Int* num) {
	Node* node = (Node*)malloc(sizeof(Node));
	setVetorInt(node->vectorKeys, NULL, NumKey);
	setVetorNode(node->vectorNodes, NULL, NumKey + 1);
	node->vectorKeys[0] = num;
	node->parent = NULL;
	node->sizeKeys = 0;

	return node;
}

// Funções privadas que ajudam na inserção.

static void insertion(Node* node, Int* num);
static void insertionNode(Node* node, Int* num);
static void moveVectorOneSpace(Int* vector[], int size, int index);
static void swap(void* vector[], int indexA, int indexB);
static Node* split(Node* node, Int* num);

// Funções privadas que verificam o node.

static bool isLeaf(Node* node);

// Funções privadas que ajudam na impressão.

static void printNodes(Node* node, int depth);
static void printInts(Int* num[], int size);

void insertionTwoThreeTree(TwoThreeTree* tree, Int* num) {
	if (!tree->root) {
		tree->root = newNode(num);
		return;
	}

	insertion(tree->root, num);
}

static void insertion(Node* node, Int* num) {
	if (!node)
		return;
	if (isLeaf(node)) {
		if (node->sizeKeys == NumKey) {
			split(node, num);
			return;
		} else {
			insertionNode(node, num);
			node->sizeKeys++;
			return;
		}
	}
}

static void insertionNode(Node* node, Int* num) {
	int i = 0;
	for (; i < NumKey && node->vectorKeys[i]; i++) {
		if (num->num < node->vectorKeys[i]->num) {
			moveVectorOneSpace(node->vectorKeys, node->sizeKeys, i);
			node->vectorKeys[i] = num;
			return;
		}
	}
	node->vectorKeys[i] = num;
}

static void moveVectorOneSpace(Int* vector[], int size, int index) {
	for (int i = (size - 1); i > index; i--) {
		swap(vector, i, i - 1);
	}
}

static void swap(void* vector[], int indexA, int indexB) {
	void* auxi = vector[indexA];
	vector[indexA] = vector[indexB];
	vector[indexB] = auxi;
}

static Node* split(Node* node, Int* num) {
}

static bool isLeaf(Node* node) {
	if (node->vectorNodes[0])
		return false;
	return true;
}

void removeTwoThreeTree(TwoThreeTree* tree, Int* num) {
}

Int* searchTwoThreeTree(TwoThreeTree* tree, int num) {
}

void printTwoThreeTree(TwoThreeTree* tree) {
	printNodes(tree->root, 0);
}

static void printNodes(Node* node, int depth) {
	if (!node)
		return;

	for (int i = 0; i < depth; i++)
		printf("    | ");
	printInts(node->vectorKeys, NumKey);

	for (int i = 0; i < (NumKey + 1); i++)
		printNodes(node->vectorNodes[i], depth + 1);
}

static void printInts(Int* num[], int size) {
	for (int i = 0; i < size; i++)
		printf("%d ", num[i]);
	printf("\n");
}
