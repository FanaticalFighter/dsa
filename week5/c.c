#include <stdlib.h>
#include <time.h>
#include <stdio.h>

typedef struct _RandomListNode
{
	int label;
	struct _RandomListNode* next;
	struct _RandomListNode* random;
} RandomListNode;

void PrintList(RandomListNode* list)
{
	RandomListNode* it = list;
	while (it != NULL) {
		if (it->random != NULL)
			printf("%d -> %d\n", it->label, it->random->label);
		else
			printf("%d\n", it->label);
		it = it->next;
	}
}

RandomListNode* Prepend(RandomListNode* node, int label, RandomListNode* random)
{
	RandomListNode* new = malloc(sizeof(*new));
	new->label = label;
	new->next = node;
	new->random = random;

	return new;
}

void InsertAfter(RandomListNode* node, int label, RandomListNode* random)
{
	RandomListNode* new = malloc(sizeof(*new));
	new->label = label;
	new->next = node->next;
	node->next = new;
	new->random = random;
}

RandomListNode* CopyRandomList(RandomListNode* list)
{
	RandomListNode* it = list;
	while (it != NULL) {
		InsertAfter(it, it->label, NULL);
		it = it->next->next;
	}

	it = list;
	while (it != NULL && it->next != NULL) {
		it->next->random = it->random->next;
		it = it->next->next;
	}

	RandomListNode* copy = list->next;

	RandomListNode* originalIt = list;
	RandomListNode* copyIt = copy;
	while (copyIt != NULL) {
		originalIt->next = copyIt->next;
		if (originalIt->next != NULL) {
			copyIt->next = originalIt->next->next;
		} else {
			copyIt->next = NULL;
		}

		originalIt = originalIt->next;
		copyIt = copyIt->next;
	}

	return copy;
}

RandomListNode* CreateList(int n)
{
	srand(time(NULL));

	RandomListNode* list = NULL;
	RandomListNode** listArray = malloc(n * sizeof(*listArray));
	for (int i = n - 1; i >= 0; i--)
	{
		list = Prepend(list, i, list);
		listArray[i] = list;
	}

	for (int i = 0; i < n; i++) {
		listArray[i]->random = listArray[rand() % n];
	}

	return list;
}

int main()
{
	RandomListNode* l = CreateList(4);

	RandomListNode* copy = CopyRandomList(l);
	PrintList(l);
	printf("\n\n");
	PrintList(copy);

	return 0;
}
