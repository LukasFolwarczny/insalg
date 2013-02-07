#include "template.cpp"
#define NEGINF (-2000000000)


int interval_tree[101000], L;

//Interval [a,b)
int maximum(int a, int b) {
	int l = L + a - 1;
	int r = L + b - 2;
	int result = max(interval_tree[l], interval_tree[r]);
	while (l != r) {
		if (l % 2 == 1) result = max(result, interval_tree[l]);
		if (r % 2 == 0) result = max(result, interval_tree[r]);
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
	FOR(i,N) update(i, sequence[i]);
}
