#include "Tikect.h"

Tikect* tikectNew(int destino, Date* emissao, float preco) {
	Tikect* new_tikect = (Tikect*)malloc(sizeof(Tikect));

	new_tikect->destino = destino;
	new_tikect->identifier = NULL;
	new_tikect->emissao = emissao;
	new_tikect->preco = preco;

	return new_tikect;
}

char destinos[2][4][30] = {
    {{"São Luiz"}, {"Brasilia"}, {"Caxias"}, {"Teresina"}},
    {{"Buenos Aires"}, {"Salta"}, {"Córdova"}, {"La Plata"}}};

void printDestinos(int nacao) {
	printf("\nEscolha um dos destinos: \n");
	for (int i = 0; i < 4; i += 2) {
		printf("%02d - %s\t\t%02d - %s.\n", (i), destinos[nacao][i], (i + 1), destinos[nacao][i + 1]);
	}
}

Tikect* tikectIn(int nacao) {
	Tikect* new_tikect = (Tikect*)malloc(sizeof(Tikect));
	new_tikect->nacao = nacao;

	printDestinos(nacao);
	printf("\nDigite o destino: ");
	scanf("%d", &new_tikect->destino);
	new_tikect->emissao = dateIn();
	printf("\nDigite o preço: ");
	scanf("%f", &new_tikect->preco);

	return new_tikect;
}

void tikectPrint(Tikect* such) {
	printf("\nDestino: %s.\n", destinos[tikectGetNacao(such)][tikectGetDestino(such)]);
	printf("Localizador: ");
	identifierPrint(such->identifier);
	printf(".\n");
	printf("Data de emissão: ");
	datePrint(such->emissao);
	printf("\nPreço: %.2f.\n", such->preco);
}

Identifier* tikectGetIdentifier(Tikect* such) {
	return such->identifier;
}

int tikectGetNacao(Tikect* such) {
	return such->identifier->nacao;
}

int tikectGetDestino(Tikect* such) {
	return such->identifier->destino;
}

int tikectGetNumAleatorio(Tikect* such) {
	return such->identifier->num_aleatorio;
}