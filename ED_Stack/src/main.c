#include <stdio.h>
#include <stdlib.h>
#include "Stack/Stack.h"

int main() {
	Stack* stack = newStack();

	for (int i = 1; i <= 5; i++)
		stack->push(stack, rand() % 10);
	stack->print(stack);

	printf("\n\nTop: %d.\n", stack->top(stack));
	printf("size: %d.", stack->size);
	freeStack(stack);
	return 0;
}