#include <stdio.h>
#include "List/List.h"

int main() {
	List* list = newList();
	int vector[] = {5, 7, 2, 1, 6, 0, 8, 9, 3, 4};

	for (int i = 0; i < 10; i++)
		addList(list, vector[i]);

	printList(list);
	printf("\n");
	printReverseList(list);

	printf("\n\n");
	sortList(list);
	printList(list);
	printf("\n");
	printReverseList(list);

	freeList(list);
	return 0;
}