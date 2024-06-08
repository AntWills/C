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

} Stack;

Stack* newStack();
void freeStack(Stack** stack);

void pushStack(Stack* stack, int);
int popStack(struct Stack* stack);
int topStack(struct Stack* stack);
bool isEmptyStack(struct Stack* stack);
void printStack(struct Stack* stack);

#endif