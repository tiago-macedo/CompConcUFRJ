//=============================
// Adapted from:
// codeproject.com/questions/1155676/simple-unix-ls-programming-in-c
//=============================

//===========
// INCLUDES
//===========

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//=============
// PROTOTYPES
//=============

/*
 * Creates and returns a list of dirents (dirent.h),
 * consisting of all subdirectories under the
 * given directory.
 *
 * @param dirname	name of directory to look into
 * @param lim		pointer to integer that recieves number of files
 * @return			array of directory entries (char*). Must be freed later!
 */
char** lsfile(const char* dirname, int* lim);


/*
 * Creates and returns a list of dirents (dirent.h),
 * consisting of all and only directories under the
 * given directory.
 *
 * @param dirname	name of directory to look into
 * @param lim		pointer to integer that recieves number of files
 * @return			array of directory entries (char*). Must be freed later!
 */
char** lsdir(const char* dirname, int* lim);

