#include <stdio.h>
#include <glib.h>

// obscure stack definition using a queue
typedef GQueue* StackWithQueue;

StackWithQueue StackWithQueueNew();
void StackWithQueuePush(StackWithQueue* s, void* data);
void* StackWithQueuePop(StackWithQueue* s);
gboolean StackWithQueueIsEmpty(StackWithQueue s);

int main()
{
	int a = 1, b = 2, c = 3, d = 4;

	StackWithQueue s = StackWithQueueNew();
	StackWithQueuePush(&s, &a);
	StackWithQueuePush(&s, &b);
	StackWithQueuePush(&s, &c);
	StackWithQueuePush(&s, &d);

	while (!StackWithQueueIsEmpty(s))
	{
		printf("%d\n", * (int*) StackWithQueuePop(&s));
	}

	return 0;
}

StackWithQueue StackWithQueueNew()
{
	return g_queue_new();
}

void StackWithQueuePush(StackWithQueue* s, void* data)
{
	GQueue* tempQueue = g_queue_new();
	g_queue_push_tail(tempQueue, data);

	while (!StackWithQueueIsEmpty(*s))
	{
		g_queue_push_tail(tempQueue, StackWithQueuePop(s));
	}

	*s = tempQueue;
}

void* StackWithQueuePop(StackWithQueue* s)
{
	return g_queue_pop_head(*s);
}

gboolean StackWithQueueIsEmpty(StackWithQueue s)
{
	return g_queue_is_empty(s);
}
