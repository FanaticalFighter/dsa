#include "sparse.h"

#include <stdlib.h>
#include <stdio.h>

SparseMatrix SparseMatrixNew(int width, int height, int defaultValue)
{
	SparseMatrix sm;

	sm.hashTable = g_hash_table_new(g_int_hash, g_int_equal);
	sm.width = width;
	sm.height = height;
	sm.defaultValue = defaultValue;

	return sm;
}

int CalculateKey(SparseMatrix sm, int x, int y)
{
	return sm.width * y + x;
}

void SparseMatrixAdd(SparseMatrix sm, int value, int x, int y)
{
	int* key = malloc(sizeof(*key));
	*key = CalculateKey(sm, x, y);

	int* val = malloc(sizeof(*val));
	*val = value;

	g_hash_table_insert(sm.hashTable, GINT_TO_POINTER(key), val);
}


int SparseMatrixGet(SparseMatrix sm, int x, int y)
{
	int key = CalculateKey(sm, x, y);

	void* data = g_hash_table_lookup(sm.hashTable, &key);
	if (data == NULL)
	{
		return sm.defaultValue;
	}
	else
	{
		return * (int*) data;
	}
}

int ReverseEngineerY(SparseMatrix sm, unsigned int key)
{
	return key / sm.height;
}

int ReverseEngineerX(SparseMatrix sm, unsigned int key)
{
	return key - sm.width* ReverseEngineerY(sm, key);
}

SparseMatrix SparseMatrixTranspose(SparseMatrix sm)
{
	SparseMatrix transposed = SparseMatrixNew(sm.height, sm.width, sm.defaultValue);

	// Key and value pair to be used for iteration
	gpointer key;
	gpointer value;

	GHashTableIter iter;
	g_hash_table_iter_init(&iter, sm.hashTable);
	while (g_hash_table_iter_next(&iter, &key, &value))
	{
		int y = ReverseEngineerY(sm, * (unsigned int*) key);
		int x = ReverseEngineerX(sm, * (unsigned int*) key);
		int val = * (int*) value;
		SparseMatrixAdd(transposed, val, y, x);
	}

	return transposed;
}

void SparseMatrixPrint(SparseMatrix sm)
{
	for(int i = 0; i < sm.height; i++)
	{
		for (int j = 0; j < sm.width; j++)
		{
			printf("%d\t", SparseMatrixGet(sm, j, i));
		}
		printf("\n");
	}
}

#ifdef DEBUG

int main()
{
	SparseMatrix sm = SparseMatrixNew(4, 4, 0);

	for(int i = 1; i <= 4; i++)
	{
		SparseMatrixAdd(sm, i, i - 1, 0);
	}

	for (int i = 1; i < 5; i++)
	{
		SparseMatrixAdd(sm, 5 * i, 0, i - 1);
	}

	SparseMatrixPrint(sm);
	SparseMatrixPrint(SparseMatrixTranspose(sm));

	return 0;
}

#endif
