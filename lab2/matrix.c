#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "timer.h"
#include <errno.h>

#define NUMARGS 2	// Número de argumentos de linha de comando
#define HELP help(argv[0])	// Para exibit mensagem de ajuda

typedef struct {
	unsigned int id;
}	THARG_T,	// THARG_T é o tipo do argumento para thread,
	*tharg;		// tharg é um ponteiro para THARG_T.

void help(char*);	// imprime mensagem de ajuda
void* task(void*);	// tarefa de cada thread
void printm(float*);	// imprime uma matriz

int dim;
int threadnum;
float* A;	// 1a matriz de entrada
float* B;	// 2a matriz de entrada
float* C;	//  matriz resultado

int main(int argc, char* argv[]) {
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
	
	A = malloc(dim * dim * sizeof(float));
	B = malloc(dim * dim * sizeof(float));
	C = calloc(dim*dim, sizeof(float));
	
	printm(C);
	
	free(A);
	free(B);
	free(C);
	
	return 0;
}

void help(char* name) {
	printf(	"Uso:\n"
			"	%s <DIMENSION> <THREADS>\n"
			"\n"
			"Onde:\n"
			"\tDIMENSION é a largura e altura das matrizes.\n"
			"\tTHREADS é o número de threads a serem usados\n"
			, name);
}

void* task(void* _args) {
	tharg args = (tharg) _args;
	for (int e=args->id; e<dim; e+=threadnum) {
		// Estamos em M[e/dim][e%dim].
		for (int k=0; k<dim; k++) {
			C[e] += A[dim*(e/dim) + k] * B[dim*k + e%dim];
		}
	}
	pthread_exit(0);
}

/*
 *	Y[i][j]	= y[dim*i + j]
 *	y[k]	= Y[k/dim][k%dim]
 * */


void printm(float* M) {
	for (int i=0; i<dim; i++) {
		printf("| ");
		for (int j=0; j<dim; j++) {
			printf("%.3f ", M[dim*i + j]);
		}
		printf("|\n");
	}
}
