#include "template.cpp"
// Lukas Folwarczny, 2013
// http://atrey.karlin.mff.cuni.cz/~folwar/insalg/

// Aho-Corasick algorithm

// Alphabet L0..LL, number of letters is LN
#define L0 'a'
#define LL 'z'
#define LN 26

/*pdf*/
// State of the automaton
struct S {
	// Forward edges, backward edge, shortcut backward edge, tree parent
	S * F[LN], * B, * SB, * P;
	bool W; // W = true mean a word ends here
	char C;
} * root;

int N, max_word_len;

S * step(S * s, char c) {
	if (s->F[c-L0] != NULL)
		return s->F[c-L0];
	if (s != root)
		return step(s->B, c);
	return root;
}

void build(int patterns_count, char ** patterns) {
	N = patterns_count;
	root = new S();
	root->B = root;
	root->SB = root;

	for (int i = 0; i < N; i++) {
		S * t = root;
		int p; int c;
		for (p = 0; (c = patterns[i][p]) != '\0'; p++) {
			if (t->F[c-L0] == NULL) {
				t->F[c-L0] = new S();
				t->F[c-L0]->P = t;
				t->F[c-L0]->C = c;
			}
			t = t->F[c-L0];
		}
		max_word_len = max(max_word_len, p);
		t->W = true;
	}

	queue<S*> Q;
	for (int i = 0; i < LN; i++) {
		S * s = root->F[i];
		if (s != NULL) {
			s->B = root;
			s->SB = root;
			Q.push(s);
		}
	}

	while (!Q.empty()) {
		S * t = Q.front(); Q.pop();
		for (int i = 0; i < LN; i++) {
			S * s = t->F[i];
			if (s != NULL) {
				S * b = step(t->B, L0+i);
				s->B = b;
				if (b->W)
					s->SB = b;
				else
					s->SB = b->SB;
					Q.push(s);
			}
		}
	}
}

void search(char * text) {
	S * state = root;
	char * out = (char *)malloc((max_word_len+1) * sizeof(char));
	out[max_word_len] = '\0';

	for (int p = 0; text[p] != '\0'; p++) {
		state = step(state, text[p]);

		S * found = state;
		if (!state->W)
			found = state->SB;

		while (found->W) {
			S * s = found;
			int k = max_word_len;
			while (s != root) {
				out[--k] = s->C;
				s = s->P;
			}
			printf("Position: %d Word: %s\n", p, out + k);
			found = found->SB;
			if (found == NULL) DP("SHIT\n");
		}
	}
	free(out);
}
/*pdf*/

void aho_corasick_demo() {
	int patterns_number = 8;
	char * patterns[] = {"arab","arara", "ararat", "bar", "bara", "baraba", "ra", "rab"};

	printf("Patterns:\n");
	for (int i = 0; i < patterns_number; i++)
		printf("%s\n", patterns[i]);

	build(patterns_number, patterns);
	char* tlt = "barabararat";
	printf("Text: %s\n", tlt);
	search(tlt);
}

#ifdef RUNDEMO
int main() { aho_corasick_demo(); return 0; }
#endif
