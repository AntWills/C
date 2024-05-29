#ifndef TIKECT_H
#define TIKECT_H

#include "../Date/Date.h"
#include "Identifier/Identifier.h"

typedef struct {
	int destino, nacao;
	Identifier* identifier;
	Date* emissao;
	float preco;
} Tikect;

Tikect* tikectNew(int destino, Date* emissao, float preco);
void printDestinos(int nacao);
Tikect* tikectIn(int nacao);

// void tikectPrint(Tikect* such, char destinos[1][30]);
void tikectPrint(Tikect* such);

Identifier* tikectGetIdentifier(Tikect* such);
int tikectGetNacao(Tikect* such);
int tikectGetDestino(Tikect* such);
int tikectGetNumAleatorio(Tikect* such);

#endif