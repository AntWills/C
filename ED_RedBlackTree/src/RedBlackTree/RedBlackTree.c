#include "RedBlakcTree.h"

static Node* auxiRootRedBlackTree = NULL;

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
static int compareFloat(float a, float b);
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
	node->parent = parent;
	if (root->left)
		root->left->parent = root;
	if (!parent) {
		auxiRootRedBlackTree = node;
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
	node->parent = parent;
	if (root->right)
		root->right->parent = root;
	if (!parent) {
		auxiRootRedBlackTree = node;
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

static bool OneRedSon(Node* node) {
	if (!node)
		return false;
	if (getColor(node->left) == RED ||
	    getColor(node->right) == RED)
		return true;
	return false;
}

static bool twoBlackSon(Node* node) {
	if (!node)
		return false;
	if (getColor(node->left) == BLACK &&
	    getColor(node->right) == BLACK)
		return true;
	return false;
}

static void orgInsertionTree(Node** node) {
	if (!(*node) || twoBlackSon(*node))
		return;

	// Verifica se tem dois filhos vermelhos.
	if (getColor((*node)->left) == RED &&
	    getColor((*node)->right) == RED) {
		// Se tiver, verificar se tem netos vermelhos.
		if (OneRedSon((*node)->left) || OneRedSon((*node)->right)) {
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
	if (auxiRootRedBlackTree) {
		tree->root = auxiRootRedBlackTree;
		auxiRootRedBlackTree = NULL;
	}
	if (tree->root) {
		tree->root->color = BLACK;
		tree->root->parent = NULL;
	}
}

static Node* searchNode(Node* current, int info) {
	while (current) {
		if (compare(current, info) == 0)
			return current;
		current = (compare(current, info) > 0)
		              ? current->left
		              : current->right;
	}
	return NULL;
}

int searchRedBlackTree(RedBlackTree* tree, int info) {
	if (!tree)
		return 0;
	Node* node = searchNode(tree->root, info);
	if (node)
		return node->obj;
	return 0;
}

static Node* getMaxNodeInLeft(Node* node) {
	if (!node)
		return NULL;
	while (node->right)
		node = node->right;
	return node;
}

static Node* getMinNodeInRight(Node* node) {
	if (!node)
		return NULL;
	while (node->left)
		node = node->left;
	return node;
}

static Node* fixOrRaiseLeft(Node* removeNode, Node* parent, Node* root) {
	Node* brother = parent->right;

	if (getColor(brother) == RED) {
		rotationLeft(parent, true);
		brother = parent->right;
	}

	// Caso onde a elevação do problema é necessaria.
	if (twoBlackSon(brother)) {
		brother->color = RED;

		// Se o pai também for vermelho, há uma exceção e
		// encerramos a verificação.
		// Se não for, procede normalmente.
		if (parent->color == RED) {
			parent->color = BLACK;
			return root;
		}
		return parent;
	}

	// Ajuste para caso o sobrinho a esquerda seja vermeho.
	if (getColor(brother->right) == BLACK) {
		rotationRight(brother, true);
		brother = parent->right;
	}

	// Se o sobrinho a direita já for vermelho, execute os passos seguinte
	// e encerre.
	brother->color = parent->color;
	parent->color = BLACK;
	brother->right->color = BLACK;
	rotationLeft(parent, false);
	return root;
}

static Node* fixOrRaiseRight(Node* removeNode, Node* parent, Node* root) {
	Node* brother = parent->left;

	// // Irmão vermelho.
	if (getColor(brother) == RED) {
		rotationRight(parent, true);
		brother = parent->right;
	}

	// Caso onde a elevação do problema é necessaria.
	if (twoBlackSon(brother)) {
		brother->color = RED;

		// Se o pai também for vermelho, há uma exceção e encerramos a verificação.
		// Se não for, procede normalmente.
		if (parent->color == RED) {
			parent->color = BLACK;
			return root;
		}
		return parent;
	}

	// Ajuste para caso o sobrinho a direita seja vermeho.
	if (getColor(brother->left) == BLACK) {
		rotationLeft(brother, true);
		brother = parent->left;
	}

	// Se o sobrinho a esquerda já for vermelho, execute os passos seguinte
	// e encerre.
	brother->color = parent->color;
	parent->color = BLACK;
	brother->left->color = BLACK;
	rotationRight(parent, false);
	return root;
}

static void fixOrRaise(Node* removeNode, Node* parent, Node* root) {
	while (removeNode != root) {
		if (parent->left == removeNode)
			removeNode = fixOrRaiseLeft(removeNode, parent, root);
		else
			removeNode = fixOrRaiseRight(removeNode, parent, root);
		parent = removeNode->parent;
	}
}

static bool simpleRemoveLeft(Node* succesor, Node* current) {
	if (getColor(succesor) == RED) {
		if (current->left == succesor)
			current->left = succesor->left;
		else
			succesor->parent->right = succesor->left;
		if (succesor->left)
			succesor->left->parent = succesor->parent;
		return true;
	}

	if (getColor(succesor->left) == RED) {
		succesor->left->color = BLACK;
		if (current->left == succesor)
			current->left = succesor->left;
		else
			succesor->parent->right = succesor->left;
		if (succesor->left)
			succesor->left->parent = succesor->parent;
		return true;
	}
	return false;
}

static bool simpleRemoveRight(Node* succesor, Node* current) {
	if (getColor(succesor) == RED) {
		if (current->right == succesor)
			current->right = succesor->right;
		else
			succesor->parent->left = succesor->right;
		if (succesor->right)
			succesor->right->parent = succesor->parent;
		return true;
	}

	if (getColor(succesor->right) == RED) {
		succesor->right->color = BLACK;
		if (current->right == succesor)
			current->right = succesor->right;
		else
			succesor->parent->left = succesor->right;
		if (succesor->right)
			succesor->right->parent = succesor->parent;
		return true;
	}
	return false;
}

static Node* removeNode(Node* removeNode, Node* root) {
	Node* succesor = removeNode->left
	                     ? getMaxNodeInLeft(removeNode->left)
	                     : getMinNodeInRight(removeNode->right);

	if (!succesor) {
		if (getColor(removeNode) == RED) {
			if (removeNode->parent->left == removeNode)
				removeNode->parent->left = NULL;
			else
				removeNode->parent->right = NULL;
			return removeNode;
		}
		succesor = removeNode;
	} else
		removeNode->obj = succesor->obj;

	if ((succesor->left)
	        ? simpleRemoveLeft(succesor, removeNode)
	        : simpleRemoveRight(succesor, removeNode))
		return succesor;

	fixOrRaise(succesor, succesor->parent, root);

	if (removeNode->left == succesor) {
		removeNode->left = succesor->left;
		return succesor;
	} else if (removeNode->right == succesor) {
		removeNode->right = succesor->left;
		return succesor;
	}

	if (succesor->parent->left == succesor) {
		succesor->parent->left = succesor->right;
		if (succesor->right)
			succesor->right->parent = succesor->parent;
	} else {
		succesor->parent->right = succesor->left;
		if (succesor->left)
			succesor->left->parent = succesor->parent;
	}

	return succesor;
}

void removeRedBlackTree(RedBlackTree* tree, int info) {
	if (!tree)
		return;
	if (!tree->root) {
		tree->size = 0;
		return;
	}

	Node* current = searchNode(tree->root, info);
	if (!current)
		return;
	if (!current->parent && !current->left && !current->right) {
		freeNode(current);
		tree->root = NULL;
		tree->size = 0;
		return;
	}

	freeNode(removeNode(current, tree->root));

	tree->size--;
	if (auxiRootRedBlackTree) {
		tree->root = auxiRootRedBlackTree;
		auxiRootRedBlackTree = NULL;
	}
}

void clearRedBlackTree(RedBlackTree* tree) {
	while (tree->root)
		removeRedBlackTree(tree, tree->root->obj);
}

void freeRedBlackTree(RedBlackTree* tree) {
	clearRedBlackTree(tree);
	free(tree);
}

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