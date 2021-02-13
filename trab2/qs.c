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
	head = NULL;
	tail = NULL;
	
	int x;
	int i = 0;
	while (i < MAX_SIZE && scanf("%d", &x) > 0)
		array[i++] = x;
	
	for (int j=0; j<i; j++) printf("%d ", array[j]);
	printf("\n");
	
	PART whole = { NULL, NULL, 0, i };
	head = &whole;
	tail = &whole;
	
	pthread_t* threads = malloc(threadnum * sizeof(pthread_t));


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

void* task(void* arg);



// Quicksort and Partition
//--------------------------

void quicksort(part P);
int partition(int lo, int hi);


// Chained list actions
//-----------------------

part nextPart();
void pushPart(part P);
void delPart(part P);

