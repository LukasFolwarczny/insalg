#include "template.cpp"
// Lukas Folwarczny, 2013
// http://atrey.karlin.mff.cuni.cz/~folwar/insalg/
// Weiszfeld's algorithm for geometric median approximation
// Inspired by a Challenge24 2013 task.


double distance(double x1, double y1, double x2, double y2) {
	return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

void geometric_median(int N, int iterations, double* X, double* Y, double &Xmed, double
&Ymed) {
	double AX[2], AY[2];
	AX[0] = (X[0]+X[1]) / 2, AY[0] = (Y[0]+Y[1])/2; // initial guess
	FOR(it,iterations) {
		double numerator_x = 0, numerator_y = 0, denominator = 0;
		int t = it % 2;
		FOR(n,N) {
			double dist = distance(X[n], Y[n], AX[t], AY[t]);
			if (dist != 0) {
    				numerator_x += X[n]/dist;
				numerator_y += Y[n]/dist;
				denominator += 1.0/dist;
			}
		}
		AX[1-t] = numerator_x/denominator;
		AY[1-t] = numerator_y/denominator;
	}
	Xmed = AX[iterations%2];
	Ymed = AY[iterations%2];
}

// DEMO

int N;
double X[1000000], Y[1000000];

void geometric_median_demo() {
	scanf("%d", &N);
	FOR(i,N) {
		scanf("%lf %lf", &X[i], &Y[i]);
	}
	double RX, RY;
	geometric_median(N, 100000, X, Y, RX, RY);
	printf("%lf %lf\n", RY, RY);
}

#ifdef RUNDEMO
int main() { geometric_median_demo(); return 0; }
#endif
