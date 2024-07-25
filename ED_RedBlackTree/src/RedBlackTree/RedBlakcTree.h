#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define BLACK 0
#define RED 1

typedef int Color;

typedef struct Node {
	int obj;
	Color color;
	struct Node *left, *right, *parent;
} Node;

typedef struct RedBlackTree {
	Node* root;
	int size;
} RedBlackTree;

RedBlackTree* newRedBlackTree();
void insertionRedBlackTree(RedBlackTree* tree, int obj);
int searchRedBlackTree(RedBlackTree* tree, int info);
void removeRedBlackTree(RedBlackTree* tree, int info);
void clearRedBlackTree(RedBlackTree* tree);
void freeRedBlackTree(RedBlackTree* tree);

void printRedBlackTree(RedBlackTree* tree);

#endif