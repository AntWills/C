#include "Stack.h"

static void push(Stack* current, int info) {
	if (!current)
		return;
	current->size++;

	Node* node = (Node*)malloc(sizeof(Node));

	if (!node)
		return;

	node->info = info;
	node->next = NULL;

	if (current->isEmpty(current)) {
		current->root = node;
		return;
	}

	node->next = current->root;
	current->root = node;
}

static int pop(Stack* current) {
	if (!current)
		return -1;
	if (!current->isEmpty(current))
		return -1;
	current->size--;
	Node* node = current->root;

	current->root = node->next;
	int auxi = node->info;
	free(node);
	return auxi;
}

static int top(Stack* current) {
	if (!current)
		return -1;
	if (!current->isEmpty(current))
		return current->root->info;
	return -1;
}

static bool isEmpty(Stack* current) {
	if (!current)
		return false;
	if (current->root)
		return false;
	return true;
}

static void print(Stack* current) {
	if (!current)
		return;

	Node* auxi = current->root;
	while (auxi) {
		printf("%d -> ", auxi->info);
		auxi = auxi->next;
	}
	printf("NULL.");
}

Stack* newStack() {
	Stack* stack = (Stack*)malloc(sizeof(Stack));

	if (!stack)
		return NULL;

	stack->root = NULL;
	stack->size = 0;
	stack->push = push;
	stack->pop = pop;
	stack->top = top;
	stack->isEmpty = isEmpty;
	stack->print = print;
}

void freeStack(Stack* current) {
	if (!current)
		return;
	if (current->isEmpty(current))
		return;
	Node* ant = current->root;
	Node* auxi = current->root->next;

	while (auxi) {
		free(ant);
		ant = auxi;
		auxi = auxi->next;
	}
	free(ant);
	free(current);
}