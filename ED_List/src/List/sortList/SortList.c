#include "SortList.h"

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

static void orgListHeapMin(List* vetor, int tam, int index) {
	if (index >= tam) {
		return;
	}
	// filhos a esquerda e direita
	int left = 2 * index + 1;
	int right = 2 * index + 2;

	if (left < tam)
		orgListHeapMin(vetor, tam, left);

	if (right < tam)
		orgListHeapMin(vetor, tam, right);

	if (left < tam)
		if (getIndexList(vetor, index) > getIndexList(vetor, left))
			swapIndexList(vetor, index, left);
	if (right < tam)
		if (getIndexList(vetor, index) > getIndexList(vetor, right))
			swapIndexList(vetor, index, right);
}

static void orgListHeapMax(List* vetor, int tam, int index) {
	if (index >= tam) {
		return;
	}
	// filhos a esquerda e direita
	int left = 2 * index + 1;
	int right = 2 * index + 2;

	if (left < tam)
		orgListHeapMax(vetor, tam, left);

	if (right < tam)
		orgListHeapMax(vetor, tam, right);

	if (left < tam)
		if (getIndexList(vetor, index) < getIndexList(vetor, left))
			swapIndexList(vetor, index, left);
	if (right < tam)
		if (getIndexList(vetor, index) < getIndexList(vetor, right))
			swapIndexList(vetor, index, right);
}

/** Organiza a lista usando heapSort.
 *  0 - Crescente.
 *  1 - Decrescente.
 */
void heapSort(List* list, int ordem) {
	if (ordem == 0) {
		for (int i = list->size - 1; i >= 0; i--) {
			orgListHeapMax(list, i + 1, 0);
			swapIndexList(list, 0, i);
		}
		return;
	}
	for (int i = list->size - 1; i >= 0; i--) {
		orgListHeapMin(list, i + 1, 0);
		swapIndexList(list, 0, i);
	}
}