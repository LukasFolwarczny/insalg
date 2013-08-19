#include "template.cpp"

#define MaxD 10000

char* word;
int F[MaxD+1];
int D;

int step(int i, char c) {
	if (i < D-1 && word[i+1] == c) {
		return i + 1;
	}
	if (i >= 0) {
		return step(F[i], c);
	}
	return -1;
}

void build(char* pattern) {
	word = pattern;
	D = strlen(word);
	F[0] = -1;
	FORI(i,1,D) {
		F[i] = step(F[i-1], word[i]);
	}
}

void search(char* text) {
	int j = -1;
	for (int i = 0; text[i] != '\0'; i++) {
		j = step(j, text[i]);
		if (j == D-1) printf("%d\n", i);
	}
}
