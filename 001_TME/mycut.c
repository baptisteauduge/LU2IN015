#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_SIZE 255

void readFile(FILE *myFile, int nbrOfTheWord) {
  char *line = (char *)malloc(sizeof(char) * LINE_SIZE);
  char *lineCopy = NULL;
  char *word = NULL;

  while (fgets(line, LINE_SIZE, myFile)) {
    lineCopy = strdup(line);
    for (int i = 1; (word = strsep(&lineCopy, " ")); ++i) {
      if (i == nbrOfTheWord)
        printf("%s\n", word);
    }
  }
  free(line);
}

int main(int argc, char *argv[]) {

  if (argc < 3) {
    fprintf(stderr, "Usage: mycut <nameOfTheFile> <numberOfTheWordToGet>\n");
    return EXIT_FAILURE;
  }

  FILE *myFile = fopen(argv[1], "r");
  if (!myFile) {
    fprintf(stderr, "Error: The file \"%s\" doesn't exist!\n", argv[1]);
    return EXIT_FAILURE;
  }

  readFile(myFile, atoi(argv[2]));
  return EXIT_SUCCESS;
}
