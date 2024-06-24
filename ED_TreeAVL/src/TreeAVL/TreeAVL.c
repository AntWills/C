#include "TreeAVL.h"

static Node* newNode(int obj, Node* left, Node* right) {
	Node* node = (Node*)malloc(sizeof(Node));
	node->obj = obj;
	node->left = left;
	node->right = right;

	return node;
}

/**
 *  Função que compara os objs de dois Nodes.
 *  Retorna 0, se forem iguais.
 *  Retorna 1, se node1 for maior que node2.
 *  Retorna -1, se node1 for menor que node2.
 */
static int isEqualNode(Node const* node1, Node const* node2) {
	if (!node1 || !node2)
		return 0;
	if (node1->obj == node2->obj)
		return 0;
	if (node1->obj > node2->obj)
		return 1;
	return -1;
}

/**
 *  Insere um Node na estrutura de Nodes de uma árvore.
 *  Caso tudo ocorra bem, retorna true.
 *  Caso encontre um obj correspondente ao Node,
 *  retorna false.
 */
static bool insertNode(Node** root, Node* node) {
	if (!node)
		return false;
	if ((*root) == NULL) {
		*root = node;
		return true;
	}
	if (isEqualNode(*root, node) == 0)
		return false;

	bool returnIsertBool = true;
	if (isEqualNode(*root, node) > 0)
		returnIsertBool = insertNode(&(*root)->left, node);
	else
		returnIsertBool = insertNode(&(*root)->right, node);

	return returnIsertBool;
}

static void printNodeTree(Node* root) {
	if (!root)
		return;
	printNodeTree(root->left);
	printf("%d ", root->obj);
	printNodeTree(root->right);
}

TreeAVL* newTreeAVL() {
	TreeAVL* tree = (TreeAVL*)malloc(sizeof(TreeAVL));
	tree->root = NULL;
	tree->size = 0;
	return tree;
}

void insertTreeAVL(TreeAVL* tree, int obj) {
	if (!tree)
		return;
	Node* node = newNode(obj, NULL, NULL);
	bool existObj = insertNode(&tree->root, node);

	if (existObj)
		tree->size++;
	else
		free(node);
}

int searchTreeAVL(TreeAVL* tree, int obj) {
	if (!tree)
		return 0;
	Node* root = tree->root;
	while (root) {
		if (root->obj == obj)
			return root->obj;

		if (root->obj > obj)
			root = root->left;
		else
			root = root->right;
	}
	return 0;
}

void printTreeAVL(TreeAVL* tree) {
	if (!tree)
		return;
	printNodeTree(tree->root);
}