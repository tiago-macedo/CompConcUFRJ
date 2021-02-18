#include "qs.h"


//========//
//  Main  //
//========//

int main(int argc, char* argv[]) {
	
	// Getting command line options:
	//-------------------------------
	
	// If no number of threads is given, fall on default:
	int threadnum = (argc < 2) ? DFLT_N_THREADS : atoi(argv[1]);
	
	printf("Número de threads: %d\n", threadnum);
	
	
	// Initializing gloal variables:
	//--------------------------------
	array = malloc(MAX_SIZE * sizeof(int));
	check(array);
	pthread_mutex_init(&headMtx, NULL);
	pthread_mutex_init(&tailMtx, NULL);
	int x;
	int i = 0;
	while (i < 1024 && scanf("%d", &x) > 0)
		array[i++] = x;
	// i = number of elements in array
	
	printf("Array recebido: [ ");
	for (int j=0; j<i; j++)
		printf("%d ", array[j]);
	printf("]\n");
	
	part whole = malloc(sizeof(PART));
	check(whole);
	whole->prev = NULL;
	whole->next = NULL;
	whole->lo = 0;
	whole->hi = i;
	head = whole;
	tail = whole;
	
	
	// Starting up the threads
	//--------------------------
	
	pthread_t* threads = malloc(threadnum * sizeof(pthread_t));
	check(threads);
	
	int* ids = malloc(threadnum * sizeof(int));
	for (int j=0; j<threadnum; j++) {
		ids[j] = j;
		if (pthread_create(threads+j, NULL, task, ids+j)) {
			printf("Erro criando thread %d.\n", j);
			exit(-3);
		}
	}
	

	for (int j=0; j<threadnum; j++)
		if (pthread_join(threads[j], NULL)) {
			printf("Erro recuperando thread %d.\n", j);
			exit(-4);
		}
	

	// Printing result:
	//-------------------
	
	printf("Array final: [ ");
	for (int j=0; j<i; j++)
		printf("%d ", array[j]);
	printf("]\n");
	
	
	// Freeing memory
	//-----------------
	
	free(array);
	free(threads);
	
	
	
	return 0;
}


//=============//
//  Functions  //
//=============//

// Threads
//----------

void* task(void* arg) {
	int id = * (int*) arg;
	while (1) {
		pthread_mutex_lock(&headMtx);
		if (head == NULL) pthread_exit(NULL);
		pthread_mutex_unlock(&headMtx);
		part P = nextPart();
		printf("thread %d pegou (%d, %d).\n", id, P->lo, P->hi);
		quicksort(P);
		printList();
	}
}



// Quicksort and Partition
//--------------------------

void quicksort(part P) {
	int lo = P->lo;
	int hi = P->hi;
	if (hi - lo == 1) return;
	int p = partition(lo, hi);
	pushPart(lo, p);
	pushPart(p, hi);
	delPart(P);
}

int partition(int lo, int hi) {
	int p = rand() % (hi-lo);
	
	while (1) {
		while (array[lo] < array[p]) lo++;
		while (array[hi] > array[p]) hi--;
		if (lo < hi) {
			int temp = array[lo];
			array[lo] = array[hi];
			array[hi] = temp;
		} else
			break;
	}
	return p;
}


// Chained list actions
//-----------------------

part nextPart() {
	pthread_mutex_lock(&headMtx);
	part P = head;
	head = head->next;
	pthread_mutex_unlock(&headMtx);
	return P;
}

void pushPart(int _lo, int _hi) {
	printf("Empurrando (%d, %d).\n", _lo, _hi);
	pthread_mutex_lock(&tailMtx);
	part P = malloc(sizeof(PART));
	check(P);
	P->lo = _lo;
	P->hi = _hi;
	if (tail) {
		tail->next = P;
		P->prev = tail;
		tail = P;
	} else {
		tail = P;
	}
	pthread_mutex_unlock(&tailMtx);
	pthread_mutex_lock(&headMtx);
	if (!head) // if list had been emptied before
		head = P;
	pthread_mutex_unlock(&headMtx);
}

void delPart(part P) {
	if (P->prev)
		P->prev->next = P->next;
	if (P->next)
		P->next->prev = P->prev;
	free(P);
}

void printList() {
	part ptr = head;
	while (ptr) {
		printf("(%d, %d)->", ptr->lo, ptr->hi);
		ptr = ptr->next;
	}
	printf("\n");
}
