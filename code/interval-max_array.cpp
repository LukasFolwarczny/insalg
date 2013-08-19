#include "template.cpp"
// Lukas Folwarczny, 2013
// http://atrey.karlin.mff.cuni.cz/~folwar/insalg/

//Maximum array, maximum query in O(1) time
//Make procedure O(N log N) time & space

/*pdf*/
int* max_array[30];
int log_table[100000];
int N, L;

//Maximum of interval [a,b)
int maximum(int a, int b) {
	int v = b-a;
	v |= v >> 1;
	v |= v >> 2;
	v |= v >> 4;
	v |= v >> 8;
	v |= v >> 16;
	v++;
	v /= 2;
	return max(max_array[log_table[v]][a], max_array[log_table[v]][b-v]);
}

void make(int length, int* sequence) {
	N = length;
	int p = 1; L = 1;
	while (p < length) { p*=2; L++; log_table[p] = L-1; }
	FOR(l,L) {
		max_array[l] = new int[N];
		if (l == 0) {
			FOR(i,N) max_array[l][i] = sequence[i];	
		}
		else {
			FOR(i,N) {
				max_array[l][i] = max(max_array[l-1][i], max_array[l-1][i+(1 << (l-1))]);
			}
		}
	}
}
/*pdf*/

void example() {
	int s[] = {2,3,1,2,2,10,11,-2,9,10};
	int N = 10;
	FOR(i,N) printf("%d ", s[i]);
	printf("\n");
	make(N, s);
	FOR(i,N) FORI(j,i,N+1) 	printf("max [%d,%d):%d\n", i, j, maximum(i,j));
}

int main() { example(); return 0; }
