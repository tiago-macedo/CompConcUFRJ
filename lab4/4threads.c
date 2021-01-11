#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//=========
// MACROS
//=========

# define OHNO { \
		printf( "Error!\nFile: %s\nFunction: %s\nLine: %d\n", \
		__FILE__, __func__, __LINE__); \
		perror(""); \
}

//=============
// PROTÓTIPOS
//=============

// As threads
void* tudobem(void*);
void* bomdia(void*);
void* atemais(void*);
void* boatarde(void*);

//===============
// VARS GLOBAIS
//===============

pthread_mutex_t mutex;
pthread_cond_t condicao;
short int saudacoes;


//=======
// MAIN
//=======

int main(void) {
	// Inicializando variáveis globais
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&condicao, NULL);
	saudacoes = 0;
	
	// Declarando threads
	pthread_t	tb,	// tudo bem?
				bd,	// bom dia!
				am,	// até mais!
				bt;	// boa tarde!
	
	// Criando threads
	if ( pthread_create(&tb, NULL, tudobem, NULL) ) OHNO;
	if ( pthread_create(&bd, NULL, bomdia, NULL) ) OHNO;
	if ( pthread_create(&am, NULL, atemais, NULL) ) OHNO;
	if ( pthread_create(&bt, NULL, boatarde, NULL) ) OHNO;
	
	// Esperando as threads completarem
	if ( pthread_join(tb, NULL) ) OHNO;
	if ( pthread_join(bd, NULL) ) OHNO;
	if ( pthread_join(am, NULL) ) OHNO;
	if ( pthread_join(bt, NULL) ) OHNO;
	
	return 0;
}


//============
// FUNÇÕES
//============

void* tudobem(void* arg) {
	printf("tudo bem?\n");
	
	pthread_mutex_lock(&mutex);
	saudacoes++;	// uma das saudações foi dita
	pthread_cond_broadcast(&condicao);	// avisar pra galera
	pthread_mutex_unlock(&mutex);
	
	pthread_exit(NULL);
}


void* bomdia(void* arg) {
	printf("bom dia!\n");
	
	pthread_mutex_lock(&mutex);
	saudacoes++;	// uma das saudações foi dita
	pthread_cond_broadcast(&condicao);	// avisar pra galera
	pthread_mutex_unlock(&mutex);
	
	pthread_exit(NULL);
}


void* atemais(void* arg) {
	pthread_mutex_lock(&mutex);
	while (saudacoes < 2)	// ainda não é hora
		pthread_cond_wait(&condicao, &mutex);
	pthread_mutex_unlock(&mutex);
	// agora sim
	printf("até mais!\n");
	pthread_exit(NULL);
}


void* boatarde(void* arg) {
	pthread_mutex_lock(&mutex);
	while (saudacoes < 2)	// ainda não é hora
		pthread_cond_wait(&condicao, &mutex);
	pthread_mutex_unlock(&mutex);
	// agora sim
	printf("boa tarde!\n");
	pthread_exit(NULL);
}

