#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char **argv) {
  int write_pipe, rand_n;
  srand(time(NULL));
  printf("%d\n", getpid());
  
  if (argc != 2) {
    fprintf(stderr, "Usage: ./exo2a <pipe_name>\n");
    exit(EXIT_FAILURE);
  }

  if (mkfifo(argv[1], S_IWUSR | S_IRUSR) != 0) {
    fprintf(stderr, "Erreur lors de la création du tube\n");
    exit(EXIT_FAILURE);
  }

  write_pipe = open(argv[1], O_TRUNC | O_WRONLY);
  if (write_pipe < 0){
    fprintf(stderr, "Erreur lors de l'ouverture du pipe en écriture\n");
    exit(EXIT_FAILURE);
  }

  rand_n = rand() % 100;
  write(write_pipe, &rand_n, sizeof(int));
  printf("La valeur écrite dans le tube est %d.\n", rand_n);
  close(write_pipe);

  return EXIT_SUCCESS;
}
