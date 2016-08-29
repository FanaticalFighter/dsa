# Written for the nako project by Utkrisht Dhankar (B15138)
# The source for this can be found at https://github.com/FanaticalFighter/nako/blob/master/makefile
# Modified to work for this project.

CC=gcc

FLAGS=-Wall -std=gnu99 `pkg-config --libs --cflags glib-2.0`

DFLAGS=-g -Wextra -Werror -DDEBUG

RM=rm
RMFLAGS=-f

all: josephus queue

# clean completely wipes directory of all executables and objects
clean:
	$(RM) $(RMFLAGS) josephus queue

debug: FLAGS+=$(DFLAGS)
debug: FLAGS+=$(DFLAGS)
debug: all

josephus:
	$(CC) $(FLAGS) josephus.c -o josephus

queue:
	$(CC) $(FLAGS) ../include/stack.c queue.c -o queue
