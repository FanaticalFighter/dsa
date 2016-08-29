# Written for the nako project by Utkrisht Dhankar (B15138)
# The source for this can be found at https://github.com/FanaticalFighter/nako/blob/master/makefile
# Modified to work for this project.

CC=gcc

FLAGS=-Wall -std=gnu99 `pkg-config --libs --cflags glib-2.0`

DFLAGS=-g -Wextra -Werror

RM=rm
RMFLAGS=-f

all: iterative recursive

# clean completely wipes directory of all executables and objects
clean:
	$(RM) $(RMFLAGS) iterative recursive

debug: CFLAGS+=$(DFLAGS)
debug: LFLAGS+=$(DFLAGS)
debug: all

iterative:
	$(CC) $(FLAGS) ../include/stack.c iterative.c -o iterative

recursive:
	$(CC) $(FLAGS) ../include/stack.c recursive.c -o recursive


