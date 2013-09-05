#include "template.cpp"
// Lukas Folwarczny, 2013
// http://atrey.karlin.mff.cuni.cz/~folwar/insalg/

// Fenwick tree
// Fenwick tree is the equivalent of a summing interval tree.
// It handles in O(log N) time two operations: add a value to an
// element on given position and compute a prefix sum of its elements.
// Implementation of the Fenwick tree is very simple and tricky :-)

// The functions _add_ and _prefix_sum_ use zero-based indices,
// but internally one-based indices are used in the _fenwick_ array.

int N, *fenwick;
// Init an enmpty Fenwick tree with _number_ elements.
void init(int number) {
	N = number;
	fenwick = (int*)calloc((N+1),sizeof(int));
}

/*pdf*/
void add(int position, int value) {
	position++; // convert from 0-based to 1-based
	while (position <= N) {
		fenwick[position] += value;
		position = position + (position & -position);
	}
}

// Prefix sum [0,position)
int prefix_sum(int position) {
	int out = 0;
	while (position != 0) {
		out += fenwick[position];
		position = position & (position - 1);
	}
	return out;
}
/*pdf*/

void fenwick_demo() {
	init(100);
	add(0, 23);
	add(4, 17);
	add(4, 12);
	add(5, 12);
	add(2, 2);
	add(2, 3);
	for (int i = 0; i < 8; i++)
	    printf("sum [0,..,%d]: %d\n", i-1, prefix_sum(i));
}

#ifdef RUNDEMO
int main() { fenwick_demo(); return 0; }
#endif
