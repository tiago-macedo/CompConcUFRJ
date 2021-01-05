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
	while ((opt = getopt(argc, argv, ":l")) != -1) {
		switch (opt) {
			case 'l':
				printf("level %d\n", atoi(optarg));
				break;
		}
	}
	for (; optind < argc; optind++) {
		printf("resto: %s\n", argv[optind]);
	}
	// Gerar lista de diretórios
	// e arquivos para analisar
	//============================
	
	// initializing global vriables
	files_list = malloc(MIN_SIZE_FILES * sizeof(NODE));
	cap_files_list = MIN_SIZE_FILES;
	
	// creating first node in the tree
	NODE root;
	
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
