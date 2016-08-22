// stack.h
// Written by Utkrisht Dhankar (B15138) for Assignment 2 of the DSA lab
// This file defines a stack data structure using the GLib's implementation
// of a singly linked list. This makes it easier to read code that uses
// stacks, as instead of prepending to GSLists, we'll be pushing and popping
// stacks.
//
// This is a non compiled header as it is ridiculously small and I don't want
// to have to link this every time I do something

#include <glib.h>


// This obscures the GSList implementation so that a Stack can be seen
// as a seperate thing from a linked list.
// And makes for a more readable code
typedef GSList* Stack;


// Returns a pointer to a new, empty Stack
// Do NOT dereference this. Basically, it is just syntax over NULL
// So dereferencing will be a BAD idea
Stack StackNew()
{
	return NULL;
}


// Pushes data onto the Stack s
void StackPush(Stack* s, void* data)
{
	*s = g_slist_prepend(*s, data);
}

// Pops the Stack
// A NULL from this function does NOT mean that the Stack is empty
// It might be that the data in the stack was NULL
// Use StackIsEmpty for checking to make sure
void* StackPop(Stack* s)
{
	// If the stack is empty, there is no data to return
	if (*s == NULL)
	{
		return NULL;
	}

	void* data = (*s)->data;
	*s = g_slist_delete_link(*s, *s);
	return data;
}

// Returns true if the stack empty
// Returns false otherwise
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
