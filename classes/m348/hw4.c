#include <iostream>
#include <stdlib.h>
#include <math>

int secantMethod(double p0, double p1, double fn(), double TOL, int N0) {
	double p2 = 0;
	double q0 = fn(p0);
	double q1 = fn(p1);
	int i = 0;
	while (i < N0) {
		p2 = p1 - ((q1 * (p1 - p0))/(q1 - q0));
		cout << "Iteration" << i << ": " << p2 << endl;
		if (abs(p2) <= TOL) return p2;

		p0 = p1;
		q0 = q1;
		p1 = p2;
		q1 = fn(p1);

		i++
	}
	return p2;
}

double fn(double x) {
	double result = -pow(x, 3) - cos(x);
	return result;
}

int main () {
	secantMethod(-1, 0, fn, .00001, 4);
}