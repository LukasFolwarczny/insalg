#include "template.cpp"
// Lukas Folwarczny, 2013
// http://atrey.karlin.mff.cuni.cz/~folwar/insalg/

// Constructs the bijection between permutations of the length N
// and {0,...,N!-1}. Pemutations are ordered lexicographically.
// The fucntion init must be run first.
// Time complexity: O(N^2)

long long F[14]; // factorial
int T[14]; // tmp

/*pdf*/
void init() {
	F[0] = 1LL;
	for (int i = 1; i <= 13; i++) F[i] = i*F[i-1];
}

// Return number of permutation P.
long long permutation_to_integer(int N, int *P) {
	long long V = 0;
	for (int i = 0; i < N; i++) {
		V += P[i] * F[N-i-1];
		for (int j = i + 1; j < N; j++)
			if (P[j] > P[i]) P[j]--;
	}
	return V;
}

int* integer_to_permutation(int N, long long V) {
	int *out = (int*)malloc(N*sizeof(int));
	for (int i = 0; i < N; i++) T[i] = 1;
	for (int i = 0; i < N; i++) {
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
/*pdf*/

// DEMO
void permutation_demo() {
	init();
	int P[14];
	int N, V;
	printf("--- Integer to permutation ---\n");
	printf("Length of the permutation: ");
	scanf("%d", &N);
	printf("Number of the permutation you want: ");
	scanf("%d", &V);

	int* v = integer_to_permutation(N, V);
	for (int i = 0; i < N; i++)
		printf("%d ", v[i]);
	
	printf("\n--- Permutation to integer ---\n"
	"Input the length of the permutation: ");
	scanf("%d", &N);
	printf("The permutation: ");
	for (int i = 0; i < N; i++)
		scanf("%d", &P[i]);
	printf("%lld\n", permutation_to_integer(N, P));
}

#ifdef RUNDEMO
int main() { permutation_demo(); return 0; }
#endif
