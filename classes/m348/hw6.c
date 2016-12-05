/*#include <stdio.h>

void neville() {
	int i, j;
	int n = 4;
	double X;
	double x[n];
	double y[n];
	double Q[n][n];

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			Q[i][j] = 0.0;
		}
	}

	x[0] = -0.75;
	x[1] = -.5;
	x[2] = -.25;
	x[3] = 0;
	y[0] = -.0718125;
	y[1] = -0.0247500;
	y[2] = .3349375;
	y[3] = 1.10100000;
	X = -1 / 3;

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
}

int main() {
	neville();
}
*/


#include<stdio.h>
 
int main()
{
    double x[10], y[10], p[10];
    int k,f,n,i,j=1,f1=1,f2=0;
    printf("\nEnter the number of observations:\n");
    scanf("%d", &n);
 
    printf("\nEnter the different values of x:\n");
    for (i=1;i<=n;i++)
        scanf("%f", &x[i]);
 
    printf("\nThe corresponding values of y are:\n");
    for (i=1;i<=n;i++)
        scanf("%f", &y[i]);
 
    f=y[1];
    printf("\nEnter the value of 'k' in f(k) you want to evaluate:\n");
    scanf("%f", &k);
 
    do
    {
        for (i=1;i<=n-1;i++)
        {
            p[i] = ((y[i+1]-y[i])/(x[i+j]-x[i]));
            y[i]=p[i];
        }
        f1=1;
        for(i=1;i<=j;i++)
            {
                f1*=(k-x[i]);
            }
        f2+=(y[1]*f1);
        n--;
        j++;
    }
 
    while(n!=1);
    f+=f2;
    printf("\nf(%f) = %f", k , f);
    //getch();
}

