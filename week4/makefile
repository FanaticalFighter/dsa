# Written for the nako project by Utkrisht Dhankar (B15138)
# The source for this can be found at https://github.com/FanaticalFighter/nako/blob/master/makefile
# Modified to work for this project.

CC=gcc

FLAGS=-Wall -std=gnu99 `pkg-config --libs --cflags glib-2.0`

DFLAGS=-g -Wextra -Werror -DDEBUG

RM=rm
RMFLAGS=-rf

all: balance

# clean completely wipes directory of all executables and objects
clean:
	$(RM) $(RMFLAGS) balance *.dSYM

debug: FLAGS+=$(DFLAGS)
debug: FLAGS+=$(DFLAGS)
debug: all

balance:
	$(CC) $(FLAGS) ../include/stack.c balance.c -o balance
