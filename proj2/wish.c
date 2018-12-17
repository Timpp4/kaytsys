/*****************************************************************************

wish.c

Tekijä: Tuomas Ikonen, 0461309
Käytetyt lähteet: -Kasurinen, Jussi & Nikula, Uolevi, 2013, C-kieli ja käytännön ohjelmointi
		  -https://github.com/brenns10/lsh/tree/407938170e8b40d231781576e05282a41634848c
		  -http://pages.cs.wisc.edu/~remzi/OSTEP/cpu-api.pdf
*****************************************************************************/
#define _GNU_SOURCE /* implicit declaration of function ‘getline’*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int wish_exit(char **parametrit);
int wish_cd(char **parametrit);

void tulosta_Virhe(void) {
	char error_message[30] = "An error has occurred.\n"; 
	write(STDERR_FILENO, error_message, strlen(error_message));
}

#define FMAARA 2
char *wish_SisalletytStr[] = {
	"exit",
	"cd"
};

int (*wish_SisalletytFunc[])(char **) = {
	&wish_exit,
	&wish_cd
};

/* cd */
int wish_cd(char **parametrit) {

	if (parametrit[1] == NULL) {
		tulosta_Virhe();
	} else if (parametrit[2] != NULL) {
		tulosta_Virhe();
	} else {
		chdir(parametrit[1]);
	}
	return 1;
}
/* exit */
int wish_exit(char **parametrit) {
	return 0;
}

int wish_Suorita(char **parametrit) {

	int pid = fork();
	if (pid < 0) {
		fprintf(stderr, "Jokin meni vikaan...\n");
		exit(1);
	} else if (pid == 0) {
		char *polku = "/bin/";
		char *ohjelma = (char*)malloc(strlen(polku)+strlen(parametrit[0])+1);
		strcpy(ohjelma, polku);
		strcat(ohjelma, parametrit[0]);
		execv(ohjelma, parametrit);
		tulosta_Virhe(); /* Jos execv kohtaa ongelman -> virheenkäsittely */
		free(ohjelma);
		return 0; /* kill the child, jos execv failaa */
	} else {
		wait(NULL);
	}
	return 1; /* Palauttaa 1, suoritus jatkuu */
}

int wish_Tarkista(char **parametrit) {

	if (parametrit[0] == NULL) {
		return 1; /* Ei parametreja, suoritus jatkuu */
	}
	/* Jos parametri == Built-In command -> suorita ko. command */
	for (int i=0; i<FMAARA; i++) { 
		if (strcmp(parametrit[0], wish_SisalletytStr[i]) == 0) {
			return (*wish_SisalletytFunc[i])(parametrit);
		}
	}
	return wish_Suorita(parametrit);
}

char **wish_Leikkaa(char *rivi) {

	int koko = 64;
	int i = 0;
	char *parametri;
	char **parametrit = malloc(koko*sizeof(char*));
	if (parametrit == NULL) {
		perror("malloc");
		exit(1);
	}
	parametri = strtok(rivi, " \t\n");
	while (parametri != NULL) {
		parametrit[i] = parametri;
		i++;
		parametri = strtok(NULL, " \t\n");		
	}
	parametrit[i] = NULL;
	return parametrit;
}

char *wish_LueRivi(void) {

	char* buffer;
	size_t koko = 32;
	size_t merkit;

	buffer = (char*)malloc(koko*sizeof(char));
	if (buffer == NULL) {
		perror("malloc");
		exit(1);
	}
	merkit = getline(&buffer, &koko, stdin);
	if (buffer[merkit-1] == '\n') {
		buffer[merkit-1] = '\0';
	}		
	return buffer;
}

void wish_Loop(void) {

	char *rivi;
	char **parametrit;
	int tila;

	do {
		printf("wish> ");
		rivi = wish_LueRivi();
		parametrit = wish_Leikkaa(rivi);
		tila = wish_Tarkista(parametrit);	
		/* Muistin vapautus */
		free(rivi); 
		free(parametrit);
	} while (tila);
}

int main(int argc, char *argv[]) {

	int pid = fork();
	if (pid < 0) {
		tulosta_Virhe();
		exit(1);
	} else if (pid == 0) {
		wish_Loop();
	} else {
		wait(NULL);
	}
	return 0;
}
/*****************************************************************************/
/* eof */
