// Written for Assignment 3 by Utkrisht Dhankar (B15138)
// This implements a ridiculously inefficient implementation of a queue
// using two stacks

#include "../include/stack.h"

// Obscuring the stack behind a queue
typedef Stack Queue;

// Creates a new queue
Queue QueueNew();

// Enqueue data to the queue q
// Behaves very similarly to StackPush
void Enqueue(Queue* q, void* data);

// Dequeue data from the queue q
// Behaves very similarly to StackPop
void* Dequeue(Queue* q);

// Returns true if q is empty
// False otherwise
gboolean QueueIsEmpty(Queue q);
