#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

#include "timer.h"	// para cronometrar partes do programa


// MACROS
#define sign(n) (2 * (int)(n%2) - 1) // -1 se n par, 1 se n ímpar


// PROTÓTIPOS
void help(char*);	// exibe mensagem de ajuda
void* task(void*);	// fluxo concorrente do programa


// VARIÁVEIS GLOBAIS
unsigned long long int N;	// quantidade de termos da soma
int n_threads;				// quantidade de threads

// MAIN
int main(int argc, char* argv[]) {
	double start, end;
	
	// Checagem e carregamento dos parâmetros de linha de comando
	if (argc < 3) {
		help(argv[0]);
		return 1;
	}
	N = strtoull(argv[1], NULL, 10);	// converte char* para unsigned long long int
	n_threads = atoi(argv[2]);
	
	// Conta sequencial
	GET_TIME(start);
	long double sumSeq = 0.L;
	for (long long int n=1; n<=N ; n++) {
		sumSeq += sign(n) * 4.L/(2*n - 1);
	}
	
	GET_TIME(end);
	printf("%.15lfs	<- tempo da parte sequencial\n", end-start);
	
	// Conta concorrente
	GET_TIME(start);

	// 1: Declarar threads
	int* ids = malloc(n_threads * sizeof(int));
	pthread_t* threads = malloc(n_threads * sizeof(pthread_t));
	if (!ids || !threads) {
		printf("Falha em alocar memória para threads ou seus ids.\n");
		return 2;
	}
	
	// 2: Disparar threads
	for (int id=0; id<n_threads; id++) {
		ids[id] = id;
		if ( pthread_create(&(threads[id]), NULL, task, (void*) &(ids[id])) != 0 ) {
			printf("Falha criando a thread %d.\n", id);
			return 3;
		}
	}
	
	// 3: Capturar threads
	long double sumConc = 0;
	for (int id=0; id<n_threads; id++) {
		long double *local_sum;
		if ( pthread_join(threads[id], (void**) &local_sum) != 0 ) {
			printf("Falha resgatando a thread %d.\n", id);
			return 4;
		}
		sumConc += *local_sum;
		free(local_sum);
	}
	GET_TIME(end);
	printf("%.15lfs	<- tempo da parte concorrente\n", end-start);
	
	
	// Exibindo resultados
	printf(	"math.h:    π = %.20lf\n"
			"sumSeq:    π = %.20Lf : diff = %Le\n"
			"sumConc:   π = %.20Lf : diff = %Le\n",
			M_PI,
			sumSeq, M_PI - sumSeq,
			sumConc, M_PI - sumConc);
	
	// Liberando memória
	free(ids);
	free(threads);
	return 0;
}


// FUNÇÕES

void help(char* name) {
	printf(	"Uso do programa:\n"
			"    %s NTERMOS NTHREADS\n"
			"onde:\n"
			"    NTERMOS    É o número de termos na soma.\n"
			"    NTHREADS   É a quantidade de threads.\n",
			name);
}

void* task(void* arg) {
	int id = *( (int*) arg );
	long double* sum = (long double *) malloc(sizeof(long double));
	if (!sum) {
		printf("Thread %d não conseguiu alocar memória para variável sum.\n", id);
		exit(5);
	}
	*sum = 0L;
	for (long long int n=id+1; n<=N; n+=n_threads) {
		*sum += sign(n) * 4.L / (2*n - 1) ;
	}
	pthread_exit(sum);
}
