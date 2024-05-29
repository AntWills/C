#include <locale.h>
#include <stdio.h>
#include "Menu/Menu.h"
#include "TreeTikect/TreeTikect.h"

// teste

int main() {
	setlocale(LC_ALL, "pt_BR.UTF-8");
	TreeTikect* arv[3];
	arv[0] = arvTikectNew(0);
	arv[1] = arvTikectNew(1);
	arv[2] = arvTikectNew(-1);

	// exemplos:
	// arvTikectInsert(arv[0], tikectNew(0, dateNew(1, 1, 1), 200));
	// arvTikectInsert(arv[0], tikectNew(0, dateNew(1, 1, 1), 200));

	// arvTikectInsert(arv[1], tikectNew(0, dateNew(1, 1, 1), 250));
	// arvTikectInsert(arv[1], tikectNew(0, dateNew(1, 1, 1), 250));

	int op;
	do {
		menu(&op);
		opcoes(op, arv);
	} while (op);

	return 0;
}