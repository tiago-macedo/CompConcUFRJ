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

	// Getting the input:
	//---------------------
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
		quicksort(P);
	}
}



// Quicksort and Partition
//--------------------------

void quicksort(part P) {
	int lo = P->lo;
	int hi = P->hi;
	if (hi - lo > 1) {
		int p = partition(lo, hi);
		if (p-lo > 1) pushPart(lo, p);
		if (hi-p > 1) pushPart(p+1, hi);
	}
	delPart(P);
}

int partition(int lo, int hi) {
	hi--;	// hi now indexes last element
	int p = rand() % (hi-lo) + lo;
	swap(p, hi);	// putting the pivot in the last place
	int pivot = array[hi];
	int i = lo-1;
	int j = hi;
	
	while (1) {
		sleep(1);
		// find element bigger than pivot:
		do { i++; } while (array[i] < pivot);
		// find element smaller than pivot:
		do { j--; } while (array[j] > pivot);	
		if (i < j)	// if they're in the wrong order...
			swap(i, j);	// ...swap them.
		else	// if not, it's over.
			break;
	}
	swap(i, hi);	// swap pivot and first greater-than-pivot
	return i;	// return pivot's position
}

void swap(int a, int b) {
	int temp = array[a];
	array[a] = array[b];
	array[b] = temp;
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
	pthread_mutex_lock(&tailMtx);
	part P = malloc(sizeof(PART));
	check(P);
	P->lo = _lo;
	P->hi = _hi;
	P->next = NULL;
	P->prev = NULL;
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
	int c = 0;
	while (ptr) {
		printf("(%d, %d)->", ptr->lo, ptr->hi);
		ptr = ptr->next;
		if (++c > 30) exit(-7);
	}
	printf("\n");
}
