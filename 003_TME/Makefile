CFLAGS = -Wall -Wextra -Werror -std=c17 -g
CC = gcc

PROGRAMS = exo1	exo2a exo2b exo3 exo4a exo4b

.PHONY: all fclean re

all: $(PROGRAMS)

re: fclean all

exo1: exo1.c
	$(CC) -o $@ $(CFLAGS) $^

exo2a: exo2a.c
	$(CC) -o $@ $(CFLAGS) $^

exo2b: exo2b.c
	$(CC) -o $@ $(CFLAGS) $^

exo3: exo3.c
	$(CC) -o $@ $(CFLAGS) $^

exo4a: exo4a.c
	$(CC) -o $@ $(CFLAGS) $^

exo4b: exo4b.c
	$(CC) -o $@ $(CFLAGS) $^

fclean:
	rm -rf *.o *~ *.dSYM $(PROGRAMS)
