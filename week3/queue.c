#include "queue.h"

Queue QueueNew()
{
	return StackNew();
}

void Enqueue(Queue* q, void* data)
{
	Stack temp = StackNew();

	while (!StackIsEmpty((Stack) *q))
	{
		StackPush(&temp, StackPop((Stack*) q));
	}

	StackPush((Stack*) q, data);

	while (!StackIsEmpty(temp))
	{
		StackPush((Stack*) q, StackPop(&temp));
	}
}

void* Dequeue(Queue* q)
{
	return StackPop((Stack*) q);
}

gboolean QueueIsEmpty(Queue q)
{
	return StackIsEmpty((Stack) q);
}

// Only execute this if called with the -DDEBUG command
// Meant for testing the queue
#ifdef DEBUG

#include <stdio.h>

int main()
{
	Queue q = QueueNew();

	int j = 10;
	Enqueue(&q, &j);
	int k = j + 1;
	Enqueue(&q, &k);
	int l = k + 1;
	Enqueue(&q, &l);
	int m = l + 1;
	Enqueue(&q, &m);
	int n = m + 1;
	Enqueue(&q, &n);

	while (!QueueIsEmpty(q))
	{
		printf("%d\n", * (int*) Dequeue(&q));
	}

	return 0;
}
#endif
