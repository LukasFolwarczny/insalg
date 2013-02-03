#include "template.cpp"

#define MaxN 100000

char prime[MaxN+1];

//primes from [1..N]
void erasthotenes(int N) {
	FORI(i,2,N) prime[i] = 1;
	
	FORI(i,2,N) {
		if (prime[i]) {
			for (int j = i * 2; j <= N; j += i)
				prime[j] = 0;
		}
	}
}

