#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/stack.h"

gboolean IsParanthesis(char ch)
{
	return ch == '(' || ch == ')';
}

int main()
{
	printf("Please enter the expression : \n");

	char* expression = malloc(256 * sizeof(*expression));
	gets(expression);

	Stack paranthesis = StackNew();

	int i;
	int len = strlen(expression);
	gboolean detectedImbalance = FALSE;
	for (i = 0; i < len; i++)
	{
		if (expression[i] == '(')
		{
			StackPush(&paranthesis, &expression[i]);
		}
		else if (expression[i] == ')')
		{
			if (StackIsEmpty(paranthesis))
			{
				detectedImbalance = TRUE;
				break;
			}
			StackPop(&paranthesis);
		}
	}

	if (StackIsEmpty(paranthesis) && !detectedImbalance)
	{
		printf("The exression %s has balanced paranthesis\n", expression);
	}
	else
	{
		printf("The exression %s does not have balanced paranthesis\n", expression);
	}

	free(expression);

	return 0;
}
