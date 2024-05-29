#ifndef CELULA_TIKECT_H
#define CELULA_TIKECT_H

#include "../../Tikect/Tikect.h"

typedef struct node {
	Tikect* content;
	Identifier* key;
	struct node *left, *right;
} Node;

void nodeSetPoints(Node* such, Node* left, Node* right);
Node* nodeNew(Tikect* tikect);

Tikect* nodeGetContent(Node* such);

int nodeSame(Node* such, Node* other);

#endif