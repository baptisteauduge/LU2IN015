#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void sec_wr(int fichier) {
  dup2(fichier, 1);
  close(fichier);
  printf("%d : deuxieme ecriture\n", getpid());
  exit(EXIT_SUCCESS);
}

void first_wr(int fichier) {
  dup2(fichier, 1);
  close(fichier);
  printf("%d : premiere ecriture\n", getpid());
  exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Paramère attendu : nom du fichier\n");
    exit(EXIT_FAILURE);
  }

  int fichier;
  int size_read;
  char file_content;

  fichier = open(argv[1], O_CREAT | O_APPEND | O_RDWR, S_IRUSR | S_IWUSR);
  size_read = pread(fichier, &file_content, sizeof(char), 0);

  if (size_read != 0) {
    sec_wr(fichier);
  } else
    first_wr(fichier);
}
