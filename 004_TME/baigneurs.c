#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

#define FILE_CABINE "cabines"
#define FILE_PANIER "paniers"
#define FILE_LOCKER "locker"
#define MAX_TMP_BAIGNAIRE 4

int open_rdwr(char *filename) {
  int fd = open(filename, O_RDWR);
  if (fd < 0) {
    fprintf(stderr, "Error, when trying to open the file %s\n", filename);
  }
  return fd;
}

void my_locker_lock(int fd) {
  lseek(fd, 0, SEEK_SET);
  flock(fd, F_LOCK);
}

void my_locker_ulock(int fd) {
  lseek(fd, 0, SEEK_SET);
  flock(fd, F_ULOCK);
}

void free_ressource(int fd_file) {
  char buffer[2];
  int nb_ressources = 0;

  lseek(fd_file, 0, SEEK_SET);
  read(fd_file, buffer, sizeof(char));
  nb_ressources = atoi(buffer);
  sprintf(buffer, "%d", ++nb_ressources);
  lseek(fd_file, 0, SEEK_SET);
  write(fd_file, buffer, sizeof(char));
}

void take_ressource(int fd_file) {
  char buffer[2] = "\0\0";
  int nb_ressources = 0;

  my_locker_lock(fd_file);
  read(fd_file, buffer, sizeof(char));
  nb_ressources = atoi(buffer);
  while (nb_ressources == 0) {
    my_locker_ulock(fd_file);
    sleep(1);
    my_locker_lock(fd_file);
    read(fd_file, buffer, sizeof(char));
    nb_ressources = atoi(buffer);
  }
  sprintf(buffer, "%d", --nb_ressources);
  lseek(fd_file, 0, SEEK_SET);
  write(fd_file, buffer, sizeof(char));
  my_locker_ulock(fd_file);
}

void go_to_swimming_pool(int id) {
  int fd_cabine = open_rdwr(FILE_CABINE);
  int fd_panier = open_rdwr(FILE_PANIER);
  int fd_locker = open(FILE_LOCKER, O_CREAT|O_TRUNC, S_IREAD|S_IWRITE);
  int tmp_baignade = rand() % (MAX_TMP_BAIGNAIRE + 1);

  printf("[%d] Arrivée à la piscine\n[%d] Cherche une cabine\n", id, id);
  my_locker_lock(fd_locker);
  take_ressource(fd_cabine);
  printf("[%d] Prise d'une cabine\n[%d] Cherche un panier\n", id, id);
  take_ressource(fd_panier);
  printf("[%d] Prise d'un panier\n[%d] Se change ...\n[%d] Libère la cabine\n", id, id, id);
  free_ressource(fd_cabine);
  printf("[%d] Se baigne pendant %d secondes ...\n", id, tmp_baignade);
  sleep(tmp_baignade);
  printf("[%d] A fini de se baigner\n", id);
  printf("[%d] Recherche d'une cabine\n", id);
  take_ressource(fd_cabine);
  my_locker_ulock(fd_cabine);
  printf("[%d] Prise d'une cabine\n[%d] Se change ...\n[%d] Libère la cabine\n", id, id, id);
  free_ressource(fd_cabine);
  printf("[%d] Libère son panier\n", id);
  free_ressource(fd_panier);
  printf("[%d] Départ à la piscine\n", id);
  close(fd_cabine);
  close(fd_panier);
  close(fd_locker);
}

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: ./baigneurs <id>\n");
    return EXIT_FAILURE;
  }
  srand(time(NULL));
  go_to_swimming_pool(atoi(argv[1]));
  return EXIT_SUCCESS;
}