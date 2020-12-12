#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "timer.h"


// MACROS ==============
#define NUMARGS 2	// Número de argumentos de linha de comando
#define MAX 100.0	// Valor máximo para elementos das matrizes
#define MIN -100.0	// Valor mínimmo para elementos das matrizes

#define HELP help(argv[0])	// Para exibir mensagem de ajuda

#define debug: if (DEBUG)

// STRUCTS =============
typedef struct {
	unsigned int id;
}	THARG_T,	// THARG_T é o tipo do argumento para thread,
	*tharg;		// tharg é um ponteiro para THARG_T.


// PROTÓTIPOS ====================
void help(char*);	// imprime mensagem de ajuda
void* task(void*);	// tarefa de cada thread
void printm(float*);	// imprime uma matriz
float randfloat();	// Gera número aleatório entre MAX e MIN


// VARIÁVEIS GLOBAIS ==============
int dim;
int threadnum;
float* A;	// 1a matriz de entrada
float* B;	// 2a matriz de entrada
float* C;	// matriz resultado


// MAIN ===============
int main(int argc, char* argv[]) {
	// Tratando erros de linha de comando
	if (argc != NUMARGS+1) {
		HELP;
		return 1;
	}
	
	dim = atoi(argv[1]);
	threadnum = atoi(argv[2]);
	if (dim <= 0 || threadnum <= 0) {
		HELP;
		return 1;
	}

	if (threadnum > dim) threadnum = dim;
	
	// Alocando e inicializando matrizes
	A = malloc(dim * dim * sizeof(float));
	B = malloc(dim * dim * sizeof(float));
	C = calloc(dim*dim, sizeof(float));
	if (!A || !B || !C) {
		printf("Erro alocando matriz(es).\n");
		return 2;
	}
	
	for (int k=0; k<dim*dim; k++) {
		A[k] = randfloat();
		B[k] = randfloat();
//		A[k] = 1;		
//		B[k] = 1;
	}
	
	// Exibindo matrizes de entrada
debug:	prinft("A:\n");
debug:	printm(A);
debug:	printf("B:\n");
debug:	printm(B);
	
	// Multiplicação de matrizes
	// Alocação de estruturas
	pthread_t threads[threadnum];
	tharg args[threadnum];
	
	// Inicialização dos argumentos e disparada das threads
	for (int k=0; k<threadnum; k++) {
		args[k] = malloc(sizeof(tharg));
		args[k]->id = k;
		pthread_create(&(threads[k]), NULL, task, (void*)args[k]);
	}
	
	// Espera do retorno das threads e liberação dos argumentos
	for (int k=0; k<threadnum; k++) {
		pthread_join(threads[k], NULL);
		free(args[k]);
	}
	
	// Exibição do resultado
debug:	printf("C:\n");
debug:	printm(C);
	
	// Liberação de memória
	free(A);
	free(B);
	free(C);
	
	return 0;
}


// FUNÇÕES ======================
void help(char* name) {
	printf(	"Uso:\n"
			"	%s <DIMENSION> <THREADS>\n"
			"\n"
			"Onde:\n"
			"	DIMENSION é a largura e altura das matrizes.\n"
			"	THREADS é o número de threads a serem usados\n"
			, name);
}

void* task(void* void_arg) {
	tharg arg = (tharg) void_arg;
	printf("thread %d\n", arg->id);
	for (int e=arg->id; e<dim*dim; e+=threadnum) {
		// Estamos em M[e/dim][e%dim].
		printf(	"[%d] elemento [%d][%d] (%d)\n",
				arg->id, e/dim, e%dim, e );
		for (int k=0; k<dim; k++) {
			C[e] += A[dim*(e/dim) + k] * B[dim*k + e%dim];
		}
	}
	pthread_exit(0);
}


void printm(float* M) {
	for (int i=0; i<dim; i++) {
		printf("| ");
		for (int j=0; j<dim; j++) {
			printf("%.3f ", M[dim*i + j]);
		}
		printf("|\n");
	}
}


float randfloat() {
	return ( (float)rand()/(float)RAND_MAX ) * (MAX-MIN) + MIN; 
}
