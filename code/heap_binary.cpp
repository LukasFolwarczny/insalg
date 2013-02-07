#include "template.cpp"

int heap[100000], N;

int min() {
	return heap[0];
}

void bubble_down(int p) {
	while (p <= (N-1)/2) {
		int min = 2*p + 1;
		if (2*p + 2 < N && heap[min] > heap[2*p + 2])
			min = 2*p + 2;
		if (heap[min] < heap[p]) {
			swap(heap[p], heap[min]);
			p = min;
		}
		else break;
	}
}

void bubble_up(int p) {
	while (p > 0 && heap[p] < heap[(p-1)/2]) {
		swap(heap[p], heap[(p-1)/2]);
		p = (p-1)/2;
	}
}

void delete_min() {
	heap[0] = heap[N-1];
	N--;
	bubble_down(0);
}

void insert(int v) {
	heap[N++] = v;
	bubble_up(N-1);
}

void make(int* array, int length) {
	N = length;
	FOR(i,N) heap[i] = array[i];
	for (int p = (N-1)/2; p >= 0; p--) {
		bubble_down(p);
	}
}

int main() {

}
