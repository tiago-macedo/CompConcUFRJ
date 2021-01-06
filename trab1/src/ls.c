//=============================
// Adapted from:
// codeproject.com/questions/1155676/simple-unix-ls-programming-in-c
//=============================

#include "ls.h"

char** lsfile(const char* dirname, int* lim) {
	DIR* dirptr;
	unsigned long int capacity = 4;
	struct dirent* direntry;
	char** list = malloc(capacity * sizeof(char*));
	
	if (! (dirptr = opendir(dirname)) ) {
		printf("opendir error\n"); //TODO: better error handling
		exit(2);
	}
	
	int i=0;
	for (; (direntry = readdir(dirptr)); i++) {
		if ( direntry->d_type != DT_REG ) {
			i--;
			continue;
		}
		list[i] = malloc(256 * sizeof(char));
		strcpy(list[i], direntry->d_name);
		if (i == capacity-1) {
			capacity *= 2;
			list = realloc(list, capacity*sizeof(struct dirent));
			//TODO: error handling!
		}
	}
	*lim = i;
	
	return list;
}

char** lsdir(const char* dirname, int* lim) {
	DIR* dirptr;
	unsigned long int capacity = 4;
	struct dirent* direntry;
	char** list = malloc(capacity * sizeof(char*));
	
	if (! (dirptr = opendir(dirname)) ) {
		printf("opendir error\n"); //TODO: better error handling
		exit(2);
	}
	
	int i=0;
	for (; (direntry = readdir(dirptr)); i++) {
		if (	!strcmp(direntry->d_name, ".") ||
				!strcmp(direntry->d_name, "..") ||
				direntry->d_type != DT_DIR) {
			i--;
			continue;
		}
		list[i] = malloc(256 * sizeof(char));
		strcpy(list[i], direntry->d_name);
		if (i == capacity-1) {
			capacity *= 2;
			list = realloc(list, capacity*sizeof(struct dirent));
			//TODO: error handling!
		}
	}
	*lim = i;
	
	return list;
}

/*
int main(void) {
	char** list = lsdir(".");
	for (int i=0; i<2; i++) {
		printf("%s\n", list[i]);
		free(list[i]);
	}
	free(list);
	
	return 0;
}
*/
