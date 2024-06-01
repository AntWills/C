#include <stdio.h>
#include <stdlib.h>
#include "Queue/Queue.h"

char* boolString(bool yN) {
	if (yN)
		return "YES\0";
	return "NO\0";
}

int main() {
	int vetorAuxi[] = {10, 7, 1, 14, 0, 3, 9};
	Queue* queue = newQueue();

	for (int i = 0; i < 7; i++)
		queue->enqueue(queue, vetorAuxi[i]);
	queue->print(queue);

	printf("\nNumber elements: %d.\n", queue->size);
	queue->dequeue(queue);
	queue->dequeue(queue);
	printf("Number elements: %d.\n", queue->size);
	printf("Front: %d.\n", queue->front(queue));
	printf("Contain 5? %s.\n", boolString(queue->contains(queue, 5)));
	printf("Contain 0? %s.\n", boolString(queue->contains(queue, 0)));
	printf("Is empty? %s.\n", boolString(queue->isEmpty(queue)));
	freeQueue(&queue);
	return 0;
}