#include "AvlTree.h"

static Node* newNode(int obj, Node* left, Node* right) {
	Node* node = (Node*)malloc(sizeof(Node));
	node->obj = obj;
	node->height = 0;
	node->left = left;
	node->right = right;

	return node;
}

#define compareObj(a, b) _Generic((a), \
	int: compareIntObj,                \
	float: compareFloatObj,            \
	char*: compareStringObj)(a, b)

/**
 *  Função que compara dois ints.
 *  Retorna 0, se forem iguais.
 *  Retorna 1, se a for maior que b.
 *  Retorna -1, se a for menor que b.
 */
static int compareIntObj(int a, int b) {
	if (a == b)
		return 0;
	return (a > b) ? 1 : -1;
}

/**
 *  Função que compara dois floats.
 *  Retorna 0, se forem iguais.
 *  Retorna 1, se a for maior que b.
 *  Retorna -1, se a for menor que b.
 */
static int compareFloatObj(float a, float b) {
	if (a == b)
		return 0;
	return (a > b) ? 1 : -1;
}

/**
 *  Função que compara duas strings.
 *  Retorna 0, se forem iguais.
 *  Retorna 1, se a for maior que b.
 *  Retorna -1, se a for menor que b.
 */
static int compareStringObj(char* a, char* b) {
	return strcmp(a, b);
}

/**
 *  Função que compara dois Nodes.
 *  Retorna 0, se forem iguais.
 *  Retorna 1, se node1 for maior que node2.
 *  Retorna -1, se node1 for menor que node2.
 */
static int compareNodes(Node* const node1, Node* const node2) {
	if (!node1 || !node2)
		return 0;
	return compareObj(node1->obj, node2->obj);
}

/**
 *  Função que compara um obj de um Node e uma info.
 *  Retorna 0, se forem iguais.
 *  Retorna 1, se o node for maior que a info.
 *  Retorna -1, se o node for menor que a info.
 */
static int compareNodeInfo(Node* const node, int const info) {
	if (!node)
		return 0;
	return compareObj(node->obj, info);
}

static int getHeight(Node* node) {
	if (!node)
		return -1;
	return node->height;
}

static int max(int x, int y) {
	return (x > y) ? x : y;
}

static int calculeHeight(Node* node) {
	return max(getHeight(node->left), getHeight(node->right)) + 1;
}

static int balancingFactor(Node* node) {
	return getHeight(node->left) - getHeight(node->right);
}

static void rotationRight(Node** root) {
	Node* node = (*root)->left;

	(*root)->left = node->right;
	node->right = *root;

	(*root)->height = calculeHeight(*root);
	node->height = calculeHeight(node);

	*root = node;
}

static void rotationLeft(Node** root) {
	Node* node = (*root)->right;

	(*root)->right = node->left;
	node->left = *root;

	(*root)->height = calculeHeight(*root);
	node->height = calculeHeight(node);

	*root = node;
}

void doubleRotationRight(Node** root) {
	rotationLeft(&(*root)->left);
	rotationRight(root);
}

void doubleRotationLeft(Node** root) {
	rotationRight(&(*root)->right);
	rotationLeft(root);
}

static void balanceTree(Node** root) {
	if (!(*root))
		return;
	(*root)->height = calculeHeight(*root);
	int fator = balancingFactor(*root);

	if (fator > 1)
		balancingFactor((*root)->left) < 0 ? doubleRotationRight(root) : rotationRight(root);
	else if (fator < -1)
		balancingFactor((*root)->right) > 0 ? doubleRotationLeft(root) : rotationLeft(root);
}

/**
 *  Insere um novo Node na estrutura de Nodes de uma árvore.
 *  Caso tudo ocorra bem, retorna true.
 *  Caso encontre um obj correspondente ao obj contido
 *  no novo Node, retorna false.
 */
static bool insertNode(Node** current, Node* node) {
	if (!node)
		return false;
	if ((*current) == NULL) {
		*current = node;
		return true;
	}
	if (compareNodes(*current, node) == 0)
		return false;

	if (!(compareNodes(*current, node) > 0
	          ? insertNode(&(*current)->left, node)
	          : insertNode(&(*current)->right, node)))
		return false;
	balanceTree(current);
	return true;
}

AvlTree* newAvlTree() {
	AvlTree* tree = (AvlTree*)malloc(sizeof(AvlTree));
	tree->root = NULL;
	tree->size = 0;
	return tree;
}

void insertAvlTree(AvlTree* tree, int obj) {
	if (!tree)
		return;
	Node* node = newNode(obj, NULL, NULL);
	bool Error = !insertNode(&tree->root, node);

	Error
	    ? free(node)
	    : tree->size++;
}

int searchAvlTree(AvlTree* tree, int info) {
	if (!tree)
		return 0;
	Node* current = tree->root;
	while (current) {
		if (compareNodeInfo(current, info) == 0)
			return current->obj;
		current = (compareNodeInfo(current, info) > 0)
		              ? current->left
		              : current->right;
	}
	return 0;
}

static Node* getBiggerNodeLeft(Node** prior, Node** current) {
	if (!(*current))
		return (*prior);

	Node* node = NULL;
	if ((*current)->right)
		node = getBiggerNodeLeft(current, &(*current)->right);
	else {
		node = (*current);
		(*prior)->right = (*current)->left;
	}
	balanceTree(prior);
	return node;
}

static Node* removeNode(Node** root) {
	Node* node = (*root);

	if (!node->left)
		*root = node->right;
	else if (!node->left->right) {
		node->left->right = node->right;
		(*root) = node->left;
	} else {
		Node* bigLeft = getBiggerNodeLeft(root, &(*root)->left);
		bigLeft->left = node->left;
		bigLeft->right = node->right;
		(*root) = bigLeft;
	}
	balanceTree(root);
	return node;
}

static Node* searchRemoveNode(Node** root, int info) {
	if (!(*root))
		return NULL;
	if (compareNodeInfo(*root, info) == 0)
		return removeNode(root);

	Node* node = (compareNodeInfo(*root, info) > 0)
	                 ? searchRemoveNode(&(*root)->left, info)
	                 : searchRemoveNode(&(*root)->right, info);

	balanceTree(root);
	return node;
}

void removeAvlTree(AvlTree* tree, int info) {
	if (!tree)
		return;
	Node* node = searchRemoveNode(&tree->root, info);
	free(node);
	tree->size--;
}

void clearAvlTree(AvlTree* tree) {
	if (!tree)
		return;
	while (tree->root)
		removeAvlTree(tree, tree->root->obj);
}

void freeAvlTree(AvlTree* tree) {
	clearAvlTree(tree);
	free(tree);
}

static void printNodeTree(Node* root, int depth) {
	if (!root)
		return;

	for (int i = depth; i > 0; i--)
		printf("      |");

	printf(" %02d : %02d:\n", root->obj, root->height);
	printNodeTree(root->left, depth + 1);
	printNodeTree(root->right, depth + 1);
}

void printAvlTree(AvlTree* tree) {
	if (!tree)
		return;
	printNodeTree(tree->root, 0);
}