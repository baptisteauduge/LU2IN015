CFLAGS = -Wall -Wextra -Werror -std=c17 -g
CC = gcc

PROGRAMS = exo1a exo1b exo2a exo2b baigneurs baigneurs2

.PHONY: all fclean re

all: $(PROGRAMS)

re: fclean all

exo1a: exo1a.c
	$(CC) -o $@ $(CFLAGS) $^

exo1b: exo1b.c
	$(CC) -o $@ $(CFLAGS) $^

exo2a: exo2a.c
	$(CC) -o $@ $(CFLAGS) $^

exo2b: exo2b.c
	$(CC) -o $@ $(CFLAGS) $^

baigneurs: baigneurs.c
	$(CC) -o $@ $(CFLAGS) $^

baigneurs2: baigneurs2.c
	$(CC) -o $@ $(CFLAGS) $^

fclean:
	rm -rf *.o *~ *.dSYM $(PROGRAMS)
