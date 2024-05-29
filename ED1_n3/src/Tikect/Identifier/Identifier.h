#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int nacao, destino, num_aleatorio;
} Identifier;

Identifier* identifierNew(int nacao, int destino, int num);
Identifier* identifierInput();

void identifierPrint(Identifier* such);

int identifierSame(Identifier* such, Identifier* other);

#endif