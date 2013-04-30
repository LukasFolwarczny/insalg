#include "template.cpp"
// Lukas Folwarczny, 2013
// http://atrey.karlin.mff.cuni.cz/~folwar/insalg/

// Constructs the bijection between permutations of the length N
// and {0,...,N-1}. Pemutations are ordered lexicographically.

long long F[14]; // factorial
int T[14];

void init(int N) {
	F[0] = 1LL;
	for (int i = 1; i <= N; i++) F[i] = i*F[i-1];
}

long long permutation_to_integer(int N, int *P) {
	long long V = 0;
	FOR(i,N) {
		V += P[i] * F[N-i-1];
		for (int j = i + 1; j < N; j++)
			if (P[j] > P[i]) P[j]--;
	}
	return V;
}

int* integer_to_permutation(int N, long long V) {
	int *out = (int*)malloc(N*sizeof(int));
	FOR(i,N) T[i] = 1;
	FOR(i,N) {
		int k = 0;
		while (V >= F[N-i-1])
			k++, V -= F[N-i-1];
		int j;
		for (j = 0; k >= 0; j++)
			if (T[j]) k--;
		out[i] = j-1;
		T[j-1] = 0;
	}
	return out;
}

int main() {
	init(14);
	int P[14];
	int a, b;
	scanf("%d%d", &a, &b);
	int* v = integer_to_permutation(a, b);
	for (int i = 0; i < a; i++)
	printf("%d ", v[i]);
	scanf("%d", &a);
	FOR(i,a)
	scanf("%d", &P[i]);
	printf("%lld\n", permutation_to_integer(a, P));
	return 0;
}
