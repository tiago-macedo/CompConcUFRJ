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
#ifdef DEBUG
#define LOG(msg, var) printf(msg, var)
#else
#define LOG(msg, var) ;
#endif


// Structs
// ------------

typedef struct _RET_MAISLONGA {
	long long int pos;	// posição inicial da sequência
	int size;			// tamanho da sequência
	int val;			// valor da sequência
} RET_MAISLONGA;



// Protótipos
// ------------

void toBuffer();	// Função que escreve números nos bufferes

void* maislonga(void*);	// Thread que cata seq. de números maislonga
void* trincas(void*);	// Thread que cata seq. de três números iguais
void* straights(void*);	// Thread que cata "0 1 2 3 4 5"




// Vars. Globais
// ---------------

int* buffers[BUF_M];	// Array de ponteiros para buffers
long long int size;		// Quantodade de inteiros no arquivo
char done;				// 0 enquanto leitura do arquivo ainda estiver ocorrendo
// Semáforos
sem_t doneMtx;	// Mutex para guardar variável done
// Threads
pthread_t T1;
pthread_t T2;
pthread_t T3;




// Main
// ------------

int main(int argc, char* argv[]) {
	// Inicializando vars. globais
	done = 0;
	sem_init(&doneMtx, 0, 1);
	for (int i=0; i<BUF_M; i++)
		buffers[i] = malloc(sizeof(int) * BUF_N);
	
	// Pegando primeiro elemento: tamanho do arquivo
	fread(&size, sizeof(long long int), 1, stdin);
	printf("size: %lld\n", size);
	
#ifdef DEBUG
	// Lendo arquivo
	printf("\n");
	int x;
	for (long long int i=0; i<size; i++) {
		fread(&x, sizeof(int), 1, stdin);
		printf("%d ", x);
	}
	printf("\n\n");
	fseek(stdin, sizeof(long long int), SEEK_SET);
#endif // DEBUG
	
	// Escrevendo no buffer
	toBuffer();
	
	// Iniciando threads
	pthread_create(&T1, NULL, maislonga, NULL);
	pthread_create(&T2, NULL, trincas, NULL);
	pthread_create(&T3, NULL, straights, NULL);
	
	// Recebendo threads de volta
	RET_MAISLONGA* seq_mais_longa;	// resultado da T1
	int* num_trincas;				// resultado da T2
	int* num_straights;				// resultado da T3
	void* temp;
	pthread_join(T1, &temp);
	seq_mais_longa = (RET_MAISLONGA*) temp;
	pthread_join(T2, &temp);
	num_trincas = (int*) temp;
	pthread_join(T3, &temp);
	num_straights = (int*) temp;
	
	// Imprimindo resultados:
	printf(	"Maior sequência de valores idênticos: %lld %d %d\n",
			seq_mais_longa->pos,
			seq_mais_longa->size,
			seq_mais_longa->val);
	printf("Quantidade de ocorrências de sequências contınuas de tamanho 3 do mesmo valor: %d\n", *num_trincas);
	printf("Quantidade de ocorrências da sequência<012345>: %d\n", *num_straights);
	for (int i=0; i<BUF_M; i++) {
		printf("[ ");
		for (int j=0; j<BUF_N; j++)
			printf("%d ", buffers[i][j]);
		printf("]\n");
	}
	
	// Liberando memória
	sem_close(&doneMtx);
	for (int i=0; i<BUF_M; i++)
		free(buffers[i]);
	free(seq_mais_longa);
	free(num_trincas);
	free(num_straights);
	return 0;
}



// Funções
// -----------

void toBuffer() {
	int i = 0;	// em qual buffer vamos escrever
	while ( fread(buffers[i], sizeof(int), BUF_N, stdin) == BUF_N )
		i = (i+1) % BUF_M;
	sem_wait(&doneMtx);
	done = 1;	// Avisa pra galera que não tem mais arquivo pra ler
	sem_post(&doneMtx);
}

// Threads

