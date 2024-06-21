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

void printList(List* list) {
	Node* auxi = list->firt;

	while (auxi) {
		printf("%d -> ", auxi->obj);
		auxi = auxi->next;
	}
	printf("NULL.");
}