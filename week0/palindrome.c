#include <stdio.h>
#include <string.h>

#define MAX_STR_SIZE 128

unsigned short is_palindrome(char *str);

int main()
{
	// This is where we store the user's input
	char input_string[MAX_STR_SIZE];

	// Get input
	printf("Please enter the string to be checke as a palindrome : \n");
	scanf("%s", input_string);

	// Check if the string is a palindrome or not and display appropriate output
	if (is_palindrome(input_string)) {
		printf("%s is a palindrome string.\n", input_string);
	} else {
		printf("%s is NOT a palindrome string.\n", input_string);
	}

	return 0;
}

unsigned short is_palindrome(char *str)
{
	char reverse[MAX_STR_SIZE];

	// Fill the reverse string array
	int len = strlen(str);
	int i, j;
	for (i = len - 1, j = 0; i >= 0; i--, j++){
		reverse[j] = str[i];
	}

	reverse[len] = '\0';

	// If the reverse is the same as the original, then the string is a palindrome
	// Otherwise it isn't
	if (strcmp(reverse, str) == 0) {
		return 1;
	} else {
		return 0;
	}
}
