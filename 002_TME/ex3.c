#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void multi_grep(int nbr_files, char **files, char *search) {
for (int i = 0; i < nbr_files; ++i) {
    if (!fork()) {
      execl("/usr/bin/grep", "grep", search, files[i], NULL);
    }
  }
}

int main(int argc, char **argv) {
  if (argc < 3) {
    printf("Usage: ./ex3 <researched> <file1> <file2> ...\n");
    return 1;
  }
  multi_grep(argc - 2, argv + 2, argv[1]);
  return 0;
}
