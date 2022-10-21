#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void wait_and_rtrn_val() {
  int rtrn_value = 0;

  if (!fork()) {
    int entry1 = 0;
    int entry2 = 0;

    scanf("%d\n%d", &entry1, &entry2);
    if (entry1 + entry2 > 10)
      exit(EXIT_SUCCESS);
    exit(EXIT_FAILURE);
  }
  wait(&rtrn_value);
  if (WEXITSTATUS(rtrn_value))
    printf("Le processus enfant s'est terminé avec une erreur\n");
  else
    printf("Le processus enfant s'est terminé avec succès\n");
}

int main(void) {
  wait_and_rtrn_val();
  return EXIT_SUCCESS;
}
