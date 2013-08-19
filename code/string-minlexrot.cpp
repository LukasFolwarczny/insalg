#include "template.cpp"
// Lukas Folwarczny, 2013
// http://atrey.karlin.mff.cuni.cz/~folwar/insalg/

// Lexicographically minimal rotation with Booth's algorithm

// A complete proof of correctness is in the original article:
// Kellog S. Booth: Lexicographically least circular substrings,
// Information Processing Letters, Volume 10, Issues 4–5, 5 July 1980,
// Pages 240-242, ISSN 0020-0190,
// http://dx.doi.org/10.1016/0020-0190(80)90149-0.

char* _S;
int *F;
int N, j, k;
char St(int index) {
	return (index < N) ? _S[index] : _S[index - N];
}


// Main idea of Booth's algorithm:
// The offset k indicates the lexicographically least substring of the
// characters scanned so far
// The algorithm in fact computes the failer function for the string
// S[k], S[k+1], ..., S[N-1], S[0], ..., S[k-1]
// Notice that there are only three new lines in comparison with the
// function in string-kmp (they are marked with // in the end of line)
// These three new lines detect a smaller rotation and adjust k
// properly

int step(int i, char c) {
	if (St(k+i+1) == c) {
		return i+1;
	}
	if  (i >= 0) {
		if (c < St(k+i+1)) //
			k = j-i-1; //		
		return step(F[i], c);
	}
	if (c < St(k+i+1)) k = j; //
	return -1;

}

// Returns the number of positions to left shift to get the
// lexicographically minimal rotation.
int minlexrot(char S[]) {
	N = strlen(S);
	_S = S;
	F = (int*)malloc(N*sizeof(int));
	F[0] = -1;
	k = 0;
	for (j = 1; j < 2*N; j++) {
		if (j - k >= N) return k;//
		F[j-k] = step(F[j-k-1], St(j));
		/*int i = F[j-k-1];
		while (i != -1 && St(j) != St(k+i+1)) {
			if (St(j) < St(k+i+1)) //
				k = j-i-1;    //

			i = F[i];
		}
		if (i == -1 && St(j) != St(k+i+1)) {
			if (St(j) < St(k+i+1))//
				k = j;//
			F[j-k] = -1;
		}
		else
			F[j-k] = i + 1;*/
		
	}

	free(F);
}

// DEMO

void minlexrot_demo() {
	char S[] = "ABBABABA";
	printf("%s %d\n", S, minlexrot(S));
}

#ifdef RUNDEMO
int main() { minlexrot_demo(); return 0; }
#endif
