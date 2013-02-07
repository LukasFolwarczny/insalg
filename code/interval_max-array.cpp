#include "template.cpp"


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

int main() {
	int v;
	while(true) { scanf("%d", &v);
	v |= v >> 1;
	v |= v >> 2;
	v |= v >> 4;
	v |= v >> 8;
	v |= v >> 16;
	v++;
	v >>= 1;
	printf("%d\n", v); 
	}
}
