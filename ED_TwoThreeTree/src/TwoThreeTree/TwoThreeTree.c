#include "TwoThreeTree.h"

// Varivael global para acessar diretamente a raiz.
static TwoThreeTree* treeGlobal = NULL;
static Node* auxiNodes[2] = {};

Int* newInt(int num) {
	Int* numInt = (Int*)malloc(sizeof(Int));
	numInt->info = num;

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

static Node* newNode(Int* num, Node* parent) {
	Node* node = (Node*)malloc(sizeof(Node));
	setVetorInt(node->vectorKeys, NULL, MaxKey);
	setVetorNode(node->vectorNodes, NULL, MaxKey + 1);
	node->vectorKeys[0] = num;
	// node->parent = parent;

	if (num)
		node->sizeKeys = 1;
	else
		node->sizeKeys = 0;
	return node;
}

// Funções privadas que ajudam na inserção.

static Int* insertion(Node* node, Int* num);
static void insertionNode(Node* node, Int* key);
static void swap(void* vector[], int indexA, int indexB);
static Int* splitLeaf(Node* node, Int* key);
static Int* split(Node* node, Int* key);
static void mergeNodes(Node* node, Int* key);

// Funções privadas que verificam o node.

static bool isLeaf(Node* node);

// Funções privadas que ajudam na impressão.

static void printNodes(Node* node, int depth);
static void printInts(Int* num[], int size);

void insertionTwoThreeTree(TwoThreeTree* tree, Int* key) {
	if (!tree->root) {
		tree->root = newNode(key, NULL);
		return;
	}
	treeGlobal = tree;
	Int* num = insertion(tree->root, key);
	if (!num)
		return;
	tree->root = newNode(num, NULL);
	tree->root->vectorNodes[0] = auxiNodes[0];
	tree->root->vectorNodes[2] = auxiNodes[1];

	auxiNodes[0] = NULL;
	auxiNodes[1] = NULL;
}

static Int* insertion(Node* node, Int* key) {
	if (!node)
		return NULL;

	if (isLeaf(node) && !node->vectorKeys[1]) {
		insertionNode(node, key);
		return NULL;
	}

	if (isLeaf(node) && node->vectorKeys[1])
		return splitLeaf(node, key);

	Int* auxi = NULL;

	if (key->info < node->vectorKeys[0]->info)
		auxi = insertion(node->vectorNodes[0], key);
	else if (key->info > node->vectorKeys[2]->info)
		auxi = insertion(node->vectorNodes[2], key);
	else
		auxi = insertion(node->vectorNodes[1], key);

	if (!auxi)
		return NULL;

	if (!node->vectorKeys[1]) {
		mergeNodes(node, auxi);
		return NULL;
	}

	return split(node, auxi);
}

static void insertionNode(Node* node, Int* key) {
	node->vectorKeys[1] = key;

	if (node->vectorKeys[0]->info > node->vectorKeys[1]->info)
		swap((void*)node->vectorKeys, 0, 1);
}

static void swap(void* vector[], int indexA, int indexB) {
	void* auxi = vector[indexA];
	vector[indexA] = vector[indexB];
	vector[indexB] = auxi;
}

static Int* splitLeaf(Node* node, Int* key) {
	Node* left = NULL;
	Node* right = NULL;
	if (key->info < node->vectorKeys[0]->info) {
		left = newNode(key, node);

		right = newNode(node->vectorKeys[1], node);
	} else if (key->info < node->vectorKeys[1]->info) {
		left = newNode(node->vectorKeys[0], node);
		node->vectorKeys[0] = NULL;

		right = newNode(node->vectorKeys[1], node);

		node->vectorKeys[0] = key;
	} else {
		left = newNode(node->vectorKeys[0], node);
		node->vectorKeys[0] = NULL;

		right = newNode(key, node);

		node->vectorKeys[0] = node->vectorKeys[1];
	}

	node->vectorKeys[1] = NULL;
	auxiNodes[0] = left;
	auxiNodes[1] = right;
	return node->vectorKeys[0];
}

static Int* split(Node* node, Int* key) {
	Node* left = NULL;
	Node* right = NULL;
	if (key->info < node->vectorKeys[0]->info) {
		left = newNode(key, NULL);
		left->vectorNodes[0] = auxiNodes[0];
		left->vectorNodes[2] = auxiNodes[1];

		key = node->vectorKeys[0];

		swap((void*)node->vectorKeys, 0, 1);
		node->vectorKeys[1] = NULL;
		node->vectorNodes[0] = node->vectorNodes[1];
		node->vectorNodes[1] = NULL;

		right = node;
	} else if (key->info < node->vectorKeys[1]->info) {
		right = newNode(node->vectorKeys[1], NULL);
		node->vectorKeys[1] = NULL;
		right->vectorNodes[0] = auxiNodes[1];
		right->vectorNodes[2] = node->vectorNodes[2];

		left = node;
		left->vectorNodes[1] = NULL;
		left->vectorNodes[0] = node->vectorNodes[0];
		left->vectorNodes[2] = auxiNodes[0];
	} else {
		right = newNode(key, NULL);
		right->vectorNodes[0] = auxiNodes[0];
		right->vectorNodes[2] = auxiNodes[1];

		key = node->vectorKeys[1];
		node->vectorKeys[1] = NULL;

		node->vectorNodes[2] = node->vectorNodes[1];
		node->vectorNodes[1] = NULL;

		left = node;
	}

	auxiNodes[0] = left;
	auxiNodes[1] = right;

	return key;
}

static void mergeNodes(Node* node, Int* key) {
	if (key->info < node->vectorKeys[0]->info) {
		node->vectorNodes[0] = auxiNodes[0];
		node->vectorNodes[1] = auxiNodes[1];
	} else {
		node->vectorNodes[1] = auxiNodes[0];
		node->vectorNodes[2] = auxiNodes[1];
	}
	insertionNode(node, key);
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

	for (int i = MaxKey; i >= 0; i--)
		printNodes(node->vectorNodes[i], depth + 1);
}

static void printInts(Int* num[], int size) {
	for (int i = 0; i < size && num[i]; i++)
		printf("%d ", num[i]->info);
	printf("\n");
}
