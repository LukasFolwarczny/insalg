#include "template.cpp"
#define MaxN 100000
// Lukas Folwarczny, 2013
// http://atrey.karlin.mff.cuni.cz/~folwar/insalg/

char prime[MaxN+1];

//Primes less than N
void eratosthenes(int N) {
	FORI(i,2,N) prime[i] = 1;
	
	FORI(i,2,N) {
		if (prime[i]) {
			for (int j = i * 2; j <= N; j += i)
				prime[j] = 0;
		}
	}
}

void example() {
	eratosthenes(10000);
	printf("First 1000 prime numbers:\n");
	int j = 0;
	for (int i = 2; j < 1000; i++) {
		if (prime[i]) { j++; printf("%d ", i); }
	}
}

int main() { example(); return 0; }
