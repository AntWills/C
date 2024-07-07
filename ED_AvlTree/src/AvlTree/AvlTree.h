#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
	int obj;
	int height;
	struct Node *left, *right;
} Node;

typedef struct AvlTree {
	Node* root;
	int size;
} AvlTree;

AvlTree* newAvlTree();
void insertAvlTree(AvlTree* tree, int obj);
int searchAvlTree(AvlTree* tree, int info);
void removeAvlTree(AvlTree* tree, int info);
void clearAvlTree(AvlTree* tree);
void freeAvlTree(AvlTree* tree);

void printAvlTree(AvlTree* tree);

#endif