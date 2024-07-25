#include "RedBlakcTree.h"

static Node* rootRedBlackTree = NULL;

static Node* newNode(int obj) {
	Node* node = (Node*)malloc(sizeof(Node));
	node->obj = obj;
	node->color = RED;
	node->left = NULL;
	node->right = NULL;
	node->parent = NULL;

	return node;
}

static void freeNode(Node* node) {
	free(node);
}

static int compareInt(int a, int b);
static int compareNode(Node* const node1, Node* const node2);
static int compareNodeInt(Node* const node, int obj);

/**
 *  Função que compara dois dados qualquer.
 *  Retorna 0, se forem iguais.
 *  Retorna 1, se a for maior que b.
 *  Retorna -1, se a for menor que b.
 */
#define compare(a, b) _Generic((a), \
	int: compareInt,                \
	Node*: _Generic((b),            \
	Node *: compareNode,            \
	int: compareNodeInt))(a, b)

static int compareInt(int a, int b) {
	if (a == b)
		return 0;
	return (a > b) ? 1 : -1;
}

static int compareNode(Node* const node1, Node* const node2) {
	return compare(node1->obj, node2->obj);
}

static int compareNodeInt(Node* const node, int obj) {
	return compare(node->obj, obj);
}

Color getColor(Node* node) {
	return !node ? BLACK : node->color;
}

/** Vai alterar a cor dos filhos para BLACK
 *  e de se mesmo para RED.
 */
static void alterColor(Node** node) {
	(*node)->color = RED;
	(*node)->left->color = BLACK;
	(*node)->right->color = BLACK;
}

static void rotationRight(Node* root, bool mudarDeCor) {
	Node* parent = root->parent;
	Node* node = root->left;

	root->left = node->right;
	node->right = root;

	if (mudarDeCor) {
		root->color = RED;
		node->color = BLACK;
	}

	root->parent = node;
	if (!parent) {
		rootRedBlackTree = node;
		return;
	}

	if (parent->left == root)
		parent->left = node;
	else
		parent->right = node;
}

static void rotationLeft(Node* root, bool alterColor) {
	Node* parent = root->parent;
	Node* node = root->right;

	root->right = node->left;
	node->left = root;

	if (alterColor) {
		root->color = RED;
		node->color = BLACK;
	}

	root->parent = node;
	if (!parent) {
		rootRedBlackTree = node;
		return;
	}

	if (parent->left == root)
		parent->left = node;
	else
		parent->right = node;
}

static void doubleRotationRight(Node** node) {
	rotationLeft((*node)->left, false);
	rotationRight(*node, true);
}

static void doubleRotationLeft(Node** root) {
	rotationRight((*root)->right, false);
	rotationLeft(*root, true);
}

static bool redChildren(Node* node) {
	if (!node)
		return false;
	if (getColor(node->left) == RED ||
	    getColor(node->right) == RED)
		return true;
	return false;
}

static bool twoRedChildren(Node* node) {
	if (!node)
		return false;
	if (getColor(node->left) == RED &&
	    getColor(node->right) == RED)
		return true;
	return false;
}

static bool twoBlackChildren(Node* node) {
	if (!node)
		return false;
	if (getColor(node->left) == BLACK &&
	    getColor(node->right) == BLACK)
		return true;
	return false;
}

static void orgInsertionTree(Node** node) {
	if (!(*node) || twoBlackChildren(*node))
		return;

	if (twoRedChildren(*node)) {
		if (redChildren((*node)->left) || redChildren((*node)->right)) {
			alterColor(node);
			return;
		}
	}

	if (getColor((*node)->left) == RED) {
		if (getColor((*node)->left->left) == RED)
			rotationRight(*node, true);
		else if (getColor((*node)->left->right))
			doubleRotationRight(node);
		return;
	}

	if (getColor((*node)->right->right) == RED)
		rotationLeft(*node, true);
	else if (getColor((*node)->right->left) == RED)
		doubleRotationLeft(node);
}

static bool insertionNode(Node** current, Node* node) {
	if (!node)
		return false;
	if (!(*current)) {
		*current = node;
		return true;
	}

	if (compare(*current, node) == 0)
		return false;

	if (!(compare(*current, node) > 0
	          ? insertionNode(&(*current)->left, node)
	          : insertionNode(&(*current)->right, node)))
		return false;

	if ((*current)->left == node || (*current)->right == node)
		node->parent = *current;

	orgInsertionTree(current);
	return true;
}

RedBlackTree* newRedBlackTree() {
	RedBlackTree* tree = (RedBlackTree*)malloc(sizeof(RedBlackTree));
	tree->root = NULL;
	tree->size = 0;

	return tree;
}

void insertionRedBlackTree(RedBlackTree* tree, int obj) {
	Node* node = newNode(obj);

	bool error = !insertionNode(&tree->root, node);

	if (error)
		free(node);
	else
		tree->size++;
	if (rootRedBlackTree) {
		tree->root = rootRedBlackTree;
		rootRedBlackTree = NULL;
	}
	if (tree->root) {
		tree->root->color = BLACK;
		tree->root->parent = NULL;
	}
}

int searchRedBlackTree(RedBlackTree* tree, int info) {
	if (!tree)
		return 0;
	Node* current = tree->root;
	while (current) {
		if (compare(current, info) == 0)
			return current->obj;
		current = (compare(current, info) > 0)
		              ? current->left
		              : current->right;
	}
	return 0;
}

void removeRedBlackTree(RedBlackTree* tree, int info) {
	if (!tree)
		return;
	if (!tree->root) {
		tree->size = 0;
		return;
	}

	if (rootRedBlackTree) {
		tree->root = rootRedBlackTree;
		rootRedBlackTree = NULL;
	}
}

void clearAvlTree(RedBlackTree* tree);
void freeAvlTree(RedBlackTree* tree);

static void printNode(Node* node, int tab) {
	if (node == NULL)
		return;

	printNode(node->right, tab + 1);

	for (int i = 0; i < tab; i++) {
		printf("|\t");
	}
	if (node->color == RED) {
		printf("\033[31m %d / RED \033[0m\n", node->obj);
	} else {
		printf(" %d / BLACK\n", node->obj);
	}
	printNode(node->left, tab + 1);
}

void printRedBlackTree(RedBlackTree* tree) {
	if (!tree->root) {
		printf("Vazio.");
		return;
	}
	printNode(tree->root, 0);
}