#include <stdio.h>
#include <stdlib.h>
#include "Stack/Stack.h"

char* boolString(bool yN) {
	if (yN)
		return "YES\0";
	return "NO\0";
}

int main() {
	Stack* stack = newStack();

	for (int i = 1; i <= 5; i++)
		pushStack(stack, rand() % 10);
	printStack(stack);

	printf("\n\nTop: %d.\n", topStack(stack));
	printf("size: %d.\n", stack->size);
	printf("Remove: %d.\n", popStack(stack));
	printf("Remove: %d.\n", popStack(stack));
	printf("size: %d.\n", stack->size);
	printf("Is empty? %s.", boolString(isEmptyStack(stack)));
	freeStack(&stack);
	return 0;
}