#ifndef UTILS_H
#define UTILS_H

//===========
// INCLUDES
//===========

#include <stdio.h>
#include <unistd.h>


//=========
// MACROS
//=========

#define STR(x) XSTR(x)	// this is needed so that...
#define XSTR(x) #x		// this works on macros like EXEC_NAME.


//==========
// STRUCTS
//==========

typedef struct _NODE {
	char* name;		// name of the file/directory
	int num_files;	// number of files here
	int num_dirs;	// number of subdirectories
	struct _NODE** files;	// array of pointers to files
	struct _NODE** dirs;	// array of pointers to subdirectories
} NODE, *node;


//=============
// PROTOTYPES
//=============

/*
 * Shows usage message.
 */
void help();


#endif // UTILS_H
