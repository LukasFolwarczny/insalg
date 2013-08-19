#include "template.cpp"
// Lukas Folwarczny, 2013
// http://atrey.karlin.mff.cuni.cz/~folwar/insalg/

// Knuth-Morris-Pratt algorithm. The function _build_ computes the
// failer function for a given word. Then you can search a substring
// with the fucntion _search_.
// Time complexity: linear with the number of letters given to a
// function (build or search)

#define MaxD 10000

char* word;
int F[MaxD+1];
int D;

/*pdf*/
int step(int i, char c) {
	if (i < D-1 && word[i+1] == c)
		return i + 1;
	if (i >= 0)
		return step(F[i], c);
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
/*pdf*/

void kmp_demo() {
	char pattern[] = "ABBAAAABBA";
	int N = strlen(pattern);
	build(pattern);
	printf("Failer function:\n");
	for (int i = 0; i < N; i++) {
		printf("%d ", F[i]);
	}
	printf("\nSearch results:\n");
	char text[] = "AABBAAAABBAAABBABAABBAAAABBAABABABBBAABAB";
	search(text);
}

#ifdef RUNDEMO
int main() { kmp_demo(); return 0; }
#endif
