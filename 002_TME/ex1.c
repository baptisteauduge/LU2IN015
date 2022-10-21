#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

void fork_n_times(unsigned int n, bool is_first) {
  if (!n)
    exit(EXIT_SUCCESS);
  
  if (!fork()) {
    printf("PPID : %i\nPID: %i\n\n", getppid(), getpid());
    fork_n_times(n - 1, false);
  } else if (is_first && !fork()) {
    printf("PPID : %i\nPID: %i\n\n", getppid(), getpid());
  }
}

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Usage: ./ex1 <n>\n");
    return EXIT_FAILURE;
  }

  fork_n_times(atoi(argv[1]), true);

  return EXIT_SUCCESS;
}
