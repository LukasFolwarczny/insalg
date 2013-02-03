#include "template.cpp"

int euclid(int a, int b) {
	int t;
	while (b != 0)  {
		t = b;
		b = a % b;
		a = t;
	}
	return a;
}

//gcd = a * x + b * y
int euclid_extended(int a, int b, int &x, int &y) {
	if (b == 0) {
		x = 1; y = 0;
		return a;
	}
	int xx, yy;
	int gcd = euclid_extended(b, a%b, xx, yy);
	x = yy;
	y = xx - (a/b) * yy;
	return gcd;
}
