#include <stdio.h>

int main()
{
	// We'll be calculating log(x)
	double x;

	// The number of terms up to which we want to calculate x
	int n;

	printf("Enter the value of x: ");
	scanf("%lf", &x);

	printf("Enter the number of terms n: ");
	scanf("%d", &n);

	// We'll store the logarithm in this
	double ans = 0;

	double term = (x - 1) / x;

	int i;
	for(i = 0; i < n; i++) {
		// Update answer
		ans += term / (i + 1);

		// Add a power to the term
		term *= (x - 1) / x;

	}

	printf("The value of log(%f) approximated to %d terms is : %f\n", x, n, ans);
	return 0;
}
