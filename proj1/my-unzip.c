/*

my-unzip.c

Tekijä: Tuomas Ikonen, 0461309
Käytetyt lähteet: -Kasurinen, Jussi & Nikula, Uolevi, 2013, C-kieli ja käytännön ohjelmointi
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KOKO 128

int main(int argc, char *argv[]) {
	
	/* Ei tiedostoa */
	if (argc == 1) {
		printf("my-unzip: file1 [file2 ...]\n");
		exit(1);
	}
	int puskuriInt;
	int puskuriChar;
	int position;

	for (int i=1; i<argc; i++) {
		printf("##### Tiedosto: %s #####\n", argv[i]);
		FILE* tiedostoInput;
		if ((tiedostoInput = fopen(argv[i], "rb")) == NULL) {
			perror("my-zip");
			exit(1);
		}
		fseek(tiedostoInput, 0L, SEEK_END);
		position = ftell(tiedostoInput);
		rewind(tiedostoInput);
		position = position / 5; /* int + char = 5 bytes, antaa iteraatioiden määrän */

		for (int j=0; j<position; j++)  {
			fread(&puskuriInt, sizeof(int), 1, tiedostoInput);
			fread(&puskuriChar, sizeof(char), 1, tiedostoInput);
			for (int k=0; k<puskuriInt; k++) {
				printf("%c", puskuriChar);
			}
			printf("\n");
		}
		fclose(tiedostoInput);
	}

	return 0;
}
