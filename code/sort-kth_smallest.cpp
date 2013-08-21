#include "template.cpp"
// Lukas Folwarczny, 2013
// http://atrey.karlin.mff.cuni.cz/~folwar/insalg/

// Finds k-th smallest (zero-based) element in given sequence
// using the Median of Medians algorithm
// Time complexity: O(N)

/*pdf*/
// Permutes the array on positions array[l] to array[r-1] with the
// pivot
// Return position of the pivot after rearrangement
int rearrange(int* array, int l, int r, int pivot) {
	int pivot_pos = l, bound = l;
	while (array[pivot_pos] != pivot) pivot_pos++;
	swap(array[pivot_pos], array[l]);

	FORI(i,l+1,r) {
		if (array[i] < array[l]) {
			swap(array[i], array[++bound]);
		}
	}
	swap(array[l], array[bound]);
	return bound;
}

// Return k-th smallest element from array[l] to array[r-1]
// array WILL BE REARRANGED
int kth(int *array, int l, int r, int k) {
	if (r - l <= 1) return array[l];
	if (r - l < 5) {
		sort(array+l, array+r);
		return array[k];
	}
	else {
		int* med = (int*)malloc(sizeof(int)*(r-l));
		int q = 0;
		for (int i = l; i + 5 <= r; i += 5) {
			sort(array+i, array+i+5);
			med[q++] = array[i+2];
		}
		int m = kth(med, 0, q, q / 2);

		int x = rearrange(array, l, r, m);

		if (k == x) return m;
		if (k < x) return kth(array, l, x, k);
		return kth(array, x + 1, r, k); 
	}

}
/*pdf*/

void kth_demo() {
	int array[] = {1,6,1,2,3,8,11,10,87,12,13,14,15,17,18,19,23};
	FOR(i,17) printf("%d\n", kth(array, 0, 17, i));
}

#ifdef RUNDEMO
int main() { kth_demo(); return 0; }
#endif
