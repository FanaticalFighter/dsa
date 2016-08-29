#include "stack.h"

Stack StackNew()
{
	return NULL;
}

gboolean StackIsEmpty(Stack s)
{
	if (s == NULL)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void StackPush(Stack* s, void* data)
{
	*s = g_slist_prepend(*s, data);
}

void* StackPop(Stack* s)
{
	// If the stack is empty, there is no data to return
	if (StackIsEmpty(*s))
	{
		return NULL;
	}

	void* data = (*s)->data;
	*s = g_slist_delete_link(*s, *s);
	return data;
}

const void* StackPeak(Stack *s)
{
	if (StackIsEmpty(*s))
	{
		return NULL;
	}

	return (*s)->data;
}
