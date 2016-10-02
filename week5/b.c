#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void writer(int** matrix, int width, int height, char* filename);
int** maker(int width, int height);
void printDelete(int** matrix, int width, int height);

int main()
{
	int m, n;
	printf("Please enter the values of m and n\n");
	scanf("%d %d", &m, &n);

	int** matrix = maker(m, n);
	writer(matrix, m, n, "matrix");
	printDelete(matrix, m, n);

	return 0;
}

int** maker(int width, int height)
{
	srand(time(NULL));

	int** matrix = malloc(height * sizeof(*matrix));
	for (int i = 0; i < height; i++) {
		int* matrixRow = malloc(width * sizeof(*matrix));
		for (int j = 0; j < width; j++) {
			matrixRow[j] = rand();
		}

		matrix[i] = matrixRow;
	}

	return matrix;
}

void writer(int** matrix, int width, int height, char* filename)
{
	FILE* f = fopen(filename, "w");

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			fprintf(f, "%d\t", matrix[i][j]);
		}

		fprintf(f, "\n");
	}
}

void printDelete(int** matrix, int width, int height)
{
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			printf("%d\t", matrix[i][j]);
		}

		free(matrix[i]);
		printf("\n");
	}

	free(matrix);
}
