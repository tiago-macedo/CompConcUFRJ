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

/*

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
	files_list = smalloc(MIN_SIZE_FILES * sizeof(NODE), WHERE);
	cap_files_list = MIN_SIZE_FILES;
	
 	// creating first node in the tree
	NODE root;
	root.name = rootname;
	fillnode(&root);
	
	for (int i=0;  i<root.n_dirs; i++) {
		free(root.dirs[i]);
	}
	for (int i=0;  i<root.n_files; i++) {
		free(root.files[i]);
	}
	free(root.dirs);
	free(root.files);
	
	// Percorrer lista, analisando
	//============================

*/
	FILE* file = fopen("Makefile", "r");
	location place = find("build", file);
	printf("line %lu column %lu\n", place->line, place->character);
	return 0;
}
