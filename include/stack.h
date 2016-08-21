/*
 * stack.h
 * Written by Utkrisht Dhankar (B15138) for Assignment 2 of the DSA lab
 * This file defines a stack data structure using the GLib's implementation
 * of a singly linked list. This makes it easier to read code that uses
 * stacks, as instead of prepending to GSLists, we'll be pushing and popping
 * stacks.
 */
#include <glib.h>

/*
 * This obscures the GSList implementation so that a stack can be seen
 * as a seperate thing from a linked list.
 * And makes for a more readable code
 */
typedef GSList* stack;

/*
 * Returns a pointer to a new, empty stack
 * Do NOT dereference this. Basically, it is just syntax over NULL
 * So dereferencing will be a BAD idea
 */
stack *stack_new()
{
	return NULL;
}

/*
 * Pushes data onto the stack s
 */
void stack_push(stack** s, void* data)
{
	*s = g_slist_prepend(*s, data);
}

void* stack_pop(stack** s)
{
	void* data = *s->data;
	*s = g_slist_delete_link(s, s);
	return data;
}

