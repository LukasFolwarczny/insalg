#include "template.cpp"
// Lukas Folwarczny, 2013
// http://atrey.karlin.mff.cuni.cz/~folwar/insalg/

/*pdf*/
int euclid(int a, int b) {
	int t;
	while (b != 0)  {
		t = b;
		b = a % b;
		a = t;
	}
	return a;
}

//GCD = a * x + b * y
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
/*pdf*/

// DEMO
void euclid_demo() {
	printf("GCD(22031993, 2203) = %d\n", euclid(22031993,2203));
	printf("GCD(332024, 224224) = %d\n", euclid(332024, 224224));
	int a = 13, b = 17, x, y;
	int gcd = euclid_extended(a, b, x, y);
	printf("%d = %d * %d + %d * %d\n", gcd, a, x, b, y);

	a = 8, b = 24;
	gcd = euclid_extended(a, b, x, y);
	printf("%d = %d * %d + %d * %d\n", gcd, a, x, b, y);

}

#ifdef RUNDEMO
int main() { euclid_demo(); return 0; }
#endif
