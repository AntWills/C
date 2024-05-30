#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int info;
	struct Node* next;
} Node;

typedef struct Stack {
	Node* root;
	int size;
	void (*push)(struct Stack*, int);
	int (*pop)(struct Stack*);
	int (*top)(struct Stack*);
	bool (*isEmpty)(struct Stack*);

	void (*print)(struct Stack*);
} Stack;

Stack* newStack();
void freeStack();

#endif