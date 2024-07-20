#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#define BLACK 0
#define RED 1

typedef int Color;

typedef struct Node {
	int obj;
	Color color;
	struct Node *left, *right;
} Node;

typedef struct RedBlackTree {
	Node* root;
	int size;
} RedBlackTree;

#endif