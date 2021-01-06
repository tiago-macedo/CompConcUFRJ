#include "utils.h"
#include "ls.h"

//============
// FUNCTIONS
//============

void help() {
	printf(	"NAME:\n"
			"	%s\n -- search file contents for match\n"
			"\n"
			"USAGE:\n"
			"	%s [ROOT] [-l LEVEL]\n"
			"\n"
			"OPTIONS:\n"
			"	ROOT:\n"
			"		directory from where to start search. If none is given, \".\" is assumed.\n"
			"	-l LEVEL:\n"
			"		Search all files up to LEVEL layers deep into the file hierarchy.\n",
			STR(EXEC_NAME),
			STR(EXEC_NAME)
			);
}

int fillnode(node n) {
	int n_files;
	int n_dirs;
	char** files = lsfile(n->name, &n_files);
	char** dirs = lsdir(n->name, &n_dirs);
	n->n_files = n_files;
	n->n_dirs = n_dirs;
	n->files = files;
	n->dirs = dirs;
	return n_dirs;
}

location find(char* string, FILE* file) {
	long unsigned int line_num = 1;
	char* line = NULL;
	char* match;
	size_t limit = 0;
	while (!feof(file)) {
		getline(&line, &limit, file);
		match = strstr(line, string);
		if (match) break;
		line_num++;
	}
	if (!match) return NULL;
	long unsigned int c = 0;
	for (; line+c != match; c++);
	location found = smalloc(sizeof(LOCATION), WHERE);
	found->line = line_num;
	found->character = (int) c;
	return found;
}

void* smalloc(size_t size, char* file, const char* func, int line) {
	void* ptr = malloc(size);
	if (!ptr) {
		printf(	"==> Error in call to malloc.\n"
				"File:	%s\n"
				"Func:	%s\n"
				"Line:	%d\n",
				file, func, line );
		exit(1);
	}
	return ptr;
}

void* scalloc(size_t n, size_t size, char* file, const char* func, int line) {
	void* ptr = calloc(n, size);
	if (!ptr) {
		printf(	"==> Error in call to calloc.\n"
				"File:	%s\n"
				"Func:	%s\n"
				"Line:	%d\n",
				file, func, line );
		exit(1);
	}
	return ptr;
}

void* srealloc(void* ptr, size_t size, char* file, const char* func, int line) {
	void* new_ptr = realloc(ptr, size);
	if (!new_ptr) {
		printf(	"==> Error in call to realloc.\n"
				"File:	%s\n"
				"Func:	%s\n"
				"Line:	%d\n",
				file, func, line );
		exit(1);
	}
	return ptr;
}
