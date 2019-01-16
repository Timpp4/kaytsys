/*****************************************************************************

my-zip.c

Tekijä: Tuomas Ikonen
Käytetyt lähteet: -Kasurinen, Jussi & Nikula, Uolevi, 2013, C-kieli ja käytännön ohjelmointi
*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KOKO 128

void zip(char* input);
void writeToFile(int* count, char* output);

int main(int argc, char *argv[]) {
	
	/* Ei tiedostoa */
	if (argc == 1) {
		printf("my-zip: file1 [file2 ...]\n");
		exit(1);
	}
	/* Useampi tiedosto */
	for (int i=1; i<argc; i++) {	
		char* tiedostoInput = argv[i];
		zip(tiedostoInput);
	}
	return 0;
}

void zip(char* input) {

	char puskuri[KOKO];
	int laskuri = 1;

	/* Tiedoston avaaminen ja virheentarkistus */
	FILE* tiedostoInput;
	if ((tiedostoInput = fopen(input, "r")) == NULL) {
		perror("my-zip");
		exit(1);
	}

	/* Tiedoston tulostaminen ja sulkeminen */
	while (fgets(puskuri, KOKO-1, tiedostoInput) != NULL) {
		for (int i=0; i<strlen(puskuri); i++) {
			if (puskuri[i] == puskuri[i+1]) {
				laskuri++;
			} else {
				if (laskuri == 1) {
					if (puskuri[i] == '\n') {
						continue;
					} else {
						writeToFile(&laskuri, &puskuri[i]);
					}
				} else {
					writeToFile(&laskuri, &puskuri[i]);
					laskuri = 1;
				}
			}
		}
	}
	fclose(tiedostoInput);
}

void writeToFile(int* count, char* output) {
	FILE* tiedostoOutput;
	if ((tiedostoOutput = fopen("file", "ab")) == NULL) {
		perror("my-zip");
		exit(1);
	}
	fwrite(count, sizeof(int), 1, tiedostoOutput);
	fwrite(output, sizeof(char), 1, tiedostoOutput);
	fclose(tiedostoOutput);

}
/*****************************************************************************/
/* eof */
