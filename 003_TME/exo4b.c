#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pid_t myFork() {
  int pid = fork();

  if (pid < 0) {
    fprintf(stderr, "Erreur lors du fork !\n");
    exit(EXIT_FAILURE);
  }
  return pid;
}

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: ./exo4b <filename>\n");
    exit(EXIT_FAILURE);
  }
  if (myFork() == 0) {
    execl("./exo4a", "./exo4a", argv[1], NULL);
  }
  execl("./exo4a", "./exo4a", argv[1], NULL);
}