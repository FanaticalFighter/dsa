# Written for the nako project by Utkrisht Dhankar (B15138)
# The source for this can be found at https://github.com/FanaticalFighter/nako/blob/master/makefile
# Modified to work for this project.

CC=gcc

FLAGS=-Wall -std=gnu99 `pkg-config --libs --cflags glib-2.0`

DFLAGS=-g -Wextra -Werror

RM=rm
RMFLAGS=-f

all: josephus

# clean completely wipes directory of all executables and objects
clean:
	$(RM) $(RMFLAGS) josephus

debug: CFLAGS+=$(DFLAGS)
debug: LFLAGS+=$(DFLAGS)
debug: all

josephus:
	$(CC) $(FLAGS) ../include/stack.c josephus.c -o josephus
