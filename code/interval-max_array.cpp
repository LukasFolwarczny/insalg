#include "template.cpp"
// Lukas Folwarczny, 2013
// http://atrey.karlin.mff.cuni.cz/~folwar/insalg/

// Maximum array
// This array is created with the function O(N log N)
// with the complexity (time and space) O(N log N).
// The array is immutable and computes the maximum of a given interval
// in O(1) (it is in fact O(log log N), but this implementation uses
// for integer constant number of operations.)

// The bithacks in maximum are a nice exercise.
// I took it from: http://graphics.stanford.edu/~seander/bithacks.html

/*pdf*/
int* max_array[30];
int N, L;

static const int MultiplyDeBruijnBitPosition[32] =
{ 0, 9, 1, 10, 13, 21, 2, 29, 11, 14, 16, 18, 22, 25, 3, 30,
  8, 12, 20, 28, 15, 17, 24, 7, 19, 27, 23, 6, 26, 5, 4, 31 };

//Maximum of interval [a,b)
int maximum(int a, int b) {
	int v = b-a;
	// bit hack
	v |= v >> 1;
	v |= v >> 2;
	v |= v >> 4;
	v |= v >> 8;
	v |= v >> 16;
	int r = MultiplyDeBruijnBitPosition[(unsigned int)(v * 0x07C4ACDDU) >> 	27];
	v++;
	v /= 2;
	return max(max_array[r][a], max_array[r][b-v]);
}

void make(int length, int* sequence) {
	N = length;
	L = 1;
	int p = 1;
	while (p < length) { p *= 2; L++; }
	FOR(l,L) {
		max_array[l] = (int*)malloc(sizeof(int)*N);
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
/*pdf*/

void max_array_demo() {
	int s[] = {2,3,1,2,2,10,11,-2,9,10};
	int N = 10;
	FOR(i,N) printf("%d ", s[i]);
	printf("\n");
	make(N, s);
	FOR(i,N) FORI(j,i+1,N+1) printf("max [%d,%d):%d\n", i, j, maximum(i,j));
}

#ifdef RUNDEMO
int main() { max_array_demo(); return 0; }
#endif
