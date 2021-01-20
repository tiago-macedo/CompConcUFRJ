#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>


// MACROS
#define READERS	3
#define WRITERS	3
#define MEMORY	5


// PROTÓTIPOS
void* read(void*);	// thread de leitura
void* write(void*);	// thread de escrita


// VARIÁVEIS GLOBAIS

pthread_t threads[READERS + WRITERS];	// array de threads
int tids[READERS + WRITERS];			// array de ids de threads
int mem[MEMORY];						// array onde ocorrerá leitura/escrita
pthread_mutex_t mtx;					// direito de leitura/escrita
#define LOCK(mtx) pthread_mutex_lock(&(mtx))
#define UNLOCK(mtx) pthread_mutex_unlock(&(mtx))

// MAIN

int main(int argc, char* argv[]) {
	// Inicializando mutex
	pthread_mutex_init(&mtx, NULL);
	
	// 2: Disparar threads
	int error;
	for (int id = 0; id < READERS+WRITERS; id++) {
		tids[id] = id;
		error = pthread_create(	&(threads[id]),				// endereço da thread
								NULL,						// atributos
								id<READERS ? read : write,	// função
								(void*) &(tids[id]));		// argumento
		if (error) {
			printf("Falha criando a thread %d.\n", id);
			return error;
		}
	}
	
	// 3: Capturar threads
	for (int id=0; id < READERS+WRITERS; id++) {
		error = pthread_join(threads[id], NULL);
		if (error) {
			printf("Falha resgatando a thread %d.\n", id);
			return error;
		}
	}
	
	return 0;
}


// FUNÇÕES

void* read(void* arg) {
	int id = *( (int*) arg );
	printf("T%d (leitura) criada.\n", id);
	int sum = 0;
	LOCK(mtx);
	printf("T%d: [ ", id);
	for (int i=0; i<MEMORY; i++) {
		printf("%d | ", mem[i]);
		sum += mem[i];
	}
	printf("]\n");
	UNLOCK(mtx);
	printf("T%d: média é %f\n", id, ((float)sum/MEMORY));
	pthread_exit(NULL);
}

void* write(void* arg) {
	int id = *( (int*) arg );
	printf("T%d (escrita) criada.\n", id);

	LOCK(mtx);
	mem[0] = id;
	printf("T%d: [ %d | ", id, mem[0]);
	for (int i=1; i<MEMORY-1; i++) {
		mem[i] = id*2;
		printf("%d | ", mem[i]);
	}
	mem[MEMORY-1] = id;
	printf("%d ] <-- escrevi\n", mem[MEMORY-1]);
	UNLOCK(mtx);
	
	pthread_exit(NULL);
}
