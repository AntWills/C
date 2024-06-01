#include "Queue.h"

static void enqueue(Queue* current, int info) {
	if (!current)
		return;
	Node* node = (Node*)malloc(sizeof(Node));
	if (!node)
		return;
	current->size++;
	node->info = info;
	node->next = NULL;

	if (current->isEmpty(current)) {
		current->nodeFront = node;
		current->nodeLast = node;
		return;
	}

	current->nodeLast->next = node;
	current->nodeLast = node;
}

static int dequeue(Queue* current) {
	if (!current)
		return 0;
	if (current->isEmpty(current))
		return 0;
	current->size--;
	Node* auxi = current->nodeFront;

	if (current->nodeFront == current->nodeLast)
		current->nodeLast = NULL;

	current->nodeFront = auxi->next;

	int info = auxi->info;
	free(auxi);
	return info;
}

static int front(Queue* current) {
	if (!current)
		return 0;
	if (current->isEmpty(current))
		return 0;

	return current->nodeFront->info;
}

static bool isEmpty(Queue* current) {
	if (!current)
		return true;
	if (!current->nodeFront)
		return true;

	return false;
}

static bool contains(Queue* current, int info) {
	if (!current)
		return false;
	if (current->isEmpty(current))
		return false;

	Node* auxi = current->nodeFront;
	while (auxi) {
		if (auxi->info == info)
			return true;
		auxi = auxi->next;
	}
	return false;
}

static void print(Queue* current) {
	if (!current)
		return;
	Node* auxi = current->nodeFront;
	while (auxi) {
		printf("%d -> ", auxi->info);
		auxi = auxi->next;
	}
	printf("NULL.");
}

Queue* newQueue() {
	Queue* queue = (Queue*)malloc(sizeof(Queue));

	if (!queue)
		return NULL;

	queue->size = 0;
	queue->nodeFront = NULL;
	queue->nodeLast = NULL;

	queue->enqueue = enqueue;
	queue->dequeue = dequeue;
	queue->front = front;
	queue->isEmpty = isEmpty;
	queue->contains = contains;
	queue->print = print;

	return queue;
}

void freeQueue(Queue** current) {
	if (!current)
		return;
	if ((*current)->isEmpty(*current)) {
		free(current);
		return;
	}

	Node* node = (*current)->nodeFront->next;
	Node* ant = (*current)->nodeFront;

	while (node) {
		free(ant);
		ant = node;
		node = node->next;
	}
	free(ant);
	free(*current);
	*current = NULL;
}