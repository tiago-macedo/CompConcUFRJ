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
	char** dirs = lsdir(n->name, &n_dirs); //TODO: create this function
	n->num_files = n_files;
	n->num_dirs = n_dirs;
	n->file_names = files;
	n->dir_names = dirs;
	return n_dirs;
}
