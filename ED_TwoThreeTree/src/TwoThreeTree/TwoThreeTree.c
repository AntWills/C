#include "TwoThreeTree.h"

// Varivael global para acessar diretamente a raiz.
static TwoThreeTree* treeGlobal = NULL;
static Int* auxiInts[3] = {};

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
	node->parent = parent;

	if (num)
		node->sizeKeys = 1;
	else
		node->sizeKeys = 0;
	return node;
}

// Funções privadas que ajudam na inserção.

static void insertion(Node* node, Int* num);
static void insertionNode(Node* node, Int* key);
static void swap(void* vector[], int indexA, int indexB);
static Node* split(Node* node, Int* key);
static Node* splitRoot(Node* node, Int* key, bool simple);
static Node* splitNode(Node* node, Int* key, Int* newNum);
static Int* getCenterAndOrgVector(Int* vector[], int size, Int* key);

// Funções privadas que verificam o node.

static bool isLeaf(Node* node);

// Funções privadas que ajudam na impressão.

static void printNodes(Node* node, int depth);
static void printInts(Int* num[], int size);

void insertionTwoThreeTree(TwoThreeTree* tree, Int* num) {
	if (!tree->root) {
		tree->root = newNode(num, NULL);
		return;
	}
	treeGlobal = tree;
	insertion(tree->root, num);
}

static void insertion(Node* node, Int* num) {
	if (!node)
		return;
	if (isLeaf(node) && !node->vectorNodes[1]) {
		insertionNode(node, num);
		return;
	}

	if (isLeaf(node) && node->vectorNodes[0]) {
		split(node, num);
		return;
	}
	int i = 0;
	for (; i < MaxKey && node->vectorKeys[i]; i++) {
		if (num->info < node->vectorKeys[i]->info) {
			insertion(node->vectorNodes[i], num);
			return;
		}
	}
	insertion(node->vectorNodes[i + 1], num);
}

static void insertionNode(Node* node, Int* key) {
	int i = 0;
	node->vectorKeys[1] = key;

	if (node->vectorKeys[0]->info > node->vectorKeys[1]->info)
		swap((void*)node->vectorKeys, 0, 1);
}

static void swap(void* vector[], int indexA, int indexB) {
	void* auxi = vector[indexA];
	vector[indexA] = vector[indexB];
	vector[indexB] = auxi;
}

static Node* split(Node* node, Int* key) {
	if (node == treeGlobal->root) {
		treeGlobal->root = splitRoot(node, key, true);
	} else {
		splitNode(node, key, NULL);
	}
	return NULL;
}

static Node* splitRoot(Node* node, Int* key, bool simple) {
	Node* newRoot = NULL;
	if (simple) {
		Int* centorNum = getCenterAndOrgVector(node->vectorKeys, node->sizeKeys, key);

		newRoot = newNode(centorNum, NULL);
		newRoot->vectorNodes[0] = newNode(node->vectorKeys[0], newRoot);
		newRoot->vectorNodes[2] = newNode(node->vectorKeys[1], newRoot);

		free(node);
		return newRoot;
	}

	if (treeGlobal->root->vectorNodes[0] == node) {
	} else {
		newRoot = newNode(treeGlobal->root->vectorKeys[1], NULL);

		Node* rithg = newNode(key, newRoot);

		Node* left = newNode(treeGlobal->root->vectorKeys[0], newRoot);
		left->vectorNodes[0] = treeGlobal->root->vectorNodes[0];
		left->vectorNodes[2] = treeGlobal->root->vectorNodes[1];
		left->vectorNodes[0]->parent = left;
		left->vectorNodes[2]->parent = left;

		newRoot->vectorNodes[0] = left;
	}
	return newRoot;
}

static Node* splitNode(Node* node, Int* key, Int* newNum) {
	Node* parent = node->parent;
	bool parentAreSimple = parent->sizeKeys == 1;
	bool nodeIsTheLeft = parent->vectorNodes[0] == node;

	if (parentAreSimple) {
		Int* center = getCenterAndOrgVector(node->vectorKeys, MaxKey, key);
		Int* right = node->vectorKeys[1];
		node->vectorKeys[1] = NULL;
		node->sizeKeys--;
		Node* nodeRight = newNode(right, parent);

		if (parent->vectorNodes[0] == node) {
			insertionNode(parent, center);
			parent->vectorNodes[1] = nodeRight;
		} else {
			parent->vectorKeys[1] = center;
			parent->sizeKeys++;
			parent->vectorNodes[1] = node;
			parent->vectorNodes[2] = nodeRight;
		}
		return NULL;
	}

	if (parent == treeGlobal->root) {
		Int* center = getCenterAndOrgVector(node->vectorKeys, MaxKey, key);
		// treeGlobal->root = splitRoot(node, center, true);
	}

	return NULL;
}

static Int* getCenterAndOrgVector(Int* vector[], int size, Int* key) {
	Int* center = NULL;
	if ((vector[0]->info < key->info) &&
	    (key->info < vector[1]->info)) {
	} else if (key->info < vector[0]->info) {
		center = vector[0];
		vector[0] = key;
	} else {
		center = vector[1];
		vector[1] = key;
	}
	return center;
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
