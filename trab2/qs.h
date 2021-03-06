#ifndef QS_H
#define QS_H


//============//
//  Includes  //
//============//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


//==========//
//  MACROS  //
//==========//

#define MAX_SIZE (1024)		// maximum size of input array
#define DFLT_N_THREADS (1)	// default number of threads

// macro to check if return from allocation is NULL:
#define check(ptr) { if (!ptr) {printf("Falha de alocação em %s, linha %d.\n", __func__, __LINE__); exit(-1); }}



//===========//
//  Structs  //
//===========//

typedef struct _PART {
	struct _PART* next;
	struct _PART* prev;
	int lo;
	int hi;
} PART, *part;


//==============//
//  Prototypes  //
//==============//

void* task(void* arg);	// thread function

void quicksort(part P, int id);	// quicksort, but pushes array part to list
int partition(int lo, int hi, int id);	// selects pivot, all elements less than pivot go before it and vice-versa
void swap(int a, int b); // swaps elements a and b in the array

part nextPart(int id);	// returns next part of the array to be processed
void pushPart(int _lo, int _hi, int id);	// pushes new part into the list
void delPart(part P, int id);	// deletes part from the list
void printList();	// prints the current list


//===========//
//  Globals  //
//===========//

int* array;	// array to be sorted
part head;	// will point to beginning of chained list
part tail;	// will point to end of chained list
int count;	// parts on the list or under processing by quicksort


// Mutexes
//----------

pthread_mutex_t headMtx;
pthread_mutex_t tailMtx;
pthread_mutex_t countMtx;
pthread_cond_t head_cond;

#endif // QS_H
