#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void PrintArray(char* s, double* arr, int size) {
	printf("%s: ", s);
	for (int i = 0; i < size - 1; i++) {
		printf("%lf, ", arr[i]); }
	printf("\n");
}

double ComputeExact(double beta, double x)
{
	return cosh(sqrt(beta) * (1 - x)) / cosh(sqrt(beta));
}

int main()
{
	double beta;
	int n;

	printf("Please enter the value of beta and n\n");
	scanf("%lf %d", &beta, &n);

	double *a = malloc((n - 1) * sizeof(*a));
	double *b = malloc((n - 1) * sizeof(*b));
	double *r = malloc((n - 1) * sizeof(*r));
	double *d = malloc(n * sizeof(*d));

	r[0] = 1;
	for (int i = 1; i < n; i++) {
		r[i] = 0;
	}

	a[0] = 0;
	for(int i = 1; i < n - 1; i++) {
		a[i] = 1.0 * (n - 1) * (n - 1);
	}

	for (int i = 0; i < n - 2; i++) {
		b[i] = 1.0 * (n - 1) * (n - 1);
	}
	b[n - 2] = -1.0;

	d[0] = 1;
	for (int i = 1; i < n; i++) {
		d[i] = - beta  - 2.0 * (n - 1) * (n - 1);
	}
	d[n - 1] = 1;

	for (int i = 1; i < n; i++) {
		d[i] -= a[i - 1] * b[i - 1] / d[i - 1];
		r[i] -= r[i - 1] * b[i - 1] / d[i - 1];
	}

	double* theta = malloc(n * sizeof(*theta));
	theta[n - 1] = r[n - 1] / d[n - 1];
	for (int i = n - 2; i > 0; i--) {
		theta[i] = (r[i] - a[i] * theta[i + 1]) / d[i];
	}
	theta[0] = 1;


	double sum = 0;
	for (int i = 0; i < n; i++) {
		sum += (ComputeExact(beta, (double) i / (n - 1)) - theta[i]) * (ComputeExact(beta, (double) i / (n - 1)) - theta[i]);
	}
	double error = sqrt(sum / n );
	printf("Error when n = %d is %lf\n", n, error);

	FILE* x_theta = fopen("x_theta", "w");
	for (int i = 0; i < n; i++) {
		fprintf(x_theta, "%lf %lf\n", (double) i / (n - 1), theta[i]);
	}

	FILE* x_theta_exact = fopen("x_theta_exact", "w");
	for (int i = 0; i < n; i++) {
		fprintf(x_theta_exact, "%lf %lf\n", (double) i / (n - 1), ComputeExact(beta, (double) i / (n - 1)));
	}


	return 0;
}
