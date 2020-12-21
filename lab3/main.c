#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

#include "timer.h"	// para cronometrar partes do programa
#include "safety.h"	// para auto-verificar retorno de NULL em malloc e calloc

// STRUCTS



// PROTÓTIPOS
void help(char*);	// exibe mensagem de ajuda


// MAIN
int main(int argc, char* argv[]) {
	double start, end;
	
	// Checagem e carregamento dos parâmetros de linha de comando
	if (argc < 3) {
		help(argv[0]);
		return 1;
	}
	unsigned long long int N = strtoull(argv[1], NULL, 10);	// converte char* para unsigned long long int
	int n_threads = atoi(argv[2]);
	
	// Declaração e inicialização de estruturas de dados
	
	// Carregamento de estruturas com dados do usuário
	
	// Conta sequencial
	long double sumSeq = 0;
	for (long double n=1.; n <= N; n++) {
		sumSeq += 4./(2.*n - 1.);
		sumSeq *= -1;
	}
	if (N % 2 == 1)
		sumSeq *= -1;
	// Conta concorrente
	
	// 1: Declarar threads
	/*
	unsigned long long int* ids = malloc(n_threads * sizeof(unsigned long long int));
	pthread_t* threads = malloc(n_threads * sizeof(pthread_t));
	*/
	// 2: Disparar threads
	// 3: Capturar threads
	
	// Exibindo resultados
	printf(	"math.h:	π = %.15lf\n"
			"sumSeq:	π = %.15Lf\n",
			M_PI,
			sumSeq);
	return 0;
}


// FUNÇÕES

void help(char* name) {
	printf(	"Uso do programa:\n"
			"	%s NTERMOS NTHREADS\n"
			"onde:\n"
			"	NTERMOS 	É o número de termos na soma.\n"
			"	NTHREADS	É a quantidade de threads.\n",
			name);
}
