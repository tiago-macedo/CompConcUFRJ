#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NTHREADS  10 

void *PrintHello (void* arg) {
	int idThread = (int) arg; // Typecast de volta para inteiro
	printf("Hello World da thread: %d\n", idThread);
	pthread_exit(NULL);
}

int main() {
	pthread_t tid_sistema[NTHREADS];
	int thread; //variavel auxiliar
//	int tid_local[NTHREADS];

	for(thread=0; thread<NTHREADS; thread++) {
		printf("--Cria a thread %d\n", thread);
		if (pthread_create(	&tid_sistema[thread],
                           NULL,
                           PrintHello,
                           (void*) thread) // Typecast para ponteiro
           ) {
    		printf("--ERRO: pthread_create()\n"); exit(-1);
		}
	}
	printf("--Thread principal terminou\n");
	pthread_exit(NULL);
}
