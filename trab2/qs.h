#ifndef QS_H
#define QS_H


//============//
//  Includes  //
//============//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


//==========//
//  MACROS  //
//==========//

#define MAX_SIZE (1024)			// maximum size of input array
#define DFLT_N_THREADS (1)	// default number of threads
#define check(ptr) { if (!ptr) {printf("Falha de malocação em %s, linha %d.\n", __func__, __LINE__); exit(-1); }



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

void* task(void* arg);

void quicksort(part P);
int partition(int lo, int hi);

part nextPart();
void pushPart(part P);
void delPart(part P);


//===========//
//  Globals  //
//===========//

int* array;	// array to be sorted
part head;	// will point to beginning of chained list
part tail;	// will point to end of chained list

#endif // QS_H
