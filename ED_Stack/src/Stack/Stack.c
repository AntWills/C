#include "Stack.h"

bool isEmptyStack(Stack* stack) {
	if (!stack)
		return true;
	if (!stack->root)
		return true;
	return false;
}

void pushStack(Stack* stack, int info) {
	if (!stack)
		return;
	stack->size++;

	Node* node = (Node*)malloc(sizeof(Node));

	if (!node)
		return;

	node->info = info;
	node->next = NULL;

	if (isEmptyStack(stack)) {
		stack->root = node;
		return;
	}

	node->next = stack->root;
	stack->root = node;
}

int popStack(Stack* stack) {
	if (!stack)
		return -1;
	if (isEmptyStack(stack))
		return -1;
	stack->size--;
	Node* node = stack->root;

	stack->root = node->next;
	int auxi = node->info;
	free(node);
	return auxi;
}

int topStack(Stack* stack) {
	if (!stack)
		return -1;
	if (!isEmptyStack(stack))
		return stack->root->info;
	return -1;
}

void printStack(Stack* stack) {
	if (!stack)
		return;

	Node* auxi = stack->root;
	while (auxi) {
		printf("%d -> ", auxi->info);
		auxi = auxi->next;
	}
	printf("NULL.");
}

Stack* newStack() {
	Stack* stack = (Stack*)malloc(sizeof(Stack));
	stack->root = NULL;
	stack->size = 0;

	if (!stack)
		return NULL;
}

void freeStack(Stack** stack) {
	if (!stack)
		return;
	if (isEmptyStack(*stack)) {
		free(stack);
		return;
	}

	Node* node = (*stack)->root->next;
	Node* ant = (*stack)->root;

	while (node) {
		free(ant);
		ant = node;
		node = node->next;
	}
	free(ant);
	free(*stack);
	*stack = NULL;
}