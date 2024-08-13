#include "TwoThreeTree.h"

// Varivael global para acessar diretamente a raiz.
static TwoThreeTree* treeGlobal = NULL;

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
	setVetorInt(node->vectorKeys, NULL, MaxKey);
	setVetorNode(node->vectorNodes, NULL, MaxKey + 1);
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
static Node* splitRoot(Node* node, Int* num);
static Node* splitNode(Node* node, Int* num, Int* newNum);

// Funções privadas que verificam o node.

static bool isLeaf(Node* node);

// Funções privadas que ajudam na impressão.

static void printNodes(Node* node, int depth);
static void printInts(Int* num[], int size);

void insertionTwoThreeTree(TwoThreeTree* tree, Int* num) {
	if (!tree->root) {
		tree->root = newNode(num);
		tree->root->sizeKeys = 1;
		return;
	}
	treeGlobal = tree;
	insertion(tree->root, num);
}

static void insertion(Node* node, Int* num) {
	if (!node)
		return;
	if (isLeaf(node) && node->sizeKeys < MaxKey) {
		insertionNode(node, num);
		return;
	}

	if (isLeaf(node) && node->sizeKeys == MaxKey) {
		return;
	}
	int i = 0;
	for (; i < MaxKey; i++) {
		if (num->num < node->vectorKeys[i]->num) {
			insertion(node->vectorNodes[i], num);
			return;
		}
	}
	insertion(node->vectorNodes[i], num);
}

static void insertionNode(Node* node, Int* num) {
	int i = 0;
	node->sizeKeys++;
	for (; i < MaxKey && node->vectorKeys[i]; i++) {
		if (num->num < node->vectorKeys[i]->num) {
			moveVectorOneSpace(node->vectorKeys, MaxKey, i);
			node->vectorKeys[i] = num;
			return;
		}
	}
	node->vectorKeys[i] = num;
}

static void moveVectorOneSpace(Int* vector[], int size, int index) {
	for (int i = (size - 1); i > index; i--) {
		swap((void*)vector, i, i - 1);
	}
}

static void swap(void* vector[], int indexA, int indexB) {
	void* auxi = vector[indexA];
	vector[indexA] = vector[indexB];
	vector[indexB] = auxi;
}

static Node* split(Node* node, Int* num) {
	if (node == treeGlobal->root) {
		if (num->num < node->vectorKeys[0]->num) {
			Node* root = newNode(node->vectorKeys[0]);
			swap((void*)node->vectorKeys, 0, 1);
			node->vectorKeys[1] = NULL;

			root->vectorNodes[0] = newNode(num);
			root->vectorNodes[1] = node;
			node->parent = root;
			root->vectorNodes[0]->parent = root;
			return root;
		} else if (num->num > node->vectorKeys[1]->num) {
		} else {
		}
		// treeGlobal->root
		return NULL;
	}
	return NULL;
}

static Node* splitRoot(Node* node, Int* num) {
	return NULL;
}

static Node* splitNode(Node* node, Int* num, Int* newNum) {
	return NULL;
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
	printInts(node->vectorKeys, MaxKey);

	for (int i = 0; i < (MaxKey + 1); i++)
		printNodes(node->vectorNodes[i], depth + 1);
}

static void printInts(Int* num[], int size) {
	for (int i = 0; i < size && num[i]; i++)
		printf("%d ", num[i]->num);
	printf("\n");
}
