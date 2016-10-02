#include <stdio.h>

// Swaps the values of a and b
void swapPointers(int* a, int* b);

// Prints the pointer a's value
void printPointerValue(int* a);

// Compares the value of a and b
// Returns 1 if a is greater than b
// 0 otherwise
int compareInts(int* a, int* b);

// Exactly like strcmp
int compareStrings(char* a, char* b);

// Prints all numbers from 1 to n
void countTillThisNum(int num);

int main()
{
	return 0;
}

void swapPointers(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void printPointerValue(int* a)
{
	printf("%d", *a);
}

int compareInts(int* a, int* b)
{
	if (*a > *b) {
		return 0;
	} else {
		return 1;
	}
}

int compareStrings(char* a, char* b)
{
	while (*a != '\0' && *b != '\0') {
		if (*a > *b) {
			return 1;
		} else if (*a < *b) {
			return -1;
		}
	}

	if (*a == '\0' && *b != '\0') {
		return -1;
	} else if (*a != '\0' && *b == '\0') {
		return 1;
	} else {
		return 0;
	} 
}

void countTillThisNum(int num)
{
	if (num != 1) {
		countTillThisNum(num - 1);
	}
	printf("%d\n", num);
}
