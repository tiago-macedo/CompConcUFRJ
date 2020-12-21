#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "timer.h"	// para cronometrar partes do programa
#include "safety.h"	// para auto-verificar retorno de NULL em malloc e calloc

// STRUCTS



// PROTÓTIPOS
void help(char*);	// exibe mensagem de ajuda


// MAIN
int main(int argc, char* argv[]) {
	// Checagem dos parâmetros de linha de comando
	if (argc < 3) {
		help(argv[0]);
		return 1;
	}
	unsigned long long int N = strtoull(argv[1], NULL, 10);	// converte char* para unsigned long long int
	int n_threads = atoi(argv[2]);

	// Declaração e inicialização de estruturas de dados
	
	// Carregamento de estruturas com dados do usuário
	
	// Conta sequencial
	
	// Conta concorrente
	
	// 1: Declarar threads
	// 2: Disparar threads
	// 3: Capturar threads
	
	// Exibindo resultados
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
