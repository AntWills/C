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