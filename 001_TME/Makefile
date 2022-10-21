CFLAGS = -Wall -Wextra -Werror -pedantic -std=c17 -g
CC = gcc

PROGRAMS = mycut

.PHONY: all clean re

all: $(PROGRAMS)

re: clean all

mycut: mycut.c
	$(CC) -o $@ $(CFLAGS) $^

clean:
	rm -rf *.o *~ *.dSYM $(PROGRAMS)
