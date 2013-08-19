#include "template.cpp"
// Lukas Folwarczny, 2013
// http://atrey.karlin.mff.cuni.cz/~folwar/insalg/

int N, fenwick[100001];

void add(int position, int value) {
	position++;
	while (position <= N) {
		fenwick[position] += value;
		position = position + (position & -position);
	}
}

//Prefix sum [0,position)
int prefix_sum(int position) {
	int out = 0;
	while (position != 0) {
		out += fenwick[position];
		position = position & (position - 1);
	}
	return out;
}

void example() {
	N = 100;
	add(0, 23);
	add(4, 17);
	add(4, 12);
	add(5, 12);
	add(2, 2);
	add(2, 3);
	FOR(i,7) printf("sum [0,..,%d]: %d\n", i-1, prefix_sum(i));
}

int main() { example(); return 0; }
