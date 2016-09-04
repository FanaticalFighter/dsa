#include <glib.h>

typedef struct _SparseMatrix
{
	GHashTable* hashTable;
	int width;
	int height;

	int defaultValue;
} SparseMatrix;

SparseMatrix SparseMatrixNew(int width, int height, int defaultValue);
void SparseMatrixAdd(SparseMatrix sm, int value, int x, int y);
int SparseMatrixGet(SparseMatrix sm, int x, int y);
SparseMatrix SparseMatrixTranspose(SparseMatrix sm);
