#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <vector>
using namespace std;


void euler(double a, double b, double N, double al) {
	double h = (b - a) / (double)(N);
	double t = a;
	double w = al;

	for (int i = 0; i < N; i++) {
		t = a + i * h;
		cout << t << " " << w << endl;
		w = w + h * (1 + w / t);
	}
	cout << b << " " << w << endl;
}

int main() {
	euler(1, 2, 100, 2);
}




