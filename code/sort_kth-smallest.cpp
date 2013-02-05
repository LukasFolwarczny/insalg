#include "template.cpp"

int rearrange(int l, int r, int pivot, int* seq) {
	int p_pos = l, bound = l;
	while (seq[p_pos] != pivot) p_pos++;
	swap(seq[p_pos], seq[l]);

	for (int i = l + 1; i < r; i++) {
		if (seq[i] < seq[l]) {
			swap(seq[i], seq[++bound]);
		}
	}
	return bound;
}

int kth(int l, int r, int k, int* seq) {
	if (r - l <= 1) return seq[l];
	if (r - l < 5) {
		sort(seq+l, seq+r);
		return seq[k];
	}
	else {
		int* med = (int*)malloc(sizeof(int)*(r-l));
		int q = 0;
		for (int i = l; i + 5 <= r; i += 5) {
			sort(seq+i, seq+i+5);
			med[q++] = seq[i+2];
		}
		int m = kth(0, q, q / 2, med);

		int x = rearrange(l, r, m, seq);

		if (k == x) return m;
		if (k < x) return kth(l, x, k, seq);
		return kth(x + 1, r, k, seq); 
	}

}

int main() {
	int pole[] = {1,6,1,2,3,8,11,10,87,12,13,14,15,17,18,19,23};
	FOR(i,17) printf("%d\n", kth(0,17,i,pole));
	return 0;

}
