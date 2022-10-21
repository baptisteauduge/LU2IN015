#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

const int MAX_FILS = 3;

void multi_grep_constraint(int nbr_files, char **files, char *search) {
  for (int i = 0; i < nbr_files;) {
    if (!fork()) {
      // Print used to check if constraint is respected
      printf("Searching in %s :\n", files[i]);
      execl("/usr/bin/grep", "grep", search, files[i], NULL);
    } else if (++i >= MAX_FILS) {
      wait(NULL);
    }
  }
}

int main(int argc, char **argv) {
  if (argc < 3) {
    printf("Usage: ./ex4 <researched> <file1> <file2> ...\n");
    return 1;
  }
  multi_grep_constraint(argc - 2, argv + 2, argv[1]);
  return 0;
}
