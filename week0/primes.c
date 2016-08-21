#include <stdio.h>
#include <stdlib.h>

#define UPPER_LIMIT 100

int main()
{
	// Stores whether or not the number
	// If an entry is non zero, then that entry is a prime
	int primes[100];

	// Initialize the array
	int i;
	for(i = 1; i <= UPPER_LIMIT; i++) {
		primes[i - 1] = i;
	}

	// 1 is not a prime number
	primes[1 - 1] = 0;

	// 2 IS a prime number
	primes[2 - 1] = 1;

	// Iterate through the primes
	for(i = 2; i <= UPPER_LIMIT; i++) {

		// For each prime, strike out the unneeded primes
		int j;
		for(j = i + 1; j <= UPPER_LIMIT; j++) {
			if (primes[j - 1] != 0 && primes[j - 1] % i == 0) {
				primes[j - 1] = 0;
			}
		}
	}

	// Display non zero numbers (primes) in the array
	for(i = 1; i <= UPPER_LIMIT; i++) {
		if (primes[i - 1] != 0) {
			printf("%d\n", i);
		}
	}

	return 0;
}
