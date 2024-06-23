#include "List.h"

static Node* newNode(int obj, Node* prior, Node* next) {
	Node* node = (Node*)malloc(sizeof(Node));
	if (!node)
		return NULL;
	node->obj = obj;
	node->prior = prior;
	node->next = next;

	return node;
}

static Node* getNodeIndexList(List* list, int index) {
	if (index < 0 || index > (list->size - 1))
		return NULL;
	int position = 0;
	Node* auxi = NULL;

	if (index > ((list->size - 1) / 2)) {
		position = (list->size - 1);
		auxi = list->last;

		while (auxi) {
			if (position == index)
				return auxi;
			position--;
			auxi = auxi->prior;
		}
	}

	auxi = list->firt;
	while (auxi) {
		if (position == index)
			return auxi;
		position++;
		auxi = auxi->next;
	}
}

static Node* getNodeList(List* list, int obj) {
	Node* auxi = NULL;

	auxi = list->firt;
	while (auxi) {
		if (auxi->obj == obj)
			return auxi;
		auxi = auxi->next;
	}
	return NULL;
}

static void removeNode(List* list, Node* node) {
	if (node->prior)
		node->prior->next = node->next;
	else
		list->firt = node->next;

	if (node->next)
		node->next->prior = node->prior;
	else
		list->last = node->prior;
}

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

List* newList() {
	List* list = (List*)malloc(sizeof(List));
	if (!list)
		return NULL;
	list->firt = NULL;
	list->last = NULL;
	list->size = 0;

	return list;
}

List* clearList(List* list) {
	Node* auxi = list->firt;
	Node* ant = NULL;

	while (auxi) {
		ant = auxi;
		auxi = auxi->next;
		free(ant);
	}
	list->firt = NULL;
	list->last = NULL;
	list->size = 0;
}

List* freeList(List* list) {
	clearList(list);
	free(list);
}

void addList(List* list, int obj) {
	if (!list)
		return;

	Node* node = newNode(obj, NULL, NULL);
	if (!node)
		return;

	list->size++;
	if (!list->firt) {
		list->firt = node;
		list->last = node;
		return;
	}

	list->last->next = node;
	node->prior = list->last;
	list->last = node;
}

void addIndexList(List* list, int index, int obj) {
	Node* nodeIndex = getNodeIndexList(list, index);
	if (!nodeIndex)
		return;

	Node* node = newNode(obj, NULL, NULL);
	if (!node)
		return;

	if (!nodeIndex->prior)
		list->firt = node;
	else {
		nodeIndex->prior->next = node;
		node->prior = nodeIndex->prior;
	}

	nodeIndex->prior = node;
	node->next = nodeIndex;
}

void removeList(List* list, int obj) {
	Node* node = getNodeList(list, obj);
	if (!node)
		return;
	removeNode(list, node);
	list->size--;
	free(node);
}

void removeIndexList(List* list, int index) {
	Node* node = getNodeIndexList(list, index);
	if (!node)
		return;
	removeNode(list, node);
	list->size--;
	free(node);
}

int getIndexList(List* list, int index) {
	Node* node = getNodeIndexList(list, index);
	if (!node)
		return 0;
	return node->obj;
}

void setIndexList(List* list, int index, int obj) {
	Node* node = getNodeIndexList(list, index);
	if (!node)
		return;
	node->obj = obj;
}

void swapIndexList(List* list, int indexA, int indexB) {
	if (indexA == indexB)
		return;
	Node* nodeA = getNodeIndexList(list, indexA);
	Node* nodeB = getNodeIndexList(list, indexB);
	if (!nodeA || !nodeB)
		return;
	swapNodeList(list, nodeA, nodeB);
}

void printList(List* list) {
	Node* auxi = list->firt;

	while (auxi) {
		printf("%d -> ", auxi->obj);
		auxi = auxi->next;
	}
	printf("NULL.");
}

void printReverseList(List* list) {
	Node* auxi = list->last;

	printf("NULL");
	while (auxi) {
		printf(" <- %d", auxi->obj);
		auxi = auxi->prior;
	}
	printf(".");
}

void sortList(List* list) {
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