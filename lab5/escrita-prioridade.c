#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>


// MACROS
#define READERS	4
#define WRITERS	4
#define MEMORY	10


// PROTÓTIPOS
void* read(void*);	// thread de leitura
void startRead();	// entra na leitura
void endRead();		// sai da leitura
void* write(void*);	// thread de escrita
void startWrite();	// entra na escrita
void endWrite();	// sai da escrita


// VARIÁVEIS GLOBAIS

pthread_t threads[READERS + WRITERS];	// array de threads
int tids[READERS + WRITERS];			// array de ids de threads
int mem[MEMORY];						// array onde ocorrerá leitura/escrita
pthread_mutex_t mtx;					// direito de leitura/escrita
#define LOCK(mtx) pthread_mutex_lock(&(mtx))
#define UNLOCK(mtx) pthread_mutex_unlock(&(mtx))
int writting;	// quantos estão escrevendo
int wanna_write;	// quantos querem escrever
int reading;	// quantos estão lendo
pthread_cond_t cond_readers;
pthread_cond_t cond_writters;
#define WAIT(c, m) pthread_cond_wait(&(c), &(m))
#define BROAD(c) pthread_cond_broadcast(&(c))
#define SIGNAL(c) pthread_cond_signal(&(c))


// MAIN

int main(int argc, char* argv[]) {
	// Inicializando
	pthread_mutex_init(&mtx, NULL);
	pthread_cond_init(&cond_readers, NULL);
	pthread_cond_init(&cond_writters, NULL);
	reading = 0;
	writting = 0;
	wanna_write = 0;
	
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
	int sum = 0;
	
	startRead();
	printf("T%d: [ ", id);
	for (int i=0; i<MEMORY; i++) {
		printf("%d | ", mem[i]);
		sum += mem[i];
	}
	printf("\n");
	printf("T%d: média é %f\n", id, ((float)sum/MEMORY));
	endRead();
	
	pthread_exit(NULL);
}

void startRead() {
	LOCK(mtx);
	while (writting > 0 || wanna_write > 0)
		WAIT(cond_readers, mtx);
	reading++;
	UNLOCK(mtx);
}

void endRead() {
	LOCK(mtx);
	reading--;
	if (reading == 0) SIGNAL(cond_writters);
	UNLOCK(mtx);
}

void* write(void* arg) {
	int id = *( (int*) arg );

	startWrite();
	mem[0] = id;
	printf("T%d: [ %d | ", id, mem[0]);
	for (int i=1; i<MEMORY-1; i++) {
		mem[i] = id*2;
		printf("%d | ", mem[i]);
	}
	mem[MEMORY-1] = id;
	printf("%d | <-- escrevi\n", mem[MEMORY-1]);
	endWrite();
	
	pthread_exit(NULL);
}

void startWrite() {
	LOCK(mtx);
	while (reading > 0 || writting > 0) {
		wanna_write++;
		WAIT(cond_writters, mtx);
	}
	wanna_write--;
	writting++;
	UNLOCK(mtx);
}

void endWrite() {
	LOCK(mtx);
	writting--;
	SIGNAL(cond_writters);
	BROAD(cond_readers);
	UNLOCK(mtx);
}
