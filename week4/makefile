# Written for the nako project by Utkrisht Dhankar (B15138)
# The source for this can be found at https://github.com/FanaticalFighter/nako/blob/master/makefile
# Modified to work for this project.

CC=gcc

FLAGS=-Wall -std=gnu99 `pkg-config --libs --cflags glib-2.0`

DFLAGS=-g -Wextra -Werror -DDEBUG

RM=rm
RMFLAGS=-rf

all: balance stack_reversal stackWithQueue

# clean completely wipes directory of all executables and objects
clean:
	$(RM) $(RMFLAGS) balance stack_reversal stackWithQueue *.dSYM

debug: FLAGS+=$(DFLAGS)
debug: FLAGS+=$(DFLAGS)
debug: all

stackWithQueue:
	$(CC) $(FLAGS) ../include/stack.c stackWithQueue.c -o stackWithQueue

balance:
	$(CC) $(FLAGS) ../include/stack.c balance.c -o balance

stack_reversal:
	$(CC) $(FLAGS) ../include/stack.c stack_reversal.c -o stack_reversal
