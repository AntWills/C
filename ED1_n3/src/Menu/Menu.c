#include "Menu.h"

void menu(int* op) {
	printf("\n#    MENU    #\n\n");

	printf("1. Adicionar novo bilhente.\n");
	printf("2. Buscar bilhetes por destino.\n");
	printf("3. Dados da empresa.\n");
	printf("4. Encerrar ano.\n");
	printf("0. Sair.\n\n");

	printf("Digite uma opção: ");
	scanf("%d", op);
}

int setNacao() {
	int nacao;

	printf("\nEscolha uma das nações abaixo: \n");
	printf("1. Brasil.\n");
	printf("2. Argentina.\n");

	printf("\nDigite a nação: ");
	scanf("%d", &nacao);

	return nacao - 1;
}

void inserir(TreeTikect* tree[]) {
	int nacao = setNacao();
	arvTikectInsert(tree[nacao], tikectIn(nacao));
}

void printBilhete(TreeTikect* tree[]) {
	int destinos;
	int nacao = setNacao();
	printDestinos(nacao);
	printf("\nDigite um destino: ");
	scanf("%d", &destinos);

	arvTikectPrintDestino(tree[nacao], destinos);
}

void printDadosTree(TreeTikect* tree[]) {
	printf("\n-- Brasil --\n\n");
	printf("Total de bilhetes vendidos: %d.\n", tree[0]->num_tikect);
	printf("Valor arrecadado: R$ %.2f.\n", tree[0]->valor_arrecado);

	printf("\n-- Argentina --\n\n");
	printf("Total de bilhetes vendidos: %d.\n", tree[1]->num_tikect);
	printf("Valor arrecadado: R$ %.2f.\n", tree[1]->valor_arrecado);

	printf("\n-- Geral --\n\n");
	printf("Total de bilhetes vendidos: %d.\n", tree[2]->num_tikect);
	printf("Valor arrecadado: R$ %.2f.\n", tree[2]->valor_arrecado);
}

void encerrarAno(TreeTikect* tree[]) {
	arvAdd(tree[2], tree[0]);
	arvAdd(tree[2], tree[1]);
}

void opcoes(int op, TreeTikect* tree[]) {
	switch (op) {
	case 1:
		inserir(tree);
		break;
	case 2:
		printBilhete(tree);
		break;
	case 3:
		printDadosTree(tree);
		break;
	case 4:
		encerrarAno(tree);
		break;
	}
}