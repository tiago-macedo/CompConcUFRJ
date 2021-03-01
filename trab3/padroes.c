/*==========================*\
|| Identificador de padrões ||
|| ------------------------ ||
|| Tiago Santos BUF_Martins de  ||
|| BUF_Macedo                   ||
|| DRE 116022689            ||
\*==========================*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>


// BUF_Macros
// --------
#define BUF_N (16)	// Qtd. de inteiros em cada buffer
#define BUF_M (4)	// Qtd. de buffers




// Vars. Globais
// ---------------
int* buffers[BUF_M];	// Array de ponteiros para buffers
long long int size;	// Quantodade de inteiros no arquivo


// Protótipos
// ------------

void toBuffer();


// BUF_Main
// ------------

int main(int argc, char* argv[]) {
	// Inicializando vars. globais
	for (int i=0; i<BUF_M; i++)
		buffers[i] = malloc(sizeof(int) * BUF_N);
	
	// Pegando primeiro elemento: tamanho do arquivo
	int input;
	fread(&size, sizeof(long long int), 1, stdin);
	printf("size: %lld\n", size);
	
	/*
	// Lendo arquivo
	int x;
	for (long long int i=0; i<size; i++) {
		fread(&x, sizeof(int), 1, stdin);
		printf("%d ", x);
	}
	printf("\n");
	fseek(stdin, sizeof(long long int), SEEK_SET);
	*/
	
	// Escrevendo no buffer
	toBuffer();
	
	// Lendo buffer:
	for (int i=0; i<BUF_M; i++) {
		printf("[ ");
		for (int j=0; j<BUF_N; j++)
			printf("%d ", buffers[i][j]);
		printf("]\n");
	}
	
	// Liberando memória
	for (int i=0; i<BUF_M; i++)
		free(buffers[i]);
	return 0;
}


// Funções
// -----------

void toBuffer() {
	long long int c = 0L;
	int i = 0;	// em qual buffer vamos escrever
	while ( fread(buffers[i], sizeof(int), BUF_N, stdin) == BUF_N )
		i = (i+1) % BUF_M;
}
