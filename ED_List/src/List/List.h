#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int obj;
	struct Node *prior, *next;
} Node;

typedef struct List {
	int size;
	Node *firt, *last;
} List;

List* newList();
List* clearList(List* list);
List* freeList(List* list);

void addList(List* list, int obj);
void addIndexList(List* list, int index, int obj);
void removeList(List* list, int obj);
void removeIndexList(List* list, int index);

int getIndexList(List* list, int index);
void setIndexList(List* list, int index, int obj);

void swapIndexList(List* list, int indexA, int indexB);
void sortList(List* list);

void printList(List* list);
void printReverseList(List* list);

#endif