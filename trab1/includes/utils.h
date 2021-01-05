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
// The definitions bellow are an ugly hack to help debugging.
// I'm having some trouble installing gdb on my pc currently.
// If you're reading this, it means I forgot to erase this.
// Damn Arch Linux.
#ifdef DEBUG
	#define HEY printf("%s : line %d\n", __func__, __LINE__);
#else
	#define HEY ;
#endif

//==========
// STRUCTS
//==========

typedef struct _NODE {
	char* name;		// name of the file/directory
	int num_files;	// number of files here
	int num_dirs;	// number of subdirectories
	char** file_names;	// array of names of files
	char ** dir_names;	// array of names of subdirectories
	struct _NODE** files;	// array of pointers to file nodes
	struct _NODE** dirs;	// array of pointers to subdir nodes
} NODE, *node;


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

#endif // UTILS_H
