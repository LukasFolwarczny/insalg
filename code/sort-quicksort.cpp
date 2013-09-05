#include "template.cpp"
// Lukas Folwarczny, 2013
// http://atrey.karlin.mff.cuni.cz/~folwar/insalg/

// Ordinary Quick Sort
// Time complexity: O(N log N) on average

// Sort the array on positions l, l+1, ..., r-1
/*pdf*/
void quicksort(int* array, int l, int r) {
	if (l < r) {
		int bound = l;
		for (int i = l + 1; i < r; i++) {
			if (array[i] < array[l])
				swap(array[i], array[++bound]);
		}
		swap(array[l], array[bound]);
		quicksort(array, l, bound);
		quicksort(array, bound + 1, r);
	}
}
/*pdf*/

void quicksort_demo() {
	int array[] = {3, 7, 1, 2, 3, 100, 1010, -2, 11, 1, 33, 22};
	for (int i = 0; i < 12; i++) printf("%d ", array[i]);
	quicksort(array, 0, 12);
	printf("\nSorted array:\n");
	for (int i = 0; i < 12; i++) printf("%d ", array[i]);
	printf("\n");
}

#ifdef RUNDEMO
int main() { quicksort_demo(); return 0; }
#endif
