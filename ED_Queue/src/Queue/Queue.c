#include "Queue.h"

bool isEmptyQueue(Queue* queue) {
	if (!queue)
		return true;
	if (!queue->nodeFront)
		return true;

	return false;
}

void enqueue(Queue* queue, int info) {
	if (!queue)
		return;
	Node* node = (Node*)malloc(sizeof(Node));
	if (!node)
		return;
	queue->size++;
	node->info = info;
	node->next = NULL;

	if (isEmptyQueue(queue)) {
		queue->nodeFront = node;
		queue->nodeLast = node;
		return;
	}

	queue->nodeLast->next = node;
	queue->nodeLast = node;
}

int dequeue(Queue* queue) {
	if (!queue)
		return 0;
	if (isEmptyQueue(queue))
		return 0;
	queue->size--;
	Node* auxi = queue->nodeFront;

	if (queue->nodeFront == queue->nodeLast)
		queue->nodeLast = NULL;

	queue->nodeFront = auxi->next;

	int info = auxi->info;
	free(auxi);
	return info;
}

int frontQueue(Queue* queue) {
	if (!queue)
		return 0;
	if (isEmptyQueue(queue))
		return 0;

	return queue->nodeFront->info;
}

bool containsQueue(Queue* queue, int info) {
	if (!queue)
		return false;
	if (isEmptyQueue(queue))
		return false;

	Node* auxi = queue->nodeFront;
	while (auxi) {
		if (auxi->info == info)
			return true;
		auxi = auxi->next;
	}
	return false;
}

void printQueue(Queue* queue) {
	if (!queue)
		return;
	Node* auxi = queue->nodeFront;
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

	return queue;
}

void freeQueue(Queue** queue) {
	if (!queue)
		return;
	if (isEmptyQueue(*queue)) {
		free(queue);
		return;
	}

	Node* node = (*queue)->nodeFront->next;
	Node* ant = (*queue)->nodeFront;

	while (node) {
		free(ant);
		ant = node;
		node = node->next;
	}
	free(ant);
	free(*queue);
	*queue = NULL;
}