#ifndef DATE_H
#define DATE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int dia;
	int mes;
	int ano;
} Date;

Date* dateNew(int dia, int mes, int ano);
Date* dateIn();
void datePrint(Date* such);
int dateSame(Date* such, Date* other);

#endif