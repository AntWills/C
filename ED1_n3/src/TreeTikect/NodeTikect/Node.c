#include "Node.h"

void nodeSetPoints(Node* such, Node* left, Node* right) {
	such->left = left;
	such->right = right;
}

Node* nodeNew(Tikect* tikect) {
	if (!tikect) {
		printf("\nError when crating node.\nNeull element.\n");
		return NULL;
	}

	Node* new_node = (Node*)malloc(sizeof(Node));

	new_node->content = tikect;
	new_node->key = tikect->identifier;
	nodeSetPoints(new_node, NULL, NULL);

	return new_node;
}

Tikect* nodeGetContent(Node* such) {
	if (!such)
		return NULL;
	return such->content;
}

/**
 * Retorna 0 se forem iguais;
 * Retorna -1 se quem chama for maior;
 * Retorna 1 se quem chama for menor;
 */
int nodeSame(Node* such, Node* other) {
	return identifierSame(such->key, other->key);
}