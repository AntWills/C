#include "RedBlakcTree.h"

static Node* newNode(int obj) {
	Node* node = (Node*)malloc(sizeof(Node));
	node->obj = obj;
	node->color = RED;
	node->left = NULL;
	node->right = NULL;

	return node;
}

static void freeNode(Node* node) {
	free(node);
}

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

static void rotationRight(Node** root, bool mudarDeCor) {
	Node* node = (*root)->left;

	(*root)->left = node->right;
	node->right = *root;

	if (mudarDeCor) {
		(*root)->color = RED;
		node->color = BLACK;
	}

	*root = node;
}

static void rotationLeft(Node** root, bool alterColor) {
	Node* node = (*root)->right;

	(*root)->right = node->left;
	node->left = *root;

	if (alterColor) {
		(*root)->color = RED;
		node->color = BLACK;
	}

	*root = node;
}

static void doubleRotationRight(Node** node) {
	rotationLeft(&(*node)->left, false);
	rotationRight(node, true);
}

static void doubleRotationLeft(Node** root) {
	rotationRight(&(*root)->right, false);
	rotationLeft(root, true);
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
			rotationRight(node, true);
		else if (getColor((*node)->left->right))
			doubleRotationRight(node);
		return;
	}

	if (getColor((*node)->right->right) == RED)
		rotationLeft(node, true);
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
	if (tree->root)
		tree->root->color = BLACK;
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

static Node* getBrother(Node* preceding, Node* current) {
	return (compare(preceding, current) > 0)
	           ? preceding->right
	           : preceding->left;
}

static void setChildren(Node* preceding,
                        Node* currentChildren,
                        Node* newChildren) {
	if (compare(preceding, currentChildren) > 0)
		preceding->left = newChildren;
	else
		preceding->right = newChildren;
}

//
static Node* auxiGetNode(Node* node) {
	static Node* auxi;
	if (node) {
		auxi = node;
		return NULL;
	}
	return auxi;
}

static int getAction(Node** preceding,
                     Node* nodeBlackBlack,
                     Node* brother) {
	if (!nodeBlackBlack && !brother)
		return 0;
	if (getColor(brother) == RED) {
		if (compare(*preceding, brother) > 0)
			return 2;  //
		return 1;
	}
	Color left = getColor(brother->left);
	Color right = getColor(brother->right);

	if (getColor(brother->left) == BLACK && getColor(brother->right) == BLACK) {
		return 3;
	}

	if (getColor(brother->left) == BLACK) {
		if (compare(*preceding, brother) > 0)
			return 5;
		return 4;
	}
}

static int orgRemoveTree(Node** preceding,
                         Node* nodeBlackBlack,
                         Node* brother) {
	Node* teste = NULL;
	switch (getAction(preceding, nodeBlackBlack, brother)) {
	case 1:
		// { irmão RED }
		// irmão vire BLACK e pai vira RED.
		// e depois rotacionar o pai para esquerda.
		// chama novamente a função orgRemoveTree.
		rotationLeft(preceding, true);
		teste = (*preceding)->left;
		return true;
		break;
	case 2:
		// { irmão RED }
		// irmão vire BLACK e pai vira RED.
		// e depois rotacionar o pai para esquerda.
		// chama novamente a função orgRemoveTree.
		rotationRight(preceding, true);
		teste = (*preceding)->right;
		return true;
		break;
	case 3:
		// { irmão BLACK, com filhos BLACK }
		// irmão fica RED,
		// se p pai for RED, fica BLACK e encerrar.
		// se não for, subir a verificação para o pai.
		brother->color = RED;
		if (getColor(*preceding) == RED) {
			(*preceding)->color = BLACK;
			return false;
		}
		return true;
		break;
	case 4:

		break;
	case 5:
		// { irmão BLACK e um dos filhos BLACK }
		// irmão fica RED e rotação a direita no filho a esquerda.

		brother->color = RED;
		rotationRight(&brother->left, false);
		break;
	}
}

static int removeBiggerNodeLeft(Node** preceding,
                                Node* nodeRemove,
                                Color nodeColor) {
	if (!nodeRemove)
		return false;
	if (nodeRemove->right) {
		if (!removeBiggerNodeLeft(&nodeRemove, nodeRemove->right, nodeColor))
			return false;
	} else if (getColor(nodeRemove) == RED) {
		setChildren(*preceding, nodeRemove, nodeRemove->left);
		auxiGetNode(nodeRemove);
		return false;
	} else if (getColor(nodeRemove->left) == RED) {
		nodeRemove->left->color = BLACK;
		setChildren(*preceding, nodeRemove, nodeRemove->left);
		auxiGetNode(nodeRemove);
		return false;
	} else {
		setChildren(*preceding, nodeRemove, nodeRemove->left);
		auxiGetNode(nodeRemove);
	}

	return orgRemoveTree(preceding, nodeRemove->left,
	                     getBrother(*preceding, nodeRemove));
}

// static Node* getBiggerNodeLeft(Node* current) {
// 	if (!current)
// 		return NULL;
// 	while (current->right)
// 		current = current->right;
// 	return current;
// }

static int removeNode(Node** preceding, Node* current) {
	// Node* bigLeft = getBiggerNodeLeft(current->left);
	bool auxi = true;
	Node* nodeAuxi = NULL;

	if (!current->left && !current->right) {
		if (getColor(current) == RED) {
			auxi = false;
		}

		setChildren(*preceding, current, NULL);
	} else if (!current->left) {
		setChildren(*preceding, current, current->right);
	} else {
		auxi = removeBiggerNodeLeft(&current, current->left, getColor(current));
		nodeAuxi = auxiGetNode(NULL);

		nodeAuxi->left = current->left;
		nodeAuxi->right = current->right;
		nodeAuxi->color = current->color;

		setChildren(*preceding, current, nodeAuxi);
	}
	if (!auxi) {
		freeNode(current);
		return false;
	}

	orgRemoveTree(preceding, nodeAuxi, getBrother(*preceding, current));
	freeNode(current);
}

static int removeSearchNode(Node** preceding,
                            Node* current,
                            int obj) {
	if (!current)
		return false;

	if (compare(current->obj, obj) == 0) {
		return removeNode(preceding, current);
	}

	if (!(compare(current->obj, obj) > 0
	          ? removeSearchNode(&current, current->left, obj)
	          : removeSearchNode(&current, current->right, obj))) {
		return false;
	}
}

void removeRedBlackTree(RedBlackTree* tree, int info) {
	if (!tree)
		return;
	if (!tree->root) {
		tree->size = 0;
		return;
	}

	if (compare(tree->root->obj, info) == 0) {
		// removeNode()
	}
	removeSearchNode(NULL, tree->root, info);
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