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

typedef struct _Peg
{
	short pegOrder; // Is the peg the 0th, 1st, or 2ng peg?
	Stack stack; // The stack of the disks in the peg
} Peg;

// Solves the tower recursively.
// disk is the top level disk in the stack
// source is the source stack, where the disk is from
// dest is the destination stack
// spare is the spare stack
void SolveTower(int disk, Peg* source, Peg* dest, Peg* spare);

int main()
{
	int numberOfDisks;
	printf("Enter the number of disks: ");
	scanf("%d", &numberOfDisks);

	// Initialize the source peg involved in the tower of Hanoi problem
	Peg source;
	source.pegOrder = 0;
	source.stack = StackNew();
	int i;
	for (i = 0; i < numberOfDisks; i++)
	{
		// The stack will only take pointers, so this is needed
		int* valueOfDisk = malloc(sizeof(*valueOfDisk));
		*valueOfDisk = numberOfDisks - i - 1;
		StackPush(&source.stack, valueOfDisk);
	}

	Peg dest;
	dest.pegOrder = 1;
	dest.stack = StackNew();

	Peg spare;
	spare.pegOrder = 2;
	spare.stack = StackNew();

	SolveTower(numberOfDisks - 1, &source, &dest, &spare);

	return 0;
}

// Helper function for SolveTower
// Moves the top disk from source to the destination
void MoveDisk(Peg* source, Peg* dest)
{
	// Move the disk
	int* disk = StackPop(&source->stack);
	StackPush(&dest->stack, disk);

	// Write the stack trace
	printf("Moved from stack %d to stack %d\n", source->pegOrder + 1, dest->pegOrder + 1);
}

void SolveTower(int disk, Peg* source, Peg* dest, Peg* spare)
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
