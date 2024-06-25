#ifndef TREEAVL_H
#define TREEAVL_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int obj;
	int height;
	struct Node *left, *right;
} Node;

typedef struct TreeAVL {
	Node* root;
	int size;
} TreeAVL;

TreeAVL* newTreeAVL();
void insertTreeAVL(TreeAVL* tree, int obj);
int searchTreeAVL(TreeAVL* tree, int obj);
void removeTreeAVL(TreeAVL* tree, int info);
void clearTreeAVL(TreeAVL* tree);
void freeTreeAVL(TreeAVL* tree);

void printTreeAVL(TreeAVL* tree);

#endif