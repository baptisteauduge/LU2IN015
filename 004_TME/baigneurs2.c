#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#define FILE_CABINE "cabines.lock"
#define FILE_PANIER "paniers.lock"

void init_files(char *nb_cabines, char *nb_paniers) {
  int fd_cab = open(FILE_CABINE, O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR);
  if (fd_cab == -1) {
    fprintf(stderr, "Error when trying to open/create file %s !\n", FILE_CABINE);
    exit(EXIT_FAILURE);
  }
  int fd_pan = open(FILE_PANIER, O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR);
  if (fd_pan == -1) {
    fprintf(stderr, "Error when trying to open/create file %s !\n", FILE_PANIER);
    exit(EXIT_FAILURE);
  }
  write(fd_cab, nb_cabines, sizeof(char));
  close(fd_cab);
  write(fd_pan, nb_paniers, sizeof(char));
  close(fd_pan);
}

void create_baigneurs(int nb_baigneurs) {
  int i;
  char i_str[2] = "\0\0";

  for (i = 0; i < nb_baigneurs; ++i) {
    sprintf(i_str, "%d", i);
    if (fork() == 0) {
      execl("./baigneurs", "./baigneurs", i_str, NULL);
    }
  }
  for (i = 0; i < nb_baigneurs; ++i) wait(NULL);
}

int main(int argc, char **argv) {
  if (argc != 4) {
    fprintf(stderr, "Usage: ./baigneurs2 <nb_baigneurs> <nb_cabines> <nb_paniers>\n");
    return EXIT_FAILURE;
  }
  init_files(argv[2], argv[3]);
  create_baigneurs(atoi(argv[1]));
}