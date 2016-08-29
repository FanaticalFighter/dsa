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
// as a seperate data structure from a GLib linked list.
// And makes for a more readable code
typedef GSList* Stack;


// Returns a pointer to a new, empty Stack
// Do NOT dereference this. Basically, it is just syntax over NULL
// Actually, don't EVER dereference a Stack. Only use the functions provided here
// So dereferencing will be a BAD idea
Stack StackNew();

// Returns true if the stack empty
// Returns false otherwise
gboolean StackIsEmpty(Stack s);

// Pushes data onto the Stack s
void StackPush(Stack* s, void* data);

// Pops the Stack
// A NULL from this function does NOT mean that the Stack is empty
// It might be that the data in the stack was NULL
// Use StackIsEmpty for checking to make sure
// Also, if this data was malloced before entering the stack, remember to
// free it.
void* StackPop(Stack* s);

// Returns a constant pointer to the data at top of the stack
const void* StackPeak(Stack *s);
