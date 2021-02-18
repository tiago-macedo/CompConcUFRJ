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
	head = NULL;
	tail = NULL;
	
	
	// Getting input:
	//-----------------
	int x;
	int i = 0;
	while (i < MAX_SIZE && scanf("%d", &x) > 0)
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
	
	for (int j=0; j<threadnum; j++)
		if (pthread_create(threads+j, NULL, task, NULL)) {
			printf("Erro criando thread %d.\n", j);
			exit(-3);
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
while (1) {
	printList();
	if (head == NULL) pthread_exit(NULL);
		part P = nextPart();
		quicksort(P);
	}
}



// Quicksort and Partition
//--------------------------

void quicksort(part P) {
	int lo = P->lo;
	int hi = P->hi;
	int p = partition(lo, hi);
	pushPart(lo, p);
	pushPart(p, hi);
	delPart(P);
}

int partition(int lo, int hi) {
	if (hi - lo == 1)
		return lo;
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
	part P = head;
	head = head->next;
	return P;
}

void pushPart(int _lo, int _hi) {
	if (tail) {
		part P = malloc(sizeof(PART));
		check(P);
		P->lo = _lo;
		P->hi = _hi;
		tail->next = P;
		P->prev = tail;
		tail = P;
	} else {
		printf("pushPart em lista vazia.\n");
		exit(-2);
	}
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
