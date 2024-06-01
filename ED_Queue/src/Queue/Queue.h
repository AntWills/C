#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int info;
	struct Node* next;
} Node;

typedef struct Queue {
	Node *nodeFront, *nodeLast;
	int size;

	void (*enqueue)(struct Queue*, int info);
	int (*dequeue)(struct Queue*);
	int (*front)(struct Queue*);
	bool (*isEmpty)(struct Queue*);
	bool (*contains)(struct Queue*, int element);

	void (*print)(struct Queue*);
} Queue;

Queue* newQueue();
void freeQueue(Queue* queue);

#endif