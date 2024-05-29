#include "Date.h"

Date* dateNew(int dia, int mes, int ano) {
	Date* new_date = (Date*)malloc(sizeof(Date));

	new_date->dia = dia;
	new_date->mes = mes;
	new_date->ano = ano;

	return new_date;
}

Date* dateIn() {
	Date* new_date = (Date*)malloc(sizeof(Date));
	printf("\nDigite o dia: ");
	scanf("%d", &new_date->dia);
	printf("Digite o mês: ");
	scanf("%d", &new_date->mes);
	printf("Digite o ano: ");
	scanf("%d", &new_date->ano);

	return new_date;
}

void datePrint(Date* such) {
	printf("%02d/%02d/%04d", such->dia, such->mes, such->ano);
}

/**
 * Retorna 0 se forem iguais;
 * Retorna 1 se quem chama for maior;
 * Retorna -1 se quem chama for menor;
 */
int dateSame(Date* such, Date* other) {
	if (such->dia == other->dia)
		if (such->mes == other->mes)
			if (such->ano == other->ano)
				return 0;
	if (such->ano > other->ano)
		return 1;

	if (such->ano < other->ano)
		return -1;

	if (such->mes > other->mes)
		return 1;

	if (such->mes < other->mes)
		return -1;

	if (such->dia > other->dia)
		return 1;
	return -1;
}