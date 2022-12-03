#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]){
	if(argc!=2){
		printf("Paramère attendu : nom du fichier\n");
		exit(EXIT_FAILURE);
	}
	struct stat sb;

  int locker_file=open("tmp", O_CREAT|O_TRUNC|O_WRONLY,S_IRUSR|S_IWUSR);
  lseek(locker_file, 0, SEEK_SET);
  lockf(locker_file, F_LOCK, 0);

	if(stat(argv[1],&sb)==-1){ // Le fichier n'existe pas, on écrit dedans
		int fichier=open(argv[1],O_CREAT|O_TRUNC|O_WRONLY,S_IRUSR|S_IWUSR);
		dup2(fichier,1);
		close(fichier);
		printf("%d : premiere ecriture\n",getpid());
    lseek(locker_file, 0, SEEK_SET);
    lockf(locker_file, F_ULOCK, 0);
    close(locker_file);
		exit(EXIT_SUCCESS);		
	}else{ // Le fichier existe, on écrit à la suite
		int fichier=open(argv[1],O_APPEND|O_WRONLY);
		dup2(fichier,1);
		close(fichier);
		printf("%d : deuxieme ecriture\n",getpid());
    lseek(locker_file, 0, SEEK_SET);
    lockf(locker_file, F_ULOCK, 0);
    close(locker_file);
		exit(EXIT_SUCCESS);
	}
	exit(EXIT_SUCCESS);
}
