#ifndef UTILS_H
#define UTILS_H

//===========
// INCLUDES
//===========

#include <stdio.h>
#include <unistd.h>
#include "ls.h"


//=========
// MACROS
//=========

#define STR(x) XSTR(x)	// this is needed so that...
#define XSTR(x) #x		// this works on macros like EXEC_NAME.

// The definitions bellow are an ugly hack to help debugging.
// I'm having some trouble installing gdb on my pc currently.
// If you're reading this, it means I forgot to erase this.
// Damn Arch Linux.
#ifdef DEBUG
	#define HEY printf("%s : line %d\n", __func__, __LINE__);
#else
	#define HEY ;
#endif

#define WHERE __FILE__, __func__, __LINE__

//==========
// STRUCTS
//==========

typedef struct _NODE {
	char* name;		// name of the file/directory
	int n_files;	// number of files here
	int n_dirs;		// number of subdirectories
	char** files;	// array of names of files
	char** dirs;	// array of names of subdirectories
} NODE, *node;

typedef struct {
	long unsigned int line;
	long unsigned int character;
} LOCATION, *location;

//=============
// PROTOTYPES
//=============

/*
 * Shows usage message.
 */
void help();

/*
 * Updates fields of NODE struct  with information
 * about directory/file it's name referes to.
 *
 * @param n	node to fill
 * @return	number of subdirectories
 */
int fillnode(node n);

/*
 * Looks for a string inside a file.
 *
 * @param string	string to look for inside file
 * @param filename	file where to look for string
 * @return			location of where string is, null if not found
 */
location find(char* string, char* filename);

/*
 * The following three functions are wrappers around malloc,
 * calloc and realloc that check if those functions returned
 * NULL and, if so, print an error message and abort the program.
 * Example: "scalloc(33, sizof(char), WHERE);
 *
 * @param file	name of the file where alloc was called
 * @param func	name of the function from where alloc as caled
 * @param line	line number where alloc was called
 */
void* smalloc(size_t size, char* file, const char* func, int line);
void* scalloc(size_t n, size_t size, char* file, const char* func, int line);
void* srealloc(void* ptr, size_t size, char* file, const char* func, int line);

#endif // UTILS_H
