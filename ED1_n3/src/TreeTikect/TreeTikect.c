#include "TreeTikect.h"

TreeTikect* arvTikectNew(int nacao) {
	TreeTikect* new_arv = (TreeTikect*)malloc(sizeof(TreeTikect));
	new_arv->nacao = nacao;
	new_arv->source = NULL;
	new_arv->num_tikect = 0;
	new_arv->valor_arrecado = 0.0;

	return new_arv;
}

void arvTikectInsertStruture(Node* source, Node* new_node) {
	if (nodeSame(source, new_node) > 0) {
		!source->left ? source->left = new_node : arvTikectInsertStruture(source->left, new_node);
	} else if (nodeSame(source, new_node) < 0) {
		!source->right ? source->right = new_node : arvTikectInsertStruture(source->right, new_node);
	} else {
		printf("Error. Key already exists");
		free(new_node);
	}
}

void arvTikectInsert(TreeTikect* such, Tikect* new_tikect) {
	if (!new_tikect || !such) {
		printf("\nError when insertinh.\nNull element.");
		return;
	}
	such->num_tikect++;
	such->valor_arrecado += new_tikect->preco;

	new_tikect->identifier = identifierNew(new_tikect->nacao, new_tikect->destino, rand() / 1000);

	Node* new_node = nodeNew(new_tikect);

	if (!such->source) {
		such->source = new_node;
		return;
	}
	arvTikectInsertStruture(such->source, new_node);
}

void arvTikectPrintStruture(Node* such) {
	if (!such)
		return;

	arvTikectPrintStruture(such->left);
	tikectPrint(nodeGetContent(such));
	arvTikectPrintStruture(such->right);
}

void arvTikectPrint(TreeTikect* such) {
	if (!such) {
		printf("Erro. Struct Null");
		return;
	} else if (!such->source) {
		printf("\nNão há passagens.\n");
		return;
	}
	arvTikectPrintStruture(such->source);
}

void arvTikectPrintDestinoStruture(Node* such, int destino) {
	if (!such)
		return;

	arvTikectPrintDestinoStruture(such->left, destino);
	if (tikectGetDestino(nodeGetContent(such)) == destino)
		tikectPrint(nodeGetContent(such));
	arvTikectPrintDestinoStruture(such->right, destino);
}

void arvTikectPrintDestino(TreeTikect* such, int destino) {
	if (!such) {
		printf("Erro. Struct Null");
		return;
	} else if (!such->source) {
		printf("\nNão há passagens.\n");
		return;
	}
	arvTikectPrintDestinoStruture(such->source, destino);
}

Node* arvTikectrRemoveBiggerNodeLeft(Node* ant, Node* atual) {
	if (!atual)
		return ant;
	if (atual->right)
		return arvTikectrRemoveBiggerNodeLeft(atual, atual->right);

	ant->right = atual->left;
	atual->left = NULL;

	return atual;
}

Node* arvTikectRemoveSource(TreeTikect* tree) {
	Node* source = tree->source;
	Node* auxi = NULL;

	if (!source->left) {
		auxi = source->right;
	} else if (!source->left->right) {
		auxi = source->left;
		auxi->right = source->right;
	} else {
		auxi = arvTikectrRemoveBiggerNodeLeft(source, source->left);
		nodeSetPoints(auxi, source->left, source->right);
	}

	tree->source = auxi;
	nodeSetPoints(source, NULL, NULL);
	return source;
}

Tikect* arvTikectRemove(TreeTikect* such, Identifier* key) {
	if (!such) {
		printf("Error. Null element.\n");
		return NULL;
	}

	if (!such->source) {
		return NULL;
	}

	Tikect* tikect = NULL;

	if (!such->source->left && !such->source->right) {
		tikect = such->source->content;
		such->source = NULL;
	} else if (identifierSame(such->source->key, key) == 0) {
		Node* node = arvTikectRemoveSource(such);
		tikect = node->content;
		free(node);
	}
	such->num_tikect--;
	such->valor_arrecado -= tikect->preco;
	return tikect;
}

void arvAdd(TreeTikect* tree1, TreeTikect* tree2) {
	while (tree2->source)
		arvTikectInsert(tree1, arvTikectRemove(tree2, tree2->source->key));
}