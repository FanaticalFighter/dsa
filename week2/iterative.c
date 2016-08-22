// Written by Utkrisht Dhankar (B15138).
// This file is a solution to Assignment 2.
// It implements a solution for the Tower of Hanoi problem iteratively
#include <stdio.h>
#include <stdlib.h>

#include "../include/stack.h"

typedef struct _Peg
{
	short pegOrder; // Is the peg the 0th, 1st, or 2ng peg?
	Stack stack; // The stack of the disks in the peg
} Peg;

// This struct represents a movement of the disks
typedef struct _Move
{
	Peg* source; // The source for the disk
	Peg* dest; // The destination for the disk
	Peg* spare; // The spare peg left over. This is useful in some cases where knowing
				// which peg is free is important

	int disk; 	// The size of the disk to be moved
				// Larger means bigger

	gboolean split; // Whether or not this move should be split, or executed
					// A split move (TRUE) means that this move isn't executed when encountered
					// in the stack, but split into different moves
					// A non-split move (FALSE) means that the move is to be executed with no splitting involved
} Move;

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

Move* NewMove(Peg* source, Peg* dest, Peg* spare, int disk)
{
	Move* move = malloc(sizeof(*move));
	move->source = source;
	move->dest = dest;
	move->spare = spare;
	move->disk = disk;
	move->split = disk ? TRUE : FALSE;
	return move;
}

void SolveTower(int disk, Peg* source, Peg* dest, Peg* spare)
{
	Stack movesToDo = StackNew();

	// Add the move for moving the biggest disk to the stack.
	Move* moveBiggestDiskToDest = NewMove(source, dest, spare, disk);
	StackPush(&movesToDo, moveBiggestDiskToDest);

	while (!StackIsEmpty(movesToDo))
	{
		Move *move = StackPop(&movesToDo);

		if (move->split == FALSE)
		{
			MoveDisk(move->source, move->dest);
		}
		else
		{
			Move* moveSmallerDisksBack = NewMove(move->spare, move->dest, move->source, move->disk - 1);
			StackPush(&movesToDo, moveSmallerDisksBack);

			Move* moveBigDiskToDest = NewMove(move->source, move->dest, move->spare, 0); 	// The disk being zero here just means
																							// That the program should immediately execute this
			StackPush(&movesToDo, moveBigDiskToDest);

			Move* moveToSpare = NewMove(move->source, move->spare, move->dest, move->disk - 1);
			StackPush(&movesToDo, moveToSpare);
		}
	}
}
