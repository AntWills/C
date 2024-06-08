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
		enqueue(queue, vetorAuxi[i]);
	printQueue(queue);

	printf("\nNumber elements: %d.\n", queue->size);
	dequeue(queue);
	dequeue(queue);
	printf("Number elements: %d.\n", queue->size);
	printf("Front: %d.\n", frontQueue(queue));
	printf("Contain 5? %s.\n", boolString(containsQueue(queue, 5)));
	printf("Contain 0? %s.\n", boolString(containsQueue(queue, 0)));
	printf("Is empty? %s.\n", boolString(isEmptyQueue(queue)));
	freeQueue(&queue);
	return 0;
}