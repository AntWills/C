#include "SortList.h"

static List* currentList = NULL;

static void swapNodeList(List* list, Node* nodeA, Node* nodeB) {
	Node* nextA = nodeA->next;
	Node* nextB = nodeB->next;

	nodeA->next = nextB;
	nodeB->next = nextA;

	if (nextA)
		nextA->prior = nodeB;
	else
		list->last = nodeB;
	if (nextB)
		nextB->prior = nodeA;
	else
		list->last = nodeA;

	Node* priorA = nodeA->prior;
	Node* priorB = nodeB->prior;

	nodeA->prior = priorB;
	nodeB->prior = priorA;

	if (priorA)
		priorA->next = nodeB;
	else
		list->firt = nodeB;
	if (priorB)
		priorB->next = nodeA;
	else
		list->firt = nodeA;
}

void bubbleSort(List* list) {
	if (!list)
		return;
	Node* auxi = list->firt;
	Node* prior = NULL;
	bool swap = false;

	do {
		swap = false;
		auxi = list->firt;
		prior = auxi;
		auxi = auxi->next;

		while (auxi) {
			if (prior->obj > auxi->obj) {
				swapNodeList(list, prior, auxi);
				swap = true;
			}
			prior = auxi;
			auxi = auxi->next;
		}
	} while (swap);
}

static Node* getNodeRelativeIndex(Node* node, int currentIndex, int getIndex) {
	if (!node)
		return NULL;
	int auxi = getIndex - currentIndex;

	if (auxi > 0) {
		for (int i = 0; i < auxi; i++)
			node = node->next;
	} else {
		// Caso onde o node desejado é anterior ao atual.
	}

	return node;
}

static Node* orgListHeapMin(Node* node, int tam, int index) {
	if (index >= tam) {
		return NULL;
	}
	// filhos a esquerda e direita
	int left = 2 * index + 1;
	int right = 2 * index + 2;

	Node* nodeLeft = NULL;
	Node* nodeRight = NULL;

	if (left < tam) {
		nodeLeft = getNodeRelativeIndex(node, index, left);
		nodeLeft = orgListHeapMin(nodeLeft, tam, left);
	}

	if (right < tam) {
		nodeRight = getNodeRelativeIndex(node, index, right);
		nodeRight = orgListHeapMin(nodeRight, tam, right);
	}

	if (nodeLeft) {
		if (node->obj > nodeLeft->obj) {
			swapNodeList(currentList, node, nodeLeft);
			node = nodeLeft;
		}
	}

	if (nodeRight) {
		if (node->obj > nodeRight->obj) {
			swapNodeList(currentList, node, nodeRight);
			node = nodeRight;
		}
	}
	return node;
}

static Node* orgListHeapMax(Node* node, int tam, int index) {
	if (index >= tam) {
		return NULL;
	}
	// filhos a esquerda e direita
	int left = 2 * index + 1;
	int right = 2 * index + 2;

	Node* nodeLeft = NULL;
	Node* nodeRight = NULL;

	if (left < tam) {
		nodeLeft = getNodeRelativeIndex(node, index, left);
		nodeLeft = orgListHeapMax(nodeLeft, tam, left);
	}

	if (right < tam) {
		nodeRight = getNodeRelativeIndex(node, index, right);
		nodeRight = orgListHeapMax(nodeRight, tam, right);
	}

	if (nodeLeft) {
		if (node->obj < nodeLeft->obj) {
			swapNodeList(currentList, node, nodeLeft);
			node = nodeLeft;
		}
	}

	if (nodeRight) {
		if (node->obj < nodeRight->obj) {
			swapNodeList(currentList, node, nodeRight);
			node = nodeRight;
		}
	}
	return node;
}

/** Organiza a lista usando heapSort.
 *  0 - Crescente.
 *  1 - Decrescente.
 */
void heapSort(List* list, int ordem) {
	currentList = list;
	if (ordem == 0) {
		for (int i = list->size - 1; i >= 0; i--) {
			orgListHeapMax(list->firt, i + 1, 0);
			swapIndexList(list, 0, i);
		}
		currentList = NULL;
		return;
	}
	for (int i = list->size - 1; i >= 0; i--) {
		orgListHeapMin(list->firt, i + 1, 0);
		swapIndexList(list, 0, i);
	}
	currentList = NULL;
}