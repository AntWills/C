#ifndef TwoThreeTree

#define NumKey 2

typedef struct Int {
	int num;
} Int;

Int* newInt(int num);
void freeInt(Int* obj);

typedef struct Node {
	Int* vetorKeys[NumKey];
} Node;

#endif