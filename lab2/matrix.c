#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "timer.h"


// MACROS ==============
#define NUMARGS 2	// Número de argumentos de linha de comando
#define MAX 100.0	// Valor máximo para elementos das matrizes
#define MIN -100.0	// Valor mínimmo para elementos das matrizes

#define HELP help(argv[0])	// Para exibir mensagem de ajuda

//	Os macros a seguir definem as palavras chaves "debug" e "production",
//	responsáveis por marcar quais comandos/funções devem ser executadas
//	apenas em builds de debugação ou produção.
#ifdef DEBUG
	#define debug if (1)
	#define production if (0)
#else
	#define debug if (0)
	#define production if(1)
#endif


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
int dim;	// dimensão das matrizes
int threadnum;	// número de threads
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
	
	// Variáveis de timing
	double start, finish, total;
	
	// Alocando e inicializando matrizes
	GET_TIME(start);
	total = start;
	
	A = malloc(dim * dim * sizeof(float));
	B = malloc(dim * dim * sizeof(float));
	C = calloc(dim*dim, sizeof(float));
	if (!A || !B || !C) {
		printf("Erro alocando matriz(es).\n");
		return 2;
	}
	
	for (int k=0; k<dim*dim; k++) {
		production A[k] = randfloat();
		production B[k] = randfloat();
		debug A[k] = 1;		
		debug B[k] = 1;
	}

	GET_TIME(finish);
	printf("%lf	Inicialização de estruturas de dados\n", finish-start);

	// Exibindo matrizes de entrada
	debug printf("A:\n");
	debug printm(A);
	debug printf("B:\n");
	debug printm(B);
	
	// Multiplicação de matrizes
	GET_TIME(start);
	// Alocação de estruturas
	pthread_t threads[threadnum];
	tharg args[threadnum];
	
	// Inicialização dos argumentos e disparada das threads
	for (int k=0; k<threadnum; k++) {
		args[k] = malloc(sizeof(tharg));
		if (!args[k]) {
			printf("Falha ao alocar memória para argumento de thread %d\n", k);
			return 2;
		}
		args[k]->id = k;
		pthread_create(&(threads[k]), NULL, task, (void*)args[k]);
	}
	
	// Espera pelo término das threads e liberação dos argumentos
	for (int k=0; k<threadnum; k++) {
		pthread_join(threads[k], NULL);
	}
	GET_TIME(finish);
	printf("%lf	Criação de threads, mult. de matrizes\n", finish-start);
	
	// Exibição do resultado
	debug printf("C:\n");
	debug printm(C);
	
	// Liberação de memória
	GET_TIME(start);
	free(A);
	free(B);
	free(C);
	for (int k=0; k<threadnum; k++) free(args[k]);
	GET_TIME(finish);
	printf("%lf	Liberação de memória\n", finish-start);
	total = finish-total;
	printf("--------\n");
	printf("%lf	Tempo total.\n", total);

	return 0;
}


// FUNÇÕES ======================

// Exibe mensagem de ajuda
void help(char* name) {
	printf(	"Uso:\n"
			"	%s <DIMENSION> <THREADS>\n"
			"\n"
			"Onde:\n"
			"	DIMENSION é a largura e altura das matrizes.\n"
			"	THREADS é o número de threads a serem usados\n"
			, name);
}

// Função a ser executada por cada thread
void* task(void* void_arg) {
	tharg arg = (tharg) void_arg;	// recuperando o argumento
	debug printf("Thread %d criada.\n", arg->id);
	for (int e=arg->id; e<dim*dim; e+=threadnum) {
		// Estamos em M[e/dim][e%dim].
		debug printf(	"thread %d calculando C[%d][%d] (%d)\n",
						arg->id, e/dim, e%dim, e );
		for (int k=0; k<dim; k++) {
			C[e] += A[dim*(e/dim) + k] * B[dim*k + e%dim];
		}
	}
	pthread_exit(0);
}

// Imprime a matriz
void printm(float* M) {
	for (int i=0; i<dim; i++) {
		printf("| ");
		for (int j=0; j<dim; j++) {
			printf("%.3f ", M[dim*i + j]);
		}
		printf("|\n");
	}
}

// Retorna um float aleatório
float randfloat() {
	return ( (float)rand()/(float)RAND_MAX ) * (MAX-MIN) + MIN; 
}
