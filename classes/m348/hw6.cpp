int i, j;
int n = 4;
double X;
double x[n];
double y[n];
double Q[n][n];

for (i = 0; i < n; i++) {
	for (j = 0; j < n; j++) {
		Q[i][j] = 0.0
	}
}

x[0] = 8.1;
x[1] = 8.3;
x[2] = 8.6;
x[3] = 8.7;
y[0] = 16.94410;
y[1] = 17.56492;
y[2] = 18.50515;
y[3] = 18.82091;

X = 8.4;

for (i = 0; i < n; i++) {
	Q[i][0] = y[i];
}

for (i = 1; i < n; i++) {
	for (j = 1; j <= i; j++) {
		Q[i][j] = ((X - x[i-j]) * (Q[i][j-1]) - (X - x[i]) * ( Q[i-1][j-1])) / (x[i] - x[i -j]);
	}
}

printf("Q matrix: \n");
for (i = 0; i < n; i++) {
	for (j = 0; j <n; j++) {
		printf("%9f ", Q[i][j]);
	}
	printf("\n");
}


