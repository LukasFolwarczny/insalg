#include "template.cpp"
// Lukas Folwarczny, 2013
// http://atrey.karlin.mff.cuni.cz/~folwar/insalg/

char *prime;

// Find all primes less than N
// Result is in the array prime, x is prime iff prime[x] == 1
/*pdf*/
void eratosthenes(int N) {
	prime = (char*)calloc(N, sizeof(char));
	for (int i = 2; i < N; i++) prime[i] = 1;
	for (int i = 2; i < N; i++) {
		if (prime[i]) {
			for (int j = i * 2; j < N; j += i)
				prime[j] = 0;
		}
	}
}
/*pdf*/

// DEMO
void eratosthenes_demo() {
	eratosthenes(10000);
	printf("First 1000 prime numbers:\n");
	int j = 0;
	for (int i = 2; j < 1000; i++) {
		if (prime[i]) { j++; printf("%d ", i); }
	}
}

#ifdef RUNDEMO
int main() { eratosthenes_demo(); return 0; }
#endif
