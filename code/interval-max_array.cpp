#include "template.cpp"
// Lukas Folwarczny, 2013
// http://atrey.karlin.mff.cuni.cz/~folwar/insalg/

// Maximum array
// This array is created with the function make
// with the complexity (time and space) O(N log N).
// The array is immutable and computes the maximum of a given interval
// in O(1).

/*pdf*/
int max_array[30][100000];
int N, L;
int bin_log[10000]; // bin_log[i] = floor(log_2(i))

//Maximum of interval [a,b)
int interval_max(int a, int b) {
	int v = b-a;
	int l = bin_log[v];
	return max(max_array[l][a], max_array[l][b - (1 << l)]);
}

void make(int length, int* sequence) {
	N = length;
	L = 1;
	int p = 1;
	while (p < length) { p *= 2; L++; }

	int exp = 0, val = 1;
	for (int i = 0; i < N; i++) {
		if (2*val == N) val *= 2, exp++;
		bin_log[N] = exp;
	}

	for (int l = 0; l < L; l++) {
		if (l == 0) {
			for (int i = 0; i < N; i++)
				max_array[l][i] = sequence[i];
		}
		else {
			for (int i = 0; i < N; i++)
				max_array[l][i] = max(max_array[l-1][i], max_array[l-1][i + (1 << (l-1))]);
		}
	}
}
/*pdf*/

void max_array_demo() {
	int s[] = {2,3,1,2,2,10,11,-2,9,10};
	int length = 10;
	for (int i = 0; i < length; i++)
		printf("%d ", s[i]);
	printf("\n");

	make(length, s);
	for (int i = 0; i < length; i++) for (int j = i + 1; j < N + 1; j++)
		printf("max [%d,%d): %d\n", i, j, interval_max(i,j));

	int len, * seq;
	printf("Enter the length of the sequence: ");
	scanf("%d", &len);
	seq = (int*)malloc(len * sizeof(int));

	printf("\nEnter the items of the sequence: ");
	for (int i = 0; i < len; i++) scanf("%d", &seq[i]);
	make(len, seq);

	int ret;
	while (ret != EOF) {
		printf("\nEnter a, b: ");
		int a, b; ret = scanf("%d%d", &a, &b);
		printf("\nmax [%d,%d): %d\n", a, b, interval_max(a,b));
	}
}

#ifdef RUNDEMO
int main() { max_array_demo(); return 0; }
#endif
