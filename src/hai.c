#include <signal.h> /* constantes como SIGINT*/
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/reg.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int cont = 0;

void no_me_jodas(int sig) {
    printf("ya va!");
	cont++;	
}

void parricidio_done(int sig){
	printf("he matado a mi padre");
	exit(0);
}

int main(int argc, char *argv[]){
	printf("empiezo");
	pid_t my_child = fork();
	if(my_child == 0){
        signal(23, no_me_jodas);
		while(1){
			if (cont ==4){
				kill(getppid(), 2);
				execvp(argv[1], &argv[2]);
			}
		}
	}else{

		for(int i=0; i < 5; i++){
			printf("sup!");
			kill(my_child, 23);
		}
        signal(2, parricidio_done);

	}
	
	return 0;
}
