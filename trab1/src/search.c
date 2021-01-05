#include "search.h"
#include "utils.h"
#include "ls.h"

//=========
// MACROS
//=========

#define MIN_SIZE_FILES (4)


//==========
// GLOBALS
//==========

node files_list;
int cap_files_list;

//=======
// MAIN
//=======

int main(int argc, char* argv[]) {
	// getting the command line arguments
	int opt;
	while ((opt = getopt(argc, argv, "h?l:")) != -1) {
		switch (opt) {
			case 'l':
				printf("level %d\n", atoi(optarg));
				break;
			case 'h':
			case '?':
				help();
				return 0;
		}
	}
	// root directory
	char* rootname;
	if (optind < argc) {
		rootname = argv[optind];
		optind++;
	} else {
		rootname = ".";
	}
	printf("root name: %s\n", rootname);
	
	// Gerar lista de diretórios
	// e arquivos para analisar
	//============================
	
	// initializing global variables
	files_list = malloc(MIN_SIZE_FILES * sizeof(NODE));
	cap_files_list = MIN_SIZE_FILES;
	
 	// creating first node in the tree
	NODE root;
	root.name = rootname;
	
	/*
	int n;
	char** dirs = ls(".", &n);
	printf("number of directories: %d\n", n);
	for (int i=0; i<n; i++) {
		printf("%s\n", dirs[i]);
		free(dirs[i]);
	}
	free(dirs);
	*/
	
	// Percorrer lista, analisando
	//============================
	
	return 0;
}
