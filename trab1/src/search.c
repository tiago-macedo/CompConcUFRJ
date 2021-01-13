#include "search.h"

//=========
// MACROS
//=========

#define MIN_SIZE_FILES (4)
#define BUF_SIZE_FULLNAME (1024)


//==========
// GLOBALS
//==========

node root;
int nthreads;
int* tids;
pthread_t* threads;
char* string;

//=======
// MAIN
//=======

int main(int argc, char* argv[]) {
	// default settings
	char *rootname = ".";
	nthreads = 1;
	
	// getting the command line arguments
	int opt;
	while ((opt = getopt(argc, argv, "hd:t:l:")) != -1) {
		switch (opt) {
			case 'h':
				help();
				return 0;
			case 'd':
				rootname = optarg;
				break;
			case 't':
				nthreads = atoi(optarg);
				break;
			case 'l':
				printf("level %d\n", atoi(optarg));
				break;
		}
	}
	
	if (optind < argc) {
		string = argv[optind];
		optind++;
	} else {
		printf("No string to be searched was given.\n\n");
		help();
		return 4;
	}
	printf("Search in: %s\n", rootname);
	
	// Initialize stuff
	//=================
	
 	// creating first node in the tree
	root = smalloc(sizeof(NODE), WHERE);
	root->name = rootname;
	fillnode(root);
	threads = smalloc(nthreads * sizeof(pthread_t), WHERE);
	tids = smalloc(nthreads * sizeof(int), WHERE);
	
	// Start the search
	//=================
	
	// First we analyse the files in the search directory
	for (int i=0; i<nthreads; i++) {
		tids[i] = i;
		if( pthread_create( &(threads[i]), NULL, simpleSearchThread, &(tids[i]) ) ) {
			printf("Error creating thread.\n");
			exit(6);
		}
	}
	for (int i=0; i<nthreads; i++) {
		if( pthread_join( threads[i], NULL ) ) {
			printf("Error joining thread.\n");
			exit(7);
		}
	}

	// Then we start the recursive part
	for (int i=0; i<nthreads; i++) {
		tids[i] = i;
		if( pthread_create( &(threads[i]), NULL, recSearchThread, &(tids[i]) ) ) {
			printf("Error creating thread.\n");
			exit(6);
		}
	}
	for (int i=0; i<nthreads; i++) {
		if( pthread_join( threads[i], NULL ) ) {
			printf("Error joining thread.\n");
			exit(7);
		}
	}
	
	// Free everything
	//================
	
	freenode(root);
	
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
		free(l);
	}
	// The recursive part
	for (int i=0; i<n->n_dirs; i++) {
		strcpy(subfilename, n->name);
		strcat(subfilename, "/");
		strcat(subfilename, n->dirs[i]);
		node subdir = smalloc(sizeof(NODE), WHERE);
		subdir->name = subfilename;
		recSearch(string, subdir);
		freenode(subdir);
	}
}

void* simpleSearchThread(void* arg) {
	int id = * (int*) arg;

	location l;
	char subfile[BUF_SIZE_FULLNAME];
	for (int i = id; i < root->n_files; i += nthreads) {
		strcpy(subfile, root->name);
		strcat(subfile, "/");
		strcat(subfile, root->files[i]);
		l = find(string, subfile);
		if (l) printf(	"%s/%s:\n"
						"	line %lu column %lu\n",
						root->name,
						root->files[i],
						l->line, l->character);
		free(l);
	}
	
	pthread_exit(NULL);
}

void* recSearchThread(void* arg) {
	int id = * (int*) arg;
	node sub;
	
	for (int i=id; i < root->n_dirs; i += nthreads) {
		sub = smalloc(sizeof(NODE), WHERE);
		sub->name = root->dirs[i];
		recSearch(string, sub);
		freenode(sub);
	}
	pthread_exit(NULL);
}
