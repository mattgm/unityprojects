#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <vector>
using namespace std;

double f(double t, double y) {
	double yp = exp(t - y);
	return yp;
}

typedef double (* func)(double arg, double arg2);

void rungeKutta(double a, double b, int N, double al, func f) {
	double h = (b - a) / (double)(N);
	double t = a;
	double w = al;
	double k1, k2, k3, k4;
	cout << "(t, w):" << endl;

	for (int i = 1; i <= N; i++) {
		k1 = h * f(t, w);
		k2 = h * f((t + (h / 2)), (w + (k1/2)));
		k3 = h * f((t + (h/2)), (w + (k2 / 2)));
		k4 = h * f((t + h), w + k3);
		w = w + ((k1 + (k2 * 2) + (k3 * 2) + k4) / 6);
		t = a + (i * h);
		cout << "(" << t << ", " << w << ")" << endl;
	}
}

void rungeKuttaFul(double a, double b, double al, double TOL, 
					double hmax, double hmin, func f) {
	double t = a;
	double w = al;
	double h = hmax;
	int FLAG = 1;
	double k1, k2, k3, k4, k5, k6, R, d;
	cout << "(t, w, h):" << endl;

	while (FLAG) {
		k1 = h * f(t, w);
		k2 = h * f((t + (1/4) * h), (w + (1/4) * k1));
		k3 = h * f((t + (3/8) * h), (w + (3/32) * k1 + (9/32) * k2));
		k4 = h * f((t + (12/13) * h), (w + (1932/2197) * k1 - (7200/2197) 
			       * k2 + (7296/2197) * k3));
		k5 = h * f((t + h), (w + (439/216) * k1 - 8 * k2 + (3680/513) * k3
			       - (845/4104) * k4));
		k6 = h * f((t + (1/2) * h), (w - (8/27) * k1 + 2 * k2 - (3544/2565)
				   * k3 + (1859/4104) * k4 - (11/40) * k5));
		R = (1/h) * abs((1/360) * k1 - (128/4275) * k3 - (2197/75240) * k4
						+ (1/50) * k5 + (2/55) * k6);
		if (R <= TOL) {
			t = t + h;
			w = w + (25/216) * k1 + (1408/2565) * k3 + (2197/4104) * k4 - (1/5) * k5;
			cout << "(" << t << ", " << w << ", " << h << ")" << endl;
		}
		
		d = (.84) * pow((TOL / R), (1/4));
		if (d <= .1) {
			h = (.1) * h;
		} else if ( d >= 4) {
			h = 4 * h;
		} else {
			h = d * h;
		}

		if (h > hmax) {
			h = hmax;
		}

		if (t >= b) {
			FLAG = 0;
		} else if ((t + h) > b) {
			h = b - t;
		} else if (h < hmin) {
			FLAG = 0;
			cout << "('minimum h exceeded')" << endl;
			cout << "(Procedure completed unsuccessfully)" << endl; 
			return;
		}
	}
	cout << "(Procedure complete)" << endl;
}

int main() {
	rungeKutta(0, 1, 10, 1, f);
	cout << endl;
	rungeKuttaFul(0, 1, 1, .0001, .025, .005, f);
}




