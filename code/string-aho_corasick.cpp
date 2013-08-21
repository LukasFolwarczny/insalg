#include "template.cpp"
// Lukas Folwarczny, 2013
// http://atrey.karlin.mff.cuni.cz/~folwar/insalg/

// Aho-Corasick algorithm
// Based on the algorithm description in KSP Cookbook:
// http://ksp.mff.cuni.cz/viz/kucharky/hledani-v-textu

// This is an experimental feature. I want to rewrite one day,
// I do not really believe in this implementation.

#define WordLen 15

int N;
struct trie {
	trie *sons[26], *parent, *link, *back_pattern;
	bool word;
	char z;
	int d;
};

trie* root;
trie* words_pos[10000];
int active[10000], active_c;

/*pdf*/
void build(int words_count, char words[][WordLen]) {
	N = words_count;
	root = new trie();
	root->d = 0;
	FOR(i,N) { words_pos[i] = root; 
	trie *t = root;
		for(int p = 0; words[i][p] != '\0'; p++) {
					int c = words[i][p]-'a';
				if (t->sons[c] == NULL) {
					t->sons[c] = new trie(); 
					t->sons[c]->parent = t;
					t->sons[c]->z = c+'a';
					t->sons[c]->d = t->d+1;
				}
				t = t->sons[c];
		}
	}
	FOR(i,N)
		active[i] = i;
	active_c = N;

	for (int p = 0; active_c; p++) {
		//printf("%d\n", p);
		FOR(i,active_c) {
			int w = active[i];
			if (words[w][p] == '\0') {
				//printf("%s %d\n", words[w], words_pos[w]->d);
				words_pos[w]->word = true;
				active[i] = active[active_c-1];
				active_c--;
				i--; //to the previos, can even preceed .begin
			}
			else {
				int c = words[w][p] - 'a';
				//printf("%d\n", c);
				trie* parent = words_pos[w];
				trie* c_node;
				if (parent->sons[c] == NULL) {
					parent->sons[c] = new trie(); 
					parent->sons[c]->parent = parent;
					parent->sons[c]->z = c+'a';
					parent->sons[c]->d = parent->d+1;
				}
				c_node = parent->sons[c];
				if (parent == root) c_node->link = root;
				else {
					trie* target = parent->link;
					while ((target != root) && target->sons[c] == NULL) {
						target = target->link;
					}
					if (target->sons[c] != NULL)
						c_node->link = target->sons[c];
					else c_node->link = root;
				}
				if (c_node->link->word)
					c_node->back_pattern = c_node->link;
				else c_node->back_pattern = c_node->link->back_pattern;
				words_pos[w] = c_node;
				//printf("d:%d\n", c_node->d);
			}
		}
	}
}

void search(char* text) {
	trie* pos = root;
	for (int p = 0; text[p] != '\0'; p++) {
		int c = text[p] - 'a';
		while (pos != root && (pos->sons[c]) == NULL) {
			pos = pos->link;
		}
		if (pos->sons[c] != NULL)
			pos = pos->sons[c];
		if (pos->word) {
			printf("Pozice: %d\n", p);
			trie* x = pos;
			while (x!=root)
			{
				printf("%c", x->z);
				x = x->parent;
			}
			printf("\n");
		}
		else if (pos->back_pattern != NULL) {
			printf("Pozice: %d\n", p);
			trie* x = pos->back_pattern;
			while (x!=root)
			{
				printf("%c", x->z);
				x = x->parent;
			}
			printf("\n");

		}
	}
}
/*pdf*/

int main() {
	char jehelnik[9][WordLen] = {"arab","arara", "ararat", "bar", "bara", "baraba", "ra", "rab"};
	printf("%s\n", jehelnik[7]);
	build(8, jehelnik);
	char* tlt = "barabararat";
	search(tlt);
	return 0;
}
