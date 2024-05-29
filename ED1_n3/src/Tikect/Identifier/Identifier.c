#include "Identifier.h"

Identifier* identifierNew(int nacao, int destino, int num) {
	Identifier* new_identifier = (Identifier*)malloc(sizeof(Identifier));

	new_identifier->nacao = nacao;
	new_identifier->destino = destino;
	new_identifier->num_aleatorio = num;

	return new_identifier;
}

void identifierPrint(Identifier* such) {
	if (!such) {
		printf("Error. Null element.");
	}
	printf("%02d.%02d.%04d", such->nacao, such->destino, such->num_aleatorio);
}

/**
 * Retorna 0 se forem iguais;
 * Retorna -1 se quem chama for maior;
 * Retorna 1 se quem chama for menor;
 */
int identifierSame(Identifier* such, Identifier* other) {
	if (such->nacao == other->nacao)
		if (such->destino == other->destino)
			if (such->num_aleatorio == other->num_aleatorio)
				return 0;

	if (such->nacao > other->nacao)
		return 1;
	if (such->nacao < other->nacao)
		return -1;

	if (such->destino > other->destino)
		return 1;
	if (such->destino < other->destino)
		return -1;

	if (such->num_aleatorio > other->num_aleatorio)
		return 1;
	return -1;
}