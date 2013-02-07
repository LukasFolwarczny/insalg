#include "template.cpp"
// Lukas Folwarczny, 2013
// http://atrey.karlin.mff.cuni.cz/~folwar/insalg/

//[l,r)
void quick_sort(int* field, int l, int r) {
	if (l < r) {
		int bound = l;
		for (int i = l + 1; i < r; i++) {
			if (field[i] < field[l])
				swap(field[i], field[++bound]);
		}
		swap(field[l], field[bound]);
		quick_sort(field, l, bound);
		quick_sort(field, bound + 1, r);
	}
}

void example() {
	int field[] = {3, 7, 1, 2, 3, 100, 1010, -2, 11, 1, 33, 22};
	quick_sort(field, 0, 12);
	FOR(i,12) printf("%d\n", field[i]);
}

int main() { example(); return 0; }
