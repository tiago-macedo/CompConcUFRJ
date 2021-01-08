#include "search.h"

//=========
// MACROS
//=========

#define MIN_SIZE_FILES (4)
#define BUF_SIZE_FULLNAME (1024)


//==========
// GLOBALS
//==========

node files_list;
int cap_files_list;


//=======
// MAIN
//=======

int main(int argc, char* argv[]) {
	// root directory
	char* rootname = ".";
	
	// getting the command line arguments
	int opt;
	while ((opt = getopt(argc, argv, "hd:l:")) != -1) {
		switch (opt) {
			case 'h':
				help();
				return 0;
			case 'd':
				rootname = optarg;
				break;
			case 'l':
				printf("level %d\n", atoi(optarg));
				break;
		}
	}
	
	// String to be searched
	char* string;
	if (optind < argc) {
		string = argv[optind];
		optind++;
	} else {
		printf("No string to be searched was given.\n\n");
		help();
		return 4;
	}
	printf("root name: %s\n", rootname);
	
	// Generate directory and
	// files list for analysis
	//============================
	
	// initializing global variables
	files_list = smalloc(MIN_SIZE_FILES * sizeof(NODE), WHERE);
	cap_files_list = MIN_SIZE_FILES;
	
 	// creating first node in the tree
	NODE root;
	root.name = rootname;
	fillnode(&root);
	
	// Run through list, analysing
	//============================
	
	recSearch(string, &root);
	
	// Free everything
	//================
	
	for (int i=0;  i<root.n_dirs; i++) {
		free(root.dirs[i]);
	}
	for (int i=0;  i<root.n_files; i++) {
		free(root.files[i]);
	}
	free(root.dirs);
	free(root.files);
	
	return 0;
}

void recSearch(char* string, node n) {
	fillnode(n);
	// Apply find() on every subfile
	char subfilename[BUF_SIZE_FULLNAME];
	location l;
	for (int i=0; i<n->n_files; i++) {
		strcpy(subfilename, n->name);
		strcat(subfilename, "/");
		strcat(subfilename, n->files[i]);
		l = find(string, subfilename);
		if (l) { // Found it!
			printf("%s:\n	line %lu column %lu\n", subfilename, l->line, l->character);
		}
	}
	// The recursive part
	for (int i=0; i<n->n_dirs; i++) {
		strcpy(subfilename, n->name);
		strcat(subfilename, "/");
		strcat(subfilename, n->dirs[i]);
		node subdir = smalloc(sizeof(NODE), WHERE);
		subdir->name = subfilename;
		recSearch(string, subdir);
		free(subdir);
	}
}
