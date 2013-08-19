#include "template.cpp"
// Lukas Folwarczny, 2013
// http://atrey.karlin.mff.cuni.cz/~folwar/insalg/

// Binary minimum heap over N elements, 0..(N-1)
// Sons of i: 2*i+1, 2*i+2
// Father of i: (i-1)/2
// Time complexity: make O(N), other O(log N)

#define MaxN 100000 // max number of elements
int heap[MaxN], N;

int get_min() {
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

void binary_heap_demo() {
	int array[] = {4,2,3,-1,0,3,7,11};
	make(array, 8);
	delete_min();
	printf("%d\n", get_min());
	insert(-3);
	printf("%d\n", get_min());
	FOR(i,8) {
		printf("%d\n", get_min());
		delete_min();
	}
}

#ifdef RUNDEMO
int main() { binary_heap_demo(); return 0; }
#endif
