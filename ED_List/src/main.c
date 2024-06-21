#include <stdio.h>
#include "List/List.h"

int main() {
	List* list = newList();

	freeList(list);
	return 0;
}