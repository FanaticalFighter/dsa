#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void PrintArray(char* s, double* arr, int size) {
	printf("%s: ", s);
	for (int i = 0; i < size - 1; i++) {
		printf("%lf, ", arr[i]); }
	printf("\n");
}

void PrintMatrix(double** m, int width, int height) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			printf("%lf\t", m[i][j]);
		}

		printf("\n");
	}
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
	double *d = malloc(n * sizeof(*d));

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

	double **augmented = malloc(n * sizeof(*augmented));
	for (int i = 0; i < n; i++) {
		augmented[i] = malloc((n + 1) * sizeof(*(augmented[i])));

		for (int j = 0; j < n; j++) {
			if (i == j) {
				augmented[i][j] = d[i];
			} else if (i == j - 1) {
				augmented[i][j] = a[i];
			} else if (i == j + 1) {
				augmented[i][j] = b[i];
			} else {
				augmented[i][j] = 0;
			}
		}
	}

	for (int i = 0; i < n; i++) {
		augmented[i][n] = 0;
	}
	augmented[0][n] = 1;

	PrintMatrix(augmented, n + 1, n);

	// The following code is from http://insite.iitmandi.ac.in/moodle/pluginfile.php/13419/mod_resource/content/1/gaussE.c
	// I have modified it to work with my program
	for(int j = 0; j < n; j++) {
		for(int i = 0; i < n; i++) {
			if(i > j) {
				double c = augmented[i][j] / augmented[j][j];
				for(int k = 0; k < n + 1; k++) {
					augmented[i][k] = augmented[i][k] - c * augmented[j][k];
				}
			}
		}
	}

	double* theta = malloc(n * sizeof(*theta));
	theta[n - 1] = augmented[n - 1][n] / augmented[n - 1][n - 1];
	for(int i = n - 2; i >= 0; i--) {
		double sum = 0;
		for(int j = i; j < n; j++) {
			sum = sum + augmented[i][j] * theta[j];
		}
		theta[i] = (augmented[i][n] - sum) / augmented[i][i];
	}

	PrintArray("theta", theta, n);

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
