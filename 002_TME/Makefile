CFLAGS = -Wall -Wextra -Werror -pedantic -std=c17 -g
CC = gcc

PROGRAMS = ex1 ex2 ex3 ex4

.PHONY: all clean re

all: $(PROGRAMS)

re: clean all

ex1: ex1.c
	$(CC) -o $@ $(CFLAGS) $^

ex2: ex2.c
	$(CC) -o $@ $(CFLAGS) $^

ex3: ex3.c
	$(CC) -o $@ $(CFLAGS) $^

ex4: ex4.c
	$(CC) -o $@ $(CFLAGS) $^

clean:
	rm -rf *.o *~ *.dSYM $(PROGRAMS)
