#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>

#define N 60

//==========//
// Structs  //
//==========//
typedef struct {
	int from;
	int to;
} range_t;


//============//
// Prototypes //
//============//

void* increment(void* _interval);


//=============//
// Global vars //
//=============//

int vector[N];


//======//
// Main //
//======//

int main(void) {
	// Inicializando vetor com 0s:
	for (int i=0; i<N; i++) vector[i] = 0;
	
	// Imprimindo os valores iniciais do vetor:
	printf("vector = [ ");
	for (int i=0; i<N; i++) printf("%d ", vector[i]);
	printf("]\n");
	
	// Agora, vamos criar os intervalos e as threads:
	range_t r1 = {0, N/2};
	range_t r2 = {N/2, N};
	pthread_t t1;
	pthread_t t2;

	// Iniciando as threads:
	if ( pthread_create(&t1, NULL, increment, (void*)&r1) ) {
		perror("Erro criando thread 1");
		exit(errno);
	}
	if ( pthread_create(&t2, NULL, increment, (void*)&r2) ) {
		perror("Erro criando thread 2");
		exit(errno);
	}

	// Esperando finalização das threads:
	if ( pthread_join(t1, NULL) ) {
		perror("Erro recebendo thread 1 de volta");
		exit(errno);
	} else printf("Thread 1 retornado.\n");
	if ( pthread_join(t2, NULL) ) {
		perror("Erro recebendo thread 2 de volta");
		exit(errno);
	} else printf("Thread 2 retornado.\n");
	
	// Imprimindo os valores finais do vetor:
	printf("vector = [ ");
	for (int i=0; i<N; i++) printf("%d ", vector[i]);
	printf("]\n");

	pthread_exit(0);

}


//===========//
// Functions //
//===========//

void* increment(void* _interval) {
	range_t* interval = (range_t*) _interval;	// Transformando o tipo do argumento
	int from = interval->from;					// Incrementar daqui...
	int to = interval->to;						// ...até aqui (não incluso o último).
	
	printf("Incrementando de %d até %d.\n", from, to-1);
	
	for (int i=from; i<to; i++) {
		vector[i]++;
	}

	pthread_exit(NULL);
}
