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
	count = 0;
	pthread_mutex_init(&headMtx, NULL);
	pthread_mutex_init(&tailMtx, NULL);
	pthread_mutex_init(&countMtx, NULL);
	pthread_cond_init(&head_cond, NULL);

	// Getting the input:
	//---------------------
	int x;
	int i = 0;
	while (i < 1024 && scanf("%d", &x) > 0)
		array[i++] = x;
	// i has the number of elements in the array
	
	printf("Array recebido: [ ");
	for (int j=0; j<i; j++)
		printf("%d ", array[j]);
	printf("]\n");
	
	// Initializing list
	//--------------------
	
	part whole = malloc(sizeof(PART));
	check(whole);
	whole->prev = NULL;
	whole->next = NULL;
	whole->lo = 0;
	whole->hi = i;
	head = whole;
	tail = whole;
	count = 1;
	
	
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
	
	pthread_mutex_destroy(&headMtx);
	pthread_mutex_destroy(&tailMtx);
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
		pthread_mutex_lock(&countMtx);
		if (count == 0) {
			pthread_cond_broadcast(&head_cond);
			pthread_mutex_unlock(&countMtx);
			pthread_exit(NULL);
		}
		pthread_mutex_unlock(&countMtx);
		part P = nextPart(id);
		quicksort(P, id);
		delPart(P, id);
		pthread_mutex_lock(&countMtx);
		count--;
		pthread_mutex_unlock(&countMtx);
	}
}



// Quicksort and Partition
//--------------------------

void quicksort(part P, int id) {
	int lo = P->lo;
	int hi = P->hi;
	if (hi - lo > 1) {
		int p = partition(lo, hi, id);
		if (p-lo > 1) {
			pushPart(lo, p, id);
		}
		if (hi-p > 1) {
			pushPart(p+1, hi, id);
		}
	}
}

int partition(int lo, int hi, int id) {
	hi--;	// hi now indexes last element
	int p = rand() % (hi-lo) + lo;
	swap(p, hi);	// putting the pivot in the last place
	int pivot = array[hi];
	int i = lo-1;
	int j = hi;
	
	while (1) {
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

part nextPart(int id) {
	pthread_mutex_lock(&headMtx);
	while (head == NULL && count > 0) {
		pthread_cond_wait(&head_cond, &headMtx);
	}
	if (head == NULL) {
		pthread_mutex_unlock(&headMtx);
		pthread_exit(NULL);
	}
	part P = head;
	head = head->next;
	pthread_mutex_unlock(&headMtx);
	return P;
}

void pushPart(int _lo, int _hi, int id) {
	part P = malloc(sizeof(PART));
	check(P);
	P->lo = _lo;
	P->hi = _hi;
	P->next = NULL;
	P->prev = NULL;
	pthread_mutex_lock(&tailMtx);
	if (tail) {
		tail->next = P;
		P->prev = tail;
		tail = P;
	} else {
		tail = P;
	}
	pthread_mutex_unlock(&tailMtx);
	pthread_mutex_lock(&headMtx);
	if (head == NULL)	// if list had been emptied before
		head = tail;
	pthread_mutex_unlock(&headMtx);
	pthread_cond_broadcast(&head_cond);
	pthread_mutex_lock(&countMtx);
	count++;
	pthread_mutex_unlock(&countMtx);
}

void delPart(part P, int id) {
	if (P == NULL) return;
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
	fflush(stdout);
}
