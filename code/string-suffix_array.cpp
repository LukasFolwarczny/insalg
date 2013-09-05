#include "template.cpp"
// Lukas Folwarczny, 2013
// http://atrey.karlin.mff.cuni.cz/~folwar/insalg/

// Suffix array construcion in linear time
// Function suffix_array creates an array of suffixes sorted
// lexicographically

// This code is based on the algorithm description in the article:
// Linear Work Suffix Array Construction
// Juha Kärkkäinen, Peter Sanders, Stefan Burkhardt
// http://algo2.iti.kit.edu/documents/jacm05-revised.pdf

/*pdf*/
bool eq(int *S, int p1, int p2) {
	return S[p1] == S[p2] && S[p1+1] == S[p2+1] && S[p1+2] ==
	S[p2+2];
}

// Return whether vector a is less or equal than b
bool leq2(int a1, int a2, int b1, int b2) {
	return a1 == b1 ? a2 <= b2 : a1 < b1;
}

// Return whether vector a is less or equal than b
bool leq3(int a1, int a2, int a3, int b1, int b2, int b3) {
	if (a1 == b1) return a2 == b2 ? a3 <= b3 : a2 < b2;
	return a1 < b1;
}

// Convert the position in sample to global position
int sample_to_global(int N, int position) {
	if (position < (N+1)/3) return position * 3 + 1;
	return (position - (N+1)/3) * 3 + 2;
}

// Convert the global position to sample
int global_to_sample(int N, int position) {
	if (position % 3 == 1) return position / 3;
	return (position + 1) / 3 + (N+1)/3 - 1;
}

void radixsort_pass(int* a, int* b, int* r, int n, int K) {
	int *c = (int*)calloc(K+1,sizeof(int)); // counter array
	for (int i = 0; i < n; i++) c[r[a[i]]]++;
	for (int i = 0, sum = 0; i <= K; i++) {
		int t = c[i]; c[i] = sum; sum += t; }
	for (int i = 0; i < n; i++) b[c[r[a[i]]]++] = a[i];
	free(c);
}

int conv1(int N, int index) {
	return -1;
}

// Construct the suffix array for the string S and store it into SA
// S[N] and S[N+1] must be set to zero
void suffix_array(int N, int *S, int *SA) {
	int N0 = (N+2)/3, N1 = (N+1)/3, N2 = N/3, N12 = N1+N2;
	int *smpl = (int*)malloc((N12+2)*sizeof(int));
	int *tmp = (int*)malloc((N12+2)*sizeof(int));
	int *SA12 = (int*)malloc((N12+2)*sizeof(int));
	int *rank = (int*)malloc((N+3)*sizeof(int));
	int *S0 = (int*)malloc(N0*sizeof(int));

	// Create sample and sort triples
	int t = 0;
	for (int i = 1; i < N; i+=3) smpl[t++] = i;
	for (int i = 2; i < N; i+=3) smpl[t++] = i;

	radixsort_pass(smpl, tmp, S+2, N12, N);
	radixsort_pass(tmp, smpl, S+1, N12, N);
	radixsort_pass(smpl, tmp, S, N12, N);
	
	// Rename triples
	for (int i = 0; i < N12 + 2; i++) smpl[i] = 0;
	int rename = 1;
	smpl[global_to_sample(N,tmp[0])] = 1;
	for (int i = 1; i < N12; i++) {
		if (!eq(S, tmp[i], tmp[i-1])) rename++;
		smpl[global_to_sample(N,tmp[i])] = rename;
	}
	smpl[N12] = smpl[N12+1] = 0;

	// Create suffix array of sample (SA12)
	if (rename < N12) suffix_array(N12, smpl, SA12);
	else { SA12[0] = N12;
		for (int i = 1; i <= N12; i++)
			SA12[smpl[i-1]] = i-1;
	}
	 
	for (int i = 0; i <= N12; i++)
		rank[sample_to_global(N,SA12[i])] = i;
	rank[N+1] = rank[N+2] = 0;
	t = 0;
	for (int i = 0; i < N; i+=3) S0[t++] = i;

	// Sort nonsample suffixes
	// i <= j <=> (S[i], rank[i+1) <= (S[j], rank[j+1])
	radixsort_pass(S0, tmp, rank+1, N0, N+2);
	radixsort_pass(tmp, S0, S, N0, N+2);

	// Merge sample and non-sample suffixes
	int p1 = 0, p2 = 1, p = 1;
	SA[0] = N;
	while (p1 < N0 && p2 <= N12) {
		int j = S0[p1];
		int i = sample_to_global(N,SA12[p2]);
		// Do the comparison
		// i % 3 == 1:
		//i <= j <=> (S[i],rank[i+1]) <= (S[j],rank[j+1])
		// i % 3 == 2:
		// i <= j <=> (S[i],S[i+1],rank[i+2]) <= (S[j],S[j+1],rank[j+2])
		if (i % 3 == 1) {
			if (leq2(S[i], rank[i+1], S[j], rank[j+1])) {
				SA[p++] = i; p2++; }
			else SA[p++] = S0[p1++];
		}
		else {
			if (leq3(S[i], S[i+1], rank[i+2],
				 S[j], S[j+1], rank[j+2])) {
				SA[p++] = i; p2++; }
			else SA[p++] = S0[p1++];
		}
	}
	while (p1 < N0)
		SA[p++] = S0[p1++];
	while (p2 <= N12)
		SA[p++] = sample_to_global(N,SA12[p2++]);
	free(smpl); free(tmp); free(SA12); free(rank); free(S0);
}
/*pdf*/

void suffix_array_demo() {
	int S[] = {10, 1, 2, 2, 1, 4, 1, 2, 2, 1, 4, 8, 0, 0};
	//int S[] = {1, 3, 2, 4, 5, 7, 8, 6, 9, 10, 0, 0};
	int SA[14];
	int N = 12;
	suffix_array(N, S, SA);
	printf("Suffix array:\n");
	for (int i = 0; i < N+1; i++) printf("%d ", SA[i]);
}

#ifdef RUNDEMO
int main() { suffix_array_demo(); return 0; }
#endif
