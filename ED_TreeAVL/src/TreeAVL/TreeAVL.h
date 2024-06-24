#ifndef TREEAVL_H
#define TREEAVL_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int obj;
	struct Node *left, *right;
} Node;

typedef struct TreeAVL {
	Node* root;
	int size;
} TreeAVL;

TreeAVL* newTreeAVL();
void clearTreeAVL(TreeAVL* tree);
void insertTreeAVL(TreeAVL* tree, int obj);
int searchTreeAVL(TreeAVL* tree, int obj);
void removeTreeAVL(TreeAVL* tree, int obj);

void printTreeAVL(TreeAVL* tree);

#endif