void* maislonga(void* args) {
	long long int pos = 0L;			// posição que está sendo lida
	int new = 0;	// número que acaba de ser lido
	int old = -1;	// número anterior
	char its_a_sequence = 0;		// 1 caso estejamos lendo uma sequência, 0 caso contrário
	
	long long int longest_head = 0;	// início da sequencia mais longa
	int longest_size = 0;			// tamanho da sequência mais longa
	int longest_val = -1;			// valor da sequência mais longa
	
	long long int cur_head;		// início da sequencia atual
	int cur_size;				// tamanho da sequência atual
	int cur_val;				// valor da sequência atual
	
	// Loop sobre os bufferes
	for (int i=0; 1; i = (i+1) % BUF_M) {
		// Loop sobre os elementos de um dos bufferes
		for (int j=0; j<BUF_N; j++) {
			old = new;
			new = buffers[i][j];
			if (new == old && !its_a_sequence) {	// começou uma sequência
				its_a_sequence = 1;
				cur_head = pos - 1;	// primeiro da seq. é o anterior
				cur_size = 2;
				cur_val = new;
			}
			else if (new == old && its_a_sequence)	// já estávamos numa sequência
				cur_size++;
			else if (new != old && its_a_sequence) {	// sequência acabou
				if (cur_size > longest_size) {	// seq. atual é a maior encontrada
					longest_size = cur_size;
					longest_head = cur_head;
					longest_val = cur_val;
				}
				its_a_sequence = 0;
			}
			pos++;
		}
		if (i == BUF_M-1) {		// acabamos de ler o último buffer
			sem_wait(&doneMtx);
			if (done) break;	// Meu trabalho acabou
			sem_post(&doneMtx);
		}
	}
	sem_post(&doneMtx);	// acabamos de acessar var. global done
	
	RET_MAISLONGA* ret = malloc(sizeof(RET_MAISLONGA));
	ret->pos = longest_head;
	ret->size = longest_size;
	ret->val = longest_val;
	
	pthread_exit((void*) ret);
}

void* trincas(void* args) {
	int count = 0;		// qtd. de trincas
	int new; int old;	// número que acaba de ser lido e anterior
	
	int seq_size = 0;	// tamanho da sequência atual
	
	for (int i=0; 1; i = (i+1) % BUF_M) {
		// Loop sobre os elementos de um dos bufferes
		for (int j=0; j<BUF_N; j++) {
			old = new;
			new = buffers[i][j];
			if (new == old) {			// estamos em uma sequência
				if (seq_size == 0) {		// seq. nova
					seq_size = 2;
				}
				else if (seq_size == 2) {	// seq. é um trio
					seq_size = 3;
					count++;
				}
				else if (seq_size == 3) {	// acabamos de sair de uma seq.
					seq_size = 0;
				}
			} else				// new != old
				seq_size = 0;
		}
		if (i == BUF_M-1) {		// acabamos de ler o último buffer
			sem_wait(&doneMtx);
			if (done) break;	// Meu trabalho acabou
			sem_post(&doneMtx);
		}
	}
	sem_post(&doneMtx);	// acabamos de acessar var. global done
	
	int* ret = malloc(sizeof(int));
	*ret = count;
	pthread_exit((void*) ret);
}

void* straights(void* args) {
	int count = 0;		// qtd. de sequências 012345
	int next = 0;		// número que esperamos agora
	
	for (int i=0; 1; i = (i+1) % BUF_M) {
		// Loop sobre os elementos de um dos bufferes
		for (int j=0; j<BUF_N; j++) {
			if (buffers[i][j] == next) {	// podemos começar uma seq.
				if (next < 5)
					next++;
				else {		// next == 5, formamos a sequência!
					count++;
					next = 0;
				}
			}
			else		// não lemos o número esperado
				next = 0;
		}
		if (i == BUF_M-1) {		// acabamos de ler o último buffer
			sem_wait(&doneMtx);
			if (done) break;	// Meu trabalho acabou
			sem_post(&doneMtx);
		}
	}
	sem_post(&doneMtx);	// acabamos de acessar var. global done
	
	int* ret = malloc(sizeof(int));
	*ret = count;
	pthread_exit((void*) ret);
}
