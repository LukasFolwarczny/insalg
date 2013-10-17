#include "template.cpp"
// Lukas Folwarczny, 2013
// http://atrey.karlin.mff.cuni.cz/~folwar/insalg/

/*pdf*/
ll euclid(ll a, ll b) {
	ll t;
	while (b != 0)  {
		t = b;
		b = a % b;
		a = t;
	}
	return a;
}

//GCD = a * x + b * y
ll euclid_extended(ll a, ll b, ll &x, ll &y) {
	if (b == 0) {
		x = 1; y = 0;
		return a;
	}
	ll xx, yy;
	ll gcd = euclid_extended(b, a%b, xx, yy);
	x = yy;
	y = xx - (a/b) * yy;
	return gcd;
}
/*pdf*/

// DEMO
void euclid_demo() {
	printf("GCD(22031993, 2203) = %lld\n", euclid(22031993,2203));
	printf("GCD(332024, 224224) = %lld\n", euclid(332024, 224224));
	ll a = 13, b = 17, x, y;
	ll gcd = euclid_extended(a, b, x, y);
	printf("%lld = %lld * %lld + %lld * %lld\n", gcd, a, x, b, y);

	a = 8, b = 24;
	gcd = euclid_extended(a, b, x, y);
	printf("%lld = %lld * %lld + %lld * %lld\n", gcd, a, x, b, y);

}

#ifdef RUNDEMO
int main() { euclid_demo(); return 0; }
#endif
