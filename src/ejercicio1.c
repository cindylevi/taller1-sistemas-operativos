#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

int n;
int numero_maldito;
int rondas;
pid_t* hijos;

int generate_random_number(){
	return (rand() % n);
}

void soy_hijo(int sig){
    printf("lllegue \n");
    srand(time(NULL));

    for(int k=0; k <rondas; k++){

        int num_elegido = generate_random_number();
        printf("%d \n", num_elegido);
        if(num_elegido == numero_maldito){
            printf("estoy malditooooo voy a morir chau \n");
            exit(0);
        }else{
            printf("i will surviveee \n");
        }
    }
    while(1){}

}

void mi_hijo_murio(int sig){
    pid_t pid_died = wait(NULL);

    for(int i=0; i <n; i++){
        if(hijos[i] == pid_died){
            hijos[i] = -1;
        }
    }
}




int main(int argc, char const *argv[]){
    pid_t hijo_actual;

    //Funcion para cargar nueva semilla para el numero aleatorio
    
    n = atoi(argv[1]);
    hijos = malloc(n * sizeof(pid_t));

	rondas = atoi(argv[2]);
	numero_maldito = atoi(argv[3]);

    for(int i=0; i <n; i++){
        hijo_actual = fork();
        if(hijo_actual == 0) break;
        hijos[i] = hijo_actual;

    }

    if(hijo_actual == 0){
        signal(15, soy_hijo);
        while(1){
            int jjjj = generate_random_number();
        }

    }

    if(hijo_actual != 0){
        signal(17, mi_hijo_murio);
    }

    if(hijo_actual != 0){
        for(int i=0; i <n; i++){
            printf("estoy x llamar a %d \n", hijos[i]);
            kill(hijos[i], 15);
            sleep(1);
        }
        for(int i=0; i <n; i++){
            if(hijos[i] != -1){
                printf("my son %d is alive! \n", hijos[i]);
                kill(hijos[i], 15);
            }
        }
    }
    
    exit(0);
}
