#include "utils.h"

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
