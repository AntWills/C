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

} Queue;

Queue* newQueue();
void freeQueue(Queue** queue);

void enqueue(struct Queue* queue, int info);
int dequeue(struct Queue* queue);
int frontQueue(struct Queue* queue);
bool isEmptyQueue(struct Queue* queue);
bool containsQueue(struct Queue* queue, int element);

void printQueue(struct Queue*);

#endif