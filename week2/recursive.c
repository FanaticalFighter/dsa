// Written by Utkrisht Dhankar (B15138).
// This file is a solution to Assignment 2.
// It implements a solution for the Tower of Hanoi problem iteratively
#include <stdio.h>
#include <stdlib.h>

#include "../include/stack.h"

// This struct represents a movement of the disks
typedef struct _Move
{
	short source; // The source for the disk
	short dest; // The destination for the disk
} Move;

// Solves the tower recursively.
// disk is the top level disk in the stack
// source is the source stack, where the disk is from
// dest is the destination stack
// spare is the spare stack
void SolveTower(int disk, Stack* source, Stack* dest, Stack* spare);

int main()
{
	int numberOfDisks;
	printf("Enter the number of disks: ");
	scanf("%d", &numberOfDisks);

	// Initialize the source peg involved in the tower of Hanoi problem
	Stack source = StackNew();
	int i;
	for (i = 0; i < numberOfDisks; i++)
	{
		// The stack will only take pointers, so this is needed
		int* valueOfDisk = malloc(sizeof(*valueOfDisk));
		*valueOfDisk = numberOfDisks - i - 1;
		StackPush(&source, valueOfDisk);
	}

	Stack dest = StackNew();
	Stack spare = StackNew();

	SolveTower(numberOfDisks - 1, &source, &dest, &spare);

	printf("%d\t%d\t%d\n", g_slist_length(source), g_slist_length(dest), g_slist_length(spare));

	return 0;
}

// Helper function for SolveTower
// Moves the top disk from source to the destination
void MoveDisk(Stack* source, Stack* dest)
{
	int* disk = StackPop(source);
	StackPush(dest, disk);
}

void SolveTower(int disk, Stack* source, Stack* dest, Stack* spare)
{
	if (disk == 0)
	{
		MoveDisk(source, dest);
	}
	else
	{
		SolveTower(disk - 1, source, spare, dest);
		MoveDisk(source, dest);
		SolveTower(disk - 1, spare, dest, source);
	}
}
