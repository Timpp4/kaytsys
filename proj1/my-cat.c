/*

my-cat.c

Tekijä: Tuomas Ikonen, 0461309
Käytetyt lähteet: -Kasurinen, Jussi & Nikula, Uolevi, 2013, C-kieli ja käytännön ohjelmointi./my
*/

#include <stdio.h>
#include <stdlib.h>

#define KOKO 128

void avaaJaTulostaTiedosto(char* nimi);

int main(int argc, char *argv[]) {
	
	/* Jos ei ole syötetty tiedostoa luettavaksi */
	if (argc == 1) {
		printf("Syötä tiedoston nimi ja yritä uudelleen!\n");
		exit(0);
	}
	
	/* Tulostetaan tiedostot */
	for (int i=1; i<argc; i++) {
		printf("##### Tiedosto %d: #####\n", i);	
		char* tiedostoNimi = argv[i];
		avaaJaTulostaTiedosto(tiedostoNimi);
	}
	return 0;
}

void avaaJaTulostaTiedosto(char* nimi) {

	char puskuri[KOKO];

	/* Tiedoston avaaminen ja virheentarkistus */
	FILE* tiedosto;
	if ((tiedosto = fopen(nimi, "r")) == NULL) {
		perror("my-cat");
		exit(1);
	}

	/* Tiedoston tulostaminen ja sulkeminen */
	while (fgets(puskuri, KOKO-1, tiedosto) != NULL) {
		printf("%s", puskuri);
	}
	fclose(tiedosto);
}
