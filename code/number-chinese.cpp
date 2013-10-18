#include "template.cpp"
#include "number-euclid.cpp"
// Lukas Folwarczny, 2013
// http://atrey.karlin.mff.cuni.cz/~folwar/insalg/
// Solve a system of congruences in the form x = r[i] (mod m[i])
// The function chinese works only for pairwise coprime moduli,
// nonchinese function works generally

/*pdf*/
// Compute the modulo of a number, even negative
ll modn(ll x, ll m) {
	if (x >= 0) return x % m;
	return ((1-x/m)*m + x) % m;
}

// Solve a set of n equations of the form: x=r[i] (mod m[i])
// Moduli must be pairwise coprime
ll chinese(int n, int *m, int *r) {
	ll M = 1, x = 0;
	for (int i = 0; i < n; i++) M *= m[i];
	for (int i = 0; i < n; i++) {
		ll u, v;
		ll s = M / m[i];
		euclid_extended(m[i], s, u, v);
		// v*s=1(mod m[i]), v*s=0(mod m[j]) for j!=i
		if (v < 0) v += m[i];
		x += r[i] * v * s;
		x = modn(x, M);
	}
	return x;
}

// For a set of n equations in the form: x=r[i] (mod m[i])
// find the smallest nonnegative solution or return -1,
// if no solution exists
ll non_chinese(int n, int *m, int *r) {
	ll res = r[0];
	ll mres = m[0];
	for (int i = 1; i < n; i++) {
		// set of 2 equations: x=res (mod mres), x=r[i] (mod m[i])
		ll g = euclid(mres, m[i]);
		if (res % g != r[i] % g)
			return -1;
		ll rnew = modn(r[i] - res, m[i]);
		// solve k*mres = rnew (mod m[i])
		ll ld = mres / g, rd = rnew / g, md = m[i] / g;
		
		ll u, v;
		euclid_extended(md, ld, u, v);
		ll k = modn(v*rd, md);
		res = k*mres + res;
		mres = md * mres;
		res %= mres;
	}
	return res;
}
/*pdf*/

// DEMO
void chinese_demo() {
	int n = 3;
	int m[] = {3, 5, 7};
	int r[] = {2, 2, 1};
	for (int i = 0; i < n; i++)
		printf("x = %d (mod %d)\n", r[i], m[i]);
	printf("Solution x = %lld\n", chinese(n, m, r));
	printf("NC Solution x = %lld\n\n", non_chinese(n, m, r));
	
	int n2  = 3;
	int m2[] = {3, 11, 13};
	int r2[] = {2,  8, 11};
	for (int i = 0; i < n2; i++)
		printf("x = %d (mod %d)\n", r2[i], m2[i]);
	printf("Solution x = %lld\n\n", chinese(n2, m2, r2));
	
	int n3  = 5;
	int m3[] = {4, 8, 3, 11, 13};
	int r3[] = {2, 4, 2,  8, 11};
	for (int i = 0; i < n3; i++)
		printf("x = %d (mod %d)\n", r3[i], m3[i]);
	printf("NC Solution x = %lld\n\n", non_chinese(n3, m3, r3));
	
	int n4  = 5;
	int m4[] = {4, 24, 21, 11, 44};
	int r4[] = {2, 14,  5,  4, 26};
	for (int i = 0; i < n4; i++)
		printf("x = %d (mod %d)\n", r4[i], m4[i]);
	printf("NC Solution x = %lld\n", non_chinese(n4, m4, r4));
}

//#ifdef RUNDEMO
int main() { chinese_demo(); return 0; }
//#endif
