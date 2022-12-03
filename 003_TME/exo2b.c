#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

int main(int argc, char **argv) {
  int read_pipe, buffer;

  srand(time(NULL));

  if (argc != 2) {
    fprintf(stderr, "Usage: ./exo2b <pipe_name>\n");
    exit(EXIT_FAILURE);
  }

  read_pipe = open(argv[1], O_RDONLY);
  if (read_pipe < 0){
    fprintf(stderr, "Erreur lors de l'ouverture du pipe en écriture\n");
    exit(EXIT_FAILURE);
  }

  read(read_pipe, &buffer, sizeof(int));
  printf("La valeur lue dans le tube est %d.\n", buffer);
  close(read_pipe);
  
  return EXIT_SUCCESS;
}
