#include "template.cpp"

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
	printf("%d\n", prefix_sum(0));
	printf("%d\n", prefix_sum(1));
	printf("%d\n", prefix_sum(2));
	printf("%d\n", prefix_sum(3));
	printf("%d\n", prefix_sum(4));
}

int main() { example(); return 0; }
