#ifndef ARV_TIKECT_H
#define ARV_TIKECT_H

#include "NodeTikect/Node.h"
typedef struct {
	Node* source;
	int nacao, num_tikect;
	float valor_arrecado;
} TreeTikect;

TreeTikect* arvTikectNew(int nacao);

void arvTikectInsert(TreeTikect* such, Tikect* new_tikect);

void arvTikectPrint(TreeTikect* such);
void arvTikectPrintDestino(TreeTikect* such, int destino);

Tikect* arvTikectRemove(TreeTikect* such, Identifier* key);
void arvAdd(TreeTikect* tree1, TreeTikect* tree2);

#endif