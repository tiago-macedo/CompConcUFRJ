/*==========================*\
|| Gerador manual de testes ||
|| ------------------------ ||
|| Tiago Santos Martins de  ||
|| Macedo                   ||
|| DRE 116022689            ||
\*==========================*/

#include <stdio.h>
#include <stdlib.h>


// Vars. Globais
// ---------------


// Protótipos
// ------------

int main(int argc, char* argv[]) {
	if (argc < 3) {
		printf("Me dê mais argumentos.\n");
		return -1;
	}
	char* buf = malloc(62 * sizeof(char));
	int x;
	char* filename = argv[1];
	long long int N = strtoll(argv[2], NULL, 10);
	FILE* fp = fopen(filename, "w");
	fwrite(&N, sizeof(long long int), 1, fp);
	for (int i=0; i<N; i++) {
		scanf("%d", &x);
		fwrite(&x, sizeof(int), 1, fp);
	}
	fclose(fp);
	free(buf);
	return 0;
}
