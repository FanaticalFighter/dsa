#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/stack.h"

void* StackPopBottom(Stack* s)
{
	void* top = StackPop(s);
	if (StackIsEmpty(*s))
	{
		return top;
	}

	void* bottom = StackPopBottom(s);
	StackPush(s, top);
	return bottom;
}

void StackReverse(Stack* s)
{
	if (StackIsEmpty(*s))
	{
		return;
	}

	void* bottom = StackPopBottom(s);
	StackReverse(s);
	StackPush(s, bottom);
}

int main()
{
	Stack s = StackNew();

	int i;
	for (i = 0; i < 10; i++)
	{
		int* temp = malloc(sizeof(*temp));
		*temp = i;
		StackPush(&s, temp);
	}

	StackReverse(&s);

	while(!StackIsEmpty(s))
	{
		int* temp = StackPop(&s);
		printf("%d\n", *temp);
		free(temp);
	}

	return 0;
}
