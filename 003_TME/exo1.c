#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(void) {
  int tube[2];
  int buffer;
  pid_t pid1;
  pid_t pid2;

  srand(time(NULL));
  if (pipe(tube)) {
    fprintf(stderr, "Erreur lors de la création du tube\n");
    exit(EXIT_FAILURE);
  }
  if ((pid1 = fork()) < 0) {
    fprintf(stderr, "Erreur lors du fork\n");
    exit(EXIT_FAILURE);
  }

  if (pid1 > 0) {
    if ((pid2 = fork()) < 0) {
          fprintf(stderr, "Erreur lors d'un fork\n");
          exit(EXIT_FAILURE);
    }
    if (!pid2) {
      // Fils 2
      close(tube[1]);
      printf("Le fils 2, s'apprète à lire la valeur dans le tube\n");
      read(tube[0], &buffer, sizeof(int));
      printf("Le fils 2, affiche la valeur lue dans le tube : %d\n", buffer);
    } else {
      // Père
      close(tube[0]);
      close(tube[1]);
    }
  }else {
    // Fils 1
    close(tube[0]);
    buffer = rand() % 100;
    printf("Le fils 1, écrit la valeur %d dans le tube\n", buffer);
    write(tube[1], &buffer, sizeof(int));
  }

  return 0;
}
