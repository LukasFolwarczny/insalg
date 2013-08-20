#include "template.cpp"
// Lukas Folwarczny, 2013
// http://atrey.karlin.mff.cuni.cz/~folwar/insalg/


// Maximum interval tree
// The function make creates the tree in O(N) time.
// The tree handles two queries (both in O(log N) time):
//   maximum - compute the maximum of a given interval
//   update - update an element on a given position

// Indices: 0,..,L-2 inner nodes; L-1,..,2L-2 leaves
int interval_tree[101000], L;

/*pdf*/
// Maximum of the interval [a,b)
int maximum(int a, int b) {
	if (a >= b) return 0;
	int l = L + a - 1;
	int r = L + b - 2;
	int result = max(interval_tree[l], interval_tree[r]);
	while ((l-1)/2 != (r-1)/2) {
		if (l % 2 == 1) result = max(result, interval_tree[l+1]);
		if (r % 2 == 0) result = max(result, interval_tree[r-1]);
		l = (l-1)/2;
		r = (r-1)/2;
	}
	return result;
}


void update(int position, int new_value) {
	int k = L + position - 1;
	interval_tree[k] = new_value;	
	while (k > 0) {
		k = (k-1)/2;
		interval_tree[k] = max(interval_tree[2*k+1], interval_tree[2*k+2]);
	}
}

void make(int N, int* sequence) {
	L = 1;
	while (L < N) L *= 2;
	FOR(i,N) interval_tree[i+L-1] = sequence[i];
	for (int i = L-2; i >= 0; i--) interval_tree[i] = max(interval_tree[2*i+1],
		interval_tree[2*i+2]);
}
/*pdf*/

void example() {
	int s[] = {2,3,1,2,2,10,11,-2,9,10};
	int N = 10;
	FOR(i,N) printf("%d ", s[i]);
	printf("\n");
	make(N, s);
	update(2, 4);
	FOR(i,N) FORI(j,i,N+1) 	printf("max [%d,%d):%d\n", i, j, maximum(i,j));
}

int main() { example(); return 0; }
