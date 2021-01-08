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


#endif // SEARCH_H
