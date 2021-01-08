#ifndef SEARCH_H
#define SEARCH_H

//===========
// INCLUDES
//===========

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "utils.h"
#include "ls.h"


//============
// PROTOTYPES
//============

/*
 * Recursively applies find() to
 * all files in a directory and
 * it's subdirectories.
 *
 * @param n			directory node where to start
 * @param string	string to search for
 */
void recSearch(char* string, node n);

/*
 * Applies find() to some files in
 * the root directory. To be executed
 * by threads.
 */
void* simpleSearchThread(void* arg);

/*
 * Applies recSearch() to some directories.
 * To be executed by threads.
 */
void* recSearchThread(void* arg);

#endif // SEARCH_H
