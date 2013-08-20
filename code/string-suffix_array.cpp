#include "template.cpp"


bool eq(int *S, int p1, int p2) {
	printf("S[p1] %d S[p2] %d\n", S[p1], S[p2]);
	return S[p1] == S[p2] && S[p1+1] == S[p2+1] && S[p1+2] ==
	S[p2+2];
}

bool leq(int a1, int a2, int b1, int b2) {
	return a1 == b1 ? a2 <= b2 : a1 < b1;
}

bool leq2(int a1, int a2, int a3, int b1, int b2, int b3) {
	if (a1 == b1) return a2 == b2 ? a3 <= b3 : a2 < b2;
	return a1 < b1;
}


void radixsort_pass(int* a, int* b, int* r, int n, int K) {
	int* c = (int*)calloc(K+1,sizeof(int)); // counter array
	for (int i = 0; i < n; i++) c[r[a[i]]]++;
	for (int i = 0, sum = 0; i <= K; i++) {
		int t = c[i]; c[i] = sum; sum += t; }
	for (int i = 0; i < n; i++) b[c[r[a[i]]]++] = a[i];
	free((void*)c);
}

int conv1(int N, int index) {
	return -1;
}
// construct the suffix array for the string S
// S[N] and S[N+1] must be set to zero
void suffix_array(int N, int *S, int *SA) {
	int N0 = (N+2)/3, N1 = (N+1)/3, N2 = N/3, N12 = N1+N2;
	int *smpl = (int*)malloc(N*sizeof(int));
	int t = 0;
	int *tmp = (int*)malloc(N*sizeof(int));
	int *conv = (int*)malloc(N*sizeof(int));
	int *rconv = (int*)malloc(N*sizeof(int));
	int *SA12 = (int*)malloc(N*sizeof(int));
	for (int i = 1; i < N; i+=3) {
		conv[i] = t;
		rconv[t] = i;
		smpl[t++] = i; }
	for (int i = 2; i < N; i+=3) {
		conv[i] = t;
		rconv[t] = i;
		smpl[t++] = i;
	}
	radixsort_pass(smpl, tmp, S+2, N12, N);
	radixsort_pass(tmp, smpl, S+1, N12, N);
	radixsort_pass(smpl, tmp, S, N12, N);
	
	FOR(i,N) smpl[i] = 0;
	int nu = 1;
	smpl[conv[tmp[0]]] = 1;

	for (int i = 1; i < N12; i++) {
		if (!eq(S, tmp[i], tmp[i-1])) nu++;
		smpl[conv[tmp[i]]] = nu;
	}
	FOR(i,N12) printf("%d ", smpl[i]);
	printf("end sml");

	if (nu < N12) suffix_array(N12, smpl, SA12);
	else { SA12[0] = N12;
		for (int i = 1; i <= N12; i++) {
			SA12[smpl[i-1]] = i-1;
		}
	}
	 
	FOR(i,N) printf("%d ", smpl[i]);
	printf("\ntt\n");
	FOR(i,N12+1) printf("%d ", SA12[i]);
	int *rank = (int*)malloc((N+3)*sizeof(int));
	for (int i = 0; i <= N12; i++) {
		rank[rconv[SA12[i]]] = i;
	}
	printf("rank  ");
	FOR(i,N+2) printf("%d ", rank[i]);
	int *S0 = (int*)malloc(N*sizeof(int));
	int tq = 0;
	for (int i = 0; i < N; i+=3) S0[tq++] = i;
	radixsort_pass(S0, tmp, rank+1, tq, N+2);
	radixsort_pass(tmp, S0, S, tq, N+2);
	

	printf("\nS0 ");
	FOR(i,tq) printf("%d ", S0[i]);
	// Merge
	int p1 = 0, p2 = 1, p = 1;
	SA[0] = N;
	while (p1 < N0 && p2 <= N12) {
		// do the comparison
		// B1  (t_i, rank(S_{i+1}))
		int j = S0[p1];
		int i = rconv[SA12[p2]];
		printf("i %d  j %d\n", i, j);
		if (i % 2 == 1) { 
			if (leq(S[i], rank[i+1], S[j], rank[j+1])) {
				SA[p++] = i; p2++; }
			else SA[p++] = S0[p1++];
		}
		else {
			if (leq2(S[i], S[i+1], rank[i+2], S[j], S[j+1],
				rank[j+2])) {
				SA[p++] = i; p2++; }
			else SA[p++] = S0[p1++];

		}
		
	}
	while (p1 < N0) {
		SA[p++] = S0[p1++];
	}
	while (p2 <= N12) {
		SA[p++] = rconv[SA12[p2++]];
	}
	printf("\n-- ");
	FOR(i,N+1) printf("%d ", SA[i]);

	// radix sort (t_i, rank_S_{i+1})

}

void suffix_array_demo() {
	int S[] = {10, 1, 2, 2, 1, 4, 1, 2, 2, 1, 4, 8, 0, 0};
	//int S[] = {1, 3, 2, 4, 5, 7, 8, 6, 9, 10, 0, 0};
	int SA[14];
	suffix_array(12, S, SA);
}

#ifdef RUNDEMO
int main() { suffix_array_demo(); return 0; }
#endif
