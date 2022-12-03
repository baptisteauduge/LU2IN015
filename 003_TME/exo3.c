#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void myPipe(int *fd) {
  if (pipe(fd) < 0) {
    fprintf(stderr, "Erreur: impossible de créer le pipe !\n");
    exit(EXIT_FAILURE);
  }
}

pid_t myFork() {
  int pid = fork();

  if (pid < 0) {
    fprintf(stderr, "Erreur lors du fork !\n");
    exit(EXIT_FAILURE);
  }
  return pid;
}

int open_file(char *filename) {
  int file = open(filename, O_RDONLY);
  if (file < 0) {
    fprintf(stderr, "Erreur: impossible d'ouvrir le fichier %s !\n", filename);
    exit(EXIT_FAILURE);
  }
  return file;
}

void read_n_char_and_write_pipe(int file, int fd_pipe_wr, int n) {
  char buffer;
  pid_t pid = getpid();

  for (int i = 0; i < n; ++i) {
    read(file, &buffer, sizeof(char));
    printf("%d a lu %c\n", pid, buffer);
    write(fd_pipe_wr, &buffer, sizeof(char));
  }
}

void run_writer_child(char *name, int file, int *fd_pipe) {
  int pid = getpid();
  printf("Le %s fils %d commence\n", name, pid);
  close(fd_pipe[0]);
  read_n_char_and_write_pipe(file, fd_pipe[1], 3);
  printf("Le fils %d se termine\n", pid);
  close(fd_pipe[1]);
  close(file);
  exit(EXIT_SUCCESS);
}

void run_reader_child(char *name, int *fd_pipe, int file) {
  int pid = getpid();
  char buffer;

  printf("Le %s fils %d commence\n", name, pid);
  for (int i = 0; i < 4; ++i) {
    read(fd_pipe[0], &buffer, sizeof(char));
    printf("%d a lu %c\n", pid, buffer);
  }
  printf("Le fils %d se termine\n", pid);
  close(fd_pipe[0]);
  close(file);
  exit(EXIT_SUCCESS);
}

void run_all_child(int file, int *fd_pipe) {
  if (myFork() == 0) {
    run_writer_child("premier", file, fd_pipe);
  }

  wait(NULL);
  read_n_char_and_write_pipe(file, fd_pipe[1], 1);

  if (myFork() == 0) {
    run_writer_child("second", file, fd_pipe);
  }

  close(fd_pipe[1]);
  wait(NULL);

  if (myFork() == 0) {
    run_reader_child("troisième", fd_pipe, file);
  }

  close(fd_pipe[0]);
  close(file);
  wait(NULL);
}

int main(int argc, char **argv) {
  pid_t pid = getpid();
  int file = 0, fd_pipe[2];

  if (argc != 2) {
    fprintf(stderr, "Usage: ./exo3 <filename>\n");
    exit(EXIT_FAILURE);
  }

  printf("Le père %d commence\n", pid);

  file = open_file(argv[1]);
  myPipe(fd_pipe);

  run_all_child(file, fd_pipe);

  printf("Le père %d se termine\n", pid);
  return 0;
}