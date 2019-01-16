/*****************************************************************************

my-grep.c

Tekijä: Tuomas Ikonen
Käytetyt lähteet: -Kasurinen, Jussi & Nikula, Uolevi, 2013, C-kieli ja käytännön ohjelmointi
*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KOKO 128

void avaaJaEtsi(char* nimi, char* sana);

int main(int argc, char *argv[]) {
	char puskuriMain[KOKO];
	char* etsittavaSana = argv[1];
	
	/* Parametrien tarkistus */
	if (argc == 1) {
		printf("my-grep: searchterm [file ...]\n");
		exit(1);
	} else if (argc == 2) { /* Luetaan stdinistä ja etsitään sieltä */
		printf("Etsitään stdin... ctrl+c lopettaa\n");
		while (fgets(puskuriMain, KOKO-1, stdin)) {
			if(strstr(puskuriMain, etsittavaSana) != NULL) {
				printf("%s", puskuriMain);
			}
		}			
	}
		
	/* Tulostetaan tiedostot */
	for (int i=2; i<argc; i++) {
		printf("##### Tiedosto: %s #####\n", argv[i]);	
		char* tiedostoNimi = argv[i];
		avaaJaEtsi(tiedostoNimi, etsittavaSana);
	}
	return 0;
}
void avaaJaEtsi(char* nimi, char* sana) {

	char puskuri[KOKO];
	int eiMerkkeja = 0;

	/* Tiedoston avaaminen ja virheentarkistus */
	FILE* tiedosto;
	if ((tiedosto = fopen(nimi, "r")) == NULL) {
		printf("my-grep: cannot open file\n");
		exit(1);
	}

	/* Sanan etsiminen ja tulostaminen */
	while (fgets(puskuri, KOKO-1, tiedosto) != NULL) {
		if(strstr(puskuri, sana) != NULL) {
			printf("%s", puskuri);
			eiMerkkeja++;
		}
	}
	if (eiMerkkeja == 0) {
		printf("Ei osumaa hakusanalle '%s'\n", sana);
	}
	fclose(tiedosto);
}
/*****************************************************************************/
/* eof */
