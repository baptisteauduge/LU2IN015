#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(void){

	srand(getpid());
	int i,k;
	
	int verrou=open("verrou",O_CREAT|O_RDWR,S_IRUSR|S_IWUSR);
	

	for(k=rand()%10;k>=0;k--){
		for(i=rand()%4;i>=0;i--){
			printf("Atchoum !\n");
			sleep(1);
		}
    lseek(verrou,0,SEEK_SET);
	  lockf(verrou,F_LOCK,0);
		printf("Atchoum rentre aux toilettes\n");
		sleep(1);
		printf("Atchoum sort des toilettes\n");
    lseek(verrou,0,SEEK_SET);
	  lockf(verrou,F_ULOCK,0);
		for(i=rand()%4;i>=0;i--){
			printf("Atchoum !\n");
			sleep(1);
		}
	}

	close(verrou);
	exit(EXIT_SUCCESS);
}
