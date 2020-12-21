#ifndef UTILS_H
#define UTILS_H


//================================
// INCLUDES
//================================

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


//================================
// MACROS
//================================

#define WHERE __FILE__, __func__, __LINE__
#define OHNO ohno(WHERE)
#define PANIC panic(WHERE)


//================================
// EXTERNAL VARIABLES
//================================

extern int errno;


//================================
// PROTOTYPES
//================================
void* smalloc(size_t, char*, const char*, int);		// Wrapper for malloc with error handling
void* scalloc(size_t, size_t, char*, const char*, int);// Wrapper for calloc with error handling
void sfree(void*);									// Nulls the pointer after free
void ohno(char*, const char*, int);					// Shows an error message
void panic(char*, const char*, int);				// Shows an error message and exits

#endif	// UTILS_H